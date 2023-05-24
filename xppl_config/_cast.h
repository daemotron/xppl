#ifndef _XPPL_CONFIG_CAST_H_
#define _XPPL_CONFIG_CAST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <xppl_config.h>

typedef enum _cast_formatter_type_n
{
    _CAST_FORMATTER_READ = 0,
    _CAST_FORMATTER_WRITE = 1
} _cast_formatter_type_t;

const char *_cast_get_formatter(xppl_config_type_t, _cast_formatter_type_t);
size_t _cast_get_size(xppl_config_type_t);

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_CONFIG_CAST_H_ */
