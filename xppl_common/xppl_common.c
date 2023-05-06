#include <stdarg.h>
#include <stdbool.h>

#include <xppl.h>
#include "_log.h"
#include "_path.h"


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
    _log_msg_v(XPPL_LOG_ERROR, message, args);
    va_end(args);
}


void
xppl_log_warn(const char *message, ...)
{
    va_list args;
    va_start(args, message);
    _log_msg_v(XPPL_LOG_WARN, message, args);
    va_end(args);
}


void
xppl_log_info(const char *message, ...)
{
    va_list args;
    va_start(args, message);
    _log_msg_v(XPPL_LOG_INFO, message, args);
    va_end(args);
}


void
xppl_log_debug(const char *message, ...)
{
    va_list args;
    va_start(args, message);
    _log_msg_v(XPPL_LOG_DEBUG, message, args);
    va_end(args);
}


bool
xppl_path_exists(const char *path)
{
    return _path_exists(path);
}


void
xppl_path_create(const char *path)
{
    _path_create_dir(path);
}


void
xppl_path_create_recursive(const char *path, const char *separator)
{
    _path_create_dir_recursive(path, separator);
}


void
xppl_destroy(void)
{
    _log_destroy();
}
