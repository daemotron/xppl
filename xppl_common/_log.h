#ifndef _XPPL_LOG_H_
#define _XPPL_LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define _LOG_MSG_BUF_SIZE   1024
#define _LOG_TSP_BUF_SIZE   20
#define _LOG_PREFIX_SIZE    32
#define _LOG_FUL_BUF_SIZE   1088
#define	_LOG_DATE_FMT       "%F %T"
#define _LOG_MSG_FMT        "%s [%s]: %s: %s\n"

void _log_init(xppl_logfunc_t, xppl_loglevel_t, const char *);
void _log_level_set(xppl_loglevel_t);
const char *_log_level_string(xppl_loglevel_t);
void _log_msg_v(xppl_loglevel_t, const char *, va_list);

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_LOG_H_ */
