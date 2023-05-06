#ifndef _XPPL_TEST_H_
#define _XPPL_TEST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>


typedef bool (*xppl_test_func_t)(void);


typedef struct xppl_test_case_s
{
    char *name;
    xppl_test_func_t runner;
    bool conduced;
    bool passed;
} xppl_test_case_t;


typedef struct xppl_test_suite_s
{
    char *name;
    unsigned int count;
    xppl_test_case_t *tests;
} xppl_test_suite_t;


typedef struct xppl_test_runner_s
{
    unsigned int count;
    xppl_test_suite_t *suites;
} xppl_test_runner_t;


void xppl_test_runner_init(xppl_test_runner_t *);
void xppl_test_runner_destroy(xppl_test_runner_t*);
xppl_test_suite_t *xppl_test_suite_create(xppl_test_runner_t *, const char *);
xppl_test_case_t *xppl_test_case_create(xppl_test_suite_t *, xppl_test_func_t, const char *);
bool xppl_test_run(xppl_test_runner_t *);

bool xppl_test_assert_str_equals(const char *, const char *);

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_TEST_H_ */
