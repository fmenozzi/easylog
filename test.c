#include "easylog.h"

EASYLOG_INIT

int main() {
    easylog_init(stdout);

    easylog_log(INFO, "Hello from stdout!");

    FILE* fp = fopen("test.txt", "w+");
    if (!fp) {
        easylog_log_file(FATAL, stdout, "Could not open test.txt");
        return -1;
    }
    easylog_config_logfile(fp);
    easylog_log(INFO, "Hello from test.txt!");

    FILE* fp2 = fopen("test2.txt", "w+");
    if (!fp2) {
        easylog_log_file(FATAL, stdout, "Coult not open test2.txt");
    }
    easylog_config_logfile(fp2);
    easylog_log(INFO, "Hello from test%d.txt!", 2);

    easylog_destroy();

    return 0;
}
