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
_xppl_test_suite_run(xppl_test_suite_t *ts)
{
    bool suite_result = true;

    for (unsigned int i = 0; i < ts->count; i++)
    {
        printf("Executing test %03u - %s ...", i + 1, ts->tests[i].name);
        if (ts->tests[i].runner())
        {
            printf("success\n");
        }
        else
        {
            printf("failed\n");
            suite_result = false;
        }
    }

    return suite_result;
}
