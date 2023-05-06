#ifndef _XPPL_CONFIG_CFG_H_
#define _XPPL_CONFIG_CFG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <xppl_config.h>

void _cfg_update(xppl_config_ctx_t *, const char *, const xppl_config_data_t);
void _cfg_parse(xppl_config_ctx_t *, const char *, int);

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_CONFIG_CFG_H_ */
