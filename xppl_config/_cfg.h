#ifndef _XPPL_CONFIG_CFG_H_
#define _XPPL_CONFIG_CFG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <xppl_config.h>

#define _XPPL_CONFIG_CFG_UNDERLINE "================================================================================================================================"

void _cfg_update(xppl_config_ctx_t *, const char *, const xppl_config_data_t);
void _cfg_parse(xppl_config_ctx_t *, const char *, int);
void _cfg_create_if_not_exists(xppl_config_ctx_t *);

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_CONFIG_CFG_H_ */
