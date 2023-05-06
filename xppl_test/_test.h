#ifndef _XPPL_TEST_TEST_H_
#define _XPPL_TEST_TEST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <xppl_test.h>

#define _XPPL_TEST_TEST_UNDERLINE "================================================================================================================================"

void _xppl_test_case_init(xppl_test_case_t *, xppl_test_func_t, const char *);
void _xppl_test_case_destroy(xppl_test_case_t *);

void _xppl_test_suite_init(xppl_test_suite_t *, const char *);
void _xppl_test_suite_destroy(xppl_test_suite_t *);
bool _xppl_test_suite_run(xppl_test_suite_t *);


#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_TEST_TEST_H_ */
