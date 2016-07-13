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
    FATAL, 
} loglevel;

void easylog_log(loglevel level, FILE* file, const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
