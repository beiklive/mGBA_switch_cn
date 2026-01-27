#ifndef BEIKLIVE_H
#define BEIKLIVE_H

#include <mgba-util/vfs.h>
#include <mgba-util/gui/font.h>
#include <mgba-util/png-io.h>
#include <mgba-util/memory.h>

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>


#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <time.h>
#include "feature/gui/gui-runner.h"


#include "bk_log.h"
#include "bk_theme.h"
#include "stb_image.h"
// ============ 常量定义 ============

#define BK_TITLE_TOP_OFFSET 80
#define BK_TITLE_BOTTOM_OFFSET 75
#define BK_ITEM_PADDING 10

// 颜色
#define BK_COLOR_BLACK 0xFF1F1F1F
#define BK_COLOR_WHITE 0xFFFFFFFF
#define BK_COLOR_BLUE  0xFFf00505



// ***********名称映射相关定义
#define BK_ORIGIN_NUM 4616
// 最大配置行长度
#define BK_CONFIG_MAX_LINE_LENGTH 256
// 最大键名长度
#define BK_CONFIG_MAX_KEY_LENGTH 100
// 最大值长度
#define BK_CONFIG_MAX_VALUE_LENGTH 150


// 元数据相关变量
#define BK_PRO_STATUS               "BK.pro.status"
#define BK_META_CONFIG_THEME        "BK.config.theme" 
#define BK_META_ISFOLDER            "BK.isFolderList"
#define BK_META_FOLDER_TARGET       "BK.folder.target"   // 目标文件夹
#define BK_META_MASK_ENABLE         "BK.config.mask.enable"
#define BK_META_MASK_STATUS_GBA         "BK.config.mask.status.gba"
#define BK_META_MASK_STATUS_GBC         "BK.config.mask.status.gbc"
#define BK_META_MASK_GBA            "BK.config.mask.gba"
#define BK_META_MASK_GBC            "BK.config.mask.gbc"
#define BK_META_PATH_BACKGROUND_ENABLE     "BK.config.path.background.enable"
#define BK_META_PATH_BACKGROUND     "BK.config.path.background"


enum BK_RUNNING_TYPE {
    BK_RUNNING_TYPE_NONE = 0,
    BK_RUNNING_TYPE_FILELIST,
    BK_RUNNING_TYPE_GAME,
    BK_RUNNING_TYPE_MENU,
    BK_RUNNING_TYPE_MAX
};

enum BK_META_FOLDER_TARGET_TYPE {
    BK_META_FOLDER_TARGET_NONE,
    BK_META_FOLDER_TARGET_ROM,
    BK_META_FOLDER_TARGET_BACKGROUND,
    BK_META_FOLDER_TARGET_MASK,
    BK_META_FOLDER_TARGET_MAX
};








// 配置文件路径
#define BK_CONFIG_FILE_PATH "sdmc:/switch/mgba/name_map.cfg"
#define BK_CONFIG_BASE_PATH "sdmc:/switch/mgba"
#define BK_CONFIG_MAPDIR_PREFIX "mgba_dir"

// 配置项结构体
typedef struct {
    char key[BK_CONFIG_MAX_KEY_LENGTH];
    char value[BK_CONFIG_MAX_VALUE_LENGTH];
} bk_config_item_t;

// ***********名称映射相关定义

// ***** logo 显示相关定义
#define BK_DEFAULT_LOGO_FILE "romfs:/switchbg.png"
#define BK_BACKGROUND_BASE_PATH "sdmc:/switch/mgba/backgrounds/"
#define BK_BACKGROUND_PATH "/switch/mgba/backgrounds/"
#define BK_OVERLAY_BASE_PATH "sdmc:/switch/mgba/overlays/"
#define BK_OVERLAY_PATH "/switch/mgba/overlays/"
#define BK_HOME_PATH "/"

// ***** logo 显示相关定义



// ============ 全局变量 ============
// 全局运行器，用于保存配置和beiklive相关状态
extern struct mGUIRunner* bk_global_runner;




// 工具函数宏定义

// ** 元数据函数
#define BK_GLOBAL_INT_SET(name, value) \
    do { \
        mCoreConfigSetIntValue(&bk_global_runner->config, name, value); \
    } while(0)


#define BK_GLOBAL_INT_GET(name, outVar) \
    do { \
        mCoreConfigGetIntValue(&bk_global_runner->config, name, &(outVar)); \
    } while(0)








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
void _bk_util_draw_menu_background(struct GUIBackground* background, void*  title);
float bk_calc_insize(unsigned realSize);
uint32_t calculate_hash(const void* data, size_t length);


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
extern GLuint bktexLocation;         // 纹理uniform位置
extern GLuint bkdimsLocation;        // 尺寸uniform位置
extern GLuint bkinsizeLocation;      // 输入大小uniform位置
extern GLuint bkcolorLocation;       // 颜色uniform位置
extern GLuint bkvbo;                 // 顶点缓冲对象
extern GLuint bkvao;                 // 顶点数组对象

bool bk_opengl_init(void);
void bk_opengl_deinit(void);
void bk_init_mask_texture(const char* filepath, int maskType);
int bk_init_menu_background(const char* filepath);



#endif