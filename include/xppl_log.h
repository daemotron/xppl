#ifndef _XPPL_LOG_H_
#define _XPPL_LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*xppl_log_func_t)(const char *);


typedef enum xppl_log_level_n
{
    XPPL_LOG_DEBUG = 0,
    XPPL_LOG_INFO = 1,
    XPPL_LOG_WARN = 2,
    XPPL_LOG_ERROR = 4
} xppl_log_level_t;


void xppl_log_init(xppl_log_func_t, xppl_log_level_t, const char *);
void xppl_log_destroy(void);

void xppl_log_level_set(xppl_log_level_t);

void xppl_log_error(const char *message, ...);
void xppl_log_warn(const char *message, ...);
void xppl_log_info(const char *message, ...);
void xppl_log_debug(const char *message, ...);

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_LOG_H_ */
