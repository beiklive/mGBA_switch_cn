
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
    BK_CONFIG_MASK,
    BK_CONFIG_BACKGROUND,
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
        .background = &runner->background.d,
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

// BKMARK 遮罩选单函数
void mGUIShowMaskSet(struct mGUIRunner* runner)
{
    char mask_name_gba[PATH_MAX] = {0};
    char mask_name_gbc[PATH_MAX] = {0};
    struct GUIMenu menu = {
		.title = "遮罩设置",
        .background = &runner->background.d,
		.index = 0
	};
    GUIMenuItemListInit(&menu.items, 0);
    // UI循环处理按键和UI更新
    while(true){
        *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
            .title = "是否启用遮罩",
            .data = GUI_V_S(BK_META_MASK_ENABLE),
            .submenu = 0,
            .state = 0,
            .validStates = (const char*[]) {
                "不启用", "启用"
            },
            .nStates = 2
        };
        // 更新显示文本
        const char* current_gba = mCoreConfigGetValue(&runner->config, BK_META_MASK_GBA);
        const char* current_gbc = mCoreConfigGetValue(&runner->config, BK_META_MASK_GBC);
        
        // 使用缓冲区中的值或配置中的值
        const char* display_gba = mask_name_gba[0] ? mask_name_gba : 
                                 (current_gba && current_gba[0] ? current_gba : "未设置");
        const char* display_gbc = mask_name_gbc[0] ? mask_name_gbc : 
                                 (current_gbc && current_gbc[0] ? current_gbc : "未设置");
        *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
            .title = "选择GBA遮罩",
            .data = GUI_V_S(BK_META_MASK_GBA),
            .leftText = display_gba,
        };
        *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
            .title = "选择GBC遮罩",
            .data = GUI_V_S(BK_META_MASK_GBC),
            .leftText = display_gbc,
        };
        *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
            .title = "保存设置",
            .data = GUI_V_U(BK_CONFIG_SAVE),
        };
        *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
            .title = "返回",
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



		enum GUIMenuExitReason reason = GUIShowMenu(&runner->params, &menu, &item);
        if (reason != GUI_MENU_EXIT_ACCEPT || GUIVariantIsVoid(item->data)) {
            GUIMenuItemListClear(&menu.items);
			break;
		}
        enum BKGUIAction action = (enum BKGUIAction) item->data.v.u;
        if(action == BK_CONFIG_SAVE)
        {
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
			if (mask_name_gba[0]) {
				mCoreConfigSetValue(&runner->config, BK_META_MASK_GBA, mask_name_gba);
                bk_init_mask_texture(mask_name_gba, 0);
			}
			if (mask_name_gbc[0]) {
				mCoreConfigSetValue(&runner->config, BK_META_MASK_GBC, mask_name_gbc);
                bk_init_mask_texture(mask_name_gbc, 1);
			}

            // 保存数据变量  mCoreConfigSetIntValue
            mCoreConfigSave(&runner->config);
			mCoreLoadForeignConfig(runner->core, &runner->config);
            // 清除缓冲区，使用新配置的值
            memset(mask_name_gba, 0, PATH_MAX);
            memset(mask_name_gbc, 0, PATH_MAX);
            GUIShowMessageBox(&runner->params, GUI_MESSAGE_BOX_OK, 240, "保存完成!");
        }else
        {
            if(GUIVariantCompareString(item->data, BK_META_MASK_GBA))
            {
                BK_GLOBAL_INT_SET(BK_META_FOLDER_TARGET, BK_META_FOLDER_TARGET_MASK);
                if (!GUISelectFile(&runner->params, mask_name_gba, sizeof(mask_name_gba), _bk_mask_Extensions, NULL, NULL)) {
                    mask_name_gba[0] = '\0';
                }
            }

            if(GUIVariantCompareString(item->data, BK_META_MASK_GBC))
            {
                BK_GLOBAL_INT_SET(BK_META_FOLDER_TARGET, BK_META_FOLDER_TARGET_MASK);
                if (!GUISelectFile(&runner->params, mask_name_gbc, sizeof(mask_name_gbc), _bk_mask_Extensions, NULL, NULL)) {
                    mask_name_gbc[0] = '\0';
                }
            }
        }
        GUIMenuItemListClear(&menu.items);
    }

    GUIMenuItemListDeinit(&menu.items);
}


