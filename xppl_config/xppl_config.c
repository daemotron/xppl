#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <xppl.h>
#include <xppl_alloc.h>
#include <xppl_config.h>

#include "_cast.h"


void _xppl_config_update(xppl_config_ctx_t *, const char *, const xppl_config_data_t);
void _xppl_config_parse(xppl_config_ctx_t *, const char *, int);


void
_xppl_config_update(xppl_config_ctx_t *ctx, const char *key, const xppl_config_data_t data)
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
        data_len = strnlen((char *)data, XPPL_CONFIG_VAL_MAXLEN - 1) + 1;
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
_xppl_config_parse(xppl_config_ctx_t *ctx, const char *input, int line_no)
{
    xppl_config_data_t buffer = xppl_calloc(XPPL_CONFIG_LIN_MAXLEN, sizeof(char));

    /* check for blank line */
    if (sscanf(input, " %s", (char *)buffer) == EOF)
    {
        xppl_log_debug("Configuration line %d: detected blank line", line_no);
        return;
    }

    /* check for comment */
    if (sscanf(input, " %[#]", (char *)buffer) == 1)
    {
        xppl_log_debug("Configuration line %d: detected comment", line_no);
        return;
    }

    /* check for registered config entries */
    char *format = xppl_calloc(XPPL_CONFIG_KEY_MAXLEN + 10, sizeof(char));

    for (unsigned int i = 0; i < ctx->entry_count; i++)
    {
        snprintf(format, XPPL_CONFIG_KEY_MAXLEN + 10, " %s = %s", ctx->entries[i].key, _cast_get_formatter(ctx->entries[i].type));
        if(sscanf(input, format, buffer))
        {
            _xppl_config_update(ctx, ctx->entries[i].key, buffer);
            
            /* write a debug log entry */
            char *log_format = xppl_calloc(64, sizeof(char));
            strncpy(log_format, "Configuration line %d: %s set to ", 64);
            strncat(log_format, _cast_get_formatter(ctx->entries[i].type), 5);
            switch (ctx->entries[i].type)
            {
                case XPPL_CONFIG_INT:
                    xppl_log_debug(log_format, line_no, ctx->entries[i].key, *((long long *)ctx->entries[i].data));
                    break;

                case XPPL_CONFIG_FLOAT:
                    xppl_log_debug(log_format, line_no, ctx->entries[i].key, *((long double *)ctx->entries[i].data));
                    break;
                
                case XPPL_CONFIG_UNSIGNED:
                    xppl_log_debug(log_format, line_no, ctx->entries[i].key, *((unsigned long long *)ctx->entries[i].data));
                    break;

                case XPPL_CONFIG_STRING:
                    xppl_log_debug(log_format, line_no, ctx->entries[i].key, (char *)ctx->entries[i].data);
                    break;

                default:
                    xppl_log_debug("Configuration line %d: %s not set (invalid format)", line_no, ctx->entries[i].key);
                    break;
            }
            free(log_format);
        }
        else
        {
            /* Anything else must be a syntax error */
            xppl_log_error("Configuration line %d: Syntax error.", line_no);
        }
        memset(format, '\0', XPPL_CONFIG_KEY_MAXLEN + 10);
    }

    /* clean up */
    free(format);
    free(buffer);
}


void
xppl_config_init(xppl_config_ctx_t *ctx, const char *path, const char *separator, bool create_file_if_not_exists)
{
    ctx->entries = NULL;
    ctx->entry_count = 0;
    ctx->create_if_not_exists = create_file_if_not_exists;

    if (path != NULL)
    {
        ctx->path = calloc(strlen(path) + 1, sizeof(char));
        strncpy(ctx->path, path, strlen(path));
    }
    else
    {
        ctx->path = NULL;
    }

    if (separator != NULL)
    {
        ctx->separator = calloc(strlen(separator) + 1, sizeof(char));
        strncpy(ctx->separator, separator, strlen(separator));
    }
    else
    {
        ctx->separator = NULL;
    }
    
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

    if (ctx->entries != NULL)
    {
        free(ctx->entries);
        ctx->entries = NULL;
    }

    if (ctx->path != NULL)
    {
        free(ctx->path);
        ctx->path = NULL;
    }

    if (ctx->separator != NULL)
    {
        free(ctx->separator);
        ctx->separator = NULL;
    }
    
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
        return 0;
    }
    strncpy(buffer, (char *)ptr->data, buflen);
    buffer[buflen-1] = '\0';
    return strnlen(buffer, buflen);
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
    _xppl_config_update(ctx, key, (const xppl_config_data_t)data);
}


xppl_config_entry_t *
xppl_config_find(xppl_config_ctx_t *ctx, const char *key)
{
    xppl_config_entry_t *ptr = NULL;
    for (unsigned int i = 0; i < ctx->entry_count; i++)
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
    FILE *fp = fopen(path, "r");
    if (fp == NULL)
    {
        xppl_log_error("Cannot open configuration file %s", path);
        return;
    }

    int line_no = 0;
    char *config_line = xppl_calloc(XPPL_CONFIG_LIN_MAXLEN, sizeof(char));

    while (fgets(config_line, XPPL_CONFIG_LIN_MAXLEN, fp))
    {
        line_no++;
        _xppl_config_parse(ctx, config_line, line_no);
        memset(config_line, '\0', XPPL_CONFIG_LIN_MAXLEN);
    }

    fclose(fp);
    free(config_line);
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

