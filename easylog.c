#include "easylog.h"

#include <stdarg.h>

#define EASYLOG_LOG_VARARG(loglevel, file, fmt, args)   \
    fprintf(file, "%s: ", loglevel_str(level));         \
    vfprintf(file, fmt, args);                          \

logstruct easylog_global_log;

static const char* loglevel_str(loglevel level) {
    switch (level) {
        case INFO:    return "INFO";
        case DEBUG:   return "DEBUG";
        case WARNING: return "WARNING";
        case ERROR:   return "ERROR";
        case FATAL:   return "FATAL";
        default:      return "<INVALID LOG LEVEL>";
    }
}

void easylog_init(FILE* file) {
    easylog_global_log.file = file;
}

void easylog_log_file(loglevel level, FILE* file, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    EASYLOG_LOG_VARARG(level, file, fmt, args);
    va_end(args);
}

void easylog_log(loglevel level, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    EASYLOG_LOG_VARARG(level, easylog_global_log.file, fmt, args);
    va_end(args);

}

void easylog_destroy() {
    if (easylog_global_log.file) {
        fclose(easylog_global_log.file);
        easylog_global_log.file = NULL;
    }
}
