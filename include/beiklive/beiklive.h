#ifndef BEIKLIVE_H
#define BEIKLIVE_H

#include <mgba-util/vfs.h>
#include <stdbool.h>

// ============ 常量定义 ============

#define BK_ORIGIN_NUM 4616
// 最大配置行长度
#define BK_CONFIG_MAX_LINE_LENGTH 256
// 最大键名长度
#define BK_CONFIG_MAX_KEY_LENGTH 100
// 最大值长度
#define BK_CONFIG_MAX_VALUE_LENGTH 150
// 配置文件路径
#define BK_CONFIG_FILE_PATH "sdmc:/switch/mgba/name_map.cfg"

// 配置项结构体
typedef struct {
    char key[BK_CONFIG_MAX_KEY_LENGTH];
    char value[BK_CONFIG_MAX_VALUE_LENGTH];
} bk_config_item_t;

// ============ 初始化与清理函数 ============

/**
 * 初始化全局配置管理器
 * 必须在程序开始时调用一次
 * @return 成功返回true，失败返回false
 */
bool bk_config_init(void);

/**
 * 清理全局配置管理器资源
 * 在程序结束时调用
 */
void bk_config_cleanup(void);

/**
 * 重新从文件加载配置到内存
 * @return 成功返回true，失败返回false
 */
bool bk_config_reload(void);

// ============ 核心操作函数 ============

/**
 * 获取配置值
 * @param key 键名
 * @return 对应的值（需要调用者释放内存），不存在返回NULL
 */
char* bk_config_get(const char* key);

/**
 * 设置配置项（如果键存在则更新，不存在则添加）
 * @param key 键名
 * @param value 值
 * @return 成功返回true，失败返回false
 */
bool bk_config_set(const char* key, const char* value);

/**
 * 添加配置项（如果键已存在则失败）
 * @param key 键名
 * @param value 值
 * @return 成功返回true，失败返回false
 */
bool bk_config_add(const char* key, const char* value);

/**
 * 删除配置项
 * @param key 键名
 * @return 成功返回true，失败返回false
 */
bool bk_config_remove(const char* key);

// ============ 批量操作函数 ============

/**
 * 获取所有配置项
 * @param count 返回配置项数量
 * @return 配置项数组（需要调用者释放内存），失败返回NULL
 */
bk_config_item_t* bk_config_get_all(int* count);

/**
 * 清空所有配置项
 * @return 成功返回true，失败返回false
 */
bool bk_config_clear(void);

/**
 * 批量设置配置项
 * @param items 配置项数组
 * @param count 配置项数量
 * @return 成功返回true，失败返回false
 */
bool bk_config_set_batch(const bk_config_item_t* items, int count);

// ============ 工具函数 ============

/**
 * 检查配置项是否存在
 * @param key 键名
 * @return 存在返回true，不存在返回false
 */
bool bk_config_exists(const char* key);

/**
 * 获取配置值（带默认值）
 * @param key 键名
 * @param default_value 默认值
 * @return 对应的值或默认值（静态缓冲区，不需要释放）
 */
const char* bk_config_get_or_default(const char* key, const char* default_value);

/**
 * 获取配置项数量
 * @return 配置项数量
 */
int bk_config_count(void);

/**
 * 导出配置到字符串
 * @return 配置字符串（需要调用者释放内存），失败返回NULL
 */
char* bk_config_export_to_string(void);

/**
 * 从字符串导入配置
 * @param config_str 配置字符串
 * @return 成功返回true，失败返回false
 */
bool bk_config_import_from_string(const char* config_str);

/**
 * 获取内部配置缓存指针（谨慎使用）
 * @return 内部配置项数组指针
 */
const bk_config_item_t* bk_config_get_internal_cache(void);



// ============ 文件名处理函数 ============

bool bk_util_is_valid_rom_extension(const char* filename);

#endif