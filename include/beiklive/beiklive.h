#ifndef BEIKLIVE_H
#define BEIKLIVE_H

#include <mgba-util/vfs.h>
#include <mgba-util/gui/font.h>
#include <mgba-util/png-io.h>
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include "feature/gui/gui-runner.h"
// ============ 常量定义 ============

// ***********名称映射相关定义
#define BK_ORIGIN_NUM 4616
// 最大配置行长度
#define BK_CONFIG_MAX_LINE_LENGTH 256
// 最大键名长度
#define BK_CONFIG_MAX_KEY_LENGTH 100
// 最大值长度
#define BK_CONFIG_MAX_VALUE_LENGTH 150
// 配置文件路径
#define BK_CONFIG_FILE_PATH "sdmc:/switch/mgba/name_map.cfg"
#define BK_CONFIG_BASE_PATH "sdmc:/switch/mgba"

// 配置项结构体
typedef struct {
    char key[BK_CONFIG_MAX_KEY_LENGTH];
    char value[BK_CONFIG_MAX_VALUE_LENGTH];
} bk_config_item_t;

// ***********名称映射相关定义

// ***** logo 显示相关定义
#define BK_LOGO_BASE_PATH "sdmc:/switch/mgba/logo"
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


// 全局log函数
#define BK_ENABLE_PRINT 1

#if BK_ENABLE_PRINT
    #define BK_LOG(...) printf(__VA_ARGS__)
#else
    #define BK_LOG(...) 
#endif




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



// ============ 文件名处理函数 ============

bool bk_util_is_valid_rom_extension(const char* filename);
char* bk_util_remove_extension(const char* filename);
char* bk_util_get_extension(const char* filename);
char* bk_util_str_concatenate(const char* str1, const char* str2);
char* bk_util_str_concatenate_multiple(int count, ...);



// =======绘图函数
struct VFile* bk_util_open_png(const char* path, int mode);
void _bk_util_draw_game_logo(struct GUIBackground* background, void*  title);

#endif