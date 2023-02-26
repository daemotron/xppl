#ifndef _XPPL_LOG_H_
#define _XPPL_LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define _LOG_PREFIX_SIZE 32

void _log_init(xppl_logfunc_t, const char *);

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_LOG_H_ */
