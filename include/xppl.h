#ifndef _XPPL_H_
#define _XPPL_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*xppl_logfunc_t)(const char *);

void xppl_init(xppl_logfunc_t, const char *);
void xppl_destroy(void);

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_H_ */
