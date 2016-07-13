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

/*
 * Initializes global log file
 */
void easylog_init(FILE* file) {
    if (file) {
        easylog_global_log.file = file;
    }
}

/*
 * Helper function for forwarding varargs to a file. Also takes care of
 * appending a newline automatically to the format string.
 */
static void easylog_log_vararg(loglevel level, FILE* file, const char* fmt, va_list args) {
    char newfmt[EASYLOG_MAX_LINE_LEN];

    snprintf(newfmt, EASYLOG_MAX_LINE_LEN, "%s: %s\n", loglevel_str(level), fmt);
    vfprintf(file, newfmt, args);
}

/*
 * Log to a specific file. Use easylog_config_logfile() to permanently
 * change the global log file.
 */
void easylog_log_file(loglevel level, FILE* file, const char* fmt, ...) {
    if (file && fmt) {
        va_list args;
        va_start(args, fmt);
        easylog_log_vararg(level, file, fmt, args);
        va_end(args);
    }
}

/*
 * Log to the current log file
 */
void easylog_log(loglevel level, const char* fmt, ...) {
    if (fmt) {
        va_list args;
        va_start(args, fmt);
        easylog_log_vararg(level, easylog_global_log.file, fmt, args);
        va_end(args);
    }
}

/*
 * Closes current log file and re-assigns it to file. The user
 * should NOT attempt to close the file passed here, as the
 * function effectively takes ownership of the file.
 */
void easylog_config_logfile(FILE* file) {
    if (file) {
        if (easylog_global_log.file) {
            fclose(easylog_global_log.file);
            easylog_global_log.file = file;
        }
    }
}

/*
 * Close current log file
 */
void easylog_destroy() {
    if (easylog_global_log.file) {
        fclose(easylog_global_log.file);
        easylog_global_log.file = NULL;
    }
}
