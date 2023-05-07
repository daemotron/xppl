#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <xppl.h>
#include <xppl_alloc.h>
#include <xppl_test.h>

#include "_test.h"


void
_xppl_test_case_init(xppl_test_case_t *tc, xppl_test_func_t f, const char *name)
{
    tc->name = xppl_calloc(strlen(name) + 1, sizeof(char));
    strcpy(tc->name, name);
    tc->runner = f;
    tc->conduced = false;
    tc->passed = false;
}


void
_xppl_test_case_destroy(xppl_test_case_t *tc)
{
    if (tc->name != NULL)
    {
        free(tc->name);
        tc->name = NULL;
    }
    tc->runner = NULL;
    tc->conduced = false;
    tc->passed = false;
}


void
_xppl_test_suite_init(xppl_test_suite_t *ts, const char *name)
{
    if (name != NULL)
    {
        ts->name = xppl_calloc(strlen(name) + 1, sizeof(char));
        strcpy(ts->name, name);
        ts->count = 0;
        ts->tests = NULL;
    }
}


void
_xppl_test_suite_destroy(xppl_test_suite_t *ts)
{
    if (ts->name != NULL)
    {
        free(ts->name);
        ts->name = NULL;
    }

    for (unsigned int i = 0; i < ts->count; i++)
    {
        _xppl_test_case_destroy(&ts->tests[i]);
    }

    if (ts->tests != NULL)
    {
        free(ts->tests);
        ts->tests = NULL;
    }
    ts->count = 0;
}


bool
_xppl_test_suite_run(xppl_test_suite_t *ts, xppl_test_stat_t *stat)
{
    bool suite_result = true;
    stat->conducted = 0;
    stat->failed = 0;
    stat->passed = 0;

    for (unsigned int i = 0; i < ts->count; i++)
    {
        printf("Executing test %03u - %.45s %.*s ", i + 1, ts->tests[i].name, 50 - xppl_min((int)strlen(ts->tests[i].name), 45), _XPPL_TEST_TEST_DOTS);
        if (ts->tests[i].runner())
        {
            printf("passed\n");
            stat->passed += 1;
            ts->tests[i].passed = true;
        }
        else
        {
            printf("failed\n");
            suite_result = false;
            stat->failed += 1;
            ts->tests[i].passed = false;
        }
        ts->tests[i].conduced = true;
        stat->conducted += 1;
    }

    return suite_result;
}
