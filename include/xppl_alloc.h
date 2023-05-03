#ifndef _XPPL_ALLOC_H_
#define _XPPL_ALLOC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "xppl.h"


#if IBM
#include <winnt.h>
#define	EXCEPTION_ASSERTION_FAILED 0x8000
#define	XPPL_CRASH()	\
	do { \
		RaiseException(EXCEPTION_ASSERTION_FAILED, \
		    EXCEPTION_NONCONTINUABLE, 0, NULL); \
		/* Needed to avoid no-return-value warnings */ \
		abort(); \
	} while (0)
#else /* ! IBM */
#define	XPPL_CRASH() abort()
#endif


static inline void *
xppl_malloc(size_t size)
{
    void *ptr = malloc(size);
    if ((size > 0) && (ptr == NULL))
    {
        xppl_log_error("Failed to allocate %lu bytes of memory (out of memory)", (long unsigned)size);
        XPPL_CRASH();
    }
    return ptr;
}


static inline void *
xppl_calloc(size_t num, size_t size)
{
	void *ptr = calloc(num, size);
	if ((num > 0) && (size > 0) && (ptr == NULL))
    {
        xppl_log_error("Failed to allocate %lu x %lu bytes of memory (out of memory)", (long unsigned)num, (long unsigned)size);
		XPPL_CRASH();
	}
	return ptr;
}


static inline void *
xppl_realloc(void *old_ptr, size_t size)
{
	void *ptr = realloc(old_ptr, size);
	if ((size > 0) && (ptr == NULL)) {
		xppl_log_error("Failed to allocate %lu bytes of memory (out of memory)", (long unsigned)size);
        XPPL_CRASH();
	}
	return ptr;
}


#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_ALLOC_H_ */
