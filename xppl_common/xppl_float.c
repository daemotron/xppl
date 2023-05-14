#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <xppl_float.h>
#include <xppl_int.h>

/*
 * Check macro collection
 *
 * xppl_float_check return values:
 *   0 - equality test false
 *   1 - equality test true
 *   2 - equality test undetermined
 * 
 * conditions for 0:
 *   - at least one of the two numbers is infinite or
 *   - at least one of the two numbers is nan or
 *   - both are not zero and have a different sign
 * 
 * conditions for 1:
 *   - both are zero (+/- doesn't matter)
 */
#define xppl_float_neg(a)      ((a.i) < (0) ? (true) : (false))
#define xppl_float_inf(a)      ((fpclassify(a.f)) == (FP_INFINITE) ? (true) : (false))
#define xppl_float_nan(a)      ((fpclassify(a.f)) == (FP_NAN)      ? (true) : (false))
#define xppl_float_zero(a)     ((fpclassify(a.f)) == (FP_ZERO)     ? (true) : (false))

#define xppl_float_check_nan(a, b)  ((xppl_float_nan(a)) || (xppl_float_nan(b)) ? (true) : (false))
#define xppl_float_check_inf(a, b)  ((xppl_float_inf(a)) || (xppl_float_inf(b)) ? (true) : (false))
#define xppl_float_check_neg(a, b)  ((xppl_float_neg(a)) != (xppl_float_neg(b)) ? (true) : (false))
#define xppl_float_check_zero(a, b) ((xppl_float_zero(a)) && (xppl_float_zero(b)) ? (true) : (false))

#define xppl_float_check(a, b) ((xppl_float_check_nan(a, b)) ? (0) : ((xppl_float_check_inf(a, b)) ? (0) : ((xppl_float_check_zero(a, b)) ? (1) : ((xppl_float_check_neg(a, b)) ? (0) : ((a.i) == (b.i) ? (1) : (2))))))


typedef union xppl_float_float_u
{
    int32_t i;
    float f;
} xppl_float_float_t;


typedef union xppl_float_double_u
{
    int64_t i;
    double f;
} xppl_float_double_t;


#ifdef XPPL_INT_128
typedef union xppl_float_long_u
{
    int128_t i;
    long double f;
} xppl_float_long_t;
#endif


bool 
xppl_float_almost_equal_f(float f1, float f2)
{
    xppl_float_float_t uf1, uf2;
    uf1.f = f1;
    uf2.f = f2;
    int check = xppl_float_check(uf1, uf2);
    
    if (check == 0)
    {
        return false;
    }
    else if (check == 1)
    {
        return true;
    }
    
    float delta_f = fabs(f1 - f2);
    if (delta_f <= XPPL_FLOAT_MAX_ULP * FLT_EPSILON)
    {
        return true;
    }

    int32_t delta_u = xppl_int_abs(uf1.i - uf2.i);

    if (delta_u <= XPPL_FLOAT_MAX_ULP)
    {
        return true;
    }

    return false;
}


bool
xppl_float_almost_equal_d(double d1, double d2)
{
    xppl_float_double_t ud1, ud2;
    ud1.f = d1;
    ud2.f = d2;
    int check = xppl_float_check(ud1, ud2);
    
    if (check == 0)
    {
        return false;
    }
    else if (check == 1)
    {
        return true;
    }

    double delta_f = fabs(d1 - d2);
    if (delta_f <= XPPL_FLOAT_MAX_ULP * DBL_EPSILON) {
        return true;
    }

    int64_t delta_u = xppl_int_abs(ud1.i - ud2.i);

    if (delta_u <= XPPL_FLOAT_MAX_ULP)
    {
        return true;
    }

    return false;
}


bool
xppl_float_almost_equal_l(long double ld1, long double ld2)
{
#ifdef XPPL_INT_128
    xppl_float_long_t ud1, ud2;
    ud1.f = ld1;
    ud2.f = ld2;
#else
    xppl_float_double_t ud1, ud2;
    ud1.f = (double)ld1;
    ud2.f = (double)ld2;
#endif
    int check = xppl_float_check(ud1, ud2);
    
    if (check == 0)
    {
        return false;
    }
    else if (check == 1)
    {
        return true;
    }

    long double delta_f = fabsl(ld1 - ld2);
    if (delta_f <= XPPL_FLOAT_MAX_ULP * LDBL_EPSILON) {
        return true;
    }

#ifdef XPPL_INT_128
    int128_t delta_u = xppl_int_abs(ud1.i - ud2.i);
#else
    int64_t delta_u = xppl_int_abs(ud1.i - ud2.i);
#endif

    if (delta_u <= XPPL_FLOAT_MAX_ULP)
    {
        return true;
    }

    return false;
}
