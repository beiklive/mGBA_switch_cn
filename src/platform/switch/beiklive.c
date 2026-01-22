#include <beiklive/beiklive.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// 内部数据结构
typedef struct {
    bk_config_item_t* items;
    int count;
    int capacity;
    bool initialized;
} bk_config_cache_t;

// 全局配置缓存
static bk_config_cache_t g_cache = {0};

// 初始键值对
static const char* DEFAULT_CONFIG[] = {
    "mgba=Switch Game",
    NULL
};

// ============ 内部辅助函数 ============

/**
 * 初始化配置文件（内部函数）
 * @return 成功返回true，失败返回false
 */
static bool bk_config_init_file(void) {
    struct VFile* vf = VFileOpen(BK_CONFIG_FILE_PATH, O_CREAT | O_TRUNC | O_WRONLY);
    if (!vf) {
        return false;
    }
    
    // 写入默认配置
    for (int i = 0; DEFAULT_CONFIG[i] != NULL; i++) {
        const char* line = DEFAULT_CONFIG[i];
        vf->write(vf, line, strlen(line));
        vf->write(vf, "\n", 1);
    }
    
    vf->close(vf);
    return true;
}

/**
 * 解析配置行（内部函数）
 * @param line 配置行
 * @param key 存储键的缓冲区
 * @param value 存储值的缓冲区
 * @return 解析成功返回true，失败返回false
 */
static bool bk_config_parse_line(const char* line, char* key, char* value) {
    if (!line || !key || !value) {
        return false;
    }
    
    // 跳过行首空白字符
    while (*line == ' ' || *line == '\t') {
        line++;
    }
    
    // 跳过空行和注释
    if (*line == '\0' || *line == '\n' || *line == '\r' || *line == '#') {
        return false;
    }
    
    // 查找等号
    const char* equal_pos = strchr(line, '=');
    if (!equal_pos) {
        return false;
    }
    
    // 提取键
    size_t key_len = equal_pos - line;
    if (key_len >= BK_CONFIG_MAX_KEY_LENGTH) {
        key_len = BK_CONFIG_MAX_KEY_LENGTH - 1;
    }
    
    strncpy(key, line, key_len);
    key[key_len] = '\0';
    
    // 去除键末尾的空白字符
    while (key_len > 0 && (key[key_len - 1] == ' ' || key[key_len - 1] == '\t')) {
        key[--key_len] = '\0';
    }
    
    // 提取值
    const char* value_start = equal_pos + 1;
    // 跳过值前面的空白字符
    while (*value_start == ' ' || *value_start == '\t') {
        value_start++;
    }
    
    size_t value_len = strlen(value_start);
    // 去除值末尾的换行符和空白字符
    while (value_len > 0 && (value_start[value_len - 1] == '\n' || 
                             value_start[value_len - 1] == '\r' ||
                             value_start[value_len - 1] == ' ' ||
                             value_start[value_len - 1] == '\t')) {
        value_len--;
    }
    
    if (value_len >= BK_CONFIG_MAX_VALUE_LENGTH) {
        value_len = BK_CONFIG_MAX_VALUE_LENGTH - 1;
    }
    
    strncpy(value, value_start, value_len);
    value[value_len] = '\0';
    
    return true;
}

/**
 * 加载配置文件到内存缓存（内部函数）
 * @return 成功返回true，失败返回false
 */
