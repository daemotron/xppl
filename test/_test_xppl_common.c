#include <stdio.h>

#include "_test_xppl_common.h"


void __console_log(const char *);


void
__console_log(const char *message)
{
    FILE *fp = fopen("log.txt", "a");
    fputs(message, fp);
    fclose(fp);
}
