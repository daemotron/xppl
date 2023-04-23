#include <stdarg.h>

#include <xppl.h>
#include "_log.h"


void
xppl_init(xppl_logfunc_t log_func, xppl_loglevel_t log_level, const char *prefix)
{
    _log_init(log_func, log_level, prefix);
}


void
xppl_log_error(const char *message, ...)
{
    va_list args;
    va_start(args, message);
    _log_msg_v(XPPL_ERROR, message, args);
    va_end(args);
}


void
xppl_log_warn(const char *message, ...)
{
    va_list args;
    va_start(args, message);
    _log_msg_v(XPPL_WARN, message, args);
    va_end(args);
}


void
xppl_log_info(const char *message, ...)
{
    va_list args;
    va_start(args, message);
    _log_msg_v(XPPL_INFO, message, args);
    va_end(args);
}


void
xppl_log_debug(const char *message, ...)
{
    va_list args;
    va_start(args, message);
    _log_msg_v(XPPL_DEBUG, message, args);
    va_end(args);
}


void
xppl_destroy(void)
{
    _log_destroy();
}
