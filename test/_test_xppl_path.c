#include <stdbool.h>
#include <stdio.h>

#include <xppl.h>
#include <xppl_test.h>
#include <xppl_path.h>

#include "_test_xppl_path.h"

/* helper functions */
void __console_log(const char *);

/* path.dirname tests*/
bool __test_xppl_path_dirname_01(void);
bool __test_xppl_path_dirname_02(void);
bool __test_xppl_path_dirname_03(void);
bool __test_xppl_path_dirname_04(void);
bool __test_xppl_path_dirname_05(void);
bool __test_xppl_path_dirname_06(void);


void _test_xppl_path_register(xppl_test_runner_t *tr)
{
    xppl_test_suite_t *suite = xppl_test_suite_create(tr, "XPPL Path");
    xppl_test_case_create(suite, __test_xppl_path_dirname_01, "xppl.path.dirname regular ending");
    xppl_test_case_create(suite, __test_xppl_path_dirname_02, "xppl.path.dirname trailing separator");
    xppl_test_case_create(suite, __test_xppl_path_dirname_03, "xppl.path.dirname separator only");
    xppl_test_case_create(suite, __test_xppl_path_dirname_04, "xppl.path.dirname path without separator");
    xppl_test_case_create(suite, __test_xppl_path_dirname_05, "xppl.path.dirname empty path string");
    xppl_test_case_create(suite, __test_xppl_path_dirname_06, "xppl.path.dirname NULL path string");
}


void
__console_log(const char *message)
{
    FILE *fp = fopen("log.txt", "a");
    fputs(message, fp);
    fclose(fp);
}


bool
__test_xppl_path_dirname_01(void)
{
    const char path[] = "/my/cool/path";
    const char sep[] = "/";
    char buffer[256] = { '\0' };
    xppl_path_dirname(path, sep, buffer, 256);
    return xppl_test_assert_str_equals(buffer, "/my/cool");
}


bool
__test_xppl_path_dirname_02(void)
{
    const char path[] = "/my/cool/path/";
    const char sep[] = "/";
    char buffer[256] = { '\0' };
    xppl_path_dirname(path, sep, buffer, 256);
    return xppl_test_assert_str_equals(buffer, "/my/cool");
}


bool
__test_xppl_path_dirname_03(void)
{
    const char path[] = "/";
    const char sep[] = "/";
    char buffer[256] = { '\0' };
    xppl_path_dirname(path, sep, buffer, 256);
    return xppl_test_assert_str_equals(buffer, "/");
}


bool
__test_xppl_path_dirname_04(void)
{
    const char path[] = "noseparator";
    const char sep[] = "/";
    char buffer[256] = { '\0' };
    xppl_path_dirname(path, sep, buffer, 256);
    return xppl_test_assert_str_equals(buffer, ".");
}


bool
__test_xppl_path_dirname_05(void)
{
    const char path[] = "";
    const char sep[] = "/";
    char buffer[256] = { '\0' };
    xppl_path_dirname(path, sep, buffer, 256);
    return xppl_test_assert_str_equals(buffer, ".");
}


bool
__test_xppl_path_dirname_06(void)
{
    const char sep[] = "/";
    char buffer[256] = { '\0' };
    xppl_path_dirname(NULL, sep, buffer, 256);
    return xppl_test_assert_str_equals(buffer, ".");
}
