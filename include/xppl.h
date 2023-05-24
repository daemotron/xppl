#ifndef _XPPL_H_
#define _XPPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#define xppl_max(a,b) ((a) >= (b) ? (a) : (b))
#define xppl_min(a,b) ((a) <= (b) ? (a) : (b))

#define xppl_unused(x) (void)(x)

#define xppl_xstr(s) #s
#define xppl_str(s) xppl_xstr(s)

#if IBM
#include <windows.h>
#define	EXCEPTION_ASSERTION_FAILED 0x8000
#define	xppl_crash()	\
	do { \
		RaiseException(EXCEPTION_ASSERTION_FAILED, \
		    EXCEPTION_NONCONTINUABLE, 0, NULL); \
		/* Needed to avoid no-return-value warnings */ \
		abort(); \
	} while (0)
#else /* ! IBM */
#define	xppl_crash() abort()
#endif

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_H_ */
