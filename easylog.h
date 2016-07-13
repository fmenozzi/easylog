#ifndef EASYLOG_H_
#define EASYLOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

typedef enum {
    INFO,
    DEBUG,
    WARNING,
    ERROR,
    FATAL
} loglevel;

typedef struct {
    FILE* file;
} logstruct;

void easylog_init(FILE* file);
void easylog_log(loglevel level, const char* fmt, ...);
void easylog_destroy();

#define EASYLOG_INIT                        \
    extern logstruct easylog_global_log;    \

#ifdef __cplusplus
}
#endif

#endif
