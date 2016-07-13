#include "easylog.h"

#include <stdarg.h>

logstruct easylog_global_log;

static const char* loglevel_str(loglevel level) {
    switch (level) {
        case INFO:
            return "INFO";
        case DEBUG:
            return "DEBUG";
        case WARNING:
            return "WARNING";
        case ERROR:
            return "ERROR";
        case FATAL:
            return "FATAL";
        default:
            return "<INVALID LOG LEVEL>";
    }
}

void easylog_init(FILE* file) {
    easylog_global_log.file = file;
}

void easylog_log(loglevel level, const char* fmt, ...) {
    va_list argptr;
    va_start(argptr, fmt);
    fprintf(easylog_global_log.file, "%s: ", loglevel_str(level));
    vfprintf(easylog_global_log.file, fmt, argptr);
    va_end(argptr);
}

void easylog_destroy() {
    if (easylog_global_log.file) {
        fclose(easylog_global_log.file);
        easylog_global_log.file = NULL;
    }
}
