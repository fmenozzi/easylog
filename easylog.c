#include "easylog.h"

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

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

static void easylog_log_vararg(loglevel level, FILE* file, const char* fmt, va_list args) {
    char newfmt[EASYLOG_MAX_LINE_LEN];

    snprintf(newfmt, EASYLOG_MAX_LINE_LEN, "%s: %s\n", loglevel_str(level), fmt);
    vfprintf(file, newfmt, args);
}

void easylog_log_file(loglevel level, FILE* file, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    easylog_log_vararg(level, file, fmt, args);
    va_end(args);
}

void easylog_log(loglevel level, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    easylog_log_vararg(level, easylog_global_log.file, fmt, args);
    va_end(args);
}

void easylog_config_logfile(FILE* file) {
    if (file) {
        if (easylog_global_log.file) {
            fclose(easylog_global_log.file);
            easylog_global_log.file = file;
        }
    }
}

void easylog_destroy() {
    if (easylog_global_log.file) {
        fclose(easylog_global_log.file);
        easylog_global_log.file = NULL;
    }
}
