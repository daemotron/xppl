#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <xppl.h>
#include <xppl_alloc.h>
#include <xppl_config.h>
#include <xppl_log.h>
#include <xppl_path.h>

#include "_cast.h"
#include "_cfg.h"


void
_cfg_update(xppl_config_ctx_t *ctx, const char *key, const xppl_config_data_t data)
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
_cfg_parse(xppl_config_ctx_t *ctx, const char *input, int line_no)
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
        snprintf(format, XPPL_CONFIG_KEY_MAXLEN + 10, " %s = %s", ctx->entries[i].key, _cast_get_formatter(ctx->entries[i].type, _CAST_FORMATTER_READ));
        if(sscanf(input, format, buffer))
        {
            _cfg_update(ctx, ctx->entries[i].key, buffer);
            
            /* write a debug log entry */
            char *log_format = xppl_calloc(64, sizeof(char));
            strncpy(log_format, "Configuration line %d: %s set to ", 64);
            strncat(log_format, _cast_get_formatter(ctx->entries[i].type, _CAST_FORMATTER_WRITE), 5);
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
_cfg_create_if_not_exists(xppl_config_ctx_t *ctx)
{
    if (!ctx->create_if_not_exists)
    {
        return;
    }

    if (xppl_path_exists(ctx->path))
    {
        return;
    }

    char conf_dir[1024] = { '\0' };
    if (xppl_path_dirname(ctx->path, ctx->separator, conf_dir, 1024) <= 0)
    {
        xppl_log_error("Invalid path name: %s", ctx->path);
        return;
    }

    if (!xppl_path_exists(conf_dir))
    {
        xppl_path_create_dir_recursive(conf_dir, ctx->separator);
    }

    FILE *fp = fopen(ctx->path, "w");
    if (fp == NULL)
    {
        xppl_log_error("Cannot open configuration file %s for writing", ctx->path);
        return;
    }

    if (ctx->title != NULL)
    {
        fprintf(fp, "# %s\n# %.*s\n\n", ctx->title, (int)strlen(ctx->title), _XPPL_CONFIG_CFG_UNDERLINE);
    }

    char *format = xppl_calloc(XPPL_CONFIG_KEY_MAXLEN + XPPL_CONFIG_DES_MAXLEN + 16, sizeof(char));
    char *buffer = xppl_calloc(3 * XPPL_CONFIG_LIN_MAXLEN, sizeof(char));

    for (unsigned int i = 0; i < ctx->entry_count; i++)
    {
        if (ctx->entries[i].description != NULL)
        {
            if (i == 0)
            {
                snprintf(format, XPPL_CONFIG_KEY_MAXLEN + XPPL_CONFIG_DES_MAXLEN + 16, "# %s\n%s = %s\n", ctx->entries[i].description, ctx->entries[i].key, _cast_get_formatter(ctx->entries[i].type, _CAST_FORMATTER_WRITE));
            }
            else
            {
                snprintf(format, XPPL_CONFIG_KEY_MAXLEN + XPPL_CONFIG_DES_MAXLEN + 16, "\n# %s\n%s = %s\n", ctx->entries[i].description, ctx->entries[i].key, _cast_get_formatter(ctx->entries[i].type, _CAST_FORMATTER_WRITE));
            }
        }
        else
        {
            snprintf(format, XPPL_CONFIG_KEY_MAXLEN + XPPL_CONFIG_DES_MAXLEN + 16, "%s = %s\n", ctx->entries[i].key, _cast_get_formatter(ctx->entries[i].type, _CAST_FORMATTER_WRITE));
        }
        switch (ctx->entries[i].type)
            {
                case XPPL_CONFIG_INT:
                    snprintf(buffer, 3 * XPPL_CONFIG_LIN_MAXLEN - 1, format, *((long long *)ctx->entries[i].data));
                    break;

                case XPPL_CONFIG_FLOAT:
                    snprintf(buffer, 3 * XPPL_CONFIG_LIN_MAXLEN - 1, format, *((long double *)ctx->entries[i].data));
                    break;
                
                case XPPL_CONFIG_UNSIGNED:
                    snprintf(buffer, 3 * XPPL_CONFIG_LIN_MAXLEN - 1, format, *((unsigned long long *)ctx->entries[i].data));
                    break;

                case XPPL_CONFIG_STRING:
                    snprintf(buffer, 3 * XPPL_CONFIG_LIN_MAXLEN - 1, format, (char *)ctx->entries[i].data);
                    break;

                default:
                    xppl_log_debug("Invalid type for configuration key %s", ctx->entries[i].key);
                    break;
            }
        fprintf(fp, buffer);
        memset(format, '\0', XPPL_CONFIG_KEY_MAXLEN + XPPL_CONFIG_DES_MAXLEN + 16);
        memset(buffer, '\0', 3 * XPPL_CONFIG_LIN_MAXLEN);
    }

    fclose(fp);
    free(format);
    free(buffer);
}
