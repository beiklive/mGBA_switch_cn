
#include "gui-beiklive.h"

#include "feature/gui/gui-runner.h"
#include "feature/gui/remap.h"
#include <mgba/core/config.h>
#include <mgba/core/core.h>
#include <mgba/internal/gba/gba.h>
#ifdef M_CORE_GB
#include <mgba/internal/gb/gb.h>
#include <mgba/internal/gb/overrides.h>
#endif
#include <mgba-util/gui/file-select.h>
#include <mgba-util/gui/menu.h>
#include <mgba-util/vfs.h>

#include <beiklive/beiklive.h>

enum BKGUIAction {
	BK_CONFIG_STATUS_1,
	BK_CONFIG_STATUS_2,
	BK_CONFIG_STATUS_3,
	BK_CONFIG_STATUS_4,
	BK_CONFIG_MAPNAME,
	BK_CONFIG_MASK,
	BK_CONFIG_SHADER,
	BK_CONFIG_SCREEN,
	BK_CONFIG_UNIFORM,
	BK_CONFIG_BACKGROUND,
	BK_CONFIG_REWIND,
	BK_CONFIG_SAVE
};

static void ReadStateConfig(struct GUIMenu* menu, struct mGUIRunner* runner) {
	// 读取配置数据
	struct GUIMenuItem* item;
	for (int i = 0; i < GUIMenuItemListSize(&menu->items); ++i) {
		item = GUIMenuItemListGetPointer(&menu->items, i);
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
						if (mCoreConfigGetFloatValue(&runner->config, item->data.v.s, &test.v.f) &&
						    fabsf(test.v.f - v->v.f) <= 1e-3f) {
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
		if (item->id == 4616) {
			item->state = bk_global_shader_index + 1;
		}
        if(item->id == 4617)
        {   // 防止底座掌机切换导致最大比例变化
            if(item->state > item->nStates - 1)
            {
                item->state = item->nStates - 1;
            }
        }
	}
}

void mGUIRewindSet(struct mGUIRunner* runner) {
	struct GUIMenu menu = { .title = "倒带设置",
		                    .background = &runner->background.d,
		                    .index = 0 };
	GUIMenuItemListInit(&menu.items, 0);
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) { 
		.title = "是否启用倒带功能",
		.data = GUI_V_S(BK_META_REWIND_ENABLE),
		.submenu = 0,
		.state = 0,
		.validStates = (const char*[]) { "不启用", "启用" },
		.nStates = 2 
	};
	// 倒带缓冲区大小
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "倒带缓冲区大小",
		.data = GUI_V_S(BK_META_REWIND_BUFFER_SIZE),
		.submenu = 0,
		.state = 0,
		.validStates = (const char*[]) { "60帧", "120帧", "180帧", "300帧", "600帧", "900帧", "1800帧", "3600帧"},
		.stateMappings = (const struct GUIVariant[]) { GUI_V_U(60), GUI_V_U(120), GUI_V_U(180),
		                                              GUI_V_U(300), GUI_V_U(600), GUI_V_U(900),
		                                              GUI_V_U(1800), GUI_V_U(3600) },
		.nStates = 8
	};
	// 倒带保存间隔
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "倒带保存间隔",
		.data = GUI_V_S(BK_META_REWIND_SAVE_INTERVAL),
		.submenu = 0,
		.state = 0,
		.validStates = (const char*[]) { "每1帧", "每2帧", "每3帧", "每5帧", "每10帧", "每30帧"},
		.stateMappings = (const struct GUIVariant[]) { GUI_V_U(1), GUI_V_U(2), GUI_V_U(3),
		                                              GUI_V_U(5), GUI_V_U(10), GUI_V_U(30) },
		.nStates = 6
	};
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) { 
		.title = "倒带时静音",
		.data = GUI_V_S(BK_META_REWIND_MUTE_ENABLE),
		.submenu = 0,
		.state = 0,
		.validStates = (const char*[]) { "不启用", "启用" },
		.nStates = 2 
	};
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "保存修改",
		.data = GUI_V_U(BK_CONFIG_SAVE),
	};
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "返回",
		.data = GUI_V_V,
	};
	ReadStateConfig(&menu, runner);
	while (true) {
		struct GUIMenuItem* item;
		enum GUIMenuExitReason reason = GUIShowMenu(&runner->params, &menu, &item);

		if (reason != GUI_MENU_EXIT_ACCEPT || GUIVariantIsVoid(item->data)) {
			GUIMenuItemListClear(&menu.items);
			break;
		}
		enum BKGUIAction action = (enum BKGUIAction) item->data.v.u;
		if (action == BK_CONFIG_SAVE) {
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
				} else {
					mCoreConfigSetUIntValue(&runner->config, item->data.v.s, item->state);
				}
			}
			mCoreConfigSave(&runner->config);
			mCoreLoadForeignConfig(runner->core, &runner->config);
			GUIShowMessageBox(&runner->params, GUI_MESSAGE_BOX_OK, 240, "保存完成!");
			break;
		}
	}
	GUIMenuItemListDeinit(&menu.items);

}
void mGUIScreenSet(struct mGUIRunner* runner) {
	struct GUIMenu menu = { .title = "画面相关参数设置",
		                    .background = &runner->background.d,
		                    .index = 0 };
	GUIMenuItemListInit(&menu.items, 0);

	int max = bk_getMaxAspectRatio();
	char** RatioNames = malloc(sizeof(const char*) * max);

	const char** validStates = malloc(sizeof(const char*) * max);
	struct GUIVariant* stateMappings = malloc(sizeof(struct GUIVariant) * max);

	for (int i = 0; i < max; i++) {
		char* stateText = malloc(8);
		snprintf(stateText, 8, "x%d", i + 1);
		validStates[i] = stateText;
		// 设置对应的数值映射
		stateMappings[i] = GUI_V_U(i + 1);
	}
    if(runner->core->platform(runner->core) == 0)
    {
        *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) { .title = "画面放大倍数(仅整数缩放生效)",
                                                                     .data = GUI_V_S(BK_META_GBA_ASPECT_RATIO),
                                                                     .submenu = 0,
                                                                     .state = max - 1,
                                                                     .validStates = validStates, // 使用动态分配的数组
                                                                     .stateMappings = stateMappings, // 使用动态分配的数组
                                                                     .nStates = max,
                                                                     .id = 4617
                                                                    };
    }
    else
    {
        *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) { .title = "画面放大倍数(仅整数缩放生效)",
                                                                     .data = GUI_V_S(BK_META_GBC_ASPECT_RATIO),
                                                                     .submenu = 0,
                                                                     .state = max - 1,
                                                                     .validStates = validStates, // 使用动态分配的数组
                                                                     .stateMappings = stateMappings, // 使用动态分配的数组
                                                                     .nStates = max,
                                                                     .id = 4617
                                                                    };
    }

	*GUIMenuItemListAppend(&menu.items) =
	    (struct GUIMenuItem) { .title = "画面亮度",
		                       .data = GUI_V_S(BK_META_SCREEN_BRIGHTNESS),
		                       .submenu = 0,
		                       .state = 4,
		                       .validStates = (const char*[]) { "1", "2", "3", "4", "5", "6", "7", "8", "9" },
		                       .stateMappings = (const struct GUIVariant[]) { GUI_V_U(1), GUI_V_U(2), GUI_V_U(3),
		                                                                      GUI_V_U(4), GUI_V_U(5), GUI_V_U(6),
		                                                                      GUI_V_U(7), GUI_V_U(8), GUI_V_U(9) },
		                       .nStates = 9 };
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "保存修改",
		.data = GUI_V_U(BK_CONFIG_SAVE),
	};
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "返回",
		.data = GUI_V_V,
	};
	ReadStateConfig(&menu, runner);

	while (true) {
		struct GUIMenuItem* item;
		enum GUIMenuExitReason reason = GUIShowMenu(&runner->params, &menu, &item);

		if (reason != GUI_MENU_EXIT_ACCEPT || GUIVariantIsVoid(item->data)) {
			GUIMenuItemListClear(&menu.items);
			break;
		}
		enum BKGUIAction action = (enum BKGUIAction) item->data.v.u;
		if (action == BK_CONFIG_SAVE) {
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
				} else {
					mCoreConfigSetUIntValue(&runner->config, item->data.v.s, item->state);
				}
			}
			mCoreConfigSave(&runner->config);
			mCoreLoadForeignConfig(runner->core, &runner->config);
			GUIShowMessageBox(&runner->params, GUI_MESSAGE_BOX_OK, 240, "保存完成!");
			break;
		}
	}
	GUIMenuItemListDeinit(&menu.items);

}

