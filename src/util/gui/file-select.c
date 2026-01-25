/* Copyright (c) 2013-2015 Jeffrey Pfau
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include <mgba-util/gui/file-select.h>

#include <mgba-util/gui/font.h>
#include <mgba-util/gui/menu.h>
#include <mgba-util/string.h>
#include <mgba-util/vfs.h>

#include <beiklive/beiklive.h>

#include <stdlib.h>

#define ITERATION_SIZE 5
#define SCANNING_THRESHOLD_1 50
#ifdef __3DS__
// 3DS is slooooow at opening files
#define SCANNING_THRESHOLD_2 10
#else
#define SCANNING_THRESHOLD_2 50
#endif

char mappSubtitle[PATH_MAX];

char* process_path_with_mapping(const char* path) {
    if (path == NULL || path[0] != '/') {
        return NULL;
    }
    // 移除尾部的斜杠
    char* processed_path = strdup(path);
    if (processed_path == NULL) {
        return NULL;
    }
    
    size_t len = strlen(processed_path);
    while (len > 1 && processed_path[len - 1] == '/') {
        len--;
        processed_path[len] = '\0';
    }
    
    // 统计路径段数
    int segment_count = 0;
    for (int i = 1; processed_path[i] != '\0'; i++) {
        if (processed_path[i] == '/' && processed_path[i-1] != '/') {
            segment_count++;
        }
    }
    if (processed_path[len-1] != '/') {
        segment_count++;
    }
    
    if (segment_count == 0) {
        // 只有根目录
        char* result = strdup("/");
        free(processed_path);
        return result;
    }
    
    // 分配数组存储路径段
    char** segments = (char**)malloc(segment_count * sizeof(char*));
    char** mapped_segments = (char**)malloc(segment_count * sizeof(char*));
    if (segments == NULL || mapped_segments == NULL) {
        free(segments);
        free(mapped_segments);
        free(processed_path);
        return NULL;
    }
    
    // 分割路径
    int index = 0;
    char* token = strtok(processed_path + 1, "/"); // 跳过开头的/
    
    while (token != NULL && index < segment_count) {
        segments[index] = strdup(token);
        if (segments[index] == NULL) {
            // 清理内存
            for (int j = 0; j < index; j++) {
                free(segments[j]);
            }
            free(segments);
            free(mapped_segments);
            free(processed_path);
            return NULL;
        }
        index++;
        token = strtok(NULL, "/");
    }
    
    // 获取映射的目录名并重新组合
    size_t total_length = 2; // 开头的/和结尾的\0
    for (int i = 0; i < segment_count; i++) {
        mapped_segments[i] = bk_config_get(segments[i]);
        if (mapped_segments[i] == NULL) {
            // 使用原始名称作为后备
            mapped_segments[i] = segments[i];
        } else {
            // 释放原始名称，使用映射名称
            free(segments[i]);
        }
        total_length += strlen(mapped_segments[i]) + 1; // +1 for /
    }
    
    // 分配结果字符串
    char* result = (char*)malloc(total_length);
    if (result == NULL) {
        for (int i = 0; i < segment_count; i++) {
            if (mapped_segments[i] != segments[i]) {
                free(mapped_segments[i]);
            }
        }
        free(segments);
        free(mapped_segments);
        free(processed_path);
        return NULL;
    }
    
    // 组合结果
    result[0] = '/';
    result[1] = '\0';
    
    for (int i = 0; i < segment_count; i++) {
        if (i > 0) {
            strcat(result, "/");
        }
        strcat(result, mapped_segments[i]);
        
        // 释放映射名称（如果是通过bk_config_get获取的）
        if (mapped_segments[i] != segments[i]) {
            free(mapped_segments[i]);
        }
    }
    
    // 清理
    free(segments);
    free(mapped_segments);
    free(processed_path);
    return result;
}


static void _cleanFiles(struct GUIMenuItemList* currentFiles) {
	size_t size = GUIMenuItemListSize(currentFiles);
	size_t i;
	for (i = 1; i < size; ++i) {
		free((char*) GUIMenuItemListGetPointer(currentFiles, i)->title);
		if(GUIMenuItemListGetPointer(currentFiles, i)->mappedTitle)
		{
			free((char*) GUIMenuItemListGetPointer(currentFiles, i)->mappedTitle);
		}
	}
	GUIMenuItemListClear(currentFiles);
}

static void _upDirectory(char* currentPath) {
	char* end = strrchr(currentPath, '/');
	if (!end) {
		currentPath[0] = '\0';
		return;
	}
	if (!end[1]) {
		// Trailing slash
		end[0] = '\0';
		return _upDirectory(currentPath);
	}
	end[1] = '\0';
}

static int _strpcmp(const void* a, const void* b) {
	return strcasecmp(((const struct GUIMenuItem*) a)->title, ((const struct GUIMenuItem*) b)->title);
}

static bool _refreshDirectory(struct GUIParams* params, const char* currentPath, struct GUIMenuItemList* currentFiles, bool (*filterName)(const char* name), bool (*filterContents)(struct VFile*), const char* preselect) {
	_cleanFiles(currentFiles);
	struct VDir* dir = VDirOpen(currentPath);
	if (!dir) {
		return false;
	}
	*GUIMenuItemListAppend(currentFiles) = (struct GUIMenuItem) { .title = "(Up)", .mappedTitle = "(返回上层文件夹)" };
	size_t i = 0;
	size_t items = 0;
	struct VDirEntry* de;
	while ((de = dir->listNext(dir))) {
		++i;
		if (!(i % SCANNING_THRESHOLD_1)) {
			uint32_t input = 0;
			GUIPollInput(params, &input, 0);
			if (input & (1 << GUI_INPUT_CANCEL)) {
				dir->close(dir);
				return false;
			}

			params->drawStart();
			if (params->guiPrepare) {
				params->guiPrepare();
			}
			GUIFontPrintf(params->font, 0, GUIFontHeight(params->font), GUI_ALIGN_LEFT, 0xFFFFFFFF, "(扫描文件中: %"PRIz"u)", i);
			GUIFontPrintf(params->font, 0, GUIFontHeight(params->font) * 2, GUI_ALIGN_LEFT, 0xFFFFFFFF, "%s", currentPath);
			if (params->guiFinish) {
				params->guiFinish();
			}
			params->drawEnd();
		}
		const char* name = de->name(de);
		if (name[0] == '.') {
			continue;
		}
		if (de->type(de) == VFS_DIRECTORY) {
			size_t len = strlen(name) + 2;
			char* n2 = malloc(len);
			snprintf(n2, len, "%s/", name);
			name = n2;
		} else if (filterName && !filterName(name)) {
			continue;
		} else {
			name = strdup(name);
		}
		// 检测后缀如果是游戏或者游戏压缩包，则尝试映射名称
		if(bk_util_is_valid_rom_extension(name))
		{
			char* basename = bk_util_remove_extension(name);
			char* extensionn = bk_util_get_extension(name);
			char* mapped_name = bk_config_get(basename);
			if(mapped_name == NULL)
			{
				*GUIMenuItemListAppend(currentFiles) = (struct GUIMenuItem) { .title = name, .mappedTitle = NULL, .data = GUI_V_U(de->type(de)) };
			}
			else
			{
				char* full_mapped_name = bk_util_str_concatenate(mapped_name, extensionn);
				*GUIMenuItemListAppend(currentFiles) = (struct GUIMenuItem) { .title = name, .mappedTitle = full_mapped_name, .data = GUI_V_U(de->type(de)) };
				free(mapped_name);
			}
			free(basename);
			free(extensionn);
			basename = NULL;
			extensionn = NULL;
		} // BKMARK 追加目录名称映射
		else if(bk_util_has_mgba_dir_prefix(name))
		{
			char* basename = bk_util_remove_trailing_slash_copy(name);
			char* mapped_name = bk_config_get(basename);
			if(mapped_name == NULL)
			{
				*GUIMenuItemListAppend(currentFiles) = (struct GUIMenuItem) { .title = name, .mappedTitle = NULL, .data = GUI_V_U(de->type(de)) };
			}
			else
			{
				*GUIMenuItemListAppend(currentFiles) = (struct GUIMenuItem) { .title = name, .mappedTitle = bk_util_str_concatenate(mapped_name, "/"), .data = GUI_V_U(de->type(de)) };
			}
			free(basename);
			basename = NULL;
		}
		else
		{
			*GUIMenuItemListAppend(currentFiles) = (struct GUIMenuItem) { .title = name, .mappedTitle = NULL, .data = GUI_V_U(de->type(de)) };
		}
		++items;
	}
	qsort(GUIMenuItemListGetPointer(currentFiles, 1), GUIMenuItemListSize(currentFiles) - 1, sizeof(struct GUIMenuItem), _strpcmp);
	if (preselect || filterContents) {
		i = 0;
		size_t item = 0;
		while (item < GUIMenuItemListSize(currentFiles)) {
			++i;
			// If we're not filtering the contents, this loop is fast, so there's no need to show updates
			if (filterContents && !(i % SCANNING_THRESHOLD_2)) {
				uint32_t input = 0;
				GUIPollInput(params, &input, 0);
				if (input & (1 << GUI_INPUT_CANCEL)) {
					dir->close(dir);
					return false;
				}

				params->drawStart();
				if (params->guiPrepare) {
					params->guiPrepare();
				}
				GUIFontPrintf(params->font, 0, GUIFontHeight(params->font), GUI_ALIGN_LEFT, 0xFFFFFFFF, "(扫描项目: %"PRIz"u / %"PRIz"u)", i, items);
				GUIFontPrintf(params->font, 0, GUIFontHeight(params->font) * 2, GUI_ALIGN_LEFT, 0xFFFFFFFF, "%s", currentPath);
				if (params->guiFinish) {
					params->guiFinish();
				}
				params->drawEnd();
			}
			struct GUIMenuItem* testItem = GUIMenuItemListGetPointer(currentFiles, item);
			if (!GUIVariantCompareUInt(testItem->data, VFS_FILE)) {
				++item;
				continue;
			}
			bool failed = false;
			if (filterContents) {
				struct VFile* vf = dir->openFile(dir, testItem->title, O_RDONLY);  // 使用文件名称打开文件
				if (!vf) {
					failed = true;
				} else {
					if (!filterContents(vf)) {
						failed = true;
					}
					vf->close(vf);
				}
			}

			if (failed) {
				free((char*) testItem->title); // 释放内存
				if(testItem->mappedTitle)
				{
					free((char*) testItem->mappedTitle);  // 释放内存
				}
				GUIMenuItemListShift(currentFiles, item, 1);
			} else {
				// 前一次玩的游戏文件名称对比
				if (preselect && strncmp(testItem->title, preselect, PATH_MAX) == 0) {
					params->fileIndex = item;
				}
				++item;
			}
		}
	}
	dir->close(dir);

	return true;
}


bool GUISelectFile(struct GUIParams* params, char* outPath, size_t outLen, bool (*filterName)(const char* name), bool (*filterContents)(struct VFile*), const char* preselect) {
	struct mGUIBackground drawState = {
		.d = {
			.draw = _bk_util_draw_game_logo
		},
		.p = bk_global_runner,
		.image = 0,
		.screenshotId = 0
	};

	strlcpy(mappSubtitle, process_path_with_mapping(params->currentPath), PATH_MAX);

	struct GUIMenu menu = {
		.title = "请选择游戏文件",
		.subtitle = mappSubtitle,
		.background = &drawState.d,
		.bkbg = BK_WINDOW
	};
	GUIMenuItemListInit(&menu.items, 0);
	_refreshDirectory(params, params->currentPath, &menu.items, filterName, filterContents, preselect);
	menu.index = params->fileIndex;

	while (true) {
		struct GUIMenuItem* item;
		enum GUIMenuExitReason reason = GUIShowMenu(params, &menu, &item);
		params->fileIndex = menu.index;
		if (reason == GUI_MENU_EXIT_CANCEL) {
			break;
		}
		if (reason == GUI_MENU_EXIT_ACCEPT) {
			if (params->fileIndex == 0) {
				if (strncmp(params->currentPath, params->basePath, PATH_MAX) == 0) {
					continue;
				}
				_upDirectory(params->currentPath);
				_upDirectory(mappSubtitle);
				if (!_refreshDirectory(params, params->currentPath, &menu.items, filterName, filterContents, NULL)) {
					break;
				}
			} else {
				size_t len = strlen(params->currentPath);
				const char* sep = PATH_SEP;
				if (!len || params->currentPath[len - 1] == *sep) {
					sep = "";
				}
				snprintf(outPath, outLen, "%s%s%s", params->currentPath, sep, item->title);
				struct GUIMenuItemList newFiles;
				GUIMenuItemListInit(&newFiles, 0);
				if (!_refreshDirectory(params, outPath, &newFiles, filterName, filterContents, NULL)) {
					_cleanFiles(&newFiles);
					GUIMenuItemListDeinit(&newFiles);
					_cleanFiles(&menu.items);
					GUIMenuItemListDeinit(&menu.items);
					return true;
				} else {
					_cleanFiles(&menu.items);
					GUIMenuItemListDeinit(&menu.items);
					menu.items = newFiles;
					strlcpy(params->currentPath, outPath, PATH_MAX);
					strlcpy(mappSubtitle, process_path_with_mapping(params->currentPath), PATH_MAX);
				}
			}
			params->fileIndex = 0;
			menu.index = 0;
		}
		if (reason == GUI_MENU_EXIT_BACK) {
			if (strncmp(params->currentPath, params->basePath, PATH_MAX) == 0) {
				break;
			}
			_upDirectory(params->currentPath);
			_upDirectory(mappSubtitle);
			if (!_refreshDirectory(params, params->currentPath, &menu.items, filterName, filterContents, NULL)) {
				break;
			}
			params->fileIndex = 0;
			menu.index = 0;
		}
	}
	_cleanFiles(&menu.items);
	GUIMenuItemListDeinit(&menu.items);
	return false;
}