static bool bk_config_load_to_cache(void) {
    // 清理现有缓存
    if (g_cache.items) {
        free(g_cache.items);
        g_cache.items = NULL;
        g_cache.count = 0;
        g_cache.capacity = 0;
    }
    
    // 确保文件存在
    struct VFile* test_vf = VFileOpen(BK_CONFIG_FILE_PATH, O_RDONLY);
    if (!test_vf) {
        // 文件不存在，创建并初始化
        if (!bk_config_init_file()) {
            return false;
        }
    } else {
        test_vf->close(test_vf);
    }
    
    // 打开文件读取
    struct VFile* vf = VFileOpen(BK_CONFIG_FILE_PATH, O_RDONLY);
    if (!vf) {
        return false;
    }
    
    // 初始化缓存
    g_cache.capacity = 16;
    g_cache.items = malloc(g_cache.capacity * sizeof(bk_config_item_t));
    if (!g_cache.items) {
        vf->close(vf);
        return false;
    }
    
    g_cache.count = 0;
    
    // 读取配置
    char line[BK_CONFIG_MAX_LINE_LENGTH];
    char key[BK_CONFIG_MAX_KEY_LENGTH];
    char value[BK_CONFIG_MAX_VALUE_LENGTH];
    
    while (vf->readline(vf, line, sizeof(line))) {
        if (bk_config_parse_line(line, key, value)) {
            // 检查是否需要扩容
            if (g_cache.count >= g_cache.capacity) {
                int new_capacity = g_cache.capacity * 2;
                bk_config_item_t* new_items = realloc(g_cache.items, 
                                                     new_capacity * sizeof(bk_config_item_t));
                if (!new_items) {
                    vf->close(vf);
                    free(g_cache.items);
                    g_cache.items = NULL;
                    return false;
                }
                g_cache.items = new_items;
                g_cache.capacity = new_capacity;
            }
            
            // 添加到缓存
            strcpy(g_cache.items[g_cache.count].key, key);
            strcpy(g_cache.items[g_cache.count].value, value);
            g_cache.count++;
        }
    }
    
    vf->close(vf);
    return true;
}

/**
 * 保存内存缓存到文件（内部函数）
 * @return 成功返回true，失败返回false
 */
static bool bk_config_save_to_file(void) {
    // 打开文件写入
    struct VFile* vf = VFileOpen(BK_CONFIG_FILE_PATH, O_CREAT | O_TRUNC | O_WRONLY);
    if (!vf) {
        return false;
    }
    
    // 写入所有配置项
    for (int i = 0; i < g_cache.count; i++) {
        char line[BK_CONFIG_MAX_LINE_LENGTH];
        snprintf(line, sizeof(line), "%s=%s\n", 
                 g_cache.items[i].key, 
                 g_cache.items[i].value);
        vf->write(vf, line, strlen(line));
    }
    
    vf->close(vf);
    return true;
}

// ============ 初始化与清理函数实现 ============

bool bk_config_init(void) {
    if (g_cache.initialized) {
        return true; // 已经初始化
    }
    
    if (!bk_config_load_to_cache()) {
        return false;
    }
    
    g_cache.initialized = true;
    return true;
}

void bk_config_cleanup(void) {
    if (g_cache.items) {
        free(g_cache.items);
    }
    memset(&g_cache, 0, sizeof(g_cache));
}

bool bk_config_reload(void) {
    // 清理当前缓存
    if (g_cache.items) {
        free(g_cache.items);
        g_cache.items = NULL;
        g_cache.count = 0;
        g_cache.capacity = 0;
    }
    
    // 重新加载
    bool success = bk_config_load_to_cache();
    if (!success) {
        g_cache.initialized = false;
    }
    
    return success;
}

// ============ 核心操作函数实现 ============

char* bk_config_get(const char* key) {
    if (!key || !g_cache.initialized) {
        return key;
    }
    
    // 在缓存中查找
    for (int i = 0; i < g_cache.count; i++) {
        if (strcmp(g_cache.items[i].key, key) == 0) {
            return strdup(g_cache.items[i].value);
        }
    }
    
    return key;
}

