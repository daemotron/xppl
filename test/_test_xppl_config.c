#include <stdbool.h>

#include <xppl_config.h>
#include <xppl_test.h>

#include "_test_xppl_config.h"

#if IBM
#define __TEST_XPPL_CONFIG_SEP "\\"
#define __TEST_XPPL_CONFIG_PATH "output\\project\\config.txt" 
#else
#define __TEST_XPPL_CONFIG_SEP "/"
#define __TEST_XPPL_CONFIG_PATH "output/project/config.txt"
#endif

bool __test_xppl_config_01(void);
bool __test_xppl_config_02(void);
bool __test_xppl_config_03(void);
bool __test_xppl_config_04(void);
bool __test_xppl_config_05(void);


void
_test_xppl_config_register(xppl_test_runner_t *tr)
{
    xppl_test_suite_t *suite = xppl_test_suite_create(tr, "XPPL Config");
    xppl_test_case_create(suite, __test_xppl_config_01, "xppl.config.ctx init create file");
    xppl_test_case_create(suite, __test_xppl_config_02, "xppl.config.ctx init entries");
    xppl_test_case_create(suite, __test_xppl_config_03, "xppl.config.ctx init entry count");
    xppl_test_case_create(suite, __test_xppl_config_04, "xppl.config.ctx init path");
    xppl_test_case_create(suite, __test_xppl_config_05, "xppl.config.ctx init separator");
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
