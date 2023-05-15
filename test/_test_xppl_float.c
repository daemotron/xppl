#include <float.h>
#include <math.h>

#include <xppl_float.h>
#include <xppl_test.h>

#include "_test_xppl_float.h"


bool __test_xppl_float_01f(void);
bool __test_xppl_float_02f(void);
bool __test_xppl_float_03f(void);
bool __test_xppl_float_04f(void);
bool __test_xppl_float_05f(void);
bool __test_xppl_float_06f(void);
bool __test_xppl_float_07f(void);
bool __test_xppl_float_08f(void);
bool __test_xppl_float_09f(void);
bool __test_xppl_float_10f(void);
bool __test_xppl_float_11f(void);
bool __test_xppl_float_01d(void);
bool __test_xppl_float_02d(void);
bool __test_xppl_float_03d(void);
bool __test_xppl_float_04d(void);
bool __test_xppl_float_05d(void);
bool __test_xppl_float_06d(void);
bool __test_xppl_float_07d(void);
bool __test_xppl_float_08d(void);
bool __test_xppl_float_09d(void);
bool __test_xppl_float_10d(void);
bool __test_xppl_float_11d(void);
bool __test_xppl_float_01l(void);
bool __test_xppl_float_02l(void);
bool __test_xppl_float_03l(void);
bool __test_xppl_float_04l(void);
bool __test_xppl_float_05l(void);
bool __test_xppl_float_06l(void);
bool __test_xppl_float_07l(void);
bool __test_xppl_float_08l(void);
bool __test_xppl_float_09l(void);
bool __test_xppl_float_10l(void);
bool __test_xppl_float_11l(void);


void
_test_xppl_float_register(xppl_test_runner_t *tr)
{
    xppl_test_suite_t *suite = xppl_test_suite_create(tr, "XPPL Float");
    xppl_test_case_create(suite, __test_xppl_float_01f, "xppl.float.f zero matching");
    xppl_test_case_create(suite, __test_xppl_float_02f, "xppl.float.f zero pos/neg");
    xppl_test_case_create(suite, __test_xppl_float_03f, "xppl.float.f zero nan");
    xppl_test_case_create(suite, __test_xppl_float_04f, "xppl.float.f zero infinity");
    xppl_test_case_create(suite, __test_xppl_float_05f, "xppl.float.f const 1.0 vs 1.0");
    xppl_test_case_create(suite, __test_xppl_float_06f, "xppl.float.f const 1.0 vs 1.1");
    xppl_test_case_create(suite, __test_xppl_float_07f, "xppl.float.f const 1.0 vs 1.0 + 2 * epsilon");
    xppl_test_case_create(suite, __test_xppl_float_08f, "xppl.float.f const 1.0 vs 1.0 + 3 * epsilon");
    xppl_test_case_create(suite, __test_xppl_float_09f, "xppl.float.f const 0.0 vs epsilon");
    xppl_test_case_create(suite, __test_xppl_float_10f, "xppl.float.f const 0.0 vs -epsilon");
    xppl_test_case_create(suite, __test_xppl_float_11f, "xppl.float.f const +epsilon vs -epsilon");
    xppl_test_case_create(suite, __test_xppl_float_01d, "xppl.float.d zero matching");
    xppl_test_case_create(suite, __test_xppl_float_02d, "xppl.float.d zero pos/neg");
    xppl_test_case_create(suite, __test_xppl_float_03d, "xppl.float.d zero nan");
    xppl_test_case_create(suite, __test_xppl_float_04d, "xppl.float.d zero infinity");
    xppl_test_case_create(suite, __test_xppl_float_05d, "xppl.float.d const 1.0 vs 1.0");
    xppl_test_case_create(suite, __test_xppl_float_06d, "xppl.float.d const 1.0 vs 1.1");
    xppl_test_case_create(suite, __test_xppl_float_07d, "xppl.float.d const 1.0 vs 1.0 + 2 * epsilon");
    xppl_test_case_create(suite, __test_xppl_float_08d, "xppl.float.d const 1.0 vs 1.0 + 3 * epsilon");
    xppl_test_case_create(suite, __test_xppl_float_09d, "xppl.float.d const 0.0 vs epsilon");
    xppl_test_case_create(suite, __test_xppl_float_10d, "xppl.float.d const 0.0 vs -epsilon");
    xppl_test_case_create(suite, __test_xppl_float_11d, "xppl.float.d const +epsilon vs -epsilon");
    xppl_test_case_create(suite, __test_xppl_float_01l, "xppl.float.l zero matching");
    xppl_test_case_create(suite, __test_xppl_float_02l, "xppl.float.l zero pos/neg");
    xppl_test_case_create(suite, __test_xppl_float_03l, "xppl.float.l zero nan");
    xppl_test_case_create(suite, __test_xppl_float_04l, "xppl.float.l zero infinity");
    xppl_test_case_create(suite, __test_xppl_float_05l, "xppl.float.l const 1.0 vs 1.0");
    xppl_test_case_create(suite, __test_xppl_float_06l, "xppl.float.l const 1.0 vs 1.1");
    xppl_test_case_create(suite, __test_xppl_float_07l, "xppl.float.l const 1.0 vs 1.0 + 2 * epsilon");
    xppl_test_case_create(suite, __test_xppl_float_08l, "xppl.float.l const 1.0 vs 1.0 + 3 * epsilon");
    xppl_test_case_create(suite, __test_xppl_float_09l, "xppl.float.l const 0.0 vs epsilon");
    xppl_test_case_create(suite, __test_xppl_float_10l, "xppl.float.l const 0.0 vs -epsilon");
    xppl_test_case_create(suite, __test_xppl_float_11l, "xppl.float.l const +epsilon vs -epsilon");
}


