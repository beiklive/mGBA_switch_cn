#include <beiklive/beiklive.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define STB_IMAGE_IMPLEMENTATION
#include <beiklive/stb_image.h>

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

uint32_t g_bk_color_text_select = BK_RGBA_BLUE;
uint32_t g_bk_color_text = BK_RGBA_BLACK;
uint32_t g_bk_config_color[BK_CONFIG_COLOR_MAX] = {
	BK_RGBA_BLACK ,
	BK_RGBA_WHITE ,
	BK_RGBA_RED   ,
	BK_RGBA_GREEN ,
	BK_RGBA_BLUE  ,
	BK_RGBA_ORANGE,
	BK_RGBA_YELLOW,
	BK_RGBA_GRAY  
};
int g_game_width = 256;
int g_game_height = 256;

int g_view_width = 1280;
int g_view_height = 720;

int g_cur_screen_aspect_ratio = 3;
float g_cur_screen_brightness = 1.0f;

int g_gba_video_offset_y = 0;
int g_gbc_video_offset_y = 0;


#define MAX_PASSES 8

static const GLfloat bkQuadVerts[] = {
    // x, y,      u, v
    -1.f, -1.f,  0.f, 0.f,
     1.f, -1.f,  1.f, 0.f,
     1.f,  1.f,  1.f, 1.f,
    -1.f,  1.f,  0.f, 1.f,
};

static const GLchar* const _gles2Header =
	"#version 100\n"
	"precision mediump float;\n";

static const GLchar* const _gl2Header =
	"#version 120\n";

static const GLchar* const _gl32VHeader =
	"#version 150 core\n"
	"#define attribute in\n"
	"#define varying out\n";

static const GLchar* const _gl32FHeader =
	"#version 150 core\n"
	"#define varying in\n"
	"#define texture2D texture\n"
	"out vec4 compat_FragColor;\n"
	"#define gl_FragColor compat_FragColor\n";

static const char* const _vertexShader =
    "attribute vec4 position;\n"
    "attribute vec2 texcoord;\n"
    "varying vec2 texCoord;\n"
    
    "void main() {\n"
    "   gl_Position = position;\n"
    "   texCoord = texcoord;\n"
    "}";

static const char* const _nullVertexShader =
    "attribute vec4 position;\n"
    "attribute vec2 texcoord;\n"
    "varying vec2 texCoord;\n"
    
    "void main() {\n"
    "   gl_Position = position;\n"
    "   texCoord = texcoord;\n"
    "}";

static const char* const _fragmentShader =
	"varying vec2 texCoord;\n"
	"uniform sampler2D tex;\n"
	"uniform float gamma;\n"
	"uniform vec3 desaturation;\n"
	"uniform vec3 scale;\n"
	"uniform vec3 bias;\n"

	"void main() {\n"
	"	vec4 color = texture2D(tex, texCoord);\n"
	"	color.a = 1.;\n"
	"	float average = dot(color.rgb, vec3(1.)) / 3.;\n"
	"	color.rgb = mix(color.rgb, vec3(average), desaturation);\n"
	"	color.rgb = scale * pow(color.rgb, vec3(gamma, gamma, gamma)) + bias;\n"
	"	gl_FragColor = color;\n"
	"}";

static const char* const _nullFragmentShader =
	"varying vec2 texCoord;\n"
	"uniform sampler2D tex;\n"

	"void main() {\n"
	"	vec4 color = texture2D(tex, texCoord);\n"
	"	color.a = 1.;\n"
	"	gl_FragColor = color;\n"
	"}";

static const char* const _interframeFragmentShader =
	"varying vec2 texCoord;\n"
	"uniform sampler2D tex;\n"

	"void main() {\n"
	"	vec4 color = texture2D(tex, texCoord);\n"
	"	color.a = 0.5;\n"
	"	gl_FragColor = color;\n"
	"}";

void mBKGLES2UniformListInit(struct mBKGLES2UniformList* vector, size_t capacity);
void mBKGLES2UniformListDeinit(struct mBKGLES2UniformList* vector);
struct mBKGLES2Uniform* mBKGLES2UniformListGetPointer(struct mBKGLES2UniformList* vector, size_t location);
struct mBKGLES2Uniform const* mBKGLES2UniformListGetConstPointer(const struct mBKGLES2UniformList* vector,
                                                                 size_t location);
struct mBKGLES2Uniform* mBKGLES2UniformListAppend(struct mBKGLES2UniformList* vector);
void mBKGLES2UniformListClear(struct mBKGLES2UniformList* vector);
void mBKGLES2UniformListResize(struct mBKGLES2UniformList* vector, ssize_t change);
void mBKGLES2UniformListShift(struct mBKGLES2UniformList* vector, size_t location, size_t difference);
void mBKGLES2UniformListUnshift(struct mBKGLES2UniformList* vector, size_t location, size_t difference);
void mBKGLES2UniformListEnsureCapacity(struct mBKGLES2UniformList* vector, size_t capacity);
size_t mBKGLES2UniformListSize(const struct mBKGLES2UniformList* vector);
size_t mBKGLES2UniformListIndex(const struct mBKGLES2UniformList* vector, const struct mBKGLES2Uniform* member);
void mBKGLES2UniformListCopy(struct mBKGLES2UniformList* dest, const struct mBKGLES2UniformList* src);


