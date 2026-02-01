#ifndef BEIKLIVE_H
#define BEIKLIVE_H

#include <mgba-util/gui/font.h>
#include <mgba-util/memory.h>
#include <mgba-util/png-io.h>
#include <mgba-util/vfs.h>

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>

#include "feature/gui/gui-runner.h"
#include <setjmp.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>

#include "bk_log.h"
#include "bk_theme.h"
#include "stb_image.h"
// ============ 常量定义 ============
#define BK_GBA_WIDTH 240
#define BK_GBA_HEIGHT 160
#define BK_GBC_WIDTH 160
#define BK_GBC_HEIGHT 144
// 主题相关偏移
#define BK_TITLE_TOP_OFFSET 80
#define BK_TITLE_BOTTOM_OFFSET 75
#define BK_ITEM_PADDING 10

// 颜色处理相关
enum BK_CONFIG_COLOR_TYPE {
	BK_CONFIG_COLOR_BLACK,
	BK_CONFIG_COLOR_WHITE,
	BK_CONFIG_COLOR_RED,
	BK_CONFIG_COLOR_GREEN,
	BK_CONFIG_COLOR_BLUE,
	BK_CONFIG_COLOR_ORANGE,
	BK_CONFIG_COLOR_YELLOW,
	BK_CONFIG_COLOR_GRAY,
	BK_CONFIG_COLOR_MAX
};

#define BK_RGBA_BLACK 0x1F1F1FFF // 黑色
#define BK_RGBA_WHITE 0xFFFFFFFF // 白色
#define BK_RGBA_RED 0xFF0000FF // 红色
#define BK_RGBA_GREEN 0x00FF00FF // 绿色
#define BK_RGBA_BLUE 0x0000FFFF // 蓝色
#define BK_RGBA_ORANGE 0xFF8000FF // 橙色
#define BK_RGBA_YELLOW 0xFFFF00FF // 黄色
#define BK_RGBA_GRAY 0x808080FF // 灰色

#define BK_COLOR_WHITE 0xFFFFFFFF // 不改动， 与初始主题相关

extern uint32_t g_bk_config_color[BK_CONFIG_COLOR_MAX];
extern uint32_t g_bk_color_text_select;
extern uint32_t g_bk_color_text;

#define BK_COLOR_HELPER(color) (_bk_rgba_to_abgr(g_bk_config_color[color]))

#define BK_COLOR_TEXT_SELECT_SET(value) g_bk_color_text_select = BK_COLOR_HELPER(value)
#define BK_COLOR_TEXT_SET(value) g_bk_color_text = BK_COLOR_HELPER(value)

#define BK_COLOR_TEXT_SELECT g_bk_color_text_select
#define BK_COLOR_TEXT g_bk_color_text // 自定义主题 颜色

// ***********名称映射相关定义
#define BK_ORIGIN_NUM 4616
// 最大配置行长度
#define BK_CONFIG_MAX_LINE_LENGTH 256
// 最大键名长度
#define BK_CONFIG_MAX_KEY_LENGTH 100
// 最大值长度
#define BK_CONFIG_MAX_VALUE_LENGTH 150

// 元数据相关变量
// 字符串类型
#define BK_META_FOLDER_TARGET                   "BK.folder.target" // 展开文件列表时的初始文件夹
#define BK_META_MASK_GBA                        "BK.config.mask.gba" // gba遮罩的路径
#define BK_META_MASK_GBC                        "BK.config.mask.gbc" // gbc遮罩的路径
#define BK_META_PATH_BACKGROUND                 "BK.config.path.background" // 背景图片的路径

// 数字类型
#define BK_PRO_STATUS                           "BK.pro.status" // 程序当前状态（列表 菜单  游戏）
#define BK_META_CONFIG_THEME                    "BK.config.theme" // 主题类型
#define BK_META_ISFOLDER                        "BK.isFolderList" // 是否为文件列表
#define BK_META_MASK_ENABLE                     "BK.config.mask.enable" // 是否启用遮罩
#define BK_META_MASK_STATUS_GBA                 "BK.config.mask.status.gba" // gba遮罩状态
#define BK_META_MASK_STATUS_GBC                 "BK.config.mask.status.gbc" // gbc遮罩状态
#define BK_META_PATH_BACKGROUND_ENABLE          "BK.config.path.background.enable" // 是否启用背景图片
#define BK_META_TEXT_COLOR_TYPE                 "BK.text.color.type" // 文本颜色类型
#define BK_META_HOVER_TEXT_COLOR_TYPE           "BK.hover.text.color.type" // 悬停文本颜色类型

// 程序当前状态（列表 菜单  游戏）
enum BK_RUNNING_TYPE {
	BK_RUNNING_TYPE_NONE = 0,
	BK_RUNNING_TYPE_FILELIST,
	BK_RUNNING_TYPE_GAME,
	BK_RUNNING_TYPE_MENU,
	BK_RUNNING_TYPE_MAX
};
// 展开文件列表时的初始文件夹
enum BK_META_FOLDER_TARGET_TYPE {
	BK_META_FOLDER_TARGET_NONE,
	BK_META_FOLDER_TARGET_ROM,
	BK_META_FOLDER_TARGET_BACKGROUND,
	BK_META_FOLDER_TARGET_MASK,
	BK_META_FOLDER_TARGET_MAX
};

