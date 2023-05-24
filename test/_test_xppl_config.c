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

bool __test_xppl_config_ctx_01(void);
bool __test_xppl_config_ctx_02(void);
bool __test_xppl_config_ctx_03(void);
bool __test_xppl_config_ctx_04(void);
bool __test_xppl_config_ctx_05(void);
bool __test_xppl_config_ctx_06(void);
bool __test_xppl_config_ctx_07(void);
bool __test_xppl_config_entry_01(void);
bool __test_xppl_config_entry_02(void);
bool __test_xppl_config_entry_03(void);
bool __test_xppl_config_entry_04(void);
bool __test_xppl_config_entry_05(void);
bool __test_xppl_config_entry_06(void);
bool __test_xppl_config_entry_07(void);
bool __test_xppl_config_entry_08(void);
bool __test_xppl_config_entry_09(void);
bool __test_xppl_config_entry_10(void);
bool __test_xppl_config_entry_11(void);
bool __test_xppl_config_file_01(void);
bool __test_xppl_config_file_02(void);

void
_test_xppl_config_register(xppl_test_runner_t *tr)
{
    xppl_test_suite_t *suite = xppl_test_suite_create(tr, "XPPL Config");
    xppl_test_case_create(suite, __test_xppl_config_ctx_01, "xppl.config.ctx   init create file");
    xppl_test_case_create(suite, __test_xppl_config_ctx_02, "xppl.config.ctx   init entries");
    xppl_test_case_create(suite, __test_xppl_config_ctx_03, "xppl.config.ctx   init entry count");
    xppl_test_case_create(suite, __test_xppl_config_ctx_04, "xppl.config.ctx   init path");
    xppl_test_case_create(suite, __test_xppl_config_ctx_05, "xppl.config.ctx   init separator");
    xppl_test_case_create(suite, __test_xppl_config_ctx_06, "xppl.config.ctx   init title");
    xppl_test_case_create(suite, __test_xppl_config_ctx_07, "xppl.config.ctx   register count");
    xppl_test_case_create(suite, __test_xppl_config_entry_01, "xppl.config.entry default value int");
    xppl_test_case_create(suite, __test_xppl_config_entry_02, "xppl.config.entry default value float");
    xppl_test_case_create(suite, __test_xppl_config_entry_03, "xppl.config.entry default value unsigned");
    xppl_test_case_create(suite, __test_xppl_config_entry_04, "xppl.config.entry default value string");
    xppl_test_case_create(suite, __test_xppl_config_entry_05, "xppl.config.entry set & get value int");
    xppl_test_case_create(suite, __test_xppl_config_entry_06, "xppl.config.entry set & get value float");
    xppl_test_case_create(suite, __test_xppl_config_entry_07, "xppl.config.entry set & get value unsigned");
    xppl_test_case_create(suite, __test_xppl_config_entry_08, "xppl.config.entry set & get value string");
    xppl_test_case_create(suite, __test_xppl_config_entry_09, "xppl.config.entry set & get multiple values");
    xppl_test_case_create(suite, __test_xppl_config_entry_10, "xppl.config.entry find among multiple");
    xppl_test_case_create(suite, __test_xppl_config_entry_10, "xppl.config.entry description");
    xppl_test_case_create(suite, __test_xppl_config_file_01, "xppl.config.file  load from file");
    xppl_test_case_create(suite, __test_xppl_config_file_02, "xppl.config.file  write to file");
}


