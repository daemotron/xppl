#ifndef _XPPL_CONFIG_H_
#define _XPPL_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <stdlib.h>


#define XPPL_CONFIG_KEY_MAXLEN 128
#define XPPL_CONFIG_VAL_MAXLEN 512


typedef enum
{
    XPPL_CONFIG_INVAL = 0,
    XPPL_CONFIG_INT = 1,
    XPPL_CONFIG_FLOAT = 2,
    XPPL_CONFIG_UNSIGNED = 4,
    XPPL_CONFIG_STRING = 32
} xppl_config_type_t;


typedef void * xppl_config_data_t;


typedef struct
{
    char* key;
    xppl_config_type_t type;
    xppl_config_data_t data;
    xppl_config_data_t default_data;
} xppl_config_entry_t;


void xppl_config_init(void);
void xppl_config_destroy(void);

void xppl_config_register(const char *, xppl_config_type_t, xppl_config_data_t);
xppl_config_entry_t *xppl_config_find(const char *);

long long xppl_config_data_get_i(const char *);
long double xppl_config_data_get_f(const char *);
unsigned long long xppl_config_data_get_u(const char *);
size_t xppl_config_data_get_s(const char *, char *, size_t);

void xppl_config_data_set_i(const char *, long long);
void xppl_config_data_set_f(const char *, long double);
void xppl_config_data_set_u(const char *, unsigned long long);
void xppl_config_data_set_s(const char *, const char*);


#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_CONFIG_H_ */
