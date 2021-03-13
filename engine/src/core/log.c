#include "log.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

b8 initialize_log() {
    // TODO: create log file.
    return TRUE;
}

void shutdown_log() {
    // TODO: cleanup and batch write to log before shutdown.
}

YAPI void logger(log_level level, const char* message, ...) {
    const char* log_level_strings[6] = {"FATAL", "ERROR", "WARN", "INFO", "DEBUG]", "TRACE"};

    // TODO: find a better way to avoid dynamic allocation
    i32 message_length = 32000;
    char out_message[message_length];
    memset(out_message, 0, sizeof(out_message));
    __builtin_va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(out_message, message_length, message, arg_ptr);
    va_end(arg_ptr);
    char out_message2[message_length];
    sprintf(out_message2, "[%s]: %s\n", log_level_strings[level], out_message);
    printf("%s", out_message2);
}