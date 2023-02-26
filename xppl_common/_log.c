#include <string.h>

#include <xppl.h>
#include "_log.h"


static char _log_prefix[_LOG_PREFIX_SIZE];
static xppl_logfunc_t _log_func;


void
_log_init(xppl_logfunc_t log_func, const char *prefix)
{
    memset(_log_prefix, '\0', _LOG_PREFIX_SIZE);
    strncpy(_log_prefix, prefix, _LOG_PREFIX_SIZE);
    _log_func = log_func;
}
