#include <stdbool.h>
#include <stdio.h>

#include <xppl.h>
#include <xppl_test.h>

#include "_test_xppl_common.h"


void __console_log(const char *);


void
__console_log(const char *message)
{
    FILE *fp = fopen("log.txt", "a");
    fputs(message, fp);
    fclose(fp);
}


bool
__test_xppl_common_path_dirname_01(void)
{
    const char path[] = "/my/cool/path";
    const char sep[] = "/";
    char buffer[256] = { '\0' };
    xppl_path_dirname(path, sep, buffer, 256);
    return xppl_test_assert_str_equals(buffer, "/my/cool");
}


void _test_xppl_common_register(xppl_test_runner_t *tr)
{
    xppl_test_suite_t *suite = xppl_test_suite_create(tr, "XPPL Common");
    xppl_test_case_create(suite, __test_xppl_common_path_dirname_01, "xppl.path.dirname regular");
}
