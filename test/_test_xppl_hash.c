#include <xppl_test.h>
#include <xppl_hash.h>
#include <stdio.h>

#include "_test_xppl_hash.h"


bool __test_xppl_hash_01_fnv1(void);
bool __test_xppl_hash_02_fnv1(void);
bool __test_xppl_hash_03_fnv1(void);
bool __test_xppl_hash_04_fnv1a(void);
bool __test_xppl_hash_05_fnv1a(void);
bool __test_xppl_hash_06_fnv1a(void);


void
_test_xppl_hash_register(xppl_test_runner_t *tr)
{
    xppl_test_suite_t *suite = xppl_test_suite_create(tr, "XPPL Hash");
    xppl_test_case_create(suite, __test_xppl_hash_01_fnv1, "xppl.hash.fnv1 foo");
    xppl_test_case_create(suite, __test_xppl_hash_02_fnv1, "xppl.hash.fnv1 bar");
    xppl_test_case_create(suite, __test_xppl_hash_03_fnv1, "xppl.hash.fnv1 bazz");
    xppl_test_case_create(suite, __test_xppl_hash_04_fnv1a, "xppl.hash.fnv1a foo");
    xppl_test_case_create(suite, __test_xppl_hash_05_fnv1a, "xppl.hash.fnv1a bar");
    xppl_test_case_create(suite, __test_xppl_hash_06_fnv1a, "xppl.hash.fnv1a bazz");
}


bool
__test_xppl_hash_01_fnv1(void)
{
    return (15621798640163566899UL == xppl_hash_fnv1("foo"));
}


bool
__test_xppl_hash_02_fnv1(void)
{
    return (15625701906442958976UL == xppl_hash_fnv1("bar"));
}


bool
__test_xppl_hash_03_fnv1(void)
{
    return (2813642004701319010UL == xppl_hash_fnv1("bazz"));
}


bool
__test_xppl_hash_04_fnv1a(void)
{
    return (15902901984413996407UL == xppl_hash_fnv1a("foo"));
}


bool
__test_xppl_hash_05_fnv1a(void)
{
    return (16101355973854746UL == xppl_hash_fnv1a("bar"));
}


bool
__test_xppl_hash_06_fnv1a(void)
{
    return (11123581685902069096UL == xppl_hash_fnv1a("bazz"));
}