// ============ 内部辅助函数 ============
#define MAX_LINE_LENGTH 256
#define MAX_KEY_LENGTH 64
#define MAX_VALUE_LENGTH 64

// 配置文件条目结构
struct ConfigEntry {
    char key[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];
};

// 配置文件结构
struct ConfigFile {
    struct ConfigEntry *entries;
    int count;
    int capacity;
} ;

static struct ConfigFile *config_cache = NULL;
static char *last_filepath = NULL;


/**
 * 去除字符串两端的空白字符
 */
static char* trim(char *str) {
    if (str == NULL) return NULL;
    
    // 去除开头的空白字符
    char *start = str;
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }
    
    // 如果整个字符串都是空白
    if (*start == '\0') {
        str[0] = '\0';
        return str;
    }
    
    // 去除结尾的空白字符
    char *end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }
    
    *(end + 1) = '\0';
    
    // 将结果移回原字符串开头
    if (start != str) {
        memmove(str, start, end - start + 2); // +2 包含 '\0'
    }
    
    return str;
}

/**
 * 初始化配置文件结构
 */
static struct ConfigFile* init_config() {
    struct ConfigFile *config = malloc(sizeof(struct ConfigFile));
    if (!config) return NULL;
    
    config->capacity = 10;
    config->count = 0;
    config->entries = malloc(config->capacity * sizeof(struct ConfigEntry));
    
    if (!config->entries) {
        free(config);
        return NULL;
    }
    
    return config;
}

/**
 * 向配置文件中添加条目
 */
static void add_entry(struct ConfigFile *config, const char *key, const char *value) {
    if (!config || !key || !value) return;
    
    // 如果容量不足，扩展
    if (config->count >= config->capacity) {
        config->capacity *= 2;
        struct ConfigEntry *new_entries = realloc(config->entries, 
                                           config->capacity * sizeof(struct ConfigEntry));
        if (!new_entries) return;
        config->entries = new_entries;
    }
    
    // 添加新条目
    strncpy(config->entries[config->count].key, key, MAX_KEY_LENGTH - 1);
    config->entries[config->count].key[MAX_KEY_LENGTH - 1] = '\0';
    
    strncpy(config->entries[config->count].value, value, MAX_VALUE_LENGTH - 1);
    config->entries[config->count].value[MAX_VALUE_LENGTH - 1] = '\0';
    
    config->count++;
}

/**
 * 释放配置文件资源
 */
static void free_config(struct ConfigFile *config) {
    if (config) {
        if (config->entries) {
            free(config->entries);
        }
        free(config);
    }
}

/**
 * 解析配置文件
 */
static struct ConfigFile* parse_config_file(const char *filepath) {
    if (!filepath) return NULL;
    
	struct VFile* vf = VFileOpen(filepath, O_RDONLY);
	if (!vf) {
		return false;
	}

    
    struct ConfigFile *config = init_config();
    if (!config) {
        vf->close(vf);
        return NULL;
    }
    
    char line[MAX_LINE_LENGTH];
    
    while (vf->readline(vf, line, sizeof(line))) {
        
        // 去除换行符
        line[strcspn(line, "\n")] = '\0';
        
        // 去除前后空白
        trim(line);
        
        // 跳过空行和注释行
        if (line[0] == '\0' || line[0] == '#') {
            continue;
        }
        
        // 查找等号分隔符
        char *separator = strchr(line, '=');
        if (!separator) {
            continue;
        }
        
        // 分割键和值
        *separator = '\0'; // 在等号处截断
        
        char *key = line;
        char *value = separator + 1;
        
        // 去除键和值的空白字符
        trim(key);
        trim(value);
        
        // 如果键或值为空，跳过
        if (key[0] == '\0' || value[0] == '\0') {
            continue;
        }
        
        // 添加条目
        add_entry(config, key, value);
    }
    
    vf->close(vf);
    return config;
}

/**
 * 查找配置值并转换为整数
 */
int getIntValue(const char *filepath, const char *key) {
    if (!filepath || !key) return 0;
    

    
    // 如果文件路径不同或缓存为空，重新解析
    if (!config_cache || !last_filepath || strcmp(filepath, last_filepath) != 0) {
        // 释放旧的缓存
        if (config_cache) {
            free_config(config_cache);
            config_cache = NULL;
        }
        if (last_filepath) {
            free(last_filepath);
            last_filepath = NULL;
        }
        
        // 解析新文件
        config_cache = parse_config_file(filepath);
        if (!config_cache) return 0;
        
        // 缓存文件路径
        last_filepath = strdup(filepath);
        if (!last_filepath) {
            free_config(config_cache);
            config_cache = NULL;
            return 0;
        }
    }
    
    // 查找键
    for (int i = 0; i < config_cache->count; i++) {
        if (strcmp(config_cache->entries[i].key, key) == 0) {
            // 转换为整数
            char *endptr;
            long value = strtol(config_cache->entries[i].value, &endptr, 10);
            
            // 检查转换是否成功
            if (endptr == config_cache->entries[i].value) {
                return 0;
            }
            
            return (int)value;
        }
    }
    return 0;
}

/**
 * 清理缓存（可选，程序结束时调用）
 */
void cleanup_config_cache() {
    if (config_cache) {
        free_config(config_cache);
        config_cache = NULL;
    }
    if (last_filepath) {
        free(last_filepath);
        last_filepath = NULL;
    }
}

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

