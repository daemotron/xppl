#ifndef _XPPL_INT_H_
#define _XPPL_INT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifdef __SIZEOF_INT128__
#define XPPL_INT_128
typedef __int128_t int128_t;
typedef __uint128_t uint128_t;
#endif

#define xppl_int_abs(a) ((a) < 0 ? (-(a)) : (a))

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_INT_H_ */
