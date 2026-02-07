/* Copyright (c) 2013-2016 Jeffrey Pfau
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "gui-runner.h"

#include <mgba/core/core.h>
#include <mgba/core/serialize.h>
#include "feature/gui/gui-config.h"
#include "feature/gui/cheats.h"
#include "feature/gui/gui-beiklive.h"
#include <mgba/internal/gba/gba.h>
#include <mgba/internal/gba/input.h>
#include <mgba/gba/interface.h>
#include <mgba-util/gui/file-select.h>
#include <mgba-util/gui/font.h>
#include <mgba-util/gui/menu.h>
#include <mgba-util/memory.h>
#include <mgba-util/png-io.h>
#include <mgba-util/vfs.h>

#include <sys/time.h>

#include <beiklive/beiklive.h>


mLOG_DECLARE_CATEGORY(GUI_RUNNER);
mLOG_DEFINE_CATEGORY(GUI_RUNNER, "GUI Runner", "gui.runner");

#define AUTOSAVE_GRANULARITY 600
#define FPS_GRANULARITY 30
#define FPS_BUFFER_SIZE 4

enum {
	RUNNER_CONTINUE = 1,
	RUNNER_EXIT,
	RUNNER_SAVE_STATE,
	RUNNER_LOAD_STATE,
	RUNNER_SCREENSHOT,
	RUNNER_CONFIG,
	RUNNER_BEIKLIVE,
	RUNNER_RESET,
	RUNNER_CHEATS,
	RUNNER_COMMAND_MASK = 0xFFFF
};

#define RUNNER_STATE(X) ((X) << 16)

enum {
	SCREENSHOT_VALID = 0x10000,
	SCREENSHOT_INVALID = 0x20000,
};

static const struct mInputPlatformInfo _mGUIKeyInfo = {
	.platformName = "gui",
	.keyId = (const char*[GUI_INPUT_MAX]) {
		"Select",
		"Back",
		"Cancel",
		"Up",
		"Down",
		"Left",
		"Right",
		[mGUI_INPUT_INCREASE_BRIGHTNESS] = "增强太阳光亮度",
		[mGUI_INPUT_DECREASE_BRIGHTNESS] = "减弱太阳光亮度",
		[mGUI_INPUT_SCREEN_MODE] = "切换屏幕模式",
		[mGUI_INPUT_SCREENSHOT] = "截图",
		[mGUI_INPUT_REWIND_HELD] = "倒带 (按住)",
		[mGUI_INPUT_FAST_FORWARD_HELD] = "加速 (按住)",
		[mGUI_INPUT_FAST_FORWARD_TOGGLE] = "加速 (切换)",
		[mGUI_INPUT_MUTE_TOGGLE] = "静音 (切换)",
	},
	.nKeys = GUI_INPUT_MAX
};

static void _log(struct mLogger*, int category, enum mLogLevel level, const char* format, va_list args);

static struct mGUILogger {
	struct mLogger d;
	struct VFile* vf;
	int logLevel;
} logger = {
	.d = {
		.log = _log
	},
	.vf = NULL,
	.logLevel = 0
};

static bool _testExtensions(const char* name) {
	char ext[PATH_MAX] = {};
	separatePath(name, NULL, NULL, ext);
	if (!strncmp(ext, "GBA", PATH_MAX)) {
		return true;
	}
	if (!strncmp(ext, "GBC", PATH_MAX)) {
		return true;
	}
	if (!strncmp(ext, "GB", PATH_MAX)) {
		return true;
	}
	if (!strncmp(ext, "ZIP", PATH_MAX)) {
		return true;
	}
	if (!strncmp(ext, "gba", PATH_MAX)) {
		return true;
	}
	if (!strncmp(ext, "gbc", PATH_MAX)) {
		return true;
	}
	if (!strncmp(ext, "gb", PATH_MAX)) {
		return true;
	}
	if (!strncmp(ext, "zip", PATH_MAX)) {
		return true;
	}
	return false;
}
// BKMARK 全局运行器的背景绘制函数(有游戏画面的时候绘制游戏帧)
static void _drawBackground(struct GUIBackground* background, void* context) {
	UNUSED(context);
	struct mGUIBackground* gbaBackground = (struct mGUIBackground*) background;

	int useCustomeTheme = false;
	if(!bk_global_runner)
		return;
	mCoreConfigGetIntValue(&bk_global_runner->config, BK_META_CONFIG_THEME, &useCustomeTheme);
	if (useCustomeTheme == BK_THEME_SWITCH) {
		if (gbaBackground->p->drawBKImage) {
			gbaBackground->p->drawBKImage(gbaBackground->p, NULL);
		}
	}else{
		if (gbaBackground->p->drawFrame) {
			gbaBackground->p->drawFrame(gbaBackground->p, true);
		}
	}



}

// BKMARK 保存和读取状态的背景绘制函数(画存档截图)
static void _drawState(struct GUIBackground* background, void* id) {

	// 将通用 GUIBackground 转换为 mGBA 专用的背景结构
	struct mGUIBackground* gbaBackground = (struct mGUIBackground*) background;

	// 从 id 的高 16 位中取出状态槽编号（stateId）
	unsigned stateId = ((uint32_t) id) >> 16;

	// 仅当平台提供 drawScreenshot 回调时才执行截图绘制逻辑
	if (gbaBackground->p->drawScreenshot) {

		// 用于保存目标视频宽高
		unsigned w, h;

		// 从核心获取期望的视频输出尺寸
		gbaBackground->p->core->desiredVideoDimensions(
			gbaBackground->p->core, &w, &h
		);

		// 计算所需像素缓冲区大小（宽 × 高 × 每像素字节数）
		size_t size = w * h * BYTES_PER_PIXEL;

		// 如果当前缓存大小与期望大小不一致
		if (size != gbaBackground->imageSize) {

			// 释放旧的像素缓存
			mappedMemoryFree(gbaBackground->image, gbaBackground->imageSize);

			// 清空指针，等待重新分配
			gbaBackground->image = NULL;
		}

		// 如果已有缓存，并且截图状态是“有效”的当前 stateId
		if (gbaBackground->image &&
			gbaBackground->screenshotId == (stateId | SCREENSHOT_VALID)) {

			// 直接绘制缓存中的截图数据
			gbaBackground->p->drawScreenshot(
				gbaBackground->p, gbaBackground->image, w, h, true
			);

			// 已成功绘制，直接返回
			return;

		// 否则，如果当前状态不是已标记为“无效截图”
		} else if (gbaBackground->screenshotId != (stateId | SCREENSHOT_INVALID)) {

			// 从核心中获取该 stateId 对应的存档文件（VFile 抽象）
			struct VFile* vf = mCoreGetState(
				gbaBackground->p->core, stateId, false
			);

			// 像素缓冲区指针
			color_t* pixels = gbaBackground->image;

			// 若当前尚未分配像素缓冲区
			if (!pixels) {

				// 使用匿名内存映射分配像素缓存
				pixels = anonymousMemoryMap(size);

				// 保存到背景结构中
				gbaBackground->image = pixels;
				gbaBackground->imageSize = size;
			}

			// 用于标记 PNG 读取是否成功
			bool success = false;

			// 如果存档文件存在、是 PNG 格式、并且像素缓冲区可用
			if (vf && isPNG(vf) && pixels) {

				// 打开 PNG 读取结构
				png_structp png = PNGReadOpen(vf, PNG_HEADER_BYTES);

				// 创建 PNG 信息结构
				png_infop info = png_create_info_struct(png);
				png_infop end  = png_create_info_struct(png);

				// 确保 PNG 相关结构创建成功
				if (png && info && end) {

					// 读取 PNG 头
					success = PNGReadHeader(png, info);

					// 读取 PNG 像素数据到 pixels 缓冲区
					success = success &&
						PNGReadPixels(png, info, pixels, w, h, w);

					// 读取 PNG 尾信息
					success = success &&
						PNGReadFooter(png, end);
				}

				// 关闭 PNG 读取并释放相关结构
				PNGReadClose(png, info, end);
			}

			// 如果 VFile 存在，关闭文件
			if (vf) {
				vf->close(vf);
			}

			// 如果 PNG 读取成功
			if (success) {

				// 绘制刚刚解码得到的截图
				gbaBackground->p->drawScreenshot(
					gbaBackground->p, pixels, w, h, true
				);

				// 标记该 stateId 的截图为有效
				gbaBackground->screenshotId = stateId | SCREENSHOT_VALID;

			} else {

				// 标记该 stateId 的截图为无效（无法读取）
				gbaBackground->screenshotId = stateId | SCREENSHOT_INVALID;
			}
		}

		// 如果存在 drawFrame 回调，并且该状态截图被标记为无效
		if (gbaBackground->p->drawFrame &&
			gbaBackground->screenshotId == (stateId | SCREENSHOT_INVALID)) {

			// 回退为绘制当前实时帧作为背景
			gbaBackground->p->drawFrame(gbaBackground->p, true);
		}
	}
}


static void _updateLux(struct GBALuminanceSource* lux) {
	UNUSED(lux);
}

static uint8_t _readLux(struct GBALuminanceSource* lux) {
	struct mGUIRunnerLux* runnerLux = (struct mGUIRunnerLux*) lux;
	int value = 0x16;
	if (runnerLux->luxLevel > 0) {
		value += GBA_LUX_LEVELS[runnerLux->luxLevel - 1];
	}
	return 0xFF - value;
}

static void _tryAutosave(struct mGUIRunner* runner) {
	int autosave = false;
	mCoreConfigGetIntValue(&runner->config, "autosave", &autosave);
	if (!autosave) {
		return;
	}

#ifdef DISABLE_THREADING
	mCoreSaveState(runner->core, 0, SAVESTATE_SAVEDATA | SAVESTATE_RTC | SAVESTATE_METADATA);
#else
	MutexLock(&runner->autosave.mutex);
	if (!runner->autosave.buffer) {
		runner->autosave.buffer = VFileMemChunk(NULL, 0);
	}
	runner->autosave.core = runner->core;
	mCoreSaveStateNamed(runner->core, runner->autosave.buffer, SAVESTATE_SAVEDATA | SAVESTATE_RTC | SAVESTATE_METADATA);
	ConditionWake(&runner->autosave.cond);
	MutexUnlock(&runner->autosave.mutex);
#endif
}

void mGUIInit(struct mGUIRunner* runner, const char* port) {
	bk_global_runner = runner;
	GUIInit(&runner->params);
	runner->port = port;
	runner->core = NULL;
	runner->luminanceSource.d.readLuminance = _readLux;
	runner->luminanceSource.d.sample = _updateLux;
	runner->luminanceSource.luxLevel = 0;
	runner->background.d.draw = _drawBackground;
	runner->background.p = runner;
	runner->fps = 0;
	runner->lastFpsCheck = 0;
	runner->totalDelta = 0;
	CircleBufferInit(&runner->fpsBuffer, FPS_BUFFER_SIZE * sizeof(uint32_t));

	mInputMapInit(&runner->params.keyMap, &_mGUIKeyInfo);
	mCoreConfigInit(&runner->config, runner->port);
	// TODO: Do we need to load more defaults?
	// BKMARK 设置项默认值
	mCoreConfigSetDefaultIntValue(&runner->config, BK_META_TEXT_COLOR_TYPE, BK_CONFIG_COLOR_BLACK);
	mCoreConfigSetDefaultIntValue(&runner->config, BK_META_HOVER_TEXT_COLOR_TYPE, BK_CONFIG_COLOR_BLUE);
	mCoreConfigSetDefaultIntValue(&runner->config, BK_META_ISFOLDER, true);
	mCoreConfigSetDefaultIntValue(&runner->config, BK_META_MASK_ENABLE, false);
	mCoreConfigSetDefaultIntValue(&runner->config, BK_META_SHADER_ENABLE, false);
	mCoreConfigSetDefaultIntValue(&runner->config, BK_META_PATH_BACKGROUND_ENABLE, false);
	mCoreConfigSetDefaultIntValue(&runner->config, BK_META_CONFIG_THEME, BK_THEME_DEFAULT);


	mCoreConfigSetDefaultIntValue(&runner->config, "volume", 0x100);
	mCoreConfigSetDefaultValue(&runner->config, "idleOptimization", "detect");
	mCoreConfigSetDefaultIntValue(&runner->config, "autoload", true);
#ifdef DISABLE_THREADING
	mCoreConfigSetDefaultIntValue(&runner->config, "autosave", false);
#else
	mCoreConfigSetDefaultIntValue(&runner->config, "autosave", true);
#endif
	mCoreConfigSetDefaultIntValue(&runner->config, "showOSD", true);
	mCoreConfigLoad(&runner->config);
	mCoreConfigGetIntValue(&runner->config, "logLevel", &logger.logLevel);

	char path[PATH_MAX];
	mCoreConfigDirectory(path, PATH_MAX);
	strncat(path, PATH_SEP "log", PATH_MAX - strlen(path));
	logger.vf = VFileOpen(path, O_CREAT | O_WRONLY | O_APPEND);
	mLogSetDefaultLogger(&logger.d);

	const char* lastPath = mCoreConfigGetValue(&runner->config, "lastDirectory");
	if (lastPath) {
		struct VDir* dir = VDirOpen(lastPath);
		if (dir) {
			dir->close(dir);
			strncpy(runner->params.currentPath, lastPath, PATH_MAX - 1);
			runner->params.currentPath[PATH_MAX - 1] = '\0';
		}
	}

#ifndef DISABLE_THREADING
	if (!runner->autosave.running) {
		runner->autosave.running = true;
		runner->autosave.core = NULL;
		MutexInit(&runner->autosave.mutex);
		ConditionInit(&runner->autosave.cond);
		ThreadCreate(&runner->autosave.thread, mGUIAutosaveThread, &runner->autosave);
	}
#endif
}

void mGUIDeinit(struct mGUIRunner* runner) {
#ifndef DISABLE_THREADING
	MutexLock(&runner->autosave.mutex);
	runner->autosave.running = false;
	ConditionWake(&runner->autosave.cond);
	MutexUnlock(&runner->autosave.mutex);

	ThreadJoin(&runner->autosave.thread);

	ConditionDeinit(&runner->autosave.cond);
	MutexDeinit(&runner->autosave.mutex);

	if (runner->autosave.buffer) {
		runner->autosave.buffer->close(runner->autosave.buffer);
	}
#endif

	if (runner->teardown) {
		runner->teardown(runner);
	}
	CircleBufferDeinit(&runner->fpsBuffer);
	mInputMapDeinit(&runner->params.keyMap);
	mCoreConfigDeinit(&runner->config);
	if (logger.vf) {
		logger.vf->close(logger.vf);
		logger.vf = NULL;
	}
}

static void _log(struct mLogger* logger, int category, enum mLogLevel level, const char* format, va_list args) {
	struct mGUILogger* guiLogger = (struct mGUILogger*) logger;
	if (!guiLogger->vf) {
		return;
	}
	if (!(guiLogger->logLevel & level)) {
		return;
	}

	char log[256] = {0};
	vsnprintf(log, sizeof(log) - 1, format, args);
	char log2[256] = {0};
	size_t len = snprintf(log2, sizeof(log2) - 1, "%s: %s\n", mLogCategoryName(category), log);
	if (len >= sizeof(log2)) {
		len = sizeof(log2) - 1;
	}
	if (guiLogger->vf->write(guiLogger->vf, log2, len) < 0) {
		char path[PATH_MAX];
		mCoreConfigDirectory(path, PATH_MAX);
		strncat(path, PATH_SEP "log", PATH_MAX - strlen(path));
		guiLogger->vf->close(guiLogger->vf);
		guiLogger->vf = VFileOpen(path, O_CREAT | O_WRONLY | O_APPEND);
		if (guiLogger->vf->write(guiLogger->vf, log2, len) < 0) {
			guiLogger->vf->close(guiLogger->vf);
			guiLogger->vf = NULL;
		}
	}
#ifdef GEKKO
	puts(log2);
#endif
}

static void _updateLoading(size_t read, size_t size, void* context) {
	struct mGUIRunner* runner = context;
	runner->params.drawStart();
	if (runner->params.guiPrepare) {
		runner->params.guiPrepare();
	}
	int themeType = BK_THEME_DEFAULT;
	BK_GLOBAL_INT_GET(BK_META_CONFIG_THEME, themeType);
	GUIFontPrintf(runner->params.font, runner->params.width / 2, (GUIFontHeight(runner->params.font) + runner->params.height) / 2, GUI_ALIGN_HCENTER, themeType == BK_THEME_DEFAULT? BK_COLOR_WHITE : BK_COLOR_TEXT, "加载中...%i%%", 100 * read / size);
	if (runner->params.guiFinish) {
		runner->params.guiFinish();
	}
	runner->params.drawEnd();
}
// BK_MARK mGUIRun  游戏运行循环
void mGUIRun(struct mGUIRunner* runner, const char* path) {
	struct mGUIBackground drawState = {
		.d = {
			.draw = _drawState
		},
		.p = runner,
		.image = 0,
		.screenshotId = 0
	};
	struct GUIMenu pauseMenu = {
		.title = "游戏已暂停",
		.index = 0,
		.background = &runner->background.d
	};
	struct GUIMenu stateSaveMenu = {
		.title = "保存状态",
		.index = 0,
		.background = &drawState.d
	};
	struct GUIMenu stateLoadMenu = {
		.title = "读取状态",
		.index = 0,
		.background = &drawState.d
	};
	int themeType = BK_THEME_DEFAULT;
	BK_GLOBAL_INT_GET(BK_META_CONFIG_THEME, themeType);
	GUIMenuItemListInit(&pauseMenu.items, 0);
	GUIMenuItemListInit(&stateSaveMenu.items, 9);
	GUIMenuItemListInit(&stateLoadMenu.items, 10);
	*GUIMenuItemListAppend(&pauseMenu.items) = (struct GUIMenuItem) { .title = "返回游戏", .data = GUI_V_U(RUNNER_CONTINUE) };
	*GUIMenuItemListAppend(&pauseMenu.items) = (struct GUIMenuItem) { .title = "快速存档", .submenu = &stateSaveMenu };
	*GUIMenuItemListAppend(&pauseMenu.items) = (struct GUIMenuItem) { .title = "快速读档", .submenu = &stateLoadMenu };

	*GUIMenuItemListAppend(&stateSaveMenu.items) = (struct GUIMenuItem) { .title = "状态 1", .data = GUI_V_U(RUNNER_SAVE_STATE | RUNNER_STATE(1)) };
	*GUIMenuItemListAppend(&stateSaveMenu.items) = (struct GUIMenuItem) { .title = "状态 2", .data = GUI_V_U(RUNNER_SAVE_STATE | RUNNER_STATE(2)) };
	*GUIMenuItemListAppend(&stateSaveMenu.items) = (struct GUIMenuItem) { .title = "状态 3", .data = GUI_V_U(RUNNER_SAVE_STATE | RUNNER_STATE(3)) };
	*GUIMenuItemListAppend(&stateSaveMenu.items) = (struct GUIMenuItem) { .title = "状态 4", .data = GUI_V_U(RUNNER_SAVE_STATE | RUNNER_STATE(4)) };
	*GUIMenuItemListAppend(&stateSaveMenu.items) = (struct GUIMenuItem) { .title = "状态 5", .data = GUI_V_U(RUNNER_SAVE_STATE | RUNNER_STATE(5)) };
	*GUIMenuItemListAppend(&stateSaveMenu.items) = (struct GUIMenuItem) { .title = "状态 6", .data = GUI_V_U(RUNNER_SAVE_STATE | RUNNER_STATE(6)) };
	*GUIMenuItemListAppend(&stateSaveMenu.items) = (struct GUIMenuItem) { .title = "状态 7", .data = GUI_V_U(RUNNER_SAVE_STATE | RUNNER_STATE(7)) };
	*GUIMenuItemListAppend(&stateSaveMenu.items) = (struct GUIMenuItem) { .title = "状态 8", .data = GUI_V_U(RUNNER_SAVE_STATE | RUNNER_STATE(8)) };
	*GUIMenuItemListAppend(&stateSaveMenu.items) = (struct GUIMenuItem) { .title = "状态 9", .data = GUI_V_U(RUNNER_SAVE_STATE | RUNNER_STATE(9)) };

	*GUIMenuItemListAppend(&stateLoadMenu.items) = (struct GUIMenuItem) { .title = "自动存档", .data = GUI_V_U(RUNNER_LOAD_STATE | RUNNER_STATE(0)) };
	*GUIMenuItemListAppend(&stateLoadMenu.items) = (struct GUIMenuItem) { .title = "状态 1", .data = GUI_V_U(RUNNER_LOAD_STATE | RUNNER_STATE(1)) };
	*GUIMenuItemListAppend(&stateLoadMenu.items) = (struct GUIMenuItem) { .title = "状态 2", .data = GUI_V_U(RUNNER_LOAD_STATE | RUNNER_STATE(2)) };
	*GUIMenuItemListAppend(&stateLoadMenu.items) = (struct GUIMenuItem) { .title = "状态 3", .data = GUI_V_U(RUNNER_LOAD_STATE | RUNNER_STATE(3)) };
	*GUIMenuItemListAppend(&stateLoadMenu.items) = (struct GUIMenuItem) { .title = "状态 4", .data = GUI_V_U(RUNNER_LOAD_STATE | RUNNER_STATE(4)) };
	*GUIMenuItemListAppend(&stateLoadMenu.items) = (struct GUIMenuItem) { .title = "状态 5", .data = GUI_V_U(RUNNER_LOAD_STATE | RUNNER_STATE(5)) };
	*GUIMenuItemListAppend(&stateLoadMenu.items) = (struct GUIMenuItem) { .title = "状态 6", .data = GUI_V_U(RUNNER_LOAD_STATE | RUNNER_STATE(6)) };
	*GUIMenuItemListAppend(&stateLoadMenu.items) = (struct GUIMenuItem) { .title = "状态 7", .data = GUI_V_U(RUNNER_LOAD_STATE | RUNNER_STATE(7)) };
	*GUIMenuItemListAppend(&stateLoadMenu.items) = (struct GUIMenuItem) { .title = "状态 8", .data = GUI_V_U(RUNNER_LOAD_STATE | RUNNER_STATE(8)) };
	*GUIMenuItemListAppend(&stateLoadMenu.items) = (struct GUIMenuItem) { .title = "状态 9", .data = GUI_V_U(RUNNER_LOAD_STATE | RUNNER_STATE(9)) };

	*GUIMenuItemListAppend(&pauseMenu.items) = (struct GUIMenuItem) { .title = "截图", .data = GUI_V_U(RUNNER_SCREENSHOT) };
	if (runner->params.getText) {
		*GUIMenuItemListAppend(&pauseMenu.items) = (struct GUIMenuItem) { .title = "金手指", .data = GUI_V_U(RUNNER_CHEATS) };
	}
	*GUIMenuItemListAppend(&pauseMenu.items) = (struct GUIMenuItem) { .title = "设置", .data = GUI_V_U(RUNNER_CONFIG) };
	*GUIMenuItemListAppend(&pauseMenu.items) = (struct GUIMenuItem) { .title = "魔改功能", .data = GUI_V_U(RUNNER_BEIKLIVE) };
	*GUIMenuItemListAppend(&pauseMenu.items) = (struct GUIMenuItem) { .title = "重置游戏", .data = GUI_V_U(RUNNER_RESET) };
	*GUIMenuItemListAppend(&pauseMenu.items) = (struct GUIMenuItem) { .title = "退出游戏", .data = GUI_V_U(RUNNER_EXIT) };

	runner->params.drawStart();
	if (runner->params.guiPrepare) {
		runner->params.guiPrepare();
	}
	if(bk_global_runner->drawBKImage){
			bk_global_runner->drawBKImage(bk_global_runner, NULL);
	}
	GUIFontPrint(runner->params.font, runner->params.width / 2, (GUIFontHeight(runner->params.font) + runner->params.height) / 2, GUI_ALIGN_HCENTER, themeType == BK_THEME_DEFAULT? BK_COLOR_WHITE : BK_COLOR_TEXT, "加载中...");
	if (runner->params.guiFinish) {
		runner->params.guiFinish();
	}
	runner->params.drawEnd();

	bool found = false;
	mLOG(GUI_RUNNER, INFO, "Attempting to load %s", path);
	runner->core = mCoreFind(path);
	if (runner->core) {
		mLOG(GUI_RUNNER, INFO, "Found core");
		runner->core->init(runner->core);
		mCoreInitConfig(runner->core, runner->port);
		mInputMapInit(&runner->core->inputMap, &GBAInputInfo);

		struct VFile* rom = mDirectorySetOpenPath(&runner->core->dirs, path, runner->core->isROM);
		if (runner->setFrameLimiter) {
			runner->setFrameLimiter(runner, false);
		}
		found = mCorePreloadVFCB(runner->core, rom, _updateLoading, runner);
		if (runner->setFrameLimiter) {
			runner->setFrameLimiter(runner, true);
		}

#ifdef FIXED_ROM_BUFFER
		extern size_t romBufferSize;
		if (!found && rom && (size_t) rom->size(rom) > romBufferSize) {
			found = runner->core->loadROM(runner->core, rom);
		}
#endif
		if (!found) {
			if (rom) {
				rom->close(rom);
			}
			mLOG(GUI_RUNNER, WARN, "Failed to load %s!", path);
			mCoreConfigDeinit(&runner->core->config);
			runner->core->deinit(runner->core);
		}
	}

	if (!found) {
		mLOG(GUI_RUNNER, WARN, "Failed to find core for %s!", path);
		GUIShowMessageBox(&runner->params, GUI_MESSAGE_BOX_OK, 240, "无法加载所选游戏!");
		return;
	}
	if (runner->core->platform(runner->core) == mPLATFORM_GBA) {
		runner->core->setPeripheral(runner->core, mPERIPH_GBA_LUMINANCE, &runner->luminanceSource.d);
	}

	mLOG(GUI_RUNNER, DEBUG, "Loading config...");
	mCoreLoadForeignConfig(runner->core, &runner->config);

	mLOG(GUI_RUNNER, DEBUG, "Loading save...");
	mCoreAutoloadSave(runner->core);  // 读取存档文件
	mCoreAutoloadCheats(runner->core); // 读取金手指文件
	if (runner->setup) {
		mLOG(GUI_RUNNER, DEBUG, "Setting up runner...");
		runner->setup(runner);  // 设置运行环境
	}
	if (runner->config.port && runner->keySources) { // 加载按键配置
		mLOG(GUI_RUNNER, DEBUG, "Loading key sources for %s...", runner->config.port);
		size_t i;
		for (i = 0; runner->keySources[i].id; ++i) {
			mInputMapLoad(&runner->core->inputMap, runner->keySources[i].id, mCoreConfigGetInput(&runner->config));
		}
	}
	mLOG(GUI_RUNNER, DEBUG, "Reseting...");
	runner->core->reset(runner->core);
	mLOG(GUI_RUNNER, DEBUG, "Reset!");


	int autoload = false;
	mCoreConfigGetIntValue(&runner->config, "autoload", &autoload);
	if (autoload) {
		mCoreLoadState(runner->core, 0, SAVESTATE_SCREENSHOT | SAVESTATE_RTC);
	}

	int showOSD = true;
	mCoreConfigGetIntValue(&runner->config, "showOSD", &showOSD);

	int drawFps = false;
	mCoreConfigGetIntValue(&runner->config, "fpsCounter", &drawFps);

	int mute = false;
	mCoreConfigGetIntValue(&runner->config, "mute", &mute);

	int fastForwardMute = false;
	mCoreConfigGetIntValue(&runner->config, "fastForwardMute", &fastForwardMute);

	bool running = true;

#ifndef DISABLE_THREADING
	MutexLock(&runner->autosave.mutex);
	runner->autosave.core = runner->core;
	MutexUnlock(&runner->autosave.mutex);
#endif

	if (runner->core->platform(runner->core) == mPLATFORM_GBA)
	{
		bk_init_fbo(BK_GBA_WIDTH, BK_GBA_HEIGHT);
	}
	else
	{
		bk_init_fbo(BK_GBC_WIDTH, BK_GBC_HEIGHT);
	}



	if (runner->gameLoaded) {
		runner->gameLoaded(runner);  // 加载游戏
	}
	mLOG(GUI_RUNNER, INFO, "Game starting");
	runner->fps = 0;
	bool fastForward = false;
	while (running) {
		CircleBufferClear(&runner->fpsBuffer);
		runner->totalDelta = 0;
		struct timeval tv;
		gettimeofday(&tv, 0);
		runner->lastFpsCheck = 1000000LL * tv.tv_sec + tv.tv_usec;

		int frame = 0;
		while (running) {
			BK_GLOBAL_INT_SET(BK_PRO_STATUS, BK_RUNNING_TYPE_GAME);
			if (runner->running) {
				running = runner->running(runner);
				if (!running) {
					break;
				}
			}
			uint32_t guiKeys;
			uint32_t heldKeys;
			GUIPollInput(&runner->params, &guiKeys, &heldKeys);
			if (guiKeys & (1 << GUI_INPUT_CANCEL)) {
				BK_GLOBAL_INT_SET(BK_PRO_STATUS, BK_RUNNING_TYPE_MENU);
				break;
			}
			if (guiKeys & (1 << mGUI_INPUT_INCREASE_BRIGHTNESS)) {
				if (runner->luminanceSource.luxLevel < 10) {
					++runner->luminanceSource.luxLevel;
				}
			}
			if (guiKeys & (1 << mGUI_INPUT_DECREASE_BRIGHTNESS)) {
				if (runner->luminanceSource.luxLevel > 0) {
					--runner->luminanceSource.luxLevel;
				}
			}
			if (guiKeys & (1 << mGUI_INPUT_SCREEN_MODE) && runner->incrementScreenMode) {
				runner->incrementScreenMode(runner);
			}
			if (guiKeys & (1 << mGUI_INPUT_SCREENSHOT)) {
				mCoreTakeScreenshot(runner->core);
			}
			bool muteTogglePressed = guiKeys & (1 << mGUI_INPUT_MUTE_TOGGLE);
			if (muteTogglePressed) {
				mute = !mute;
				mCoreConfigSetUIntValue(&runner->config, "mute", mute);
				runner->core->reloadConfigOption(runner->core, "mute", &runner->config);
			}
			if (guiKeys & (1 << mGUI_INPUT_FAST_FORWARD_TOGGLE)) {
				fastForward = !fastForward;
			}
			bool fastForwarding = fastForward || (heldKeys & (1 << mGUI_INPUT_FAST_FORWARD_HELD));
			if (runner->setFrameLimiter) {
				if (fastForwarding) {
					if (fastForwardMute && !mute && !muteTogglePressed) {
						mCoreConfigSetUIntValue(&runner->core->config, "mute", fastForwardMute);
						runner->core->reloadConfigOption(runner->core, "mute", NULL);
					}

					runner->setFrameLimiter(runner, false);
				} else {
					runner->setFrameLimiter(runner, true);

					if (fastForwardMute && !mute && !muteTogglePressed) {
						mCoreConfigSetUIntValue(&runner->core->config, "mute", !fastForwardMute);
						runner->core->reloadConfigOption(runner->core, "mute", NULL);
					}
				}
			}
			bool rewinding = heldKeys & (1 << mGUI_INPUT_REWIND_HELD);
			if (rewinding) {
				printf("倒带中...\n");
			}

			uint16_t keys = runner->pollGameInput(runner);
			if (runner->prepareForFrame) {
				runner->prepareForFrame(runner);
			}
			runner->core->setKeys(runner->core, keys);
			runner->core->runFrame(runner->core);
			// 绘制游戏画面
			if (runner->drawFrame) {
				runner->params.drawStart();  // 清空背景
				
				runner->drawFrame(runner, false);
				// ========== 添加遮罩绘制 ==========
				int isMaskEnabled = 0;
				BK_GLOBAL_INT_GET(BK_META_MASK_ENABLE, isMaskEnabled);
				if(isMaskEnabled)
				{
					// 获取平台
					int platform = runner->core->platform(runner->core);
					runner->drawGameMask(runner, platform);
				}
				// ========== 遮罩绘制结束 ==========
				
				if (showOSD || drawFps) {// 绘制OSD和FPS
					if (runner->params.guiPrepare) { // 调整视口
						runner->params.guiPrepare();
					}
					if (drawFps) {
						GUIFontPrintf(runner->params.font, 0, GUIFontHeight(runner->params.font), GUI_ALIGN_LEFT, 0x7FFFFFFF, "%.2f fps", runner->fps);
					}
					if (showOSD) {
						unsigned origin = runner->params.width - GUIFontHeight(runner->params.font) / 2;
						unsigned w;
						if (fastForward || (heldKeys & (1 << mGUI_INPUT_FAST_FORWARD_HELD))) {
							GUIFontDrawIcon(runner->params.font, origin, GUIFontHeight(runner->params.font) / 2, GUI_ALIGN_RIGHT, 0, 0x7FFFFFFF, GUI_ICON_STATUS_FAST_FORWARD);
							GUIFontIconMetrics(runner->params.font, GUI_ICON_STATUS_FAST_FORWARD, &w, NULL);
							origin -= w + GUIFontHeight(runner->params.font) / 2;
						}
						if (runner->core->opts.mute) {
							GUIFontDrawIcon(runner->params.font, origin, GUIFontHeight(runner->params.font) / 2, GUI_ALIGN_RIGHT, 0, 0x7FFFFFFF, GUI_ICON_STATUS_MUTE);
							GUIFontIconMetrics(runner->params.font, GUI_ICON_STATUS_MUTE, &w, NULL);
							origin -= w + GUIFontHeight(runner->params.font) / 2;
						}
					}
					if (runner->params.guiFinish) { // 提交文字绘制
						runner->params.guiFinish();
					}
				}
				runner->params.drawEnd();

				++frame; // 帧数统计
				if (frame % FPS_GRANULARITY == 0) {
					if (drawFps) {
						struct timeval tv;
						gettimeofday(&tv, 0);
						uint64_t t = 1000000LL * tv.tv_sec + tv.tv_usec;
						uint64_t delta = t - runner->lastFpsCheck;
						runner->lastFpsCheck = t;
						if (delta > 0x7FFFFFFFLL) {
							CircleBufferClear(&runner->fpsBuffer);
							runner->fps = 0;
						}
						if (CircleBufferSize(&runner->fpsBuffer) == CircleBufferCapacity(&runner->fpsBuffer)) {
							int32_t last;
							CircleBufferRead32(&runner->fpsBuffer, &last);
							runner->totalDelta -= last;
						}
						CircleBufferWrite32(&runner->fpsBuffer, delta);
						runner->totalDelta += delta;
						runner->fps = (CircleBufferSize(&runner->fpsBuffer) * FPS_GRANULARITY * 1000000.0f) / (runner->totalDelta * sizeof(uint32_t));
					}
				}
				if (frame % (AUTOSAVE_GRANULARITY * (fastForwarding ? 2 : 1)) == 0) {
					_tryAutosave(runner);
				}
				if (frame == FPS_GRANULARITY * AUTOSAVE_GRANULARITY) {
					frame = 0;
				}
			}
		}
		if (!running) {
			break;
		}

		if (runner->paused) {
			runner->paused(runner);
		}
		if (runner->setFrameLimiter) {
			runner->setFrameLimiter(runner, true);
		}

		GUIInvalidateKeys(&runner->params);
		uint32_t keys = 0xFFFFFFFF; // Huge hack to avoid an extra variable!
		struct GUIMenuItem* item;
		runner->params.drawStart();
		enum GUIMenuExitReason reason = GUIShowMenu(&runner->params, &pauseMenu, &item);
		if (reason == GUI_MENU_EXIT_ACCEPT && item->data.type == GUI_VARIANT_UNSIGNED) {
			switch (item->data.v.u & RUNNER_COMMAND_MASK) {
			case RUNNER_EXIT:
				running = false;
				keys = 0;
				break;
			case RUNNER_RESET:
				runner->core->reset(runner->core);
				break;
			case RUNNER_SAVE_STATE:
				// If we are saving state, then the screenshot stored for the state previously should no longer be considered up-to-date.
				// Therefore, mark it as stale so that at draw time we load the new save state's screenshot.
				((struct mGUIBackground*) stateSaveMenu.background)->screenshotId |= SCREENSHOT_INVALID;
				mCoreSaveState(runner->core, item->data.v.u >> 16, SAVESTATE_SCREENSHOT | SAVESTATE_SAVEDATA | SAVESTATE_RTC | SAVESTATE_METADATA);
				break;
			case RUNNER_LOAD_STATE:
				mCoreLoadState(runner->core, item->data.v.u >> 16, SAVESTATE_SCREENSHOT | SAVESTATE_RTC);
				break;
			case RUNNER_SCREENSHOT:
				mCoreTakeScreenshot(runner->core);
				break;
			case RUNNER_CONFIG:
				mGUIShowConfig(runner, runner->configExtra, runner->nConfigExtra);
				break;
			case RUNNER_BEIKLIVE:
				mGUIShowBeiklive(runner);
				break;
			case RUNNER_CHEATS:
				mGUIShowCheats(runner);
				break;
			case RUNNER_CONTINUE:
				break;
			}
		}
		int frames = 0;
		GUIPollInput(&runner->params, 0, &keys);
		while (keys && frames < 30) {
#ifdef __3DS__
			if (!frames) {
#endif
				runner->params.drawStart();
				runner->drawFrame(runner, true);
				runner->params.drawEnd();
#ifdef __3DS__
			} else {
				// XXX: Why does this fix #1294?
				usleep(15000);
			}
#endif
			++frames;
			GUIPollInput(&runner->params, 0, &keys);
		}
		if (runner->unpaused) {
			runner->unpaused(runner);
		}
		mCoreConfigGetIntValue(&runner->config, "fpsCounter", &drawFps);
		mCoreConfigGetIntValue(&runner->config, "showOSD", &showOSD);
		mCoreConfigGetIntValue(&runner->config, "mute", &mute);
		mCoreConfigGetIntValue(&runner->config, "fastForwardMute", &fastForwardMute);



#ifdef M_CORE_GB
		if (runner->core->platform(runner->core) == mPLATFORM_GB) {
			runner->core->reloadConfigOption(runner->core, "gb.pal", &runner->config);
		}
#endif
	}
	mLOG(GUI_RUNNER, DEBUG, "Shutting down...");
	if (runner->gameUnloaded) {
		runner->gameUnloaded(runner);
	}
#ifndef DISABLE_THREADING
	MutexLock(&runner->autosave.mutex);
	runner->autosave.core = NULL;
	MutexUnlock(&runner->autosave.mutex);
#endif

	int autosave = false;
	mCoreConfigGetIntValue(&runner->config, "autosave", &autosave);
	if (autosave) {
		mCoreSaveState(runner->core, 0, SAVESTATE_SAVEDATA | SAVESTATE_RTC | SAVESTATE_METADATA);
	}

	mLOG(GUI_RUNNER, DEBUG, "Unloading game...");
	runner->core->unloadROM(runner->core);
	drawState.screenshotId = 0;
	if (drawState.image) {
		mappedMemoryFree(drawState.image, drawState.imageSize);
	}

	if (runner->config.port) {
		mLOG(GUI_RUNNER, DEBUG, "Saving key sources...");
		if (runner->keySources) {
			size_t i;
			for (i = 0; runner->keySources[i].id; ++i) {
				mInputMapSave(&runner->core->inputMap, runner->keySources[i].id, mCoreConfigGetInput(&runner->config));
				mInputMapSave(&runner->params.keyMap, runner->keySources[i].id, mCoreConfigGetInput(&runner->config));
			}
		}
		mCoreConfigSave(&runner->config);
	}
	mInputMapDeinit(&runner->core->inputMap);
	mLOG(GUI_RUNNER, DEBUG, "Deinitializing core...");
	mCoreConfigDeinit(&runner->core->config);
	runner->core->deinit(runner->core);
	runner->core = NULL;

	GUIMenuItemListDeinit(&pauseMenu.items);
	GUIMenuItemListDeinit(&stateSaveMenu.items);
	GUIMenuItemListDeinit(&stateLoadMenu.items);

	mLOG(GUI_RUNNER, INFO, "Game stopped!");
}

// BK_MARK mGUIRunloop  程序启动循环
void mGUIRunloop(struct mGUIRunner* runner) {
	if (runner->keySources) {
		mLOG(GUI_RUNNER, DEBUG, "Loading key sources for %s...", runner->config.port);
		size_t i;
		for (i = 0; runner->keySources[i].id; ++i) {
			mInputMapLoad(&runner->params.keyMap, runner->keySources[i].id, mCoreConfigGetInput(&runner->config));
		}
	}
	while (!runner->running || runner->running(runner)) {
		char path[PATH_MAX];
		const char* preselect = mCoreConfigGetValue(&runner->config, "lastGame");
		if (preselect) {
			preselect = strrchr(preselect, '/');
		}
		if (preselect) {
			++preselect;
		}
		BK_GLOBAL_INT_SET(BK_META_ISFOLDER, true);
		BK_GLOBAL_INT_SET(BK_PRO_STATUS, BK_RUNNING_TYPE_FILELIST);
		BK_GLOBAL_INT_SET(BK_META_FOLDER_TARGET, BK_META_FOLDER_TARGET_ROM);
		


		if (!GUISelectFile(&runner->params, path, sizeof(path), _testExtensions, NULL, preselect)) {
			break;
		}
		mCoreConfigSetValue(&runner->config, "lastDirectory", runner->params.currentPath);
		mCoreConfigSetValue(&runner->config, "lastGame", path);
		BK_GLOBAL_INT_SET(BK_META_ISFOLDER, false);
		mCoreConfigSave(&runner->config);
		




		mGUIRun(runner, path); 
	}
}

#ifndef DISABLE_THREADING
THREAD_ENTRY mGUIAutosaveThread(void* context) {
	struct mGUIAutosaveContext* autosave = context;
	MutexLock(&autosave->mutex);
	while (autosave->running) {
		ConditionWait(&autosave->cond, &autosave->mutex);
		if (autosave->running && autosave->core) {
			if (!autosave->buffer) {
				continue;
			}
			struct VFile* vf = mCoreGetState(autosave->core, 0, true);
			if (!vf) {
				continue;
			}
			void* mem = autosave->buffer->map(autosave->buffer, autosave->buffer->size(autosave->buffer), MAP_READ);
			vf->write(vf, mem, autosave->buffer->size(autosave->buffer));
			autosave->buffer->unmap(autosave->buffer, mem, autosave->buffer->size(autosave->buffer));
			vf->close(vf);
		}
	}
	MutexUnlock(&autosave->mutex);
	THREAD_EXIT(0);
}
#endif
