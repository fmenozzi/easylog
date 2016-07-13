Simple logging library for C/C++ programs. Use `make` to run test code with `gcc`. Check out the Makefile for more.

Example use:

```c
#include "easylog.h"

EASYLOG_INIT

int main() {
    easylog_init(stdout);
    
    easylog_log(INFO, "Hello, World!");
    easylog_log(INFO, "Here's an int: %d", 3);
    
    FILE* fp = fopen("test.txt", "w+");
    if (!fp) {
        easylog_log_file(FATAL, stdout, "Could not open test.txt");
        return -1;
    }
    
    easylog_config_logfile(fp);
    
    easylog_log(INFO, "Hello from test.txt!");
}
```
