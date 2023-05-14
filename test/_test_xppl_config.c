#include <stdbool.h>
#include <stdio.h>

#include <xppl_config.h>
#include <xppl_float.h>
#include <xppl_test.h>

#include "_test_xppl_config.h"

#if IBM
#define __TEST_XPPL_CONFIG_SEP "\\"
#define __TEST_XPPL_CONFIG_PATH "output\\project\\config.txt" 
#define __TEST_XPPL_CONFIG_FILE "config.txt"
#else
#define __TEST_XPPL_CONFIG_SEP "/"
#define __TEST_XPPL_CONFIG_PATH "output/project/config.txt"
#define __TEST_XPPL_CONFIG_FILE "config.txt"
#endif

static void __aux_config_file_create(void);
static void __aux_config_file_delete(void);

bool __test_xppl_config_01(void);
bool __test_xppl_config_02(void);
bool __test_xppl_config_03(void);
bool __test_xppl_config_04(void);
bool __test_xppl_config_05(void);
bool __test_xppl_config_06(void);
bool __test_xppl_config_07(void);
bool __test_xppl_config_08(void);

void
_test_xppl_config_register(xppl_test_runner_t *tr)
{
    xppl_test_suite_t *suite = xppl_test_suite_create(tr, "XPPL Config");
    xppl_test_case_create(suite, __test_xppl_config_01, "xppl.config.ctx init create file");
    xppl_test_case_create(suite, __test_xppl_config_02, "xppl.config.ctx init entries");
    xppl_test_case_create(suite, __test_xppl_config_03, "xppl.config.ctx init entry count");
    xppl_test_case_create(suite, __test_xppl_config_04, "xppl.config.ctx init path");
    xppl_test_case_create(suite, __test_xppl_config_05, "xppl.config.ctx init separator");
    xppl_test_case_create(suite, __test_xppl_config_06, "xppl.config.ctx register count");
    xppl_test_case_create(suite, __test_xppl_config_07, "xppl.config.ctx int default value");
    xppl_test_case_create(suite, __test_xppl_config_08, "xppl.config.ctx float default value");
}


bool
__test_xppl_config_01(void)
{
    xppl_config_ctx_t ctx;
    xppl_config_init(&ctx, __TEST_XPPL_CONFIG_PATH, __TEST_XPPL_CONFIG_SEP, false);
    bool result = ctx.create_if_not_exists == false;
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_02(void)
{
    xppl_config_ctx_t ctx;
    xppl_config_init(&ctx, __TEST_XPPL_CONFIG_PATH, __TEST_XPPL_CONFIG_SEP, false);
    bool result = ctx.entries == NULL;
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_03(void)
{
    xppl_config_ctx_t ctx;
    xppl_config_init(&ctx, __TEST_XPPL_CONFIG_PATH, __TEST_XPPL_CONFIG_SEP, false);
    bool result = ctx.entry_count == 0;
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_04(void)
{
    xppl_config_ctx_t ctx;
    xppl_config_init(&ctx, __TEST_XPPL_CONFIG_PATH, __TEST_XPPL_CONFIG_SEP, false);
    bool result = xppl_test_assert_str_equals(ctx.path, __TEST_XPPL_CONFIG_PATH);
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_05(void)
{
    xppl_config_ctx_t ctx;
    xppl_config_init(&ctx, __TEST_XPPL_CONFIG_PATH, __TEST_XPPL_CONFIG_SEP, false);
    bool result = xppl_test_assert_str_equals(ctx.separator, __TEST_XPPL_CONFIG_SEP);
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_06(void)
{
    xppl_config_ctx_t ctx;
    long long default_value = 42;
    xppl_config_init(&ctx, __TEST_XPPL_CONFIG_FILE, __TEST_XPPL_CONFIG_SEP, false);
    xppl_config_register(&ctx, "answer", XPPL_CONFIG_INT, &default_value);
    bool result = ctx.entry_count == 1;
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_07(void)
{
    xppl_config_ctx_t ctx;
    long long default_value = 42;
    xppl_config_init(&ctx, __TEST_XPPL_CONFIG_FILE, __TEST_XPPL_CONFIG_SEP, false);
    xppl_config_register(&ctx, "answer", XPPL_CONFIG_INT, &default_value);
    bool result = xppl_config_data_get_i(&ctx, "answer") == default_value;
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_08(void)
{
    xppl_config_ctx_t ctx;
    long double default_value = 3.1415926535;
    xppl_config_init(&ctx, __TEST_XPPL_CONFIG_FILE, __TEST_XPPL_CONFIG_SEP, false);
    xppl_config_register(&ctx, "pi", XPPL_CONFIG_FLOAT, &default_value);
    bool result = xppl_float_almost_equal_l(xppl_config_data_get_i(&ctx, "pi"), default_value);
    xppl_config_destroy(&ctx);
    return result;
}


static void
__aux_config_file_create(void)
{
    char buffer[] = "# test configuration file\n\n# syntax error\nnon ? sense\n#correct entry\nfoo = bar\nanswer = 42\npi = 3.1415926535# duplicate\nfoo = baz";
    FILE *fp = fopen(__TEST_XPPL_CONFIG_FILE, "w");
    if (fp != NULL)
    {
        fputs(buffer, fp);
        fclose(fp);
    }
}


static void
__aux_config_file_delete(void)
{
    remove(__TEST_XPPL_CONFIG_FILE);
}