bool
__test_xppl_float_01f(void)
{
    return xppl_float_almost_equal_f(0.0, 0.0);
}


bool
__test_xppl_float_02f(void)
{
    return xppl_float_almost_equal_f(0.0, -0.0);
}


bool
__test_xppl_float_03f(void)
{
    return !xppl_float_almost_equal_f(0.0, NAN);
}


bool
__test_xppl_float_04f(void)
{
    return !xppl_float_almost_equal_f(0.0, INFINITY);
}


bool
__test_xppl_float_05f(void)
{
    return xppl_float_almost_equal_f(1.0, 1.0);
}


bool
__test_xppl_float_06f(void)
{
    return !xppl_float_almost_equal_f(1.0, 1.1);
}


bool
__test_xppl_float_07f(void)
{
    return xppl_float_almost_equal_f(1.0, 1.0 + 2 * FLT_EPSILON);
}


bool
__test_xppl_float_08f(void)
{
    return !xppl_float_almost_equal_f(1.0, 1.0 + 3 * FLT_EPSILON);
}


bool
__test_xppl_float_09f(void)
{
    return xppl_float_almost_equal_f(0.0, FLT_EPSILON);
}


bool
__test_xppl_float_10f(void)
{
    return xppl_float_almost_equal_f(0.0, (-FLT_EPSILON));
}


bool
__test_xppl_float_11f(void)
{
    return !xppl_float_almost_equal_f((-FLT_EPSILON), FLT_EPSILON);
}


bool
__test_xppl_float_01d(void)
{
    return xppl_float_almost_equal_d(0.0, 0.0);
}


bool
__test_xppl_float_02d(void)
{
    return xppl_float_almost_equal_d(0.0, -0.0);
}


bool
__test_xppl_float_03d(void)
{
    return !xppl_float_almost_equal_d(0.0, NAN);
}


bool
__test_xppl_float_04d(void)
{
    return !xppl_float_almost_equal_d(0.0, INFINITY);
}


bool
__test_xppl_float_05d(void)
{
    return xppl_float_almost_equal_d(1.0, 1.0);
}


bool
__test_xppl_float_06d(void)
{
    return !xppl_float_almost_equal_d(1.0, 1.1);
}


bool
__test_xppl_float_07d(void)
{
    return xppl_float_almost_equal_d(1.0, 1.0 + 2 * DBL_EPSILON);
}


bool
__test_xppl_float_08d(void)
{
    return !xppl_float_almost_equal_d(1.0, 1.0 + 3 * DBL_EPSILON);
}


bool
__test_xppl_float_09d(void)
{
    return xppl_float_almost_equal_d(0.0, DBL_EPSILON);
}


bool
__test_xppl_float_10d(void)
{
    return xppl_float_almost_equal_d(0.0, (-DBL_EPSILON));
}


bool
__test_xppl_float_11d(void)
{
    return !xppl_float_almost_equal_d((-DBL_EPSILON), DBL_EPSILON);
}


bool
__test_xppl_float_01l(void)
{
    return xppl_float_almost_equal_l(0.0, 0.0);
}


bool
__test_xppl_float_02l(void)
{
    return xppl_float_almost_equal_l(0.0, -0.0);
}


bool
__test_xppl_float_03l(void)
{
    return !xppl_float_almost_equal_l(0.0, NAN);
}


bool
__test_xppl_float_04l(void)
{
    return !xppl_float_almost_equal_l(0.0, INFINITY);
}


bool
__test_xppl_float_05l(void)
{
    return xppl_float_almost_equal_l(1.0, 1.0);
}


bool
__test_xppl_float_06l(void)
{
    return !xppl_float_almost_equal_l(1.0, 1.1);
}


bool
__test_xppl_float_07l(void)
{
    return xppl_float_almost_equal_l(1.0, 1.0 + 2 * LDBL_EPSILON);
}


bool
__test_xppl_float_08l(void)
{
    return !xppl_float_almost_equal_l(1.0, 1.0 + 3 * LDBL_EPSILON);
}


bool
__test_xppl_float_09l(void)
{
    return xppl_float_almost_equal_l(0.0, LDBL_EPSILON);
}


bool
__test_xppl_float_10l(void)
{
    return xppl_float_almost_equal_l(0.0, (-LDBL_EPSILON));
}


bool
__test_xppl_float_11l(void)
{
    return !xppl_float_almost_equal_l((-LDBL_EPSILON), LDBL_EPSILON);
}