void mGUIUniformSet(struct mGUIRunner* runner, int ShaderIndex) {
	if (!runner || ShaderIndex <= 0) {
		return;
	}

	struct BKVideoShader* shader = bk_global_shaders->shaders[ShaderIndex - 1];
	if (!shader) {
		return;
	}

	struct GUIMenu menu = {
		.title = "滤镜参数设置(有需要再改)", .subtitle = shader->name, .background = &runner->background.d, .index = 0
	};
	GUIMenuItemListInit(&menu.items, 0);

	struct mBKGLES2Shader* passes = (struct mBKGLES2Shader*) shader->passes;

	for (size_t p = 0; p < shader->nPasses; ++p) {
		struct mBKGLES2Shader* pass = &passes[p];
		if (!pass->uniforms || pass->nUniforms == 0) {
			continue;
		}

		for (size_t u = 0; u < pass->nUniforms; ++u) {
			struct mBKGLES2Uniform* uniform = &pass->uniforms[u];
			ApplyUniform(uniform);
			char* title = malloc(128);
			char* valueStr = malloc(64);
			const char* name = uniform->readableName ? uniform->readableName : uniform->name;
			snprintf(title, 128, "%s", name);
			UniformValueToString(uniform, valueStr, 64);

			*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
				.title = title,
				.leftText = valueStr,
				.data = GUI_V_U(BK_CONFIG_UNIFORM | (u << 16)),
			};
		}
	}

	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "保存设置",
		.data = GUI_V_U(BK_CONFIG_SAVE),
	};
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "返回",
		.data = GUI_V_V,
	};

	while (true) {
		struct GUIMenuItem* item;
		enum GUIMenuExitReason reason = GUIShowMenu(&runner->params, &menu, &item);

		if (reason != GUI_MENU_EXIT_ACCEPT || GUIVariantIsVoid(item->data)) {
			GUIMenuItemListClear(&menu.items);
			break;
		}
		enum BKGUIAction action = (enum BKGUIAction) item->data.v.u;
	}

	GUIMenuItemListDeinit(&menu.items);
}

