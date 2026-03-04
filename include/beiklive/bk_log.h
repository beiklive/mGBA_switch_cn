// 增强版日志系统，支持时间戳和配置控制

#ifndef BK_LOG_H
#define BK_LOG_H

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>

// 日志级别定义
typedef enum {
    BK_LOG_LEVEL_DEBUG = 0,
    BK_LOG_LEVEL_INFO,
    BK_LOG_LEVEL_WARN,
    BK_LOG_LEVEL_ERROR,
    BK_LOG_LEVEL_NONE
} BK_LogLevel;

// 日志配置结构体
typedef struct {
    BK_LogLevel level;
    int enable_timestamp;
    int enable_color;
} BK_LogConfig;

// 默认配置
extern BK_LogConfig g_bk_log_config;

// 初始化日志系统 - 修正语法
#define BK_LOG_INIT(log_level, enable_time, enabled_color) \
    do { \
        g_bk_log_config.level = (log_level); \
        g_bk_log_config.enable_timestamp = (enable_time); \
        g_bk_log_config.enable_color = (enabled_color); \
    } while(0)

// 获取当前时间字符串
static inline const char* bk_get_timestamp() {
    static char timestamp[64];
    time_t now;
    struct tm *tm_info;
    
    time(&now);
    tm_info = localtime(&now);
    
    // 格式: [YYYY-MM-DD HH:MM:SS]
    strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S]", tm_info);
    return timestamp;
}

// 获取日志级别字符串和颜色（ANSI颜色代码）
static inline const char* bk_get_log_level_info(BK_LogLevel level, const char** color) {
    switch(level) {
        case BK_LOG_LEVEL_DEBUG:
            if(color) *color = "\033[36m"; // 青色
            return "DEBUG";
        case BK_LOG_LEVEL_INFO:
            if(color) *color = "\033[32m"; // 绿色
            return "INFO";
        case BK_LOG_LEVEL_WARN:
            if(color) *color = "\033[33m"; // 黄色
            return "WARN";
        case BK_LOG_LEVEL_ERROR:
            if(color) *color = "\033[31m"; // 红色
            return "ERROR";
        default:
            if(color) *color = "\033[0m"; // 默认色
            return "UNKNOWN";
    }
}

// 内部日志打印函数
static inline void bk_log_internal(BK_LogLevel level, const char* file, int line, 
                                  const char* format, ...) {
    if(level < g_bk_log_config.level) {
        return; // 日志级别不够，不打印
    }
    
    // 获取时间戳
    const char* timestamp = "";
    if(g_bk_log_config.enable_timestamp) {
        timestamp = bk_get_timestamp();
    }
    
    // 获取级别信息和颜色
    const char* color_code = "";
    const char* color_reset = "";
    const char* level_str = bk_get_log_level_info(level, 
        g_bk_log_config.enable_color ? &color_code : NULL);
    
    if(g_bk_log_config.enable_color) {
        color_reset = "\033[0m";
    }
    
    // 打印日志头
    printf("%s%s %s%-5s%s ", timestamp, color_code, color_code, level_str, color_reset);
    
    // 打印源文件和行号（可选）
    if(file != NULL) {
        // 只取文件名，去掉路径
        const char* filename = strrchr(file, '/');
        if(filename == NULL) filename = strrchr(file, '\\');
        if(filename != NULL) filename++;
        else filename = file;
        
        printf("(%s:%d) ", filename, line);
    }
    
    // 打印消息
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    
    // 确保换行
    printf("\n");
    fflush(stdout);
}

// 简化配置宏 - 修正语法
#define BK_LOG_ENABLE(enable) \
    do { g_bk_log_config.level = (enable) ? BK_LOG_LEVEL_DEBUG : BK_LOG_LEVEL_NONE; } while(0)

#define BK_LOG_SET_LEVEL(log_level) \
    do { g_bk_log_config.level = (log_level); } while(0)

#define BK_LOG_SET_TIMESTAMP(enable) \
    do { g_bk_log_config.enable_timestamp = (enable); } while(0)

#define BK_LOG_SET_COLOR(enable) \
    do { g_bk_log_config.enable_color = (enable); } while(0)

// 主日志宏
#if 1
    #define BK_LOG(level, ...) \
        bk_log_internal((level), __FILE__, __LINE__, __VA_ARGS__)
    
    // 便捷日志宏
    #define BK_LOG_DEBUG(...) BK_LOG(BK_LOG_LEVEL_DEBUG, __VA_ARGS__)
    #define BK_LOG_INFO(...)  BK_LOG(BK_LOG_LEVEL_INFO, __VA_ARGS__)
    #define BK_LOG_WARN(...)  BK_LOG(BK_LOG_LEVEL_WARN, __VA_ARGS__)
    #define BK_LOG_ERROR(...) BK_LOG(BK_LOG_LEVEL_ERROR, __VA_ARGS__)
    
    // 兼容旧版本的简单日志宏
    #define BK_LOG_SIMPLE(...) \
        do { \
            if(g_bk_log_config.enable_timestamp) { \
                printf("%s ", bk_get_timestamp()); \
            } \
            printf(__VA_ARGS__); \
        } while(0)
#else
    #define BK_LOG(level, ...) 
    #define BK_LOG_DEBUG(...) 
    #define BK_LOG_INFO(...) 
    #define BK_LOG_WARN(...) 
    #define BK_LOG_ERROR(...) 
    #define BK_LOG_SIMPLE(...)
#endif

#endif // BK_LOG_H