void mGUIBackgroundSet(struct mGUIRunner* runner)
{
    char background_name[PATH_MAX] = {0};
    struct GUIMenu menu = {
		.title = "菜单背景图片设置",
        .background = &runner->background.d,
		.index = 0
	};
    GUIMenuItemListInit(&menu.items, 0);
    // UI循环处理按键和UI更新
    while(true){
        *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
            .title = "是否启用背景图片(不启用会使用默认背景)",
            .data = GUI_V_S(BK_META_PATH_BACKGROUND_ENABLE),
            .submenu = 0,
            .state = 0,
            .validStates = (const char*[]) {
                "不启用", "启用"
            },
            .nStates = 2
        };
        const char* current_bg = mCoreConfigGetValue(&runner->config, BK_META_PATH_BACKGROUND);
        
        const char* display_bg = background_name[0] ? background_name : 
                                 (current_bg && current_bg[0] ? current_bg : "未设置");
        // 有背景就拷贝到background_name
        if(current_bg && current_bg[0])
        {
            strlcpy(background_name, current_bg, sizeof(background_name));
        }

        *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
            .title = "选择背景图片",
            .data = GUI_V_S(BK_META_PATH_BACKGROUND),
            .leftText = display_bg,
        };
        *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
            .title = "保存设置",
            .data = GUI_V_U(BK_CONFIG_SAVE),
        };
        *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
            .title = "返回",
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



		enum GUIMenuExitReason reason = GUIShowMenu(&runner->params, &menu, &item);
        if (reason != GUI_MENU_EXIT_ACCEPT || GUIVariantIsVoid(item->data)) {
            GUIMenuItemListClear(&menu.items);
			break;
		}
        enum BKGUIAction action = (enum BKGUIAction) item->data.v.u;
        if(action == BK_CONFIG_SAVE)
        {
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
            int isBgEnabled = 0;
            BK_GLOBAL_INT_GET(BK_META_PATH_BACKGROUND_ENABLE, isBgEnabled);
            printf("isBgEnabled:%d\n", isBgEnabled);

			if (background_name[0]) {
                printf("background_name:%s\n", background_name);
				mCoreConfigSetValue(&runner->config, BK_META_PATH_BACKGROUND, background_name);
                if(isBgEnabled)
                {
                    char* path = bk_util_str_concatenate("sdmc:", background_name);
                    bk_init_menu_background(path);
                    free(path);
                }else{
                    bk_init_menu_background(BK_DEFAULT_LOGO_FILE);
                }
			}else{
                if(!isBgEnabled)
                {
                    bk_init_menu_background(BK_DEFAULT_LOGO_FILE);
                }
            }

            // 保存数据变量  mCoreConfigSetIntValue
            mCoreConfigSave(&runner->config);
			mCoreLoadForeignConfig(runner->core, &runner->config);
            // 清除缓冲区，使用新配置的值
            memset(background_name, 0, PATH_MAX);
            GUIShowMessageBox(&runner->params, GUI_MESSAGE_BOX_OK, 240, "保存完成!");
        }else
        {
            if(GUIVariantCompareString(item->data, BK_META_PATH_BACKGROUND))
            {
                BK_GLOBAL_INT_SET(BK_META_FOLDER_TARGET, BK_META_FOLDER_TARGET_BACKGROUND);
                if (!GUISelectFile(&runner->params, background_name, sizeof(background_name), _bk_mask_Extensions, NULL, NULL)) {
                    background_name[0] = '\0';
                }
            }
        }
        GUIMenuItemListClear(&menu.items);
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
			"原版黑白", "自定义风格"
		},
		.nStates = 2
	};
    *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "遮罩设置",
		.data = GUI_V_U(BK_CONFIG_MASK),
	};
    *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "菜单背景图片设置(仅在自定义风格下有效)",
		.data = GUI_V_U(BK_CONFIG_BACKGROUND),
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
        case BK_CONFIG_MASK:
            mGUIShowMaskSet(runner);
            break;
        case BK_CONFIG_BACKGROUND:
            mGUIBackgroundSet(runner);
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
            GUIShowMessageBox(&runner->params, GUI_MESSAGE_BOX_OK, 240, "保存完成!");
            break;
        default:
            break;
        }

    }
    GUIMenuItemListDeinit(&menu.items);
}
