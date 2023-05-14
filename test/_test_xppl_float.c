#include <float.h>
#include <math.h>

#include <xppl_float.h>
#include <xppl_test.h>

#include "_test_xppl_float.h"


bool __test_xppl_float_01(void);
bool __test_xppl_float_02(void);
bool __test_xppl_float_03(void);
bool __test_xppl_float_04(void);
bool __test_xppl_float_05(void);
bool __test_xppl_float_06(void);
bool __test_xppl_float_07(void);
bool __test_xppl_float_08(void);
bool __test_xppl_float_09(void);
bool __test_xppl_float_10(void);
bool __test_xppl_float_11(void);
bool __test_xppl_float_12(void);
bool __test_xppl_float_13(void);
bool __test_xppl_float_14(void);
bool __test_xppl_float_15(void);
bool __test_xppl_float_16(void);
bool __test_xppl_float_17(void);
bool __test_xppl_float_18(void);
bool __test_xppl_float_19(void);
bool __test_xppl_float_20(void);
bool __test_xppl_float_21(void);
bool __test_xppl_float_22(void);
bool __test_xppl_float_23(void);
bool __test_xppl_float_24(void);

void
_test_xppl_float_register(xppl_test_runner_t *tr)
{
    xppl_test_suite_t *suite = xppl_test_suite_create(tr, "XPPL Float");
    xppl_test_case_create(suite, __test_xppl_float_01, "xppl.float.f zero matching");
    xppl_test_case_create(suite, __test_xppl_float_02, "xppl.float.f zero pos/neg");
    xppl_test_case_create(suite, __test_xppl_float_03, "xppl.float.f zero nan");
    xppl_test_case_create(suite, __test_xppl_float_04, "xppl.float.f zero infinity");
    xppl_test_case_create(suite, __test_xppl_float_05, "xppl.float.f const 1.0 vs 1.0");
    xppl_test_case_create(suite, __test_xppl_float_06, "xppl.float.f const 1.0 vs 1.1");
    xppl_test_case_create(suite, __test_xppl_float_07, "xppl.float.f const 1.0 vs 1.0 + 2 * epsilon");
    xppl_test_case_create(suite, __test_xppl_float_08, "xppl.float.f const 1.0 vs 1.0 + 3 * epsilon");
    xppl_test_case_create(suite, __test_xppl_float_09, "xppl.float.d zero matching");
    xppl_test_case_create(suite, __test_xppl_float_10, "xppl.float.d zero pos/neg");
    xppl_test_case_create(suite, __test_xppl_float_11, "xppl.float.d zero nan");
    xppl_test_case_create(suite, __test_xppl_float_12, "xppl.float.d zero infinity");
    xppl_test_case_create(suite, __test_xppl_float_13, "xppl.float.d const 1.0 vs 1.0");
    xppl_test_case_create(suite, __test_xppl_float_14, "xppl.float.d const 1.0 vs 1.1");
    xppl_test_case_create(suite, __test_xppl_float_15, "xppl.float.d const 1.0 vs 1.0 + 2 * epsilon");
    xppl_test_case_create(suite, __test_xppl_float_16, "xppl.float.d const 1.0 vs 1.0 + 3 * epsilon");
    xppl_test_case_create(suite, __test_xppl_float_17, "xppl.float.l zero matching");
    xppl_test_case_create(suite, __test_xppl_float_18, "xppl.float.l zero pos/neg");
    xppl_test_case_create(suite, __test_xppl_float_19, "xppl.float.l zero nan");
    xppl_test_case_create(suite, __test_xppl_float_20, "xppl.float.l zero infinity");
    xppl_test_case_create(suite, __test_xppl_float_21, "xppl.float.l const 1.0 vs 1.0");
    xppl_test_case_create(suite, __test_xppl_float_22, "xppl.float.l const 1.0 vs 1.1");
    xppl_test_case_create(suite, __test_xppl_float_23, "xppl.float.l const 1.0 vs 1.0 + 2 * epsilon");
    xppl_test_case_create(suite, __test_xppl_float_24, "xppl.float.l const 1.0 vs 1.0 + 3 * epsilon");
}



bool
__test_xppl_float_01(void)
{
    return xppl_float_almost_equal_f(0.0, 0.0);
}


bool
__test_xppl_float_02(void)
{
    return xppl_float_almost_equal_f(0.0, -0.0);
}


bool
__test_xppl_float_03(void)
{
    return !xppl_float_almost_equal_f(0.0, NAN);
}


bool
__test_xppl_float_04(void)
{
    return !xppl_float_almost_equal_f(0.0, INFINITY);
}


bool
__test_xppl_float_05(void)
{
    return xppl_float_almost_equal_f(1.0, 1.0);
}


bool
__test_xppl_float_06(void)
{
    return !xppl_float_almost_equal_f(1.0, 1.1);
}


bool
__test_xppl_float_07(void)
{
    return xppl_float_almost_equal_f(1.0, 1.0 + 2 * FLT_EPSILON);
}


bool
__test_xppl_float_08(void)
{
    return !xppl_float_almost_equal_f(1.0, 1.0 + 3 * FLT_EPSILON);
}


bool
__test_xppl_float_09(void)
{
    return xppl_float_almost_equal_d(0.0, 0.0);
}


bool
__test_xppl_float_10(void)
{
    return xppl_float_almost_equal_d(0.0, -0.0);
}


bool
__test_xppl_float_11(void)
{
    return !xppl_float_almost_equal_d(0.0, NAN);
}


bool
__test_xppl_float_12(void)
{
    return !xppl_float_almost_equal_d(0.0, INFINITY);
}


bool
__test_xppl_float_13(void)
{
    return xppl_float_almost_equal_d(1.0, 1.0);
}


bool
__test_xppl_float_14(void)
{
    return !xppl_float_almost_equal_d(1.0, 1.1);
}


bool
__test_xppl_float_15(void)
{
    return xppl_float_almost_equal_d(1.0, 1.0 + 2 * DBL_EPSILON);
}


bool
__test_xppl_float_16(void)
{
    return !xppl_float_almost_equal_d(1.0, 1.0 + 3 * DBL_EPSILON);
}


bool
__test_xppl_float_17(void)
{
    return xppl_float_almost_equal_l(0.0, 0.0);
}


bool
__test_xppl_float_18(void)
{
    return xppl_float_almost_equal_l(0.0, -0.0);
}


bool
__test_xppl_float_19(void)
{
    return !xppl_float_almost_equal_l(0.0, NAN);
}


bool
__test_xppl_float_20(void)
{
    return !xppl_float_almost_equal_l(0.0, INFINITY);
}


bool
__test_xppl_float_21(void)
{
    return xppl_float_almost_equal_l(1.0, 1.0);
}


bool
__test_xppl_float_22(void)
{
    return !xppl_float_almost_equal_l(1.0, 1.1);
}


bool
__test_xppl_float_23(void)
{
    return xppl_float_almost_equal_l(1.0, 1.0 + 2 * LDBL_EPSILON);
}


bool
__test_xppl_float_24(void)
{
    return !xppl_float_almost_equal_l(1.0, 1.0 + 3 * LDBL_EPSILON);
}
