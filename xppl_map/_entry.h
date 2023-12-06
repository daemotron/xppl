#ifndef _XPPL_MAP_ENTRY_H_
#define _XPPL_MAP_ENTRY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <xppl_map.h>

void _entry_create_i(xppl_map_t *, const char *, int);
void _entry_create_l(xppl_map_t *, const char *, long);
void _entry_create_f(xppl_map_t *, const char *, float);
void _entry_create_d(xppl_map_t *, const char *, double);
void _entry_create_u(xppl_map_t *, const char *, unsigned long);
void _entry_create_p(xppl_map_t *, const char *, void *);
void _entry_destroy(xppl_map_entry_t *);

xppl_map_entry_t * _entry_get(xppl_map_t *, const char *);
xppl_map_entry_t * _entry_get_or_create(xppl_map_t *, const char *);

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_MAP_ENTRY_H_ */