// 颜色转换
uint32_t _bk_rgba_to_abgr(uint32_t rgba) {
    // RGBA格式: 0xRRGGBBAA
    // ABGR格式: 0xAABBGGRR
    
    uint8_t r = (rgba >> 24) & 0xFF;  // 红色
    uint8_t g = (rgba >> 16) & 0xFF;  // 绿色
    uint8_t b = (rgba >> 8) & 0xFF;   // 蓝色
    uint8_t a = rgba & 0xFF;          // Alpha
    
    // 重新排列为 ABGR: A|B|G|R
    return ((uint32_t)a << 24) | ((uint32_t)b << 16) | 
           ((uint32_t)g << 8) | (uint32_t)r;
}

uint32_t _bk_getBatteryColor(int batteryLevel) {
    // 确保电量值在有效范围内
    if (batteryLevel < 1) batteryLevel = 1;
    if (batteryLevel > 100) batteryLevel = 100;
    
    // 将电量转换为0.0-1.0的百分比
    float percentage = batteryLevel / 100.0f;
    
    uint8_t r, g, b, a;
    a = 0xFF;  // 完全不透明
    
    if (percentage <= 0.2f) {
        // 0-20%: 深红 -> 亮红
        float factor = percentage / 0.2f;  // 0.0-1.0
        r = 128 + (uint8_t)(127 * factor);  // 128-255
        g = 0;
        b = 0;
    }
    else if (percentage <= 0.4f) {
        // 20-40%: 红 -> 橙
        float factor = (percentage - 0.2f) / 0.2f;  // 0.0-1.0
        r = 255;
        g = (uint8_t)(128 * factor);  // 0-128
        b = 0;
    }
    else if (percentage <= 0.6f) {
        // 40-60%: 橙 -> 黄
        float factor = (percentage - 0.4f) / 0.2f;  // 0.0-1.0
        r = 255;
        g = 128 + (uint8_t)(127 * factor);  // 128-255
        b = 0;
    }
    else if (percentage <= 0.8f) {
        // 60-80%: 黄 -> 黄绿
        float factor = (percentage - 0.6f) / 0.2f;  // 0.0-1.0
        r = 255 - (uint8_t)(127 * factor);  // 255-128
        g = 255;
        b = 0;
    }
    else {
        // 80-100%: 黄绿 -> 绿
        float factor = (percentage - 0.8f) / 0.2f;  // 0.0-1.0
        r = 128 - (uint8_t)(128 * factor);  // 128-0
        g = 255;
        b = 0;
    }
    
    // 组合为RGBA格式
    return ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | a;
}

bool _bk_mask_Extensions(const char* name) {
		char ext[PATH_MAX] = {};
	separatePath(name, NULL, NULL, ext);
	if (!strncmp(ext, "png", PATH_MAX)) {
		return true;
	}
	if (!strncmp(ext, "PNG", PATH_MAX)) {
		return true;
	}
	return false;
}


static bool _lookupIntValue(const struct Configuration* config, const char* section, const char* key, int* out) {
	const char* charValue = ConfigurationGetValue(config, section, key);
	if (!charValue) {
		return false;
	}
	char* end;
	unsigned long value = strtol(charValue, &end, 10);
	if (*end) {
		return false;
	}
	*out = value;
	return true;
}

static bool _lookupFloatValue(const struct Configuration* config, const char* section, const char* key, float* out) {
	const char* charValue = ConfigurationGetValue(config, section, key);
	if (!charValue) {
		return false;
	}
	char* end;
	float value = strtof_u(charValue, &end);
	if (*end) {
		return false;
	}
	*out = value;
	return true;
}

static bool _lookupBoolValue(const struct Configuration* config, const char* section, const char* key, GLboolean* out) {
	const char* charValue = ConfigurationGetValue(config, section, key);
	if (!charValue) {
		return false;
	}
	if (!strcmp(charValue, "true")) {
		*out = GL_TRUE;
		return true;
	}
	if (!strcmp(charValue, "false")) {
		*out = GL_FALSE;
		return true;
	}
	char* end;
	unsigned long value = strtol(charValue, &end, 10);
	if (*end) {
		return false;
	}
	*out = value;
	return true;
}




