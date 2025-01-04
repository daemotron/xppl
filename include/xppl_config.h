#ifndef _XPPL_CONFIG_H_
#define _XPPL_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <stdbool.h>
#include <stdlib.h>


#define XPPL_CONFIG_KEY_MAXLEN 128
#define XPPL_CONFIG_VAL_MAXLEN 512
#define XPPL_CONFIG_STR_MAXLEN 511
#define XPPL_CONFIG_LIN_MAXLEN 1024
#define XPPL_CONFIG_DES_MAXLEN 1024


typedef enum xppl_config_type_n
{
    XPPL_CONFIG_INVAL = 0,
    XPPL_CONFIG_INT = 1,
    XPPL_CONFIG_FLOAT = 2,
    XPPL_CONFIG_UNSIGNED = 4,
    XPPL_CONFIG_STRING = 32
} xppl_config_type_t;


typedef void * xppl_config_data_t;


typedef struct xppl_config_entry_s
{
    char *key;
    char *description;
    xppl_config_type_t type;
    xppl_config_data_t data;
    xppl_config_data_t default_data;
} xppl_config_entry_t;


typedef struct xppl_config_ctx_s
{
    char *title;
    unsigned int entry_count;
    xppl_config_entry_t *entries;
    bool create_if_not_exists;
    char *path;
    char *separator;
} xppl_config_ctx_t;


void xppl_config_init(xppl_config_ctx_t *, const char *, const char *, const char *, bool);
void xppl_config_destroy(xppl_config_ctx_t *);

void xppl_config_register(xppl_config_ctx_t *, const char *, xppl_config_type_t, xppl_config_data_t, const char *);
void xppl_config_load(xppl_config_ctx_t *);

xppl_config_entry_t *xppl_config_find(xppl_config_ctx_t *, const char *);

long long xppl_config_data_get_i(xppl_config_ctx_t *, const char *);
long double xppl_config_data_get_f(xppl_config_ctx_t *, const char *);
unsigned long long xppl_config_data_get_u(xppl_config_ctx_t *, const char *);
size_t xppl_config_data_get_s(xppl_config_ctx_t *, const char *, char *, size_t);

void xppl_config_data_set_i(xppl_config_ctx_t *, const char *, long long);
void xppl_config_data_set_f(xppl_config_ctx_t *, const char *, long double);
void xppl_config_data_set_u(xppl_config_ctx_t *, const char *, unsigned long long);
void xppl_config_data_set_s(xppl_config_ctx_t *, const char *, const char*);


#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_CONFIG_H_ */