void mGUIShaderSet(struct mGUIRunner* runner) {
	struct GUIMenu menu = { .title = "滤镜设置", .background = &runner->background.d, .index = 0 };
	GUIMenuItemListInit(&menu.items, 0);

	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) { .title = "是否启用滤镜功能",
		                                                         .data = GUI_V_S(BK_META_SHADER_ENABLE),
		                                                         .submenu = 0,
		                                                         .state = 0,
		                                                         .validStates = (const char*[]) { "不启用", "启用" },
		                                                         .nStates = 2 };

	int shaderCount = bk_shader_get_count();
	char** shaderNames = bk_shader_get_names();

	int total = shaderCount + 1;
	const char** names = malloc(sizeof(const char*) * total);
	if (!names) {
		return;
	}
	names[0] = "无滤镜";
	for (int i = 0; i < shaderCount; i++) {
		names[i + 1] = shaderNames[i];
	}
	free(shaderNames);

	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) { .title = "选择滤镜",
		                                                         .data = GUI_V_S(BK_META_SHADER_INDEX),
		                                                         .submenu = 0,
		                                                         .state = 0,
		                                                         .id = 4616,
		                                                         .validStates = names,
		                                                         .nStates = total };

    // BKTODO 暂时移除
	// *GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
	// 	.title = "滤镜参数设置(有需要再改)",
	// 	.data = GUI_V_U(BK_CONFIG_STATUS_1),
	// };

	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "保存设置",
		.data = GUI_V_U(BK_CONFIG_SAVE),
	};
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "返回",
		.data = GUI_V_V,
	};

	ReadStateConfig(&menu, runner);
	while (true) {
		struct GUIMenuItem* item;
		enum GUIMenuExitReason reason = GUIShowMenu(&runner->params, &menu, &item);

		if (reason != GUI_MENU_EXIT_ACCEPT || GUIVariantIsVoid(item->data)) {
			GUIMenuItemListClear(&menu.items);
			break;
		}
		enum BKGUIAction action = (enum BKGUIAction) item->data.v.u;
		if (action == BK_CONFIG_SAVE) {
			for (int i = 0; i < GUIMenuItemListSize(&menu.items); ++i) {
				item = GUIMenuItemListGetPointer(&menu.items, i);
				if (!item->validStates || !GUIVariantIsString(item->data)) {
					continue;
				}
				// 保存滤镜配置
				if (item->id == 4616) {
					if (item->state == 0) // 未选择滤镜保存
					{
						mCoreConfigSetValue(&runner->config, BK_META_SHADER_NAME, "no");
						bk_global_shader_index = -1;
					} else {
						mCoreConfigSetValue(&runner->config, BK_META_SHADER_NAME,
						                    bk_global_shaders->shaders[item->state - 1]->name);
						bk_global_shader_index = item->state - 1;
					}
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
				} else {
					mCoreConfigSetUIntValue(&runner->config, item->data.v.s, item->state);
				}
			}
			mCoreConfigSave(&runner->config);
			mCoreLoadForeignConfig(runner->core, &runner->config);
			// 初始化滤镜和fbo缓冲尺寸
			int isShaderEnabled = 0;
			BK_GLOBAL_INT_GET(BK_META_SHADER_ENABLE, isShaderEnabled);
			if (isShaderEnabled && (bk_global_shaders == NULL)) {
				bk_shader_list_init();
			}
			bk_init_fbo(g_game_width, g_game_height);
			GUIShowMessageBox(&runner->params, GUI_MESSAGE_BOX_OK, 240, "保存完成!");
			break;
		} else if (action == BK_CONFIG_STATUS_1) {
			for (int i = 0; i < GUIMenuItemListSize(&menu.items); ++i) {
				item = GUIMenuItemListGetPointer(&menu.items, i);
				if (!item->validStates || !GUIVariantIsString(item->data)) {
					continue;
				}
				if (item->id == 4616) {
					// 选择滤镜
					int index = item->state;
					if (index == 0) {
						GUIShowMessageBox(&runner->params, GUI_MESSAGE_BOX_OK, 240, "先选择滤镜再设置参数!");
					} else {
						mGUIUniformSet(runner, index);
					}
				}
			}
		} else {
			break;
		}
		GUIMenuItemListClear(&menu.items);
	}

	GUIMenuItemListDeinit(&menu.items);
	free(names);
}

