#include <beiklive/beiklive.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 内部数据结构
typedef struct {
	bk_config_item_t* items;
	int count;
	int capacity;
	bool initialized;
} bk_config_cache_t;

// 全局配置缓存
static bk_config_cache_t g_cache = { 0 };
BK_LogConfig g_bk_log_config = {
    .level = BK_LOG_LEVEL_INFO,
    .enable_timestamp = 1,
    .enable_color = 1
};
// 初始键值对
static const char* DEFAULT_CONFIG[] = { "mgba=Switch Game", NULL };

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
	while (value_len > 0 &&
	       (value_start[value_len - 1] == '\n' || value_start[value_len - 1] == '\r' ||
	        value_start[value_len - 1] == ' ' || value_start[value_len - 1] == '\t')) {
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
				bk_config_item_t* new_items = realloc(g_cache.items, new_capacity * sizeof(bk_config_item_t));
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
		snprintf(line, sizeof(line), "%s=%s\n", g_cache.items[i].key, g_cache.items[i].value);
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
		return NULL;
	}

	// 在缓存中查找
	for (int i = 0; i < g_cache.count; i++) {
		if (strcmp(g_cache.items[i].key, key) == 0) {
			return strdup(g_cache.items[i].value);
		}
	}

	return NULL;
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
		bk_config_item_t* new_items = realloc(g_cache.items, new_capacity * sizeof(bk_config_item_t));
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
		if (count)
			*count = 0;
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
		int written =
		    snprintf(ptr, total_size - (ptr - result), "%s=%s\n", g_cache.items[i].key, g_cache.items[i].value);
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
				bk_config_item_t* new_items = realloc(g_cache.items, new_capacity * sizeof(bk_config_item_t));
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
	if (!str || !suffix)
		return false;

	size_t str_len = strlen(str);
	size_t suffix_len = strlen(suffix);

	if (suffix_len > str_len)
		return false;

	// 从末尾开始比较，忽略大小写
	const char* str_end = str + str_len - suffix_len;
	for (size_t i = 0; i < suffix_len; i++) {
		if (tolower((unsigned char) str_end[i]) != tolower((unsigned char) suffix[i])) {
			return false;
		}
	}

	return true;
}

bool bk_util_has_mgba_dir_prefix(const char* str) {
    // "mgba_dir"的长度是8
    const char* prefix = BK_CONFIG_MAPDIR_PREFIX;
    const size_t prefix_len = 8;
    
    // 检查字符串长度是否足够
    if (str == NULL || strlen(str) < prefix_len) {
        return false;
    }
    
    // 比较前8个字符
    return strncmp(str, prefix, prefix_len) == 0;
}