// 配置文件路径
#define BK_CONFIG_FILE_PATH "sdmc:/mGBA/name_map.cfg"
#define BK_CONFIG_BASE_PATH "sdmc:/mGBA"
// 配置文件名映射前缀
#define BK_CONFIG_MAPDIR_PREFIX "mgba_dir"

// 配置项结构体
typedef struct {
	char key[BK_CONFIG_MAX_KEY_LENGTH];
	char value[BK_CONFIG_MAX_VALUE_LENGTH];
} bk_config_item_t;

// ***********名称映射相关定义

// ***** logo 显示相关定义
#define BK_DEFAULT_LOGO_FILE            "romfs:/switchbg.png"
#define BK_BACKGROUND_BASE_PATH         "sdmc:/mGBA/backgrounds/"
#define BK_OVERLAY_BASE_PATH            "sdmc:/mGBA/overlays/"
#define BK_SHADER_BASE_PATH             "sdmc:/mGBA/shaders/"
#define BK_BACKGROUND_PATH              "/mGBA/backgrounds/"
#define BK_OVERLAY_PATH                 "/mGBA/overlays/"
#define BK_HOME_PATH                    "/"

// ***** logo 显示相关定义

// ============ 全局变量 ============
// 全局运行器，用于保存配置和beiklive相关状态
extern struct mGUIRunner* bk_global_runner;

// 工具函数宏定义

// ** 元数据函数
#define BK_GLOBAL_INT_SET(name, value)                                  \
	do {                                                                \
		mCoreConfigSetIntValue(&bk_global_runner->config, name, value); \
	} while (0)

#define BK_GLOBAL_INT_GET(name, outVar)                                     \
	do {                                                                    \
		mCoreConfigGetIntValue(&bk_global_runner->config, name, &(outVar)); \
	} while (0)

// ============ 初始化与清理函数 ============
bool bk_config_init(void);
void bk_config_cleanup(void);
bool bk_config_reload(void);

// ============ 核心操作函数 ============
char* bk_config_get(const char* key);
bool bk_config_set(const char* key, const char* value);
bool bk_config_add(const char* key, const char* value);
bool bk_config_remove(const char* key);

// ============ 批量操作函数 ============
bk_config_item_t* bk_config_get_all(int* count);
bool bk_config_clear(void);
bool bk_config_set_batch(const bk_config_item_t* items, int count);

// ============ 工具函数 ============
bool bk_config_exists(const char* key);
const char* bk_config_get_or_default(const char* key, const char* default_value);
int bk_config_count(void);
char* bk_config_export_to_string(void);
bool bk_config_import_from_string(const char* config_str);
const bk_config_item_t* bk_config_get_internal_cache(void);
uint32_t bk_util_normalize_cn_symbol(uint32_t u);

// ============ 文件名处理函数 ============
bool bk_util_has_mgba_dir_prefix(const char* str);
char* bk_util_remove_trailing_slash_copy(const char* str);
bool bk_util_is_valid_rom_extension(const char* filename);
char* bk_util_remove_extension(const char* filename);
char* bk_util_get_extension(const char* filename);
char* bk_util_str_concatenate(const char* str1, const char* str2);
char* bk_util_str_concatenate_multiple(int count, ...);
bool _bk_mask_Extensions(const char* name);

// =======绘图函数
struct VFile* bk_util_open_png(const char* path, int mode);
void _bk_util_draw_menu_background(struct GUIBackground* background, void* title);
float bk_calc_insize(unsigned realSize);
uint32_t calculate_hash(const void* data, size_t length);
uint32_t _bk_rgba_to_abgr(uint32_t rgba);
uint32_t _bk_getBatteryColor(int batteryLevel);

// oopengl 相关函数
// 背景纹理类型
enum BKGL_TYPE {
	BK_NONE = 0, // 无
	BK_WINDOW, // 窗口背景
	BK_LOGO, // logo背景
	BK_MASK, // 遮罩背景
	BK_MAX
};

extern GLuint bkTex;
extern GLuint bkMaskTexGBA;
extern GLuint bkMaskTexGBC;
extern GLuint bkProgram;
extern GLuint bktexLocation; // 纹理uniform位置
extern GLuint bkdimsLocation; // 尺寸uniform位置
extern GLuint bkinsizeLocation; // 输入大小uniform位置
extern GLuint bkcolorLocation; // 颜色uniform位置
extern GLuint bkvbo; // 顶点缓冲对象
extern GLuint bkvao; // 顶点数组对象

bool bk_opengl_init(void);
void bk_opengl_deinit(void);
void bk_init_mask_texture(const char* filepath, int maskType);
int bk_init_menu_background(const char* filepath);

// +++++++++++++++++++shader相关定义++++++++++++++++++++++++++++++






// ============================================ gles2 着色器参数结构体



// ============================================fbo相关定义

typedef struct {
	GLuint texture; // 纹理
	GLuint fbo; // 绘制到fbo的纹理
	GLuint program; // 着色器程序
	int width; // FBO宽度
	int height; // FBO高度
	bool is_enable; // 当前是否绑定
} bk_FrameBufferObject_t;

extern GLuint bkfbo;
extern GLuint bkfboTex;

extern GLuint bkfboVao;
extern GLuint bkfboVbo;

extern GLuint bkShaderProgram;

extern bool useFBO;

void bk_init_fbo(int width, int height);
void bk_switch_to_fbo(bool enable);
void bk_render_fbo(GLuint* texture, int width, int height);
void bk_deinit_fbo(void);

#endif