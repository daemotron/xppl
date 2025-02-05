#include <float.h>
#include <stdlib.h>

#include <xppl.h>
#include <xppl_config.h>
#include "_cast.h"


#define __CAST_FLOAT_FORMATTER_WRITE "%." xppl_str(DBL_DIG) "lf"
#define __CAST_STRING_FORMATTER_READ "%" xppl_str(XPPL_CONFIG_STR_MAXLEN) "[^\n\r]"


const char *
_cast_get_formatter(xppl_config_type_t type, _cast_formatter_type_t ftype)
{
    switch (type)
    {
        case XPPL_CONFIG_INVAL:
            return "";
            break;
        
        case XPPL_CONFIG_INT:
            return "%lli";
            break;

        case XPPL_CONFIG_FLOAT:
            if (ftype == _CAST_FORMATTER_WRITE)
            {
                return __CAST_FLOAT_FORMATTER_WRITE;
            }
            else
            {
                return "%lf";
            }
            break;

        case XPPL_CONFIG_UNSIGNED:
            return "%llu";
            break;

        case XPPL_CONFIG_STRING:
            if (ftype == _CAST_FORMATTER_READ)
            {
                return __CAST_STRING_FORMATTER_READ;
            }
            else
            {
                return "%s";
            }
            break;

        default:
            return "";
            break;
    }
}


size_t
_cast_get_size(xppl_config_type_t type)
{
    switch (type)
    {
        case XPPL_CONFIG_INVAL:
            return 0;
            break;
        
        case XPPL_CONFIG_INT:
            return sizeof(long long);
            break;

        case XPPL_CONFIG_FLOAT:
            return sizeof(double);
            break;

        case XPPL_CONFIG_UNSIGNED:
            return sizeof(unsigned long long);
            break;

        case XPPL_CONFIG_STRING:
            return sizeof(char);
            break;

        default:
            return 0;
            break;
    }
}
