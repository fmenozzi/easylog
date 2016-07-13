#include "easylog.h"

#include <stdarg.h>

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

void easylog_log(loglevel level, FILE* file, const char* fmt, ...) {
    va_list argptr;
    va_start(argptr, fmt);
    fprintf(file, "%s: ", loglevel_str(level));
    vfprintf(file, fmt, argptr);
    va_end(argptr);
}
