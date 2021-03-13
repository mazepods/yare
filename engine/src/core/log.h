#pragma once

#include "defines.h"

typedef enum {
    LOG_LEVEL_FATAL,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARN,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_TRACE
} log_level;

b8 initialize_log();
void shutdown_log();

YAPI void logger(log_level level, const char* message, ...);

#define LL_FATAL(message, ...) logger(LOG_LEVEL_FATAL, message, ##__VA_ARGS__);
#define LL_ERROR(message, ...) logger(LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
#define LL_WARN(message, ...) logger(LOG_LEVEL_WARN, message, ##__VA_ARGS__);
#define LL_INFO(message, ...) logger(LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#define LL_DEBUG(message, ...) logger(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#define LL_TRACE(message, ...) logger(LOG_LEVEL_TRACE, message, ##__VA_ARGS__);