void mBKGLES2UniformListInit(struct mBKGLES2UniformList* vector, size_t capacity) {
	vector->size = 0;
	if (capacity == 0) {
		capacity = 4;
	}
	vector->capacity = capacity;
	vector->vector = calloc(capacity, sizeof(struct mBKGLES2Uniform));
}
void mBKGLES2UniformListDeinit(struct mBKGLES2UniformList* vector) {
	free(vector->vector);
	vector->vector = 0;
	vector->capacity = 0;
	vector->size = 0;
}
struct mBKGLES2Uniform* mBKGLES2UniformListGetPointer(struct mBKGLES2UniformList* vector, size_t location) {
	return &vector->vector[location];
}
struct mBKGLES2Uniform const* mBKGLES2UniformListGetConstPointer(const struct mBKGLES2UniformList* vector,
                                                                 size_t location) {
	return &vector->vector[location];
}
struct mBKGLES2Uniform* mBKGLES2UniformListAppend(struct mBKGLES2UniformList* vector) {
	mBKGLES2UniformListResize(vector, 1);
	return &vector->vector[vector->size - 1];
}
void mBKGLES2UniformListResize(struct mBKGLES2UniformList* vector, ssize_t change) {
	if (change > 0) {
		mBKGLES2UniformListEnsureCapacity(vector, vector->size + change);
	}
	vector->size += change;
}
void mBKGLES2UniformListClear(struct mBKGLES2UniformList* vector) {
	vector->size = 0;
}
void mBKGLES2UniformListEnsureCapacity(struct mBKGLES2UniformList* vector, size_t capacity) {
	if (capacity <= vector->capacity) {
		return;
	}
	while (capacity > vector->capacity) {
		vector->capacity <<= 1;
	}
	vector->vector = realloc(vector->vector, vector->capacity * sizeof(struct mBKGLES2Uniform));
}
void mBKGLES2UniformListShift(struct mBKGLES2UniformList* vector, size_t location, size_t difference) {
	memmove(&vector->vector[location], &vector->vector[location + difference],
	        (vector->size - location - difference) * sizeof(struct mBKGLES2Uniform));
	vector->size -= difference;
}
void mBKGLES2UniformListUnshift(struct mBKGLES2UniformList* vector, size_t location, size_t difference) {
	mBKGLES2UniformListResize(vector, difference);
	memmove(&vector->vector[location + difference], &vector->vector[location],
	        (vector->size - location - difference) * sizeof(struct mBKGLES2Uniform));
}
size_t mBKGLES2UniformListSize(const struct mBKGLES2UniformList* vector) {
	return vector->size;
}
size_t mBKGLES2UniformListIndex(const struct mBKGLES2UniformList* vector, const struct mBKGLES2Uniform* member) {
	return member - (const struct mBKGLES2Uniform*) vector->vector;
}
void mBKGLES2UniformListCopy(struct mBKGLES2UniformList* dest, const struct mBKGLES2UniformList* src) {
	mBKGLES2UniformListEnsureCapacity(dest, src->size);
	memcpy(dest->vector, src->vector, src->size * sizeof(struct mBKGLES2Uniform));
	dest->size = src->size;
}


