/* Copyright (c) 2013-2016 Jeffrey Pfau
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef GUI_RUNNER_H
#define GUI_RUNNER_H

#include <mgba-util/common.h>

CXX_GUARD_START

#include <mgba/core/config.h>
#include "feature/gui/remap.h"
#include <mgba/gba/interface.h>
#include <mgba-util/circle-buffer.h>
#include <mgba-util/gui.h>
#include <mgba-util/threading.h>

#include <beiklive/beiklive.h>

enum mGUIInput {
	mGUI_INPUT_INCREASE_BRIGHTNESS = GUI_INPUT_USER_START,
	mGUI_INPUT_DECREASE_BRIGHTNESS,
	mGUI_INPUT_SCREEN_MODE,
	mGUI_INPUT_SCREENSHOT,
	mGUI_INPUT_REWIND_HOLD,
	mGUI_INPUT_FAST_FORWARD_HELD,
	mGUI_INPUT_FAST_FORWARD_TOGGLE,
	mGUI_INPUT_MUTE_TOGGLE,
};

struct mGUIBackground {
	struct GUIBackground d;
	struct mGUIRunner* p;

	color_t* image;
	size_t imageSize;

	unsigned screenshotId;
};

struct mCore;
struct mGUIRunnerLux {
	struct GBALuminanceSource d;
	int luxLevel;
};

#ifndef DISABLE_THREADING
struct VFile;
struct mGUIAutosaveContext {
	struct VFile* buffer;
	struct mCore* core;
	Thread thread;
	Mutex mutex;
	Condition cond;
	bool running;
};
#endif

struct mGUIRunner {
	struct mCore* core;
	struct GUIParams params;

	struct mGUIBackground background;
	struct mGUIRunnerLux luminanceSource;
#ifndef DISABLE_THREADING
	struct mGUIAutosaveContext autosave;
#endif

	struct mInputMap guiKeys;
	struct mCoreConfig config;
	struct GUIMenuItem* configExtra;
	size_t nConfigExtra;

	struct GUIInputKeys* keySources;

    // 倒带相关
    struct mCoreRewindContext rewind;       // 倒带上下文
    bool rewinding;                         // 当前是否正在倒带
    bool rewindEnabled;                     // 倒带功能是否启用
    bool rewindMuteEnabled;                 // 倒带静音功能是否启用
    int rewindBufferSize;                   // 倒带缓冲区大小（帧数）
    int rewindSaveInterval;                 // 保存间隔（每N帧保存一次）
    unsigned rewindFrames;                  // 已保存的帧数
                
    // 用于倒带状态显示
    bool rewindPaused;                      // 倒带时是否暂停
    int rewindShowStatus;                      // 倒带时是否暂停

	const char* port;
	float fps;
	int64_t lastFpsCheck;
	int32_t totalDelta;
	struct CircleBuffer fpsBuffer;

	void (*setup)(struct mGUIRunner*);
	void (*teardown)(struct mGUIRunner*);
	void (*gameLoaded)(struct mGUIRunner*);
	void (*gameUnloaded)(struct mGUIRunner*);
	void (*prepareForFrame)(struct mGUIRunner*);
	void (*drawFrame)(struct mGUIRunner*, bool faded);
	void (*drawScreenshot)(struct mGUIRunner*, const color_t* pixels, unsigned width, unsigned height, bool faded);
	void (*drawBKImage)(struct mGUIRunner*, const color_t* pixels);
	void (*drawGameMask)(struct mGUIRunner*, int platfrom);
	void (*paused)(struct mGUIRunner*);
	void (*unpaused)(struct mGUIRunner*);
	void (*incrementScreenMode)(struct mGUIRunner*);
	void (*setFrameLimiter)(struct mGUIRunner*, bool limit);
	uint16_t (*pollGameInput)(struct mGUIRunner*);
	bool (*running)(struct mGUIRunner*);
};

void mGUIInit(struct mGUIRunner*, const char* port);
void mGUIDeinit(struct mGUIRunner*);
void mGUIRun(struct mGUIRunner*, const char* path);
void mGUIRunloop(struct mGUIRunner*);

#ifndef DISABLE_THREADING
THREAD_ENTRY mGUIAutosaveThread(void* context);
#endif

CXX_GUARD_END

#endif
