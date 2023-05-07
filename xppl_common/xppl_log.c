#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <xppl.h>
#include <xppl_log.h>

#define _LOG_MSG_BUF_SIZE   1024
#define _LOG_TSP_BUF_SIZE   20
#define _LOG_PREFIX_SIZE    32
#define _LOG_FUL_BUF_SIZE   1088
#define	_LOG_DATE_FMT       "%Y-%m-%d %H:%M:%S"
#define _LOG_MSG_FMT        "%s [%s]: %s: %s\n"

static char _log_prefix[_LOG_PREFIX_SIZE];
static xppl_log_func_t _log_func;
static xppl_log_level_t _log_level;
static bool _log_initialized = false;

static const char *__log_level_string(xppl_log_level_t);
static void __log_msg_v(xppl_log_level_t, const char *, va_list);


static const char *
__log_level_string(xppl_log_level_t level)
{
    switch (level)
    {
        case XPPL_LOG_DEBUG:
            return "DEBUG";
            break;

        case XPPL_LOG_INFO:
            return " INFO";
            break;

        case XPPL_LOG_WARN:
            return " WARN";
            break;

        case XPPL_LOG_ERROR:
            return "ERROR";
            break;

        default:
            return "INVAL";
            break;
    }
}


static void
__log_msg_v(xppl_log_level_t level, const char *message, va_list args)
{
    if (level < _log_level)
    {
        return;
    }

    time_t timer;
    struct tm *utc_time;
    char tsp_buffer[_LOG_TSP_BUF_SIZE];
    memset(tsp_buffer, '\0', _LOG_TSP_BUF_SIZE);
    time(&timer);
    utc_time = gmtime(&timer);
    if (strftime(tsp_buffer, _LOG_TSP_BUF_SIZE, _LOG_DATE_FMT, utc_time) == 0)
    {
        _log_func("XPPL ERROR: Unable to format time stamp.\n");
        return;
    }

    char msg_buffer[_LOG_MSG_BUF_SIZE];
    memset(msg_buffer, '\0', _LOG_MSG_BUF_SIZE);
    if (vsnprintf(msg_buffer, _LOG_MSG_BUF_SIZE, message, args) < 0)
    {
        _log_func("XPPL ERROR: Unable to format log message.\n");
        return;
    }

    char ful_buffer[_LOG_FUL_BUF_SIZE];
    memset(ful_buffer, '\0', _LOG_FUL_BUF_SIZE);
    if (snprintf(ful_buffer, _LOG_FUL_BUF_SIZE, _LOG_MSG_FMT, tsp_buffer, _log_prefix, __log_level_string(level), msg_buffer) < 0)
    {
        _log_func("XPPL ERROR: Unable to format full log entry.\n");
        return;
    }
    
    _log_func(ful_buffer);
}


void
xppl_log_init(xppl_log_func_t log_func, xppl_log_level_t log_level, const char *prefix)
{
    memset(_log_prefix, '\0', _LOG_PREFIX_SIZE);
    strncpy(_log_prefix, prefix, _LOG_PREFIX_SIZE - 1);
    _log_func = log_func;
    _log_level = log_level;
    _log_initialized = true;
}


void
xppl_log_destroy(void)
{
    memset(_log_prefix, '\0', _LOG_PREFIX_SIZE);
    _log_func = NULL;
    _log_initialized = false;
}


void
xppl_log_level_set(xppl_log_level_t level)
{
    _log_level = level;
}


void
xppl_log_error(const char *message, ...)
{
    if (!_log_initialized) { return; }
    va_list args;
    va_start(args, message);
    __log_msg_v(XPPL_LOG_ERROR, message, args);
    va_end(args);
}


void
xppl_log_warn(const char *message, ...)
{
    if (!_log_initialized) { return; }
    va_list args;
    va_start(args, message);
    __log_msg_v(XPPL_LOG_WARN, message, args);
    va_end(args);
}


void
xppl_log_info(const char *message, ...)
{
    if (!_log_initialized) { return; }
    va_list args;
    va_start(args, message);
    __log_msg_v(XPPL_LOG_INFO, message, args);
    va_end(args);
}


void
xppl_log_debug(const char *message, ...)
{
    if (!_log_initialized) { return; }
    va_list args;
    va_start(args, message);
    __log_msg_v(XPPL_LOG_DEBUG, message, args);
    va_end(args);
}