bool bk_config_set(const char* key, const char* value) {
    if (!key || !value || !g_cache.initialized) {
        return false;
    }
    
    // 检查是否已存在
    for (int i = 0; i < g_cache.count; i++) {
        if (strcmp(g_cache.items[i].key, key) == 0) {
            // 更新现有值
            strncpy(g_cache.items[i].value, value, BK_CONFIG_MAX_VALUE_LENGTH - 1);
            g_cache.items[i].value[BK_CONFIG_MAX_VALUE_LENGTH - 1] = '\0';
            // 保存到文件
            return bk_config_save_to_file();
        }
    }
    
    // 不存在，添加新项
    if (g_cache.count >= g_cache.capacity) {
        int new_capacity = g_cache.capacity == 0 ? 16 : g_cache.capacity * 2;
        bk_config_item_t* new_items = realloc(g_cache.items, 
                                             new_capacity * sizeof(bk_config_item_t));
        if (!new_items) {
            return false;
        }
        g_cache.items = new_items;
        g_cache.capacity = new_capacity;
    }
    
    // 添加新配置项
    strncpy(g_cache.items[g_cache.count].key, key, BK_CONFIG_MAX_KEY_LENGTH - 1);
    g_cache.items[g_cache.count].key[BK_CONFIG_MAX_KEY_LENGTH - 1] = '\0';
    
    strncpy(g_cache.items[g_cache.count].value, value, BK_CONFIG_MAX_VALUE_LENGTH - 1);
    g_cache.items[g_cache.count].value[BK_CONFIG_MAX_VALUE_LENGTH - 1] = '\0';
    
    g_cache.count++;
    
    // 保存到文件
    return bk_config_save_to_file();
}

bool bk_config_add(const char* key, const char* value) {
    if (!key || !value || !g_cache.initialized) {
        return false;
    }
    
    // 检查是否已存在
    if (bk_config_exists(key)) {
        return false; // 已存在，添加失败
    }
    
    // 添加新项（复用set的逻辑，但这里可以简化）
    return bk_config_set(key, value);
}

bool bk_config_remove(const char* key) {
    if (!key || !g_cache.initialized) {
        return false;
    }
    
    // 查找要删除的项
    int found_index = -1;
    for (int i = 0; i < g_cache.count; i++) {
        if (strcmp(g_cache.items[i].key, key) == 0) {
            found_index = i;
            break;
        }
    }
    
    if (found_index == -1) {
        return false; // 键不存在
    }
    
    // 删除项
    for (int i = found_index; i < g_cache.count - 1; i++) {
        g_cache.items[i] = g_cache.items[i + 1];
    }
    g_cache.count--;
    
    // 保存到文件
    return bk_config_save_to_file();
}

// ============ 批量操作函数实现 ============

bk_config_item_t* bk_config_get_all(int* count) {
    if (!count || !g_cache.initialized) {
        if (count) *count = 0;
        return NULL;
    }
    
    // 复制配置项
    bk_config_item_t* items = malloc(g_cache.count * sizeof(bk_config_item_t));
    if (!items) {
        *count = 0;
        return NULL;
    }
    
    memcpy(items, g_cache.items, g_cache.count * sizeof(bk_config_item_t));
    *count = g_cache.count;
    
    return items;
}

bool bk_config_clear(void) {
    if (!g_cache.initialized) {
        return false;
    }
    
    // 清空缓存
    g_cache.count = 0;
    
    // 清空文件
    struct VFile* vf = VFileOpen(BK_CONFIG_FILE_PATH, O_CREAT | O_TRUNC | O_WRONLY);
    if (!vf) {
        return false;
    }
    
    vf->close(vf);
    
    // 重新初始化默认配置
    if (!bk_config_init_file()) {
        return false;
    }
    
    // 重新加载缓存
    return bk_config_reload();
}

bool bk_config_set_batch(const bk_config_item_t* items, int count) {
    if (!items || count <= 0 || !g_cache.initialized) {
        return false;
    }
    
    // 清空当前缓存
    g_cache.count = 0;
    
    // 确保有足够容量
    if (g_cache.capacity < count) {
        bk_config_item_t* new_items = realloc(g_cache.items, count * sizeof(bk_config_item_t));
        if (!new_items) {
            return false;
        }
        g_cache.items = new_items;
        g_cache.capacity = count;
    }
    
    // 复制新配置项
    for (int i = 0; i < count; i++) {
        strncpy(g_cache.items[i].key, items[i].key, BK_CONFIG_MAX_KEY_LENGTH - 1);
        g_cache.items[i].key[BK_CONFIG_MAX_KEY_LENGTH - 1] = '\0';
        
        strncpy(g_cache.items[i].value, items[i].value, BK_CONFIG_MAX_VALUE_LENGTH - 1);
        g_cache.items[i].value[BK_CONFIG_MAX_VALUE_LENGTH - 1] = '\0';
    }
    g_cache.count = count;
    
    // 保存到文件
    return bk_config_save_to_file();
}

