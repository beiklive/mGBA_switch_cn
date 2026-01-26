
#include "gui-beiklive.h"

#include <mgba/core/config.h>
#include <mgba/core/core.h>
#include "feature/gui/gui-runner.h"
#include "feature/gui/remap.h"
#include <mgba/internal/gba/gba.h>
#ifdef M_CORE_GB
#include <mgba/internal/gb/gb.h>
#include <mgba/internal/gb/overrides.h>
#endif
#include <mgba-util/gui/file-select.h>
#include <mgba-util/gui/menu.h>
#include <mgba-util/vfs.h>

#include <beiklive/beiklive.h>


enum BKGUIAction{
    BK_CONFIG_STATUS_1,
    BK_CONFIG_STATUS_2,
    BK_CONFIG_STATUS_3,
    BK_CONFIG_STATUS_4,
	BK_CONFIG_MAPNAME,
	BK_CONFIG_SAVE
};


// 名称映射相关功能
void mGUIShowMapName(struct mGUIRunner* runner) {
    char *gameName = runner->core->dirs.baseName;
    char* mapped_name = NULL;
    char* gameName_title = NULL;
    char* mapped_name_title = NULL;

    struct GUIMenu menu = {
		.title = "游戏名称映射",
		.index = 0
	};
    GUIMenuItemListInit(&menu.items, 0);

    // UI循环处理按键和UI更新
    while(true){
        mapped_name = bk_config_get(gameName);
        gameName_title = bk_util_str_concatenate_multiple(2, "文件名:", gameName);
        *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
                .title = gameName_title,
                .readonly = true,
        };
        mapped_name_title = bk_util_str_concatenate_multiple(2, "映射名:", mapped_name ? mapped_name : "未映射");
        *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
                .title = mapped_name_title,
                .readonly = true,
        };

        *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
            .title = "设置映射名称(不用后缀)",
            .data = GUI_V_U(BK_CONFIG_STATUS_1),
        };

        *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
            .title = "删除映射(当前游戏)",
            .data = GUI_V_U(BK_CONFIG_STATUS_2),
        };
        *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
            .title = "删除映射(所有游戏)",
            .data = GUI_V_U(BK_CONFIG_STATUS_3),
        };
        *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
            .title = "返回",
            .data = GUI_V_V,
        };


        struct GUIMenuItem* item;
		enum GUIMenuExitReason reason = GUIShowMenu(&runner->params, &menu, &item);

        if (reason != GUI_MENU_EXIT_ACCEPT || GUIVariantIsVoid(item->data)) {
            GUIMenuItemListClear(&menu.items);
            free(mapped_name);
            free(gameName_title);
            free(mapped_name_title);
			break;
		}
        enum BKGUIAction action = (enum BKGUIAction) item->data.v.u;
        switch (action)
        {
        case BK_CONFIG_STATUS_1:
            printf("设置映射名称\n");
            {
                struct GUIKeyboardParams keyboard;
                GUIKeyboardParamsInit(&keyboard);
                keyboard.maxLen = 50;
                strlcpy(keyboard.title, "映射名称", sizeof(keyboard.title));
                strlcpy(keyboard.result, mapped_name ? mapped_name : "未映射", sizeof(keyboard.result));
                if (runner->params.getText(&keyboard) == GUI_KEYBOARD_DONE) {
                    bk_config_set(gameName, keyboard.result);
                    printf("映射设置为:%s\n", keyboard.result);
                }
            }
            break;
        case BK_CONFIG_STATUS_2:
            printf("删除映射(当前游戏)\n");
            {
                if(bk_config_remove(gameName)){
		            GUIShowMessageBox(&runner->params, GUI_MESSAGE_BOX_OK, 240, "映射删除成功!");
                }
            }
            break;
        case BK_CONFIG_STATUS_3:
            printf("删除映射(所有游戏)\n");
            {
                if(bk_config_clear()){
                    GUIShowMessageBox(&runner->params, GUI_MESSAGE_BOX_OK, 240, "映射清空成功");
                }
            }
            break;
        default:
            break;
        }
        GUIMenuItemListClear(&menu.items);
        free(mapped_name);
        free(gameName_title);
        free(mapped_name_title);
    }
    GUIMenuItemListDeinit(&menu.items);

}




