#include <xppl.h>
#include "_log.h"


void
xppl_init(xppl_logfunc_t log_func, const char *prefix)
{
    _log_init(log_func, prefix);
}


void
xppl_destroy(void)
{
    
}
