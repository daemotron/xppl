#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <xppl.h>
#include <xppl_alloc.h>
#include <xppl_test.h>

#include "_test.h"


void
xppl_test_runner_init(xppl_test_runner_t *tr)
{
    tr->count = 0;
    tr->suites = NULL;
}


void
xppl_test_runner_destroy(xppl_test_runner_t *tr)
{
    for (unsigned int i = 0; i < tr->count; i++)
    {
        _xppl_test_suite_destroy(&tr->suites[i]);
    }

    if (tr->suites != NULL)
    {
        free(tr->suites);
    }
    tr->count = 0;
}


xppl_test_suite_t *
xppl_test_suite_create(xppl_test_runner_t *tr, const char *name)
{
    tr->count++;

    if (tr->count == 1)
    {
        tr->suites = xppl_calloc(1, sizeof(xppl_test_suite_t));
    }
    else
    {
        tr->suites = xppl_realloc(tr->suites, tr->count * sizeof(xppl_test_suite_t));
    }

    xppl_test_suite_t *ptr = &tr->suites[tr->count - 1];
    _xppl_test_suite_init(ptr, name);
    return ptr;
}


xppl_test_case_t *
xppl_test_case_create(xppl_test_suite_t *ts, xppl_test_func_t f, const char *name)
{
    ts->count++;

    if (ts->count == 1)
    {
        ts->tests = xppl_calloc(1, sizeof(xppl_test_case_t));
    }
    else
    {
        ts->tests = xppl_realloc(ts->tests, ts->count * sizeof(xppl_test_case_t));
    }

    xppl_test_case_t *ptr = &ts->tests[ts->count - 1];
    _xppl_test_case_init(ptr, f, name);
    return ptr;
}


bool
xppl_test_run(xppl_test_runner_t *tr)
{
    bool runner_result = true;
    xppl_test_stat_t runner_stat;
    runner_stat.conducted = 0;
    runner_stat.failed = 0;
    runner_stat.passed = 0;

    for (unsigned int i = 0; i < tr->count; i++)
    {
        printf("Test Suite %03u: %s\n", i + 1, tr->suites[i].name);
        printf("%.*s\n", (int)strlen(tr->suites[i].name) + 16, _XPPL_TEST_TEST_UNDERLINE);
        xppl_test_stat_t suite_stat;
        runner_result = _xppl_test_suite_run(&tr->suites[i], &suite_stat) && runner_result;
        printf("\n");
        printf(
            "%s: %d tests conducted, %d tests passed, %d tests failed\n\n", 
            suite_stat.failed > 0 ? "FAILED" : "PASSED", 
            suite_stat.conducted, suite_stat.passed, suite_stat.failed
        );
        runner_stat.conducted += suite_stat.conducted;
        runner_stat.passed += suite_stat.passed;
        runner_stat.failed += suite_stat.failed;
    }
    printf("%s: %d tests conducted, %d tests passed, %d tests failed\n",
        runner_result ? "PASSED" : "FAULED", 
        runner_stat.conducted, runner_stat.passed, runner_stat.failed
    );
    return runner_result;
}


bool
xppl_test_assert_str_equals(const char *s1, const char *s2)
{
    return strlen(s1) == strlen(s2) && strncmp(s1, s2, xppl_min(strlen(s1), strlen(s2))) == 0;
}