void mGUIShowBeiklive(struct mGUIRunner* runner) {
    // UI 初始化
    struct GUIMenu menu = {
		.title = "魔改功能",
		.subtitle = "beiklive制作",
		.index = 0,
		.background = &runner->background.d
	};
	GUIMenuItemListInit(&menu.items, 0);

    *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "游戏名称映射",
		.data = GUI_V_U(BK_CONFIG_MAPNAME),
	};
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "主题选择",
		.data = GUI_V_S(BK_META_CONFIG_THEME),
		.submenu = 0,
		.state = 0,
		.validStates = (const char*[]) {
			"原版黑白", "switch风格"
		},
		.nStates = 2
	};
    *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "保存设置",
		.data = GUI_V_U(BK_CONFIG_SAVE),
	};
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "返回游戏",
		.data = GUI_V_V,
	};

    // 读取配置数据
	struct GUIMenuItem* item;
	for (int i = 0; i < GUIMenuItemListSize(&menu.items); ++i) {
		item = GUIMenuItemListGetPointer(&menu.items, i);
		if (!item->validStates || GUIVariantIsVoid(item->data)) {
			continue;
		}
		if (GUIVariantIsString(item->data)) {
			if (item->stateMappings) {
				size_t j;
				for (j = 0; j < item->nStates; ++j) {
					const struct GUIVariant* v = &item->stateMappings[j];
					struct GUIVariant test;
					switch (v->type) {
					case GUI_VARIANT_VOID:
						if (!mCoreConfigGetValue(&runner->config, item->data.v.s)) {
							item->state = j;
							break;
						}
						break;
					case GUI_VARIANT_UNSIGNED:
						if (mCoreConfigGetUIntValue(&runner->config, item->data.v.s, &test.v.u) && test.v.u == v->v.u) {
							item->state = j;
							break;
						}
						break;
					case GUI_VARIANT_INT:
						if (mCoreConfigGetIntValue(&runner->config, item->data.v.s, &test.v.i) && test.v.i == v->v.i) {
							item->state = j;
							break;
						}
						break;
					case GUI_VARIANT_FLOAT:
						if (mCoreConfigGetFloatValue(&runner->config, item->data.v.s, &test.v.f) && fabsf(test.v.f - v->v.f) <= 1e-3f) {
							item->state = j;
							break;
						}
						break;
					case GUI_VARIANT_STRING:
						test.v.s = mCoreConfigGetValue(&runner->config, item->data.v.s);
						if (test.v.s && strcmp(test.v.s, v->v.s) == 0) {
							item->state = j;
							break;						
						}
						break;
					case GUI_VARIANT_POINTER:
						break;
					}
				}
			} else {
				mCoreConfigGetUIntValue(&runner->config, item->data.v.s, &item->state);
			}
		}
	}






    // UI循环处理按键和UI更新
    while(true){
        struct GUIMenuItem* item;
		enum GUIMenuExitReason reason = GUIShowMenu(&runner->params, &menu, &item);

        if (reason != GUI_MENU_EXIT_ACCEPT || GUIVariantIsVoid(item->data)) {
			break;
		}
        enum BKGUIAction action = (enum BKGUIAction) item->data.v.u;
        switch (action)
        {
        case BK_CONFIG_MAPNAME:
            mGUIShowMapName(runner);
            break;
        case BK_CONFIG_SAVE:
            for (int i = 0; i < GUIMenuItemListSize(&menu.items); ++i) {
                item = GUIMenuItemListGetPointer(&menu.items, i);
				if (!item->validStates || !GUIVariantIsString(item->data)) {
					continue;
				}
                if (item->stateMappings) {
					const struct GUIVariant* v = &item->stateMappings[item->state];
					switch (v->type) {
					case GUI_VARIANT_VOID:
						mCoreConfigSetValue(&runner->config, item->data.v.s, NULL);
						break;
					case GUI_VARIANT_UNSIGNED:
						mCoreConfigSetUIntValue(&runner->config, item->data.v.s, v->v.u);
						break;
					case GUI_VARIANT_INT:
						mCoreConfigSetUIntValue(&runner->config, item->data.v.s, v->v.i);
						break;
					case GUI_VARIANT_FLOAT:
						mCoreConfigSetFloatValue(&runner->config, item->data.v.s, v->v.f);
						break;
					case GUI_VARIANT_STRING:
						mCoreConfigSetValue(&runner->config, item->data.v.s, v->v.s);
						break;
					case GUI_VARIANT_POINTER:
						break;
					}
                }
                else
                {
                    mCoreConfigSetUIntValue(&runner->config, item->data.v.s, item->state);
                }
            }
            // 保存数据变量  mCoreConfigSetIntValue
            mCoreConfigSave(&runner->config);
			mCoreLoadForeignConfig(runner->core, &runner->config);
            break;
        default:
            break;
        }

    }
    GUIMenuItemListDeinit(&menu.items);
}
