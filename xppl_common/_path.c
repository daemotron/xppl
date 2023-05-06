#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if     IBM
#include <windows.h>
#else   /* !IBM */
#include <errno.h>
#include <sys/stat.h>
#endif  /* !IBM */

#include <xppl.h>
#include <xppl_alloc.h>

#include "_path.h"


bool
_path_exists(const char *path)
{
#if IBM
    size_t len = strlen(path);
    WCHAR pathW[len + 1];
    DWORD attr;
    MultiByteToWideChar(CP_UTF8, 0, path, -1, pathW, len + 1);
    attr = GetFileAttributesW(pathW);
    return (attr != INVALID_FILE_ATTRIBUTES);
#else /* !IBM */
    struct stat st;
    return (stat(path, &st) >= 0);
#endif /* !IBM */
}


void
_path_create_dir(const char *path)
{
    if (path == NULL)
    {
        return;
    }

    bool error_flag = false;

#if IBM
    DWORD error;
    size_t len = strlen(path);
    WCHAR pathW[len + 1];
    MultiByteToWideChar(CP_UTF8, 0, path, -1, pathW, len + 1);
    if (!CreateDirectoryW(pathW, NULL) && (error = GetLastError()) != ERROR_ALREADY_EXISTS)
    {
        error_flag = true;
    }
#else /* !IBM */
    if (mkdir(path, 0777) != 0 && errno != EEXIST)
    {
        error_flag = true;
    }
#endif /* !IBM */

    if (error_flag)
    {
        xppl_log_error("Failed to create directory %s", path);
    }
}


void
_path_create_dir_recursive(const char *path, const char *separator)
{
    if ((path == NULL) || (separator == NULL))
    {
        return;
    }

    int sepchar = (int)separator[0];
    char *partname = xppl_calloc(strlen(path) + 1, sizeof(char));

    for (const char *start = path, *end = strchr(&path[1], sepchar); end != NULL; start = end, end = strchr(&start[1], sepchar))
    {
        strncat(partname, start, end - start);
        _path_create_dir(partname);
    }

    free(partname);
    _path_create_dir(path);
}