// ============ 工具函数实现 ============

bool bk_config_exists(const char* key) {
    if (!key || !g_cache.initialized) {
        return false;
    }
    
    for (int i = 0; i < g_cache.count; i++) {
        if (strcmp(g_cache.items[i].key, key) == 0) {
            return true;
        }
    }
    
    return false;
}

const char* bk_config_get_or_default(const char* key, const char* default_value) {
    static char static_buffer[BK_CONFIG_MAX_VALUE_LENGTH];
    
    if (!g_cache.initialized) {
        return default_value;
    }
    
    for (int i = 0; i < g_cache.count; i++) {
        if (strcmp(g_cache.items[i].key, key) == 0) {
            strncpy(static_buffer, g_cache.items[i].value, sizeof(static_buffer) - 1);
            static_buffer[sizeof(static_buffer) - 1] = '\0';
            return static_buffer;
        }
    }
    
    return default_value;
}

int bk_config_count(void) {
    return g_cache.initialized ? g_cache.count : 0;
}

char* bk_config_export_to_string(void) {
    if (!g_cache.initialized) {
        return NULL;
    }
    
    // 计算所需缓冲区大小
    size_t total_size = 0;
    for (int i = 0; i < g_cache.count; i++) {
        total_size += strlen(g_cache.items[i].key) + strlen(g_cache.items[i].value) + 2; // +2 for '=' and '\n'
    }
    total_size++; // 字符串结束符
    
    // 分配缓冲区
    char* result = malloc(total_size);
    if (!result) {
        return NULL;
    }
    
    // 构建字符串
    char* ptr = result;
    for (int i = 0; i < g_cache.count; i++) {
        int written = snprintf(ptr, total_size - (ptr - result), 
                              "%s=%s\n", g_cache.items[i].key, g_cache.items[i].value);
        if (written > 0) {
            ptr += written;
        }
    }
    
    return result;
}

bool bk_config_import_from_string(const char* config_str) {
    if (!config_str || !g_cache.initialized) {
        return false;
    }
    
    // 清空当前缓存
    g_cache.count = 0;
    
    // 解析字符串
    const char* line_start = config_str;
    const char* line_end;
    int index = 0;
    
    while (*line_start) {
        // 找到行结束
        line_end = strchr(line_start, '\n');
        if (!line_end) {
            line_end = line_start + strlen(line_start);
        }
        
        // 解析行
        char line[BK_CONFIG_MAX_LINE_LENGTH];
        size_t line_len = line_end - line_start;
        if (line_len >= sizeof(line)) {
            line_len = sizeof(line) - 1;
        }
        
        strncpy(line, line_start, line_len);
        line[line_len] = '\0';
        
        char key[BK_CONFIG_MAX_KEY_LENGTH];
        char value[BK_CONFIG_MAX_VALUE_LENGTH];
        
        if (bk_config_parse_line(line, key, value)) {
            // 确保有足够容量
            if (index >= g_cache.capacity) {
                int new_capacity = g_cache.capacity == 0 ? 16 : g_cache.capacity * 2;
                bk_config_item_t* new_items = realloc(g_cache.items, 
                                                     new_capacity * sizeof(bk_config_item_t));
                if (!new_items) {
                    return false;
                }
                g_cache.items = new_items;
                g_cache.capacity = new_capacity;
            }
            
            // 添加到缓存
            strcpy(g_cache.items[index].key, key);
            strcpy(g_cache.items[index].value, value);
            index++;
        }
        
        // 移动到下一行
        if (*line_end == '\0') {
            break;
        }
        line_start = line_end + 1;
    }
    
    g_cache.count = index;
    
    // 保存到文件
    return bk_config_save_to_file();
}

const bk_config_item_t* bk_config_get_internal_cache(void) {
    return g_cache.initialized ? g_cache.items : NULL;
}

// ============ 文件名处理函数实现 ============

