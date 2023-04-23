#ifndef _XPPL_H_
#define _XPPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#define xppl_max(a,b) ((a) >= (b) ? (a) : (b))
#define xppl_min(a,b) ((a) <= (b) ? (a) : (b))

typedef void (*xppl_logfunc_t)(const char *);

typedef enum
{
    XPPL_LOG_DEBUG = 0,
    XPPL_LOG_INFO = 1,
    XPPL_LOG_WARN = 2,
    XPPL_LOG_ERROR = 4
} xppl_loglevel_t;

void xppl_init(xppl_logfunc_t, xppl_loglevel_t, const char *);
void xppl_destroy(void);

void xppl_log_error(const char *message, ...);
void xppl_log_warn(const char *message, ...);
void xppl_log_info(const char *message, ...);
void xppl_log_debug(const char *message, ...);

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_H_ */
