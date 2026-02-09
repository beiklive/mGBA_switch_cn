/* Copyright (c) 2013-2021 Jeffrey Pfau
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "gui-config.h"

#include <mgba/core/cheats.h>
#include <mgba/core/core.h>
#include "feature/gui/gui-runner.h"
#include <mgba-util/gui/menu.h>
#include <mgba-util/string.h>

enum mGUICheatAction {
	CHEAT_BACK = 0,
	CHEAT_ADD_LINE = 1,
	CHEAT_RENAME,
	CHEAT_DELETE,
};

static const char* const offOn[] = { "未启用", "已启用" };

static void _rebuildCheatView(struct GUIMenuItemList* items, const struct mCheatSet* set) {
	GUIMenuItemListClear(items);
	size_t i;
	for (i = 0; i < StringListSize(&set->lines); ++i) {
		*GUIMenuItemListAppend(items) = (struct GUIMenuItem) {
			.title = *StringListGetConstPointer(&set->lines, i),
			.readonly = true
		};
	}
	*GUIMenuItemListAppend(items) = (struct GUIMenuItem) {
		.title = "返回",
		.data = GUI_V_U(CHEAT_BACK),
	};
}

static void mGUIShowCheatSet(struct mGUIRunner* runner, struct mCheatDevice* device, struct mCheatSet* set) {
	char str1[80] = "金手指名称: ";
	strcat(str1, set->name);
	struct GUIMenu menu = {
		.title = "编辑金手指",
		.subtitle = str1,
		.index = 0,
		.background = &runner->background.d
	};
	GUIMenuItemListInit(&menu.items, 0);

	struct GUIMenu view = {
		.title = "查看金手指",
		.subtitle = set->name,
		.index = 0,
		.background = &runner->background.d
	};

	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "启用",
		.state = set->enabled,
		.validStates = offOn,
		.nStates = 2
	};
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "添加一行",
		.data = GUI_V_U(CHEAT_ADD_LINE),
	};
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "查看金手指",
		.submenu = &view,
	};
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "重命名",
		.data = GUI_V_U(CHEAT_RENAME),
	};
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "删除金手指",
		.data = GUI_V_U(CHEAT_DELETE),
	};
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "返回列表",
		.data = GUI_V_V,
	};

	GUIMenuItemListInit(&view.items, 0);
	_rebuildCheatView(&view.items, set);

	while (true) {
		struct GUIKeyboardParams keyboard;
		GUIKeyboardParamsInit(&keyboard);
		struct GUIMenuItem* item;
		enum GUIMenuExitReason reason = GUIShowMenu(&runner->params, &menu, &item);
		set->enabled = GUIMenuItemListGetPointer(&menu.items, 0)->state;
		if (reason != GUI_MENU_EXIT_ACCEPT || GUIVariantIsVoid(item->data)) {
			break;
		}

		enum mGUICheatAction action = (enum mGUICheatAction) item->data.v.u;
		switch (action) {
		case CHEAT_ADD_LINE:
			strlcpy(keyboard.title, "添加一行", sizeof(keyboard.title));
			keyboard.maxLen = 17;
			if (runner->params.getText(&keyboard) == GUI_KEYBOARD_DONE) {
				mCheatAddLine(set, keyboard.result, 0);
				_rebuildCheatView(&view.items, set);
			}
			break;
		case CHEAT_RENAME:
			strlcpy(keyboard.title, "重命名金手指集", sizeof(keyboard.title));
			strlcpy(keyboard.result, set->name, sizeof(keyboard.result));
			keyboard.maxLen = 50;
			if (runner->params.getText(&keyboard) == GUI_KEYBOARD_DONE) {
				mCheatSetRename(set, keyboard.result);
				menu.subtitle = set->name;
				view.subtitle = set->name;
			}
			break;
		case CHEAT_DELETE:
			mCheatRemoveSet(device, set);
			break;
		case CHEAT_BACK:
			// Used by submenus to return to the top menu
			break;
		}

		if (action == CHEAT_DELETE) {
			break;
		}
	}
	GUIMenuItemListDeinit(&menu.items);
	GUIMenuItemListDeinit(&view.items);
}

void mGUIShowCheats(struct mGUIRunner* runner) {
	struct mCheatDevice* device = runner->core->cheatDevice(runner->core);
	if (!device) {
		return;
	}
	struct GUIMenu menu = {
		.title = "金手指",
		.index = 0,
		.background = &runner->background.d
	};
	GUIMenuItemListInit(&menu.items, 0);

	while (true) {
		*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
			.title = "返回游戏",
			.data = GUI_V_I(-1),
		};
		*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
			.title = "添加新的金手指集",
			.data = GUI_V_V,
		};
		*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
			.title = "[金手指列表]",
			.readonly = true,
		};
		const int premenuCount = 3;
		size_t i;
		for (i = 0; i < mCheatSetsSize(&device->cheats); ++i) {
			struct mCheatSet* set = *mCheatSetsGetPointer(&device->cheats, i);
			// 计算所需空间
			size_t name_len = strlen(set->name);
			char *formatted_name = malloc(name_len + 20);  // 额外空间给序号和点号
			if (formatted_name) {
				snprintf(formatted_name, name_len + 20, " [%zu] %s", i + 1, set->name);
				
				*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
					.title = formatted_name,
					.data = GUI_V_P(set),
					.state = set->enabled,
					.validStates = offOn,
					.nStates = 2
				};
			}
		}

		struct GUIMenuItem* item;
		enum GUIMenuExitReason reason = GUIShowMenu(&runner->params, &menu, &item);
		for (i = 0; i < mCheatSetsSize(&device->cheats); ++i) {
			struct mCheatSet* set = *mCheatSetsGetPointer(&device->cheats, i);
			struct GUIMenuItem* item = GUIMenuItemListGetPointer(&menu.items, i + premenuCount);
			set->enabled = item->state;
		}

		if (reason != GUI_MENU_EXIT_ACCEPT || GUIVariantCompareInt(item->data, -1)) {
			break;
		}
		struct mCheatSet* set = NULL;
		if (GUIVariantIsVoid(item->data)) {
			struct GUIKeyboardParams keyboard;
			GUIKeyboardParamsInit(&keyboard);
			keyboard.maxLen = 50;
			strlcpy(keyboard.title, "金手指名称", sizeof(keyboard.title));
			strlcpy(keyboard.result, "新金手指", sizeof(keyboard.result));
			if (runner->params.getText(&keyboard) == GUI_KEYBOARD_DONE) {
				set = device->createSet(device, keyboard.result);
				mCheatAddSet(device, set);
			}
		} else {
			set = item->data.v.p;
		}
		if (set) {
			mGUIShowCheatSet(runner, device, set);
		}
		GUIMenuItemListClear(&menu.items);
	}
	GUIMenuItemListDeinit(&menu.items);
	mCheatAutosave(device);
}