/**
 * 比较字符串末尾（不区分大小写）
 * @param str 源字符串
 * @param suffix 后缀
 * @return 匹配返回true，否则返回false
 */
static bool bk_string_ends_with_ignore_case(const char* str, const char* suffix) {
    if (!str || !suffix) return false;
    
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);
    
    if (suffix_len > str_len) return false;
    
    // 从末尾开始比较，忽略大小写
    const char* str_end = str + str_len - suffix_len;
    for (size_t i = 0; i < suffix_len; i++) {
        if (tolower((unsigned char)str_end[i]) != tolower((unsigned char)suffix[i])) {
            return false;
        }
    }
    
    return true;
}
char* bk_util_get_basename_without_extension(const char* filename) {
    if (!filename) return NULL;
    
    // 提取基本文件名（去除路径）
    const char* basename = filename;
    
    // 查找最后一个路径分隔符
    const char* last_slash = strrchr(filename, '/');
    const char* last_backslash = strrchr(filename, '\\');
    
    // 找到最后一个路径分隔符
    if (last_slash || last_backslash) {
        const char* last_separator = last_slash > last_backslash ? last_slash : last_backslash;
        if (last_separator) {
            basename = last_separator + 1;
        }
    }
    
    // 计算不带扩展名的长度
    size_t basename_len = strlen(basename);
    
    // 获取文件扩展名
    const char* extension = bk_util_get_file_extension(basename);
    
    if (!extension) {
        // 没有有效的扩展名，返回完整文件名
        char* result = (char*)malloc(basename_len + 1);
        if (!result) return NULL;
        strcpy(result, basename);
        return result;
    }
    
    // 计算扩展名长度（包括点号）
    size_t ext_len = strlen(extension);
    
    // 确保文件名长度足够
    if (basename_len <= ext_len) {
        // 文件名太短，可能只有扩展名
        return NULL;
    }
    
    // 分配内存并复制不带扩展名的文件名
    char* result = (char*)malloc(basename_len - ext_len + 1);
    if (!result) {
        return NULL;
    }
    
    // 复制文件名（不包括扩展名）
    strncpy(result, basename, basename_len - ext_len);
    result[basename_len - ext_len] = '\0';
    
    return result;
}



bool bk_util_is_valid_rom_extension(const char* filename) {
    if (!filename) return false;
    
    // 检查是否以支持的扩展名结尾（不区分大小写）
    bool has_valid_extension = false;
    
    // 检查 .gba 扩展名
    if (bk_string_ends_with_ignore_case(filename, ".gba")) {
        has_valid_extension = true;
    }
    // 检查 .zip 扩展名
    else if (bk_string_ends_with_ignore_case(filename, ".zip")) {
        has_valid_extension = true;
    }
    // 检查 .gb 扩展名
    else if (bk_string_ends_with_ignore_case(filename, ".gb")) {
        has_valid_extension = true;
    }
    // 检查 .gbc 扩展名
    else if (bk_string_ends_with_ignore_case(filename, ".gbc")) {
        has_valid_extension = true;
    }
    // 检查 .sgb 扩展名
    else if (bk_string_ends_with_ignore_case(filename, ".sgb")) {
        has_valid_extension = true;
    }

    return has_valid_extension;
}

const char* bk_util_get_file_extension(const char* filename) {
    if (!filename) {
        return NULL;
    }
        // 检查 .gba 扩展名
    if (bk_string_ends_with_ignore_case(filename, ".gba")) {
        return ".gba";
    }
    // 检查 .zip 扩展名
    else if (bk_string_ends_with_ignore_case(filename, ".zip")) {
        return ".zip";
    }
    // 检查 .gb 扩展名
    else if (bk_string_ends_with_ignore_case(filename, ".gb")) {
        return ".gb";
    }
    // 检查 .gbc 扩展名
    else if (bk_string_ends_with_ignore_case(filename, ".gbc")) {
        return ".gbc";
    }
    // 检查 .sgb 扩展名
    else if (bk_string_ends_with_ignore_case(filename, ".sgb")) {
        return ".sgb";
    }

    return NULL;
}