// 名称映射相关功能
void mGUIShowMapName(struct mGUIRunner* runner) {
	char* gameName = runner->core->dirs.baseName;
	char* mapped_name = NULL;
	char* gameName_title = NULL;
	char* mapped_name_title = NULL;

	struct GUIMenu menu = { .title = "游戏名称映射", .background = &runner->background.d, .index = 0 };
	GUIMenuItemListInit(&menu.items, 0);

	// UI循环处理按键和UI更新
	while (true) {
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
		switch (action) {
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
				if (bk_config_remove(gameName)) {
					GUIShowMessageBox(&runner->params, GUI_MESSAGE_BOX_OK, 240, "映射删除成功!");
				}
			}
			break;
		case BK_CONFIG_STATUS_3:
			printf("删除映射(所有游戏)\n");
			{
				if (bk_config_clear()) {
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
void mGUIShowMaskSet(struct mGUIRunner* runner) {
	char mask_name_gba[PATH_MAX] = { 0 };
	char mask_name_gbc[PATH_MAX] = { 0 };
	struct GUIMenu menu = { .title = "遮罩设置", .background = &runner->background.d, .index = 0 };
	GUIMenuItemListInit(&menu.items, 0);
	// UI循环处理按键和UI更新
	while (true) {
		*GUIMenuItemListAppend(&menu.items) =
		    (struct GUIMenuItem) { .title = "是否启用遮罩",
			                       .data = GUI_V_S(BK_META_MASK_ENABLE),
			                       .submenu = 0,
			                       .state = 0,
			                       .validStates = (const char*[]) { "不启用", "启用" },
			                       .nStates = 2 };
		// 更新显示文本
		const char* current_gba = mCoreConfigGetValue(&runner->config, BK_META_MASK_GBA);
		const char* current_gbc = mCoreConfigGetValue(&runner->config, BK_META_MASK_GBC);

		// 使用缓冲区中的值或配置中的值
		const char* display_gba =
		    mask_name_gba[0] ? mask_name_gba : (current_gba && current_gba[0] ? current_gba : "未设置");
		const char* display_gbc =
		    mask_name_gbc[0] ? mask_name_gbc : (current_gbc && current_gbc[0] ? current_gbc : "未设置");
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
		ReadStateConfig(&menu, runner);

		struct GUIMenuItem* item;

		enum GUIMenuExitReason reason = GUIShowMenu(&runner->params, &menu, &item);
		if (reason != GUI_MENU_EXIT_ACCEPT || GUIVariantIsVoid(item->data)) {
			GUIMenuItemListClear(&menu.items);
			break;
		}
		enum BKGUIAction action = (enum BKGUIAction) item->data.v.u;
		if (action == BK_CONFIG_SAVE) {
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
				} else {
					mCoreConfigSetUIntValue(&runner->config, item->data.v.s, item->state);
				}
			}
			if (mask_name_gba[0]) {
				mCoreConfigSetValue(&runner->config, BK_META_MASK_GBA, mask_name_gba);
				bk_init_mask_texture(mask_name_gba, 0);
                g_gba_video_offset_y = bk_Mask_OffsetRead(mask_name_gba);
			}
			if (mask_name_gbc[0]) {
				mCoreConfigSetValue(&runner->config, BK_META_MASK_GBC, mask_name_gbc);
				bk_init_mask_texture(mask_name_gbc, 1);
                g_gbc_video_offset_y = bk_Mask_OffsetRead(mask_name_gbc);
			}

			// 保存数据变量  mCoreConfigSetIntValue
			mCoreConfigSave(&runner->config);
			mCoreLoadForeignConfig(runner->core, &runner->config);
			// 清除缓冲区，使用新配置的值
			memset(mask_name_gba, 0, PATH_MAX);
			memset(mask_name_gbc, 0, PATH_MAX);
			GUIShowMessageBox(&runner->params, GUI_MESSAGE_BOX_OK, 240, "保存完成!");
		} else {
			if (GUIVariantCompareString(item->data, BK_META_MASK_GBA)) {
				BK_GLOBAL_INT_SET(BK_META_FOLDER_TARGET, BK_META_FOLDER_TARGET_MASK);
				if (!GUISelectFile(&runner->params, mask_name_gba, sizeof(mask_name_gba), _bk_mask_Extensions, NULL,
				                   NULL)) {
					mask_name_gba[0] = '\0';
				}
			}

			if (GUIVariantCompareString(item->data, BK_META_MASK_GBC)) {
				BK_GLOBAL_INT_SET(BK_META_FOLDER_TARGET, BK_META_FOLDER_TARGET_MASK);
				if (!GUISelectFile(&runner->params, mask_name_gbc, sizeof(mask_name_gbc), _bk_mask_Extensions, NULL,
				                   NULL)) {
					mask_name_gbc[0] = '\0';
				}
			}
		}
		GUIMenuItemListClear(&menu.items);
	}

	GUIMenuItemListDeinit(&menu.items);
}

void mGUIBackgroundSet(struct mGUIRunner* runner) {
	char background_name[PATH_MAX] = { 0 };
	struct GUIMenu menu = { .title = "主题设置", .background = &runner->background.d, .index = 0 };
	GUIMenuItemListInit(&menu.items, 0);
	// UI循环处理按键和UI更新
	while (true) {
		*GUIMenuItemListAppend(&menu.items) =
		    (struct GUIMenuItem) { .title = "是否启用背景图片(不启用会使用默认背景)",
			                       .data = GUI_V_S(BK_META_PATH_BACKGROUND_ENABLE),
			                       .submenu = 0,
			                       .state = 0,
			                       .validStates = (const char*[]) { "不启用", "启用" },
			                       .nStates = 2 };
		const char* current_bg = mCoreConfigGetValue(&runner->config, BK_META_PATH_BACKGROUND);

		const char* display_bg =
		    background_name[0] ? background_name : (current_bg && current_bg[0] ? current_bg : "未设置");
		// 有背景就拷贝到background_name
		if (!background_name[0] && current_bg && current_bg[0]) {
			strlcpy(background_name, current_bg, sizeof(background_name));
		}

		*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
			.title = "选择背景图片",
			.data = GUI_V_S(BK_META_PATH_BACKGROUND),
			.leftText = display_bg,
		};
		*GUIMenuItemListAppend(&menu.items) =
		    (struct GUIMenuItem) { .title = "文字颜色",
			                       .data = GUI_V_S(BK_META_TEXT_COLOR_TYPE),
			                       .submenu = 0,
			                       .state = 0,
			                       .validStates = (const char*[]) { "黑色", "白色", "红色", "绿色", "蓝色", "橙色",
			                                                        "黄色", "灰色" },
			                       .nStates = BK_CONFIG_COLOR_MAX };
		*GUIMenuItemListAppend(&menu.items) =
		    (struct GUIMenuItem) { .title = "文字选中色",
			                       .data = GUI_V_S(BK_META_HOVER_TEXT_COLOR_TYPE),
			                       .submenu = 0,
			                       .state = 0,
			                       .validStates = (const char*[]) { "黑色", "白色", "红色", "绿色", "蓝色", "橙色",
			                                                        "黄色", "灰色" },
			                       .nStates = BK_CONFIG_COLOR_MAX };
		*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
			.title = "保存设置",
			.data = GUI_V_U(BK_CONFIG_SAVE),
		};
		*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
			.title = "返回",
			.data = GUI_V_V,
		};

		ReadStateConfig(&menu, runner);

		struct GUIMenuItem* item;

		enum GUIMenuExitReason reason = GUIShowMenu(&runner->params, &menu, &item);
		if (reason != GUI_MENU_EXIT_ACCEPT || GUIVariantIsVoid(item->data)) {
			GUIMenuItemListClear(&menu.items);
			break;
		}
		enum BKGUIAction action = (enum BKGUIAction) item->data.v.u;
		if (action == BK_CONFIG_SAVE) {
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
				} else {
					mCoreConfigSetUIntValue(&runner->config, item->data.v.s, item->state);
				}
			}
			int isBgEnabled = 0;
			BK_GLOBAL_INT_GET(BK_META_PATH_BACKGROUND_ENABLE, isBgEnabled);

			if (background_name[0]) {
				mCoreConfigSetValue(&runner->config, BK_META_PATH_BACKGROUND, background_name);
				if (isBgEnabled) {
					char* path = bk_util_str_concatenate("sdmc:", background_name);
					bk_init_menu_background(path);
					free(path);
				} else {
					bk_init_menu_background(BK_DEFAULT_LOGO_FILE);
				}
			} else {
				if (!isBgEnabled) {
					bk_init_menu_background(BK_DEFAULT_LOGO_FILE);
				}
			}

			// 保存数据变量  mCoreConfigSetIntValue
			mCoreConfigSave(&runner->config);
			mCoreLoadForeignConfig(runner->core, &runner->config);

			int colorType = 0;
			BK_GLOBAL_INT_GET(BK_META_TEXT_COLOR_TYPE, colorType);
			BK_COLOR_TEXT_SET(colorType);
			int hoverColorType = 0;
			BK_GLOBAL_INT_GET(BK_META_HOVER_TEXT_COLOR_TYPE, hoverColorType);
			BK_COLOR_TEXT_SELECT_SET(hoverColorType);

			// 清除缓冲区，使用新配置的值
			memset(background_name, 0, PATH_MAX);
			GUIShowMessageBox(&runner->params, GUI_MESSAGE_BOX_OK, 240, "保存完成!");
		} else {
			if (GUIVariantCompareString(item->data, BK_META_PATH_BACKGROUND)) {
				BK_GLOBAL_INT_SET(BK_META_FOLDER_TARGET, BK_META_FOLDER_TARGET_BACKGROUND);
				if (!GUISelectFile(&runner->params, background_name, sizeof(background_name), _bk_mask_Extensions, NULL,
				                   NULL)) {
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
		.title = "魔改功能", .subtitle = "beiklive制作", .index = 0, .background = &runner->background.d
	};
	GUIMenuItemListInit(&menu.items, 0);

	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "游戏名称映射",
		.data = GUI_V_U(BK_CONFIG_MAPNAME),
	};
	*GUIMenuItemListAppend(&menu.items) =
	    (struct GUIMenuItem) { .title = "主题选择",
		                       .data = GUI_V_S(BK_META_CONFIG_THEME),
		                       .submenu = 0,
		                       .state = 0,
		                       .validStates = (const char*[]) { "原版黑白", "自定义风格" },
		                       .nStates = 2 };
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "主题设置(仅在自定义风格下有效)",
		.data = GUI_V_U(BK_CONFIG_BACKGROUND),
	};
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "遮罩设置",
		.data = GUI_V_U(BK_CONFIG_MASK),
	};
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "滤镜设置(整数缩放下效果最佳)",
		.data = GUI_V_U(BK_CONFIG_SHADER),
	};
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "画面设置",
		.data = GUI_V_U(BK_CONFIG_SCREEN),
	};
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "倒带设置",
		.data = GUI_V_U(BK_CONFIG_REWIND),
	};
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "保存修改",
		.data = GUI_V_U(BK_CONFIG_SAVE),
	};
	*GUIMenuItemListAppend(&menu.items) = (struct GUIMenuItem) {
		.title = "返回游戏",
		.data = GUI_V_V,
	};

	// 读取配置数据
	ReadStateConfig(&menu, runner);

	struct GUIMenuItem* item;

	// UI循环处理按键和UI更新
	while (true) {
		struct GUIMenuItem* item;
		enum GUIMenuExitReason reason = GUIShowMenu(&runner->params, &menu, &item);

		if (reason != GUI_MENU_EXIT_ACCEPT || GUIVariantIsVoid(item->data)) {
			break;
		}
		enum BKGUIAction action = (enum BKGUIAction) item->data.v.u;
		switch (action) {
		case BK_CONFIG_MAPNAME:
			mGUIShowMapName(runner);
			break;
		case BK_CONFIG_MASK:
			mGUIShowMaskSet(runner);
			break;
		case BK_CONFIG_BACKGROUND:
			mGUIBackgroundSet(runner);
			break;
		case BK_CONFIG_SHADER:
			mGUIShaderSet(runner);
			break;
		case BK_CONFIG_REWIND:
			mGUIRewindSet(runner);
			break;
		case BK_CONFIG_SCREEN:
			mGUIScreenSet(runner);
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
				} else {
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