static void _loadValue(struct Configuration* description, const char* name, GLenum type, const char* field, union mBKGLES2UniformValue* value) {
	char fieldName[16];
	switch (type) {
	case GL_FLOAT:
		value->f = 0;
		_lookupFloatValue(description, name, field, &value->f);
		break;
	case GL_FLOAT_VEC2:
		value->fvec2[0] = 0;
		value->fvec2[1] = 0;
		snprintf(fieldName, sizeof(fieldName), "%s[0]", field);
		_lookupFloatValue(description, name, fieldName, &value->fvec2[0]);
		snprintf(fieldName, sizeof(fieldName), "%s[1]", field);
		_lookupFloatValue(description, name, fieldName, &value->fvec2[1]);
		break;
	case GL_FLOAT_VEC3:
		value->fvec3[0] = 0;
		value->fvec3[1] = 0;
		value->fvec3[2] = 0;
		snprintf(fieldName, sizeof(fieldName), "%s[0]", field);
		_lookupFloatValue(description, name, fieldName, &value->fvec3[0]);
		snprintf(fieldName, sizeof(fieldName), "%s[1]", field);
		_lookupFloatValue(description, name, fieldName, &value->fvec3[1]);
		snprintf(fieldName, sizeof(fieldName), "%s[2]", field);
		_lookupFloatValue(description, name, fieldName, &value->fvec3[2]);
		break;
	case GL_FLOAT_VEC4:
		value->fvec4[0] = 0;
		value->fvec4[1] = 0;
		value->fvec4[2] = 0;
		value->fvec4[3] = 0;
		snprintf(fieldName, sizeof(fieldName), "%s[0]", field);
		_lookupFloatValue(description, name, fieldName, &value->fvec4[0]);
		snprintf(fieldName, sizeof(fieldName), "%s[1]", field);
		_lookupFloatValue(description, name, fieldName, &value->fvec4[1]);
		snprintf(fieldName, sizeof(fieldName), "%s[2]", field);
		_lookupFloatValue(description, name, fieldName, &value->fvec4[2]);
		snprintf(fieldName, sizeof(fieldName), "%s[3]", field);
		_lookupFloatValue(description, name, fieldName, &value->fvec4[3]);
		break;
	case GL_FLOAT_MAT2:
		value->fmat2x2[0] = 0;
		value->fmat2x2[1] = 0;
		value->fmat2x2[2] = 0;
		value->fmat2x2[3] = 0;
		snprintf(fieldName, sizeof(fieldName), "%s[0,0]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat2x2[0]);
		snprintf(fieldName, sizeof(fieldName), "%s[0,1]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat2x2[1]);
		snprintf(fieldName, sizeof(fieldName), "%s[1,0]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat2x2[2]);
		snprintf(fieldName, sizeof(fieldName), "%s[1,1]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat2x2[3]);
		break;
	case GL_FLOAT_MAT3:
		value->fmat3x3[0] = 0;
		value->fmat3x3[1] = 0;
		value->fmat3x3[2] = 0;
		value->fmat3x3[3] = 0;
		value->fmat3x3[4] = 0;
		value->fmat3x3[5] = 0;
		value->fmat3x3[6] = 0;
		value->fmat3x3[7] = 0;
		value->fmat3x3[8] = 0;
		snprintf(fieldName, sizeof(fieldName), "%s[0,0]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat3x3[0]);
		snprintf(fieldName, sizeof(fieldName), "%s[0,1]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat3x3[1]);
		snprintf(fieldName, sizeof(fieldName), "%s[0,2]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat3x3[2]);
		snprintf(fieldName, sizeof(fieldName), "%s[1,0]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat3x3[3]);
		snprintf(fieldName, sizeof(fieldName), "%s[1,1]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat3x3[4]);
		snprintf(fieldName, sizeof(fieldName), "%s[1,2]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat3x3[5]);
		snprintf(fieldName, sizeof(fieldName), "%s[2,0]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat3x3[6]);
		snprintf(fieldName, sizeof(fieldName), "%s[2,1]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat3x3[7]);
		snprintf(fieldName, sizeof(fieldName), "%s[2,2]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat3x3[8]);
		break;
	case GL_FLOAT_MAT4:
		value->fmat4x4[0] = 0;
		value->fmat4x4[1] = 0;
		value->fmat4x4[2] = 0;
		value->fmat4x4[3] = 0;
		value->fmat4x4[4] = 0;
		value->fmat4x4[5] = 0;
		value->fmat4x4[6] = 0;
		value->fmat4x4[7] = 0;
		value->fmat4x4[8] = 0;
		value->fmat4x4[9] = 0;
		value->fmat4x4[10] = 0;
		value->fmat4x4[11] = 0;
		value->fmat4x4[12] = 0;
		value->fmat4x4[13] = 0;
		value->fmat4x4[14] = 0;
		value->fmat4x4[15] = 0;
		snprintf(fieldName, sizeof(fieldName), "%s[0,0]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat4x4[0]);
		snprintf(fieldName, sizeof(fieldName), "%s[0,1]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat4x4[1]);
		snprintf(fieldName, sizeof(fieldName), "%s[0,2]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat4x4[2]);
		snprintf(fieldName, sizeof(fieldName), "%s[0,3]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat4x4[3]);
		snprintf(fieldName, sizeof(fieldName), "%s[1,0]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat4x4[4]);
		snprintf(fieldName, sizeof(fieldName), "%s[1,1]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat4x4[5]);
		snprintf(fieldName, sizeof(fieldName), "%s[1,2]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat4x4[6]);
		snprintf(fieldName, sizeof(fieldName), "%s[1,3]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat4x4[7]);
		snprintf(fieldName, sizeof(fieldName), "%s[2,0]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat4x4[8]);
		snprintf(fieldName, sizeof(fieldName), "%s[2,1]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat4x4[9]);
		snprintf(fieldName, sizeof(fieldName), "%s[2,2]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat4x4[10]);
		snprintf(fieldName, sizeof(fieldName), "%s[2,3]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat4x4[11]);
		snprintf(fieldName, sizeof(fieldName), "%s[3,0]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat4x4[12]);
		snprintf(fieldName, sizeof(fieldName), "%s[3,1]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat4x4[13]);
		snprintf(fieldName, sizeof(fieldName), "%s[3,2]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat4x4[14]);
		snprintf(fieldName, sizeof(fieldName), "%s[3,3]", field);
		_lookupFloatValue(description, name, fieldName, &value->fmat4x4[15]);
		break;
	case GL_INT:
		value->i = 0;
		_lookupIntValue(description, name, field, &value->i);
		break;
	case GL_INT_VEC2:
		value->ivec2[0] = 0;
		value->ivec2[1] = 0;
		snprintf(fieldName, sizeof(fieldName), "%s[0]", field);
		_lookupIntValue(description, name, fieldName, &value->ivec2[0]);
		snprintf(fieldName, sizeof(fieldName), "%s[1]", field);
		_lookupIntValue(description, name, fieldName, &value->ivec2[1]);
		break;
	case GL_INT_VEC3:
		value->ivec3[0] = 0;
		value->ivec3[1] = 0;
		value->ivec3[2] = 0;
		snprintf(fieldName, sizeof(fieldName), "%s[0]", field);
		_lookupIntValue(description, name, fieldName, &value->ivec3[0]);
		snprintf(fieldName, sizeof(fieldName), "%s[1]", field);
		_lookupIntValue(description, name, fieldName, &value->ivec3[1]);
		snprintf(fieldName, sizeof(fieldName), "%s[2]", field);
		_lookupIntValue(description, name, fieldName, &value->ivec3[2]);
		break;
	case GL_INT_VEC4:
		value->ivec4[0] = 0;
		value->ivec4[1] = 0;
		value->ivec4[2] = 0;
		value->ivec4[3] = 0;
		snprintf(fieldName, sizeof(fieldName), "%s[0]", field);
		_lookupIntValue(description, name, fieldName, &value->ivec4[0]);
		snprintf(fieldName, sizeof(fieldName), "%s[1]", field);
		_lookupIntValue(description, name, fieldName, &value->ivec4[1]);
		snprintf(fieldName, sizeof(fieldName), "%s[2]", field);
		_lookupIntValue(description, name, fieldName, &value->ivec4[2]);
		snprintf(fieldName, sizeof(fieldName), "%s[3]", field);
		_lookupIntValue(description, name, fieldName, &value->ivec4[3]);
		break;
	case GL_BOOL:
		value->b = 0;
		_lookupBoolValue(description, name, field, &value->b);
		break;
	case GL_BOOL_VEC2:
		value->bvec2[0] = 0;
		value->bvec2[1] = 0;
		snprintf(fieldName, sizeof(fieldName), "%s[0]", field);
		_lookupBoolValue(description, name, fieldName, &value->bvec2[0]);
		snprintf(fieldName, sizeof(fieldName), "%s[1]", field);
		_lookupBoolValue(description, name, fieldName, &value->bvec2[1]);
		break;
	case GL_BOOL_VEC3:
		value->bvec3[0] = 0;
		value->bvec3[1] = 0;
		value->bvec3[2] = 0;
		snprintf(fieldName, sizeof(fieldName), "%s[0]", field);
		_lookupBoolValue(description, name, fieldName, &value->bvec3[0]);
		snprintf(fieldName, sizeof(fieldName), "%s[1]", field);
		_lookupBoolValue(description, name, fieldName, &value->bvec3[1]);
		snprintf(fieldName, sizeof(fieldName), "%s[2]", field);
		_lookupBoolValue(description, name, fieldName, &value->bvec3[2]);
		break;
	case GL_BOOL_VEC4:
		value->bvec4[0] = 0;
		value->bvec4[1] = 0;
		value->bvec4[2] = 0;
		value->bvec4[3] = 0;
		snprintf(fieldName, sizeof(fieldName), "%s[0]", field);
		_lookupBoolValue(description, name, fieldName, &value->bvec4[0]);
		snprintf(fieldName, sizeof(fieldName), "%s[1]", field);
		_lookupBoolValue(description, name, fieldName, &value->bvec4[1]);
		snprintf(fieldName, sizeof(fieldName), "%s[2]", field);
		_lookupBoolValue(description, name, fieldName, &value->bvec4[2]);
		snprintf(fieldName, sizeof(fieldName), "%s[3]", field);
		_lookupBoolValue(description, name, fieldName, &value->bvec4[3]);
		break;
	}
}

static void _uniformHandler(const char* sectionName, void* user) {
	struct mBKGLES2UniformList* uniforms = user;
	unsigned passId;
	int sentinel;
	if (sscanf(sectionName, "pass.%u.uniform.%n", &passId, &sentinel) < 1) {
		return;
	}
	struct mBKGLES2Uniform* u = mBKGLES2UniformListAppend(uniforms);
	u->name = sectionName;
}

static bool _loadUniform(struct Configuration* description, size_t pass, struct mBKGLES2Uniform* uniform) {
	unsigned passId;
	if (sscanf(uniform->name, "pass.%u.uniform.", &passId) < 1 || passId != pass) {
		return false;
	}
	const char* type = ConfigurationGetValue(description, uniform->name, "type");
	if (!type) {
		return false;
	}
	if (!strcmp(type, "float")) {
		uniform->type = GL_FLOAT;
	} else if (!strcmp(type, "float2")) {
		uniform->type = GL_FLOAT_VEC2;
	} else if (!strcmp(type, "float3")) {
		uniform->type = GL_FLOAT_VEC3;
	} else if (!strcmp(type, "float4")) {
		uniform->type = GL_FLOAT_VEC4;
	} else if (!strcmp(type, "float2x2")) {
		uniform->type = GL_FLOAT_MAT2;
	} else if (!strcmp(type, "float3x3")) {
		uniform->type = GL_FLOAT_MAT3;
	} else if (!strcmp(type, "float4x4")) {
		uniform->type = GL_FLOAT_MAT4;
	} else if (!strcmp(type, "int")) {
		uniform->type = GL_INT;
	} else if (!strcmp(type, "int2")) {
		uniform->type = GL_INT_VEC2;
	} else if (!strcmp(type, "int3")) {
		uniform->type = GL_INT_VEC3;
	} else if (!strcmp(type, "int4")) {
		uniform->type = GL_INT_VEC4;
	} else if (!strcmp(type, "bool")) {
		uniform->type = GL_BOOL;
	} else if (!strcmp(type, "bool2")) {
		uniform->type = GL_BOOL_VEC2;
	} else if (!strcmp(type, "bool3")) {
		uniform->type = GL_BOOL_VEC3;
	} else if (!strcmp(type, "bool4")) {
		uniform->type = GL_BOOL_VEC4;
	} else {
		return false;
	}
	_loadValue(description, uniform->name, uniform->type, "default", &uniform->value);
	_loadValue(description, uniform->name, uniform->type, "min", &uniform->min);
	_loadValue(description, uniform->name, uniform->type, "max", &uniform->max);
	const char* readable = ConfigurationGetValue(description, uniform->name, "readableName");
	if (readable) {
		uniform->readableName = strdup(readable);
	} else {
		uniform->readableName = 0;
	}
	uniform->name = strdup(strstr(uniform->name, "uniform.") + strlen("uniform."));
	return true;
}

void mBKGLES2ShaderInit(struct mBKGLES2Shader* shader, const char* vs, const char* fs, int width, int height, bool integerScaling, struct mBKGLES2Uniform* uniforms, size_t nUniforms) {
	shader->width = width;
	shader->height = height;
	shader->integerScaling = integerScaling;
	shader->filter = false;
	shader->blend = false;
	shader->dirty = true;
	shader->uniforms = uniforms;
	shader->nUniforms = nUniforms;
	
	// GBA framebuffer texture
	glGenFramebuffers(1, &shader->gba_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, shader->gba_fbo);
	glGenTextures(1, &shader->gba_tex);
	glBindTexture(GL_TEXTURE_2D, shader->gba_tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, BK_GBA_WIDTH, BK_GBA_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);		
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, shader->gba_tex, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// GBC framebuffer texture
	glGenFramebuffers(1, &shader->gbc_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, shader->gbc_fbo);
	glGenTextures(1, &shader->gbc_tex);
	glBindTexture(GL_TEXTURE_2D, shader->gbc_tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, BK_GBC_WIDTH, BK_GBC_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);		
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, shader->gbc_tex, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 创建VAO和VBO
    glGenVertexArrays(1, &shader->vao);
    glGenBuffers(1, &shader->vbo);
    
    glBindVertexArray(shader->vao);
    glBindBuffer(GL_ARRAY_BUFFER, shader->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bkQuadVerts), bkQuadVerts, GL_STATIC_DRAW);
    
    // 配置顶点属性（位置）
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    
    // 配置纹理坐标属性
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0);  // 解绑VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);  // 可选：解绑VBO

	shader->program = glCreateProgram();
	shader->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	shader->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* shaderBuffer[2];
	const GLubyte* version = glGetString(GL_VERSION);
	if (strncmp((const char*) version, "OpenGL ES ", strlen("OpenGL ES ")) == 0) {
		shaderBuffer[0] = _gles2Header;
	} else if (version[0] == '2') {
		shaderBuffer[0] = _gl2Header;
	} else {
		shaderBuffer[0] = _gl32VHeader;
	}
	if (vs) {
		shaderBuffer[1] = vs;
	} else {
		shaderBuffer[1] = _nullVertexShader;
	}
	glShaderSource(shader->vertexShader, 2, shaderBuffer, 0);

	if (shaderBuffer[0] == _gl32VHeader) {
		shaderBuffer[0] = _gl32FHeader;
	}
	if (fs) {
		shaderBuffer[1] = fs;
	} else {
		shaderBuffer[1] = _nullFragmentShader;
	}
	glShaderSource(shader->fragmentShader, 2, shaderBuffer, 0);

	glCompileShader(shader->fragmentShader);
	glCompileShader(shader->vertexShader);
	glAttachShader(shader->program, shader->vertexShader);
	glAttachShader(shader->program, shader->fragmentShader);
	glLinkProgram(shader->program);

	shader->texLocation = glGetUniformLocation(shader->program, "tex");
	shader->texSizeLocation = glGetUniformLocation(shader->program, "texSize");
	shader->positionLocation = glGetAttribLocation(shader->program, "position");
	size_t i;
	for (i = 0; i < shader->nUniforms; ++i) {
		shader->uniforms[i].location = glGetUniformLocation(shader->program, shader->uniforms[i].name);
	}



}

bool mBKGLES2ShaderLoad(struct BKVideoShader* shader, struct VDir* dir) {
	struct VFile* manifest = dir->openFile(dir, "manifest.ini", O_RDONLY);
	if (!manifest) {
		return false;
	}
	bool success = false;
	struct Configuration description;
	ConfigurationInit(&description);
	if (ConfigurationReadVFile(&description, manifest)) {
		int inShaders;
		success = _lookupIntValue(&description, "shader", "passes", &inShaders);
		if (inShaders > MAX_PASSES || inShaders < 1) {
			success = false;
		}

		if (success) {
			struct mBKGLES2Shader* shaderBlock = calloc(inShaders, sizeof(struct mBKGLES2Shader));
			int n;
			for (n = 0; n < inShaders; ++n) {
				char passName[12];
				snprintf(passName, sizeof(passName), "pass.%u", n);
				const char* fs = ConfigurationGetValue(&description, passName, "fragmentShader");
				const char* vs = ConfigurationGetValue(&description, passName, "vertexShader");
				if (fs && (fs[0] == '.' || strstr(fs, PATH_SEP))) {
					success = false;
					break;
				}
				if (vs && (vs[0] == '.' || strstr(vs, PATH_SEP))) {
					success = false;
					break;
				}
				char* fssrc = 0;
				char* vssrc = 0;
				if (fs) {
					struct VFile* fsf = dir->openFile(dir, fs, O_RDONLY);
					if (!fsf) {
						success = false;
						break;
					}
					fssrc = malloc(fsf->size(fsf) + 1);
					fssrc[fsf->size(fsf)] = '\0';
					fsf->read(fsf, fssrc, fsf->size(fsf));
					fsf->close(fsf);
				}
				if (vs) {
					struct VFile* vsf = dir->openFile(dir, vs, O_RDONLY);
					if (!vsf) {
						success = false;
						free(fssrc);
						break;
					}
					vssrc = malloc(vsf->size(vsf) + 1);
					vssrc[vsf->size(vsf)] = '\0';
					vsf->read(vsf, vssrc, vsf->size(vsf));
					vsf->close(vsf);
				}
				int width = 0;
				int height = 0;
				int scaling = 0;
				_lookupIntValue(&description, passName, "width", &width);
				_lookupIntValue(&description, passName, "height", &height);
				_lookupIntValue(&description, passName, "integerScaling", &scaling);

				struct mBKGLES2UniformList uniformVector;
				mBKGLES2UniformListInit(&uniformVector, 0);
				ConfigurationEnumerateSections(&description, _uniformHandler, &uniformVector);
				size_t u;
				for (u = 0; u < mBKGLES2UniformListSize(&uniformVector); ++u) {
					struct mBKGLES2Uniform* uniform = mBKGLES2UniformListGetPointer(&uniformVector, u);
					if (!_loadUniform(&description, n, uniform)) {
						mBKGLES2UniformListShift(&uniformVector, u, 1);
						--u;
					}
				}
				u = mBKGLES2UniformListSize(&uniformVector);
				struct mBKGLES2Uniform* uniformBlock;
				if (u) {
					uniformBlock = calloc(u, sizeof(*uniformBlock));
					memcpy(uniformBlock, mBKGLES2UniformListGetPointer(&uniformVector, 0), sizeof(*uniformBlock) * u);
				}
				mBKGLES2UniformListDeinit(&uniformVector);
				
				mBKGLES2ShaderInit(&shaderBlock[n], vssrc, fssrc, width, height, scaling, uniformBlock, u);
				int b = 0;
				_lookupIntValue(&description, passName, "blend", &b);
				if (b) {
					shaderBlock[n].blend = b;
				}
				b = 0;
				_lookupIntValue(&description, passName, "filter", &b);
				if (b) {
					shaderBlock[n].filter = b;
				}
				free(fssrc);
				free(vssrc);
			}

			if (success) {
				
				shader->nPasses = inShaders;
				shader->passes = shaderBlock;
				shader->name = ConfigurationGetValue(&description, "shader", "name");
				if (shader->name) {
					shader->name = strdup(shader->name);
				}
				shader->author = ConfigurationGetValue(&description, "shader", "author");
				if (shader->author) {
					shader->author = strdup(shader->author);
				}
				shader->description = ConfigurationGetValue(&description, "shader", "description");
				if (shader->description) {
					shader->description = strdup(shader->description);
				}
			} else {
				inShaders = n;
				for (n = 0; n < inShaders; ++n) {
					mBKGLES2ShaderDeinit(&shaderBlock[n]);
				}
				free(shaderBlock);
			}
		}
	}
	manifest->close(manifest);
	ConfigurationDeinit(&description);
	return success;
}

void mBKGLES2ShaderDeinit(struct mBKGLES2Shader* shader) {
	glDeleteTextures(1, &shader->gbc_tex);
	glDeleteTextures(1, &shader->gba_tex);
	glDeleteShader(shader->fragmentShader);
	glDeleteProgram(shader->program);
	glDeleteFramebuffers(1, &shader->gbc_fbo);
	glDeleteFramebuffers(1, &shader->gba_fbo);
#ifdef BUILD_GLES3
	if (shader->vao != (GLuint) -1) {
		glDeleteVertexArrays(1, &shader->vao);
	}
#endif
}



int bk_getMaxAspectRatio(void)
{
	float aspectX = g_view_width / (float) g_game_width;
	float aspectY = g_view_height / (float) g_game_height;
	int max = 1;
	if (aspectX > aspectY) {
		max = floor(aspectY);
	} else {
		max = floor(aspectX);
	}
	return max;
}

float bk_mapNumberToBrightness(int num) {
    if (num < 1) num = 1;
    if (num > 9) num = 9;
    
    return 0.2f * num;
}

char* bk_replace_suffix(const char* path, const char* new_suffix) {
    if (path == NULL || new_suffix == NULL) {
        return NULL;
    }
    const char* last_dot = strrchr(path, '.');
    const char* last_slash = strrchr(path, '/');
    if (last_dot != NULL && (last_slash == NULL || last_dot > last_slash)) {
        size_t base_len = last_dot - path;
        size_t new_len = base_len + strlen(new_suffix);
        
        char* new_path = (char*)malloc(new_len + 1);
        if (new_path == NULL) {
            return NULL;
        }
        strncpy(new_path, path, base_len);
        new_path[base_len] = '\0';
        
        strcat(new_path, new_suffix);
        
        return new_path;
    } else {
        size_t path_len = strlen(path);
        size_t new_len = path_len + strlen(new_suffix);
        
        char* new_path = (char*)malloc(new_len + 1);
        if (new_path == NULL) {
            return NULL;
        }
        
        strcpy(new_path, path);
        
        strcat(new_path, new_suffix);
        
        return new_path;
    }
}


int bk_Mask_OffsetRead(const char* maskPath)
{
	char* maskConfigFilePath = bk_replace_suffix(maskPath, ".cfg");
	if (maskConfigFilePath == NULL) {
		return 0;
	}
	int Padding_Bottom = getIntValue(maskConfigFilePath, "Padding_Bottom");
	int mask_height = getIntValue(maskConfigFilePath, "mask_height");

	int mask_offset = (int)(g_view_height * (Padding_Bottom / (float)mask_height));


	free(maskConfigFilePath);
	cleanup_config_cache();
	return mask_offset;
}


int bk_Normal_offset(struct mGUIRunner* runner, int height, int vheight){
	int asHeight = (int)(height * (float)g_cur_screen_aspect_ratio);
	int renderY = (g_view_height - asHeight) / 2;
	if(runner->core->platform(runner->core) == 1)
	{
		return renderY - g_gbc_video_offset_y;
	}else{
		return renderY - g_gba_video_offset_y;
		
	}
}