bool bk_util_is_valid_rom_extension(const char* filename) {

	if (!filename)
		return false;

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

char* bk_util_remove_trailing_slash_copy(const char* str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str);
    
    // 计算需要移除的斜杠数量
    size_t new_len = len;
    while (new_len > 0 && str[new_len - 1] == '/') {
        new_len--;
    }
    
    // 分配新字符串内存
    char* result = (char*)malloc(new_len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    // 复制内容
    strncpy(result, str, new_len);
    result[new_len] = '\0';
    
    return result;
}
/**
 * 去除文件后缀，返回文件名称（不含后缀）
 * @param filename 完整文件名
 * @return 去除后缀的文件名（需要调用者释放内存）
 */
char* bk_util_remove_extension(const char* filename) {
	if (filename == NULL) {
		return NULL;
	}

	// 查找最后一个点（后缀分隔符）的位置
	const char* dot = strrchr(filename, '.');
	const char* slash = strrchr(filename, '/'); // 处理可能包含路径的情况

	// 如果没有找到点，或者点在路径分隔符之前，返回整个字符串
	if (dot == NULL || (slash != NULL && dot < slash)) {
		char* result = (char*) malloc(strlen(filename) + 1);
		if (result == NULL) {
			return NULL;
		}
		strcpy(result, filename);
		return result;
	}

	// 计算文件名（不含后缀）的长度
	size_t name_length = dot - filename;

	// 分配内存并复制文件名部分
	char* result = (char*) malloc(name_length + 1);
	if (result == NULL) {
		return NULL;
	}

	strncpy(result, filename, name_length);
	result[name_length] = '\0';

	return result;
}

/**
 * 获取文件后缀（包含点）
 * @param filename 完整文件名
 * @return 文件后缀（需要调用者释放内存）
 */
char* bk_util_get_extension(const char* filename) {
	if (filename == NULL) {
		return NULL;
	}

	// 查找最后一个点（后缀分隔符）的位置
	const char* dot = strrchr(filename, '.');
	const char* slash = strrchr(filename, '/'); // 处理可能包含路径的情况
#ifdef _WIN32
	const char* backslash = strrchr(filename, '\\');
	if (backslash > slash) {
		slash = backslash;
	}
#endif

	// 如果没有找到点，或者点在路径分隔符之前，返回空字符串
	if (dot == NULL || (slash != NULL && dot < slash)) {
		char* result = (char*) malloc(1);
		if (result == NULL) {
			return NULL;
		}
		result[0] = '\0';
		return result;
	}

	// 分配内存并复制后缀部分（包含点）
	char* result = (char*) malloc(strlen(dot) + 1);
	if (result == NULL) {
		return NULL;
	}

	strcpy(result, dot);
	return result;
}

/**
 * 拼接两个字符串（动态分配内存）
 * @param str1 第一个字符串
 * @param str2 第二个字符串
 * @return 拼接后的新字符串（需要调用者释放内存）
 */
char* bk_util_str_concatenate(const char* str1, const char* str2) {
	if (str1 == NULL || str2 == NULL) {
		return NULL;
	}

	// 计算总长度（包括结束符）
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	size_t total_len = len1 + len2 + 1;

	// 分配内存
	char* result = (char*) malloc(total_len);
	if (result == NULL) {
		return NULL;
	}

	// 复制字符串
	strcpy(result, str1);
	strcat(result, str2);

	return result;
}

/**
 * 拼接多个字符串（可变参数）
 * @param count 要拼接的字符串数量
 * @param ... 要拼接的字符串
 * @return 拼接后的新字符串（需要调用者释放内存）
 */
char* bk_util_str_concatenate_multiple(int count, ...) {
	if (count <= 0) {
		char* result = (char*) malloc(1);
		if (result)
			result[0] = '\0';
		return result;
	}

	va_list args;
	va_start(args, count);

	// 第一步：计算总长度
	size_t total_len = 1; // 结束符
	for (int i = 0; i < count; i++) {
		const char* str = va_arg(args, const char*);
		if (str) {
			total_len += strlen(str);
		}
	}

	// 重置参数列表
	va_end(args);
	va_start(args, count);

	// 第二步：分配内存
	char* result = (char*) malloc(total_len);
	if (result == NULL) {
		va_end(args);
		return NULL;
	}

	// 第三步：拼接字符串
	result[0] = '\0'; // 确保以null开头
	for (int i = 0; i < count; i++) {
		const char* str = va_arg(args, const char*);
		if (str) {
			strcat(result, str);
		}
	}

	va_end(args);
	return result;
}

struct VFile* bk_util_open_png(const char* path, int mode) {
	struct VFile* vf = VFileOpen(path, mode);
	if (!vf) {
		return NULL;
	}

	if (!isPNG(vf)) {
		vf->close(vf);
		return NULL;
	}

	return vf;
}


uint32_t bk_util_normalize_cn_symbol(uint32_t u)
{
    switch (u)
    {
        // 标点
        case 0xFF0C: return 0x002C; // ， ,
        case 0x3002: return 0x002E; // 。 .
        case 0x3001: return 0x002F; // 、 /
        case 0xFF1A: return 0x003A; // ： :
        case 0xFF1B: return 0x003B; // ； ;
        case 0xFF1F: return 0x003F; // ？ ?
        case 0xFF01: return 0x0021; // ！ !

        // 括号
        case 0xFF08: return 0x0028; // （ (
        case 0xFF09: return 0x0029; // ） )
        case 0x3010: return 0x005B; // 【 [
        case 0x3011: return 0x005D; // 】 ]

        // 引号
        case 0x300C: // 「
        case 0x300D: // 」
        case 0x300E: // 『
        case 0x300F: // 』
        case 0x201C: // “
        case 0x201D: // ”
            return 0x0022; // "

        case 0x2018: // ‘
        case 0x2019: // ’
            return 0x0027; // '

        // 数学符号
        case 0xFF0B: return 0x002B; // ＋ +
        case 0xFF0D: return 0x002D; // － -
        case 0x00D7: return 0x002A; // × *
        case 0x00F7: return 0x002F; // ÷ /
        case 0xFF1D: return 0x003D; // ＝ =
        case 0xFF1C: return 0x003C; // ＜ <
        case 0xFF1E: return 0x003E; // ＞ >

        // 其他
        case 0xFFE5: return 0x0024; // ￥ $
        case 0xFF5E: return 0x007E; // ～ ~
        case 0xFF5C: return 0x007C; // ｜ |
        case 0xFF06: return 0x0026; // ＆ &
        case 0xFF20: return 0x0040; // ＠ @
        case 0xFF03: return 0x0023; // ＃ #
        case 0x3000: return 0x0020; // 全角空格

        default:
            return u;
    }
}

float bk_calc_insize(unsigned realSize) {
    unsigned pot = 1;
    while (pot < realSize) {
        pot <<= 1;
    }
    return (float)realSize / (float)pot;
}

// 哈希函数
uint32_t calculate_hash(const void* data, size_t length) {
    const uint8_t* bytes = (const uint8_t*)data;
    uint32_t hash = 2166136261u;
    
    for (size_t i = 0; i < length; i++) {
        hash ^= bytes[i];
        hash *= 16777619u;
    }
    
    return hash;
}


bool _bk_mask_Extensions(const char* name) {
	if (!strncmp(name, "cfg", PATH_MAX)) {
		return true;
	}
	// return false;
	return true;
}