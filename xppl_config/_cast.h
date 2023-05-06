#ifndef _XPPL_CONFIG_CAST_H_
#define _XPPL_CONFIG_CAST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <xppl_config.h>

const char *_cast_get_formatter(xppl_config_type_t);
size_t _cast_get_size(xppl_config_type_t);

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_CONFIG_CAST_H_ */
