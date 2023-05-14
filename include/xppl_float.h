#ifndef _XPPL_FLOAT_H_
#define _XPPL_FLOAT_H_

#ifdef __cplusplus
extern "C" {
#endif

#define XPPL_FLOAT_MAX_ULP 2

#include <stdbool.h>

bool xppl_float_almost_equal_f(float, float);
bool xppl_float_almost_equal_d(double, double);
bool xppl_float_almost_equal_l(long double, long double);

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_FLOAT_H_ */
