#ifndef _XPPL_MAP_H_
#define _XPPL_MAP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <xppl_int.h>

#define XPPL_MAP_PAGE_SIZE_DEFAULT (size_t)16UL

typedef struct xppl_map_entry_s
{
    uint64_t hash;
    char *key;
    union
    {
        int i;
        long l;
        float f;
        double d;
        unsigned long u;
        void *p; 
    } value;
} xppl_map_entry_t;

typedef struct xppl_map_s
{
    xppl_map_entry_t **entries;
    size_t pages;
    size_t page_size;
} xppl_map_t;

void xppl_map_init(xppl_map_t *, size_t);
void xppl_map_destroy(xppl_map_t *);

int xppl_map_get_i(xppl_map_t *, const char *);
long xppl_map_get_l(xppl_map_t *, const char *);
float xppl_map_get_f(xppl_map_t *, const char *);
double xppl_map_get_d(xppl_map_t *, const char *);
unsigned long xppl_map_get_u(xppl_map_t *, const char *);
void *xppl_map_get_p(xppl_map_t *, const char *);

void xppl_map_set_i(xppl_map_t *, const char *, int);
void xppl_map_set_l(xppl_map_t *, const char *, long);
void xppl_map_set_f(xppl_map_t *, const char *, float);
void xppl_map_set_d(xppl_map_t *, const char *, double);
void xppl_map_set_u(xppl_map_t *, const char *, unsigned long);
void xppl_map_set_p(xppl_map_t *, const char *, void *);

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_MAP_H_ */