bool
__test_xppl_config_ctx_01(void)
{
    xppl_config_ctx_t ctx;
    xppl_config_init(&ctx, "Test Configuration", __TEST_XPPL_CONFIG_PATH, __TEST_XPPL_CONFIG_SEP, false);
    bool result = ctx.create_if_not_exists == false;
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_ctx_02(void)
{
    xppl_config_ctx_t ctx;
    xppl_config_init(&ctx, "Test Configuration", __TEST_XPPL_CONFIG_PATH, __TEST_XPPL_CONFIG_SEP, false);
    bool result = ctx.entries == NULL;
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_ctx_03(void)
{
    xppl_config_ctx_t ctx;
    xppl_config_init(&ctx, "Test Configuration", __TEST_XPPL_CONFIG_PATH, __TEST_XPPL_CONFIG_SEP, false);
    bool result = ctx.entry_count == 0;
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_ctx_04(void)
{
    xppl_config_ctx_t ctx;
    xppl_config_init(&ctx, "Test Configuration", __TEST_XPPL_CONFIG_PATH, __TEST_XPPL_CONFIG_SEP, false);
    bool result = xppl_test_assert_str_equals(ctx.path, __TEST_XPPL_CONFIG_PATH);
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_ctx_05(void)
{
    xppl_config_ctx_t ctx;
    xppl_config_init(&ctx, "Test Configuration", __TEST_XPPL_CONFIG_PATH, __TEST_XPPL_CONFIG_SEP, false);
    bool result = xppl_test_assert_str_equals(ctx.separator, __TEST_XPPL_CONFIG_SEP);
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_ctx_06(void)
{
    xppl_config_ctx_t ctx;
    xppl_config_init(&ctx, "Test Configuration", __TEST_XPPL_CONFIG_PATH, __TEST_XPPL_CONFIG_SEP, false);
    bool result = xppl_test_assert_str_equals(ctx.title, "Test Configuration");
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_ctx_07(void)
{
    xppl_config_ctx_t ctx;
    long long default_value = 42;
    xppl_config_init(&ctx, "Test Configuration", __TEST_XPPL_CONFIG_FILE, __TEST_XPPL_CONFIG_SEP, false);
    xppl_config_register(&ctx, "answer", XPPL_CONFIG_INT, &default_value, NULL);
    bool result = ctx.entry_count == 1;
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_entry_01(void)
{
    xppl_config_ctx_t ctx;
    long long default_value = 42;
    xppl_config_init(&ctx, "Test Configuration", __TEST_XPPL_CONFIG_FILE, __TEST_XPPL_CONFIG_SEP, false);
    xppl_config_register(&ctx, "answer", XPPL_CONFIG_INT, &default_value, NULL);
    bool result = xppl_config_data_get_i(&ctx, "answer") == default_value;
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_entry_02(void)
{
    xppl_config_ctx_t ctx;
    long double default_value = 3.1415926535L;
    xppl_config_init(&ctx, "Test Configuration", __TEST_XPPL_CONFIG_FILE, __TEST_XPPL_CONFIG_SEP, false);
    xppl_config_register(&ctx, "pi", XPPL_CONFIG_FLOAT, &default_value, NULL);
    bool result = xppl_float_almost_equal_l(xppl_config_data_get_f(&ctx, "pi"), default_value);
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_entry_03(void)
{
    xppl_config_ctx_t ctx;
    unsigned long long default_value = 9460730472580800ULL;
    xppl_config_init(&ctx, "Test Configuration", __TEST_XPPL_CONFIG_FILE, __TEST_XPPL_CONFIG_SEP, false);
    xppl_config_register(&ctx, "light-year", XPPL_CONFIG_UNSIGNED, &default_value, NULL);
    bool result = xppl_config_data_get_u(&ctx, "light-year") == default_value;
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_entry_04(void)
{
    xppl_config_ctx_t ctx;
    char default_value[] = "The greatest enemy of knowledge is not ignorance, it is the illusion of knowledge. - Stephen Hawking";
    char return_value[256] = { '\0' };
    xppl_config_init(&ctx, "Test Configuration", __TEST_XPPL_CONFIG_FILE, __TEST_XPPL_CONFIG_SEP, false);
    xppl_config_register(&ctx, "quote", XPPL_CONFIG_STRING, default_value, NULL);
    xppl_config_data_get_s(&ctx, "quote", return_value, 256);
    bool result = xppl_test_assert_str_equals(return_value, default_value);
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_entry_05(void)
{
    xppl_config_ctx_t ctx;
    long long default_value = 42;
    long long updated_value = -42;
    xppl_config_init(&ctx, "Test Configuration", __TEST_XPPL_CONFIG_FILE, __TEST_XPPL_CONFIG_SEP, false);
    xppl_config_register(&ctx, "answer", XPPL_CONFIG_INT, &default_value, NULL);
    xppl_config_data_set_i(&ctx, "answer", updated_value);
    bool result = xppl_config_data_get_i(&ctx, "answer") == updated_value;
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_entry_06(void)
{
    xppl_config_ctx_t ctx;
    long double default_value = 3.1415926535L;
    long double updated_value = 6.02214076L;
    xppl_config_init(&ctx, "Test Configuration", __TEST_XPPL_CONFIG_FILE, __TEST_XPPL_CONFIG_SEP, false);
    xppl_config_register(&ctx, "pi", XPPL_CONFIG_FLOAT, &default_value, NULL);
    xppl_config_data_set_f(&ctx, "pi", updated_value);
    bool result = xppl_float_almost_equal_l(xppl_config_data_get_f(&ctx, "pi"), updated_value);
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_entry_07(void)
{
    xppl_config_ctx_t ctx;
    unsigned long long default_value = 9460730472580800ULL;
    unsigned long long updated_value = 149597870700ULL;
    xppl_config_init(&ctx, "Test Configuration", __TEST_XPPL_CONFIG_FILE, __TEST_XPPL_CONFIG_SEP, false);
    xppl_config_register(&ctx, "light-year", XPPL_CONFIG_UNSIGNED, &default_value, NULL);
    xppl_config_data_set_u(&ctx, "light-year", updated_value);
    bool result = xppl_config_data_get_u(&ctx, "light-year") == updated_value;
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_entry_08(void)
{
    xppl_config_ctx_t ctx;
    char default_value[] = "The greatest enemy of knowledge is not ignorance, it is the illusion of knowledge. - Stephen Hawking";
    char updated_value[] = "Imagination is more important than knowledge. - Albert Einstein";
    char return_value[256] = { '\0' };
    xppl_config_init(&ctx, "Test Configuration", __TEST_XPPL_CONFIG_FILE, __TEST_XPPL_CONFIG_SEP, false);
    xppl_config_register(&ctx, "quote", XPPL_CONFIG_STRING, default_value, NULL);
    xppl_config_data_set_s(&ctx, "quote", updated_value);
    xppl_config_data_get_s(&ctx, "quote", return_value, 256);
    bool result = xppl_test_assert_str_equals(return_value, updated_value);
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_entry_09(void)
{
    xppl_config_ctx_t ctx;
    long long default_i = 42;
    long double default_f = 3.1415926535L;
    unsigned long long default_u = 9460730472580800ULL;
    char default_s[] = "The greatest enemy of knowledge is not ignorance, it is the illusion of knowledge. - Stephen Hawking";
    char return_s[256] = { '\0' };
    xppl_config_init(&ctx, "Test Configuration", __TEST_XPPL_CONFIG_FILE, __TEST_XPPL_CONFIG_SEP, false);
    xppl_config_register(&ctx, "answer", XPPL_CONFIG_INT, &default_i, NULL);
    xppl_config_register(&ctx, "pi", XPPL_CONFIG_FLOAT, &default_f, NULL);
    xppl_config_register(&ctx, "light-year", XPPL_CONFIG_UNSIGNED, &default_u, NULL);
    xppl_config_register(&ctx, "quote", XPPL_CONFIG_STRING, default_s, NULL);
    bool result_i = xppl_config_data_get_i(&ctx, "answer") == default_i;
    bool result_f = xppl_float_almost_equal_l(xppl_config_data_get_f(&ctx, "pi"), default_f);
    bool result_u = xppl_config_data_get_u(&ctx, "light-year") == default_u;
    xppl_config_data_get_s(&ctx, "quote", return_s, 256);
    bool result_s = xppl_test_assert_str_equals(return_s, default_s);
    xppl_config_destroy(&ctx);
    return result_i && result_f && result_u && result_s;
}


bool
__test_xppl_config_entry_10(void)
{
    xppl_config_ctx_t ctx;
    long long default_i = 42;
    long double default_f = 3.1415926535L;
    unsigned long long default_u = 9460730472580800ULL;
    char default_s[] = "The greatest enemy of knowledge is not ignorance, it is the illusion of knowledge. - Stephen Hawking";
    xppl_config_init(&ctx, "Test Configuration", __TEST_XPPL_CONFIG_FILE, __TEST_XPPL_CONFIG_SEP, false);
    xppl_config_register(&ctx, "answer", XPPL_CONFIG_INT, &default_i, NULL);
    xppl_config_register(&ctx, "pi", XPPL_CONFIG_FLOAT, &default_f, NULL);
    xppl_config_register(&ctx, "light-year", XPPL_CONFIG_UNSIGNED, &default_u, NULL);
    xppl_config_register(&ctx, "quote", XPPL_CONFIG_STRING, default_s, NULL);
    xppl_config_entry_t *entry = xppl_config_find(&ctx, "light-year");
    bool result_found = entry != NULL;
    bool result_type = entry->type == XPPL_CONFIG_UNSIGNED;
    bool result_data = *((unsigned long long *)entry->data) == default_u;
    bool result_key = xppl_test_assert_str_equals(entry->key, "light-year");
    return result_found && result_type && result_key && result_data;
}


bool
__test_xppl_config_entry_11(void)
{
    xppl_config_ctx_t ctx;
    long long default_value = 42;
    xppl_config_init(&ctx, "Test Configuration", __TEST_XPPL_CONFIG_FILE, __TEST_XPPL_CONFIG_SEP, false);
    xppl_config_register(&ctx, "answer", XPPL_CONFIG_INT, &default_value, "The answer to the ultimate question of life, the universe and everything");
    bool result = xppl_test_assert_str_equals(ctx.title, "The answer to the ultimate question of life, the universe and everything");
    xppl_config_destroy(&ctx);
    return result;
}


bool
__test_xppl_config_file_01(void)
{
    xppl_config_ctx_t ctx;
    long long init_i = -42;
    long double init_f = 6.02214076L;
    unsigned long long init_u = 9460730472580800ULL;
    char init_s[] = "boo";
    long long correct_i = 42;
    long double correct_f = 3.1415926535L;
    unsigned long long correct_u = 9460730472580800ULL;
    char correct_s[] = "baz";
    char return_s[256] = { '\0' };

    xppl_config_init(&ctx, "Test Configuration", __TEST_XPPL_CONFIG_FILE, __TEST_XPPL_CONFIG_SEP, false);
    xppl_config_register(&ctx, "answer", XPPL_CONFIG_INT, &init_i, NULL);
    xppl_config_register(&ctx, "pi", XPPL_CONFIG_FLOAT, &init_f, NULL);
    xppl_config_register(&ctx, "light-year", XPPL_CONFIG_UNSIGNED, &init_u, NULL);
    xppl_config_register(&ctx, "foo", XPPL_CONFIG_STRING, init_s, NULL);
    
    __aux_config_file_create();
    xppl_config_load(&ctx);
    __aux_config_file_delete();

    bool result_i = xppl_config_data_get_i(&ctx, "answer") == correct_i;
    bool result_f = xppl_float_almost_equal_l(xppl_config_data_get_f(&ctx, "pi"), correct_f);
    bool result_u = xppl_config_data_get_u(&ctx, "light-year") == correct_u;
    xppl_config_data_get_s(&ctx, "foo", return_s, 256);
    bool result_s = xppl_test_assert_str_equals(return_s, correct_s);
    xppl_config_destroy(&ctx);
    return result_i && result_f && result_u && result_s;
}


bool
__test_xppl_config_file_02(void)
{
    xppl_config_ctx_t ctx;
    long long default_i = 42;
    long double default_f = 3.1415926535L;
    unsigned long long default_u = 9460730472580800ULL;
    char default_s[] = "The greatest enemy of knowledge is not ignorance, it is the illusion of knowledge. - Stephen Hawking";
    char return_s[256] = { '\0' };
    xppl_config_init(&ctx, "Test Configuration", __TEST_XPPL_CONFIG_PATH, __TEST_XPPL_CONFIG_SEP, true);
    xppl_config_register(&ctx, "answer", XPPL_CONFIG_INT, &default_i, "The answer to the ultimate question of life, the universe and everything");
    xppl_config_register(&ctx, "pi", XPPL_CONFIG_FLOAT, &default_f, "Going round in circles");
    xppl_config_register(&ctx, "light-year", XPPL_CONFIG_UNSIGNED, &default_u, "Space: the final frontier.");
    xppl_config_register(&ctx, "quote", XPPL_CONFIG_STRING, default_s, "Mostly Harmless");

    xppl_config_load(&ctx);

    bool result_i = xppl_config_data_get_i(&ctx, "answer") == default_i;
    bool result_f = xppl_float_almost_equal_l(xppl_config_data_get_f(&ctx, "pi"), default_f);
    bool result_u = xppl_config_data_get_u(&ctx, "light-year") == default_u;
    xppl_config_data_get_s(&ctx, "quote", return_s, 256);
    bool result_s = xppl_test_assert_str_equals(return_s, default_s);

    xppl_config_destroy(&ctx);
    /* remove(__TEST_XPPL_CONFIG_PATH); */

    return result_i && result_f && result_u && result_s;
}


static void
__aux_config_file_create(void)
{
    char buffer[] = "# test configuration file\n\n# syntax error\nnon ? sense\n#correct entry\nfoo = bar\nanswer = 42\npi = 3.1415926535\n# duplicate\nfoo = baz";
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
