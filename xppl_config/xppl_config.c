#include <string.h>

#include <xppl.h>
#include <xppl_alloc.h>
#include <xppl_config.h>

#include "_cast.h"


void _xppl_config_update(xppl_config_ctx_t *, const char *, xppl_config_data_t);


static unsigned int _xppl_config_entry_count;
static xppl_config_entry_t *_xppl_config_entries;


void
_xppl_config_update(xppl_config_ctx_t *ctx, const char *key, xppl_config_data_t data)
{
    xppl_config_entry_t *ptr = xppl_config_find(ctx, key);
    if (ptr == NULL)
    {
        xppl_log_warn("Config update: Cannot find configuration entry for %s", key);
        return;
    }
    size_t data_len = 0;
    if (ptr->type == XPPL_CONFIG_STRING)
    {
        data_len = strlnlen((char *)data, XPPL_CONFIG_VAL_MAXLEN - 1) + 1;
    }
    else
    {
        data_len = _cast_get_size(ptr->type);
    }
    if (ptr->data == NULL)
    {
        ptr->data = xppl_calloc(data_len, 1);
    }
    else
    {
        ptr->data = xppl_realloc(ptr->data, data_len);
    }
    memcpy(ptr->data, data, data_len);
}


void
xppl_config_init(xppl_config_ctx_t *ctx)
{
    ctx->entries = NULL;
    ctx->entry_count = 0;
}


void
xppl_config_destroy(xppl_config_ctx_t *ctx)
{
    for (size_t i = 0; i < ctx->entry_count; i++)
    {
        xppl_config_entry_t *current_entry = &ctx->entries[i];
        if (current_entry->key != NULL)
        {
            free(current_entry->key);
        }
        if (current_entry->data != NULL)
        {
            free(current_entry->data);
        }
        if (current_entry->default_data != NULL)
        {
            free(current_entry->default_data);
        }
    }
    free(ctx->entries);
    ctx->entries = NULL;
    ctx->entry_count = 0;
}


long long
xppl_config_data_get_i(xppl_config_ctx_t *ctx, const char *key)
{
    xppl_config_entry_t *ptr = xppl_config_find(ctx, key);
    if (ptr == NULL)
    {
        xppl_log_warn("Config data: Cannot find configuration entry for %s", key);
        return 0;
    }
    return *((long long *)ptr->data);
}


long double
xppl_config_data_get_f(xppl_config_ctx_t *ctx, const char *key)
{
    xppl_config_entry_t *ptr = xppl_config_find(ctx, key);
    if (ptr == NULL)
    {
        xppl_log_warn("Config data: Cannot find configuration entry for %s", key);
        return 0.0;
    }
    return *((long double *)ptr->data);
}


unsigned long long
xppl_config_data_get_u(xppl_config_ctx_t *ctx, const char *key)
{
    xppl_config_entry_t *ptr = xppl_config_find(ctx, key);
    if (ptr == NULL)
    {
        xppl_log_warn("Config data: Cannot find configuration entry for %s", key);
        return 0;
    }
    return *((unsigned long long *)ptr->data);
}


size_t
xppl_config_data_get_s(xppl_config_ctx_t *ctx, const char *key, char *buffer, size_t buflen)
{
    xppl_config_entry_t *ptr = xppl_config_find(ctx, key);
    if (ptr == NULL)
    {
        xppl_log_warn("Config data: Cannot find configuration entry for %s", key);
        return NULL;
    }
    strncpy(buffer, (char *)ptr->data, buflen);
    buffer[buflen-1] = '\0';
    return strlen(buffer);
}


void
xppl_config_data_set_i(xppl_config_ctx_t *ctx, const char *key, long long data)
{
    _xppl_config_update(ctx, key, &data);
}


void
xppl_config_data_set_f(xppl_config_ctx_t *ctx, const char *key, long double data)
{
    _xppl_config_update(ctx, key, &data);
}


void
xppl_config_data_set_u(xppl_config_ctx_t *ctx, const char *key, unsigned long long data)
{
    _xppl_config_update(ctx, key, &data);
}


void
xppl_config_data_set_s(xppl_config_ctx_t *ctx, const char *key, const char* data)
{
    _xppl_config_update(ctx, key, data);
}


xppl_config_entry_t *
xppl_config_find(xppl_config_ctx_t *ctx, const char *key)
{
    xppl_config_entry_t *ptr = NULL;
    for (size_t i = 0; i < ctx->entry_count; i++)
    {
        if (strncmp(key, ctx->entries[i].key, XPPL_CONFIG_KEY_MAXLEN) == 0)
        {
            ptr = &ctx->entries[i];
            break;
        }
    }
    return ptr;
}


void
xppl_config_load(xppl_config_ctx_t *ctx, const char *path)
{

}


void
xppl_config_register(xppl_config_ctx_t *ctx, const char *key, xppl_config_type_t type, xppl_config_data_t default_value)
{
    /* create and initialize a new node */
    ctx->entry_count++;
    if (ctx->entry_count == 1)
    {
        ctx->entries = xppl_calloc(1, sizeof(xppl_config_entry_t));
    }
    else
    {
        ctx->entries = xppl_realloc(ctx->entries, sizeof(xppl_config_entry_t) * ctx->entry_count);
    }
    xppl_config_entry_t *new_entry = &ctx->entries[ctx->entry_count - 1];
    new_entry->key = NULL;
    new_entry->data = NULL;
    new_entry->default_data = NULL;
    
    /* set the key */
    size_t keylen = strnlen(key, (size_t)(XPPL_CONFIG_KEY_MAXLEN - 1));
    new_entry->key = xppl_calloc(keylen + 1, sizeof(char));
    strncpy(new_entry->key, key, keylen);

    /* set the type */
    new_entry->type = type;

    /* set the default data */
    if (type == XPPL_CONFIG_STRING)
    {
        size_t vallen = strnlen((char *)default_value, XPPL_CONFIG_VAL_MAXLEN - 1);
        new_entry->default_data = xppl_calloc(vallen + 1, _cast_get_size(type));
        new_entry->data = xppl_calloc(vallen + 1, _cast_get_size(type));
        strncpy(new_entry->default_data, default_value, vallen);
        strncpy(new_entry->data, default_value, vallen);
    }
    else
    {
        size_t vallen = _cast_get_size(type);
        new_entry->default_data = xppl_calloc(vallen, 1);
        new_entry->data = xppl_calloc(vallen, 1);
        memcpy(new_entry->default_data, default_value, vallen);
        memcpy(new_entry->data, default_value, vallen);
    }
}

