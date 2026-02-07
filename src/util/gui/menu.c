/* Copyright (c) 2013-2015 Jeffrey Pfau
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include <mgba-util/gui/menu.h>

#include <mgba-util/gui.h>
#include <mgba-util/gui/font.h>

#ifdef __3DS__
#include <3ds.h>
#elif defined(__SWITCH__)
#include <switch.h>
#include <beiklive/beiklive.h>
#include "feature/gui/gui-runner.h"

#endif

DEFINE_VECTOR(GUIMenuItemList, struct GUIMenuItem);
DEFINE_VECTOR(GUIMenuSavedList, struct GUIMenuSavedState);

void _itemNext(struct GUIMenuItem* item, bool wrap) {
	if (wrap || item->state < item->nStates - 1) {
		unsigned oldState = item->state;
		do {
			++item->state;
			if (item->state >= item->nStates) {
				item->state -= item->nStates;
			}
		} while (!item->validStates[item->state] && item->state < item->nStates - 1);
		if (!item->validStates[item->state]) {
			item->state = oldState;
		}
	}
}

void _itemPrev(struct GUIMenuItem* item, bool wrap) {
	if (wrap || item->state > 0) {
		unsigned oldState = item->state;
		do {
			if (item->state > 0) {
				--item->state;
			} else {
				item->state = item->nStates - 1;
			}
		} while (!item->validStates[item->state] && item->state > 0);
		if (!item->validStates[item->state]) {
			item->state = oldState;
		}
	}
}

void GUIMenuStateInit(struct GUIMenuState* state) {
	state->start = 0;
	state->cursorOverItem = 0;
	state->cursor = GUI_CURSOR_NOT_PRESENT;
	state->resultItem = NULL;
	GUIMenuSavedListInit(&state->stack, 0);
}

void GUIMenuStateDeinit(struct GUIMenuState* state) {
	GUIMenuSavedListDeinit(&state->stack);
}

enum GUIMenuExitReason GUIShowMenu(struct GUIParams* params, struct GUIMenu* menu, struct GUIMenuItem** item) {
	struct GUIMenuState state;
	GUIMenuStateInit(&state);
	GUIInvalidateKeys(params);
	while (true) {
#ifdef __3DS__
		if (!aptMainLoop()) {
			return GUI_MENU_EXIT_CANCEL;
		}
#elif defined(__SWITCH__)
		if (!appletMainLoop()) {
			return GUI_MENU_EXIT_CANCEL;
		}
#endif
		enum GUIMenuExitReason reason = GUIMenuRun(params, menu, &state);
		switch (reason) {
		case GUI_MENU_EXIT_BACK:
			if (GUIMenuSavedListSize(&state.stack) > 0) {
				struct GUIMenuSavedState* last = GUIMenuSavedListGetPointer(&state.stack, GUIMenuSavedListSize(&state.stack) - 1);
				state.start = last->start;
				menu = last->menu;
				GUIMenuSavedListResize(&state.stack, -1);
				break;
			}
		// Fall through
		case GUI_MENU_EXIT_CANCEL:
		case GUI_MENU_EXIT_ACCEPT:
			*item = state.resultItem;
			GUIMenuStateDeinit(&state);
			return reason;
		case GUI_MENU_ENTER:
			*GUIMenuSavedListAppend(&state.stack) = (struct GUIMenuSavedState) {
				.start = state.start,
				.menu = menu
			};
			menu = state.resultItem->submenu;
			state.start = 0;
			break;
		case GUI_MENU_CONTINUE:
			break;
		}
	}
}

static enum GUIMenuExitReason GUIMenuPollInput(struct GUIParams* params, struct GUIMenu* menu, struct GUIMenuState* state) {
	int themeType = BK_THEME_DEFAULT;
	BK_GLOBAL_INT_GET(BK_META_CONFIG_THEME, themeType);
	size_t lineHeight = GUIFontHeight(params->font);
	size_t pageSize = themeType == BK_THEME_DEFAULT?  params->height / lineHeight : (params->height - BK_TITLE_TOP_OFFSET - BK_TITLE_BOTTOM_OFFSET) / (lineHeight + (themeType == BK_THEME_DEFAULT? 0 : BK_ITEM_PADDING));
	if (pageSize > 4) {
		pageSize -= 4;
	} else {
		pageSize = 1;
	}
	uint32_t newInput = 0;
	GUIPollInput(params, &newInput, NULL);
	state->cursor = GUIPollCursor(params, &state->cx, &state->cy);

	// Check for new direction presses
	if (newInput & (1 << GUI_INPUT_UP) && menu->index > 0) {
		--menu->index;
	}
	if (newInput & (1 << GUI_INPUT_DOWN) && menu->index < GUIMenuItemListSize(&menu->items) - 1) {
		++menu->index;
	}
	if (newInput & (1 << GUI_INPUT_LEFT)) {
		struct GUIMenuItem* item = GUIMenuItemListGetPointer(&menu->items, menu->index);
		if (item->validStates && !item->readonly) {
			_itemPrev(item, false);
		} else if (menu->index >= pageSize) {
			menu->index -= pageSize;
		} else {
			menu->index = 0;
		}
	}
	if (newInput & (1 << GUI_INPUT_RIGHT)) {
		struct GUIMenuItem* item = GUIMenuItemListGetPointer(&menu->items, menu->index);
		if (item->validStates && !item->readonly) {
			_itemNext(item, false);
		} else if (menu->index + pageSize < GUIMenuItemListSize(&menu->items)) {
			menu->index += pageSize;
		} else {
			menu->index = GUIMenuItemListSize(&menu->items) - 1;
		}
	}

	// Handle cursor movement
	if (state->cursor != GUI_CURSOR_NOT_PRESENT) {
		unsigned cx = state->cx;
		unsigned cy = state->cy;
		if (cx < params->width - 16) {
			int index = (cy / lineHeight) - 2;
			if (index >= 0 && index + state->start < GUIMenuItemListSize(&menu->items)) {
				if (menu->index != index + state->start || !state->cursorOverItem) {
					state->cursorOverItem = 1;
				}
				menu->index = index + state->start;
			} else {
				state->cursorOverItem = 0;
			}
		} else if (state->cursor == GUI_CURSOR_DOWN || state->cursor == GUI_CURSOR_DRAGGING) {
			if (cy <= 2 * lineHeight && cy > lineHeight && menu->index > 0) {
				--menu->index;
			} else if (cy <= params->height && cy > params->height - lineHeight && menu->index < GUIMenuItemListSize(&menu->items) - 1) {
				++menu->index;
			} else if (cy <= params->height - lineHeight && cy > 2 * lineHeight) {
				size_t location = cy - 2 * lineHeight;
				location *= GUIMenuItemListSize(&menu->items) - 1;
				menu->index = location / (params->height - 3 * lineHeight);
			}
		}
	}

	// Move view up if the active item is before the top of the view
	if (menu->index < state->start) {
		state->start = menu->index;
	}
	// Move the view down if the active item is after the bottom of the view
	while ((menu->index - state->start + 4) * lineHeight > (themeType == BK_THEME_DEFAULT?  params->height : params->height - BK_TITLE_TOP_OFFSET - BK_TITLE_BOTTOM_OFFSET - lineHeight)) {
		// TODO: Should this loop be replaced with division?
		++state->start;
	}

	// Handle action inputs
	if (newInput & (1 << GUI_INPUT_CANCEL)) {
		return GUI_MENU_EXIT_CANCEL;
	}
	if (newInput & (1 << GUI_INPUT_SELECT) || (state->cursorOverItem == 2 && state->cursor == GUI_CURSOR_CLICKED)) {
		struct GUIMenuItem* item = GUIMenuItemListGetPointer(&menu->items, menu->index);
		if (!item->readonly) {
			if (item->submenu) {
				// Selected menus get shown inline
				state->resultItem = item;
				return GUI_MENU_ENTER;
			} else if (item->validStates && GUIVariantIsString(item->data)) {
				// Selected items with multiple (named) states get scrolled through
				_itemNext(item, true);
			} else {
				// Otherwise tell caller item was accepted
				state->resultItem = item;
				return GUI_MENU_EXIT_ACCEPT;
			}
		}
	}
	if (state->cursorOverItem == 1 && (state->cursor == GUI_CURSOR_UP || state->cursor == GUI_CURSOR_NOT_PRESENT)) {
		state->cursorOverItem = 2;
	}
	if (newInput & (1 << GUI_INPUT_BACK)) {
		return GUI_MENU_EXIT_BACK;
	}

	// No action taken
	return GUI_MENU_CONTINUE;
}
// BKMARK: 菜单绘制函数 GUIMenuDraw
static void GUIMenuDraw(struct GUIParams* params, const struct GUIMenu* menu, const struct GUIMenuState* state) {
	
	int isFold = false;
	BK_GLOBAL_INT_GET(BK_META_ISFOLDER, isFold);
	int themeType = BK_THEME_DEFAULT;
	BK_GLOBAL_INT_GET(BK_META_CONFIG_THEME, themeType);

	size_t lineHeight = GUIFontHeight(params->font);
	params->drawStart(); // 背景全部涂黑
	if (menu->background) {
		menu->background->draw(menu->background, GUIMenuItemListGetConstPointer(&menu->items, menu->index)->data.v.p);
	}



	// 调整视口大小用于全屏绘制文字
	if (params->guiPrepare) {
		params->guiPrepare();
	}
	unsigned y = lineHeight;

	GUIFontPrint(params->font, themeType == BK_THEME_DEFAULT? 0 : y, isFold && themeType != BK_THEME_DEFAULT ? y * 1.5f : y, GUI_ALIGN_LEFT, themeType == BK_THEME_DEFAULT? BK_COLOR_WHITE : BK_COLOR_TEXT, menu->title);
	
	if (menu->subtitle) {
		if(isFold && themeType != BK_THEME_DEFAULT)
		{
			GUIFontPrint(params->font, lineHeight, params->height - BK_TITLE_BOTTOM_OFFSET + lineHeight*1.5f, GUI_ALIGN_LEFT, themeType == BK_THEME_DEFAULT? BK_COLOR_WHITE : BK_COLOR_TEXT, menu->subtitle);
		}
		else
		{
			GUIFontPrint(params->font, 0, y + lineHeight, GUI_ALIGN_LEFT, themeType == BK_THEME_DEFAULT? BK_COLOR_WHITE : BK_COLOR_TEXT, menu->subtitle);
		}
	}
	y += (themeType == BK_THEME_DEFAULT?  2 * lineHeight : BK_TITLE_TOP_OFFSET);
	unsigned right;
	GUIFontIconMetrics(params->font, GUI_ICON_SCROLLBAR_BUTTON, &right, 0);

	size_t itemsPerScreen = (params->height - y - (themeType == BK_THEME_DEFAULT? 0 : BK_TITLE_BOTTOM_OFFSET)) / (lineHeight + (themeType == BK_THEME_DEFAULT? 0 : (BK_ITEM_PADDING + lineHeight)));
	
	size_t i;
	for (i = state->start; i < GUIMenuItemListSize(&menu->items); ++i) {
		int color = themeType == BK_THEME_DEFAULT? 0xE0A0A0A0 : BK_COLOR_TEXT;
		const struct GUIMenuItem* item = GUIMenuItemListGetConstPointer(&menu->items, i);
		// 根据当前选择的菜单项改变图标
		if (i == menu->index) {
			color = (themeType == BK_THEME_DEFAULT? BK_COLOR_WHITE : BK_COLOR_TEXT_SELECT);
			// 	printf("当前菜单项: %s, %s\n", item->title, bk_util_is_valid_rom_extension(item->title) ? "游戏文件" : "不是游戏");
			// beiklive  可以在这里绘制 背景图片   但是需要提前读取图片到缓存
			GUIFontDrawIcon(params->font, lineHeight * 0.8f, y, GUI_ALIGN_BOTTOM | GUI_ALIGN_RIGHT, GUI_ORIENT_0, color, GUI_ICON_POINTER);
		}
		// 检查是否有映射名称
		if((themeType != BK_THEME_DEFAULT) && (y > (params->height - BK_TITLE_BOTTOM_OFFSET)))
		{
			break;
		}
		if(NULL == item->mappedTitle)
		{
			GUIFontPrint(params->font, item->readonly ? lineHeight * 3 / 2 : lineHeight, y, GUI_ALIGN_LEFT, color, item->title);
		}else{
			GUIFontPrint(params->font, item->readonly ? lineHeight * 3 / 2 : lineHeight, y, GUI_ALIGN_LEFT, color, item->mappedTitle);
		}
		// 绘制选项菜单
		if (item->validStates && item->validStates[item->state]) {
			GUIFontPrintf(params->font, params->width - right - 8, y, GUI_ALIGN_RIGHT, color, "%s ", item->validStates[item->state]);
		}else{
			if(item->leftText)
			{
				GUIFontPrintf(params->font, params->width - right - 8, y, GUI_ALIGN_RIGHT, color, "%s ", item->leftText);
			}
		}
		y += lineHeight + (themeType == BK_THEME_DEFAULT? 0 : BK_ITEM_PADDING);
		if (y + lineHeight > params->height) {
			break;
		}
	}
	// 绘制滚动条
	if (itemsPerScreen < GUIMenuItemListSize(&menu->items)) {
		size_t top = (themeType == BK_THEME_DEFAULT?  2 * lineHeight : BK_TITLE_TOP_OFFSET);
		size_t bottom = params->height - (themeType == BK_THEME_DEFAULT? 8 : BK_TITLE_BOTTOM_OFFSET);
		unsigned w;
		GUIFontIconMetrics(params->font, GUI_ICON_SCROLLBAR_TRACK, &w, 0);
		right = (right - w) / 2;
		GUIFontDrawIconSize(params->font, params->width - right - 8, top, 0, bottom - top, themeType == BK_THEME_DEFAULT? BK_COLOR_WHITE : BK_COLOR_TEXT, GUI_ICON_SCROLLBAR_TRACK);
		GUIFontDrawIcon(params->font, params->width - 8, top, GUI_ALIGN_HCENTER | GUI_ALIGN_BOTTOM, GUI_ORIENT_VMIRROR, themeType == BK_THEME_DEFAULT? BK_COLOR_WHITE : BK_COLOR_TEXT, GUI_ICON_SCROLLBAR_BUTTON);
		GUIFontDrawIcon(params->font, params->width - 8, bottom, GUI_ALIGN_HCENTER | GUI_ALIGN_TOP, GUI_ORIENT_0, themeType == BK_THEME_DEFAULT? BK_COLOR_WHITE : BK_COLOR_TEXT, GUI_ICON_SCROLLBAR_BUTTON);

		y = menu->index * (bottom - top - 16) / GUIMenuItemListSize(&menu->items);
		GUIFontDrawIcon(params->font, params->width - 8, top + y, GUI_ALIGN_HCENTER | GUI_ALIGN_TOP, GUI_ORIENT_0, themeType == BK_THEME_DEFAULT? BK_COLOR_WHITE : BK_COLOR_TEXT, GUI_ICON_SCROLLBAR_THUMB);
	}

	GUIDrawBattery(params);
	GUIDrawClock(params);

	if (state->cursor != GUI_CURSOR_NOT_PRESENT) {
		GUIFontDrawIcon(params->font, state->cx, state->cy, GUI_ALIGN_HCENTER | GUI_ALIGN_TOP, GUI_ORIENT_0, themeType == BK_THEME_DEFAULT? BK_COLOR_WHITE : BK_COLOR_TEXT, GUI_ICON_CURSOR);
	}

	if (params->guiFinish) {
		params->guiFinish();
	}
	params->drawEnd();
}

enum GUIMenuExitReason GUIMenuRun(struct GUIParams* params, struct GUIMenu* menu, struct GUIMenuState* state) {
	enum GUIMenuExitReason reason = GUIMenuPollInput(params, menu, state);
	if (reason != GUI_MENU_CONTINUE) {
		return reason;
	}
	GUIMenuDraw(params, menu, state);
	return GUI_MENU_CONTINUE;
}

enum GUIMenuExitReason GUIShowMessageBox(struct GUIParams* params, int buttons, int frames, const char* format, ...) {
	va_list args;
	va_start(args, format);
	char message[256] = {0};
	vsnprintf(message, sizeof(message) - 1, format, args);
	va_end(args);
	int themeType = BK_THEME_DEFAULT;
	BK_GLOBAL_INT_GET(BK_META_CONFIG_THEME, themeType);
	while (true) {
		if (frames) {
			--frames;
			if (!frames) {
				break;
			}
		}
		params->drawStart();
		if (params->guiPrepare) {
			params->guiPrepare();
		}
		if(!bk_global_runner)
			break;
		if (themeType == BK_THEME_SWITCH) {
			if(bk_global_runner->drawBKImage){
					bk_global_runner->drawBKImage(bk_global_runner, NULL);
			}
		}
		// 绘制消息弹窗的文字
		GUIFontPrint(params->font, params->width / 2, (GUIFontHeight(params->font) + params->height) / 2, GUI_ALIGN_HCENTER, themeType == BK_THEME_DEFAULT? BK_COLOR_WHITE : BK_COLOR_TEXT, message);
		if (params->guiFinish) {
			params->guiFinish();
		}
		params->drawEnd();

		uint32_t input = 0;
		GUIPollInput(params, &input, 0);
		if (input) {
			if (input & (1 << GUI_INPUT_SELECT)) {
				if (buttons & GUI_MESSAGE_BOX_OK) {
					return GUI_MENU_EXIT_ACCEPT;
				}
				if (buttons & GUI_MESSAGE_BOX_CANCEL) {
					return GUI_MENU_EXIT_CANCEL;
				}
			}
			if (input & (1 << GUI_INPUT_BACK)) {
				if (buttons & GUI_MESSAGE_BOX_CANCEL) {
					return GUI_MENU_EXIT_BACK;
				}
				if (buttons & GUI_MESSAGE_BOX_OK) {
					return GUI_MENU_EXIT_ACCEPT;
				}
			}
			if (input & (1 << GUI_INPUT_CANCEL)) {
				if (buttons & GUI_MESSAGE_BOX_CANCEL) {
					return GUI_MENU_EXIT_CANCEL;
				}
				if (buttons & GUI_MESSAGE_BOX_OK) {
					return GUI_MENU_EXIT_ACCEPT;
				}
			}
		}
	}
	return GUI_MENU_EXIT_CANCEL;
}

void GUIDrawBattery(struct GUIParams* params) {
	if (!params->batteryState) {
		return;
	}
	int state = params->batteryState();
	if (state == BATTERY_NOT_PRESENT) {
		return;
	}
	int themeType = BK_THEME_DEFAULT;
	BK_GLOBAL_INT_GET(BK_META_CONFIG_THEME, themeType);
	uint32_t color = 0xFF000000;
	if(themeType == BK_THEME_DEFAULT)
	{
		color = 0xFF000000;
		if ((state & (BATTERY_CHARGING | BATTERY_FULL)) == (BATTERY_CHARGING | BATTERY_FULL)) {
			color |= 0xFFC060;
		} else if (state & BATTERY_CHARGING) {
			color |= 0x60FF60;
		} else if ((state & BATTERY_VALUE) >= BATTERY_HALF) {
			color |= 0xFFFFFF;
		} else if ((state & BATTERY_VALUE) >= BATTERY_LOW) {
			color |= 0x30FFFF;
		} else {
			color |= 0x3030FF;
		}
	}
	else if(themeType == BK_THEME_SWITCH)
	{
		if ((state & (BATTERY_CHARGING | BATTERY_FULL)) == (BATTERY_CHARGING | BATTERY_FULL))  {
        	color = BK_COLOR_HELPER(BK_CONFIG_COLOR_BLUE);  // 显示蓝色（充满）
		}
		// 检查是否正在充电（但未满）
		else if (state & BATTERY_CHARGING) {
			color = BK_COLOR_HELPER(BK_CONFIG_COLOR_ORANGE);  // 显示橙色（充电中）
		}
		// 非充电状态，根据电量值获取渐变颜色
		else {
			int batteryLevel = state & BATTERY_VALUE;  // 获取电量值（0-100）
			
			// 使用之前定义的 getBatteryColor 函数获取RGBA颜色
			uint32_t rgba_color;
			
			// 根据电量值选择不同的颜色
			if (batteryLevel >= BATTERY_HIGH) {
				// 高电量（75-100%）：使用绿色渐变
				rgba_color = _bk_getBatteryColor(batteryLevel);
			} else if (batteryLevel >= BATTERY_HALF) {
				// 中等电量（50-74%）：使用黄绿色渐变
				rgba_color = _bk_getBatteryColor(batteryLevel);
			} else if (batteryLevel >= BATTERY_LOW) {
				// 低电量（25-49%）：使用黄色/橙色渐变
				rgba_color = _bk_getBatteryColor(batteryLevel);
			} else if (batteryLevel > BATTERY_EMPTY) {
				// 极低电量（1-24%）：使用红色渐变
				rgba_color = _bk_getBatteryColor(batteryLevel);
			} else {
				// 空电量（0%）：红色
				rgba_color = 0xFF0000FF;  // 纯红色
			}
			
			color = _bk_rgba_to_abgr(rgba_color);
		}
	}

	enum GUIIcon batteryIcon;
	switch ((state & BATTERY_VALUE) - (state & BATTERY_VALUE) % 25) {
	case BATTERY_EMPTY:
		batteryIcon = GUI_ICON_BATTERY_EMPTY;
		break;
	case BATTERY_LOW:
		batteryIcon = GUI_ICON_BATTERY_LOW;
		break;
	case BATTERY_HALF:
		batteryIcon = GUI_ICON_BATTERY_HALF;
		break;
	case BATTERY_HIGH:
		batteryIcon = GUI_ICON_BATTERY_HIGH;
		break;
	case BATTERY_FULL:
		batteryIcon = GUI_ICON_BATTERY_FULL;
		break;
	default:
		batteryIcon = GUI_ICON_BATTERY_EMPTY;
		break;
	}

	GUIFontDrawIcon(params->font, params->width, GUIFontHeight(params->font) + 2, GUI_ALIGN_RIGHT | GUI_ALIGN_BOTTOM, GUI_ORIENT_0, color, batteryIcon);
	if (state & BATTERY_PERCENTAGE_VALID) {
		unsigned width;
		GUIFontIconMetrics(params->font, batteryIcon, &width, NULL);
		GUIFontPrintf(params->font, params->width - width, GUIFontHeight(params->font), GUI_ALIGN_RIGHT, themeType == BK_THEME_DEFAULT? BK_COLOR_WHITE : BK_COLOR_TEXT, "%u%%", state & BATTERY_VALUE);
	}
}

void GUIDrawClock(struct GUIParams* params) {
	int themeType = BK_THEME_DEFAULT;
	BK_GLOBAL_INT_GET(BK_META_CONFIG_THEME, themeType);
	char buffer[32];
	time_t t = time(0);
	struct tm tm;
	localtime_r(&t, &tm);
	strftime(buffer, sizeof(buffer), "%H:%M:%S", &tm);
	GUIFontPrint(params->font, params->width / 2, GUIFontHeight(params->font) , GUI_ALIGN_HCENTER, themeType == BK_THEME_DEFAULT? BK_COLOR_WHITE : BK_COLOR_TEXT, buffer);
}
