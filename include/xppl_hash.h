#ifndef _XPPL_MAP_HASH_H_
#define _XPPL_MAP_HASH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <xppl_int.h>

#define XPPL_HASH_FNV_OFFSET 14695981039346656037UL
#define XPPL_HASH_FNV_PRIME 1099511628211UL

uint64_t xppl_hash_fnv1(const char *);
uint64_t xppl_hash_fnv1a(const char *);

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_MAP_HASH_H_ */
