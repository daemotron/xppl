#include <stdarg.h>
#include <string.h>
#include <time.h>

#include <xppl.h>
#include "_log.h"


static char _log_prefix[_LOG_PREFIX_SIZE];
static xppl_logfunc_t _log_func;
static xppl_loglevel_t _log_level;


void
_log_init(xppl_logfunc_t log_func, xppl_loglevel_t log_level, const char *prefix)
{
    memset(_log_prefix, '\0', _LOG_PREFIX_SIZE);
    strncpy(_log_prefix, prefix, _LOG_PREFIX_SIZE);
    _log_func = log_func;
    _log_level = log_level;
}


void
_log_level_set(xppl_loglevel_t level)
{
    _log_level = level;
}


const char *
_log_level_string(xppl_loglevel_t level)
{
    switch (level)
    {
        case XPPL_DEBUG:
            return "DEBUG";
            break;

        case XPPL_INFO:
            return " INFO";
            break;

        case XPPL_WARN:
            return " WARN";
            break;

        case XPPL_ERROR:
            return "ERROR";
            break;

        default:
            return "INVAL";
            break;
    }
}


void
_log_msg_v(xppl_loglevel_t level, const char *message, va_list args)
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
    if (snprintf(ful_buffer, _LOG_FUL_BUF_SIZE, _LOG_MSG_FMT, tsp_buffer, _log_prefix, _log_level_string(level), msg_buffer) < 0)
    {
        _log_func("XPPL_ERROR: Unable to format full log entry.\n");
        return;
    }
    
    _log_func(ful_buffer);
}
