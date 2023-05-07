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
#include <xppl_path.h>


bool
xppl_path_exists(const char *path)
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
xppl_path_create_dir(const char *path)
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
xppl_path_create_dir_recursive(const char *path, const char *separator)
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
        xppl_path_create_dir(partname);
    }

    free(partname);
    xppl_path_create_dir(path);
}


size_t
xppl_path_dirname(const char *path, const char *separator, char *buffer, size_t buflen)
{
    if ((separator == NULL) || (buflen < 2))
    {
        return 0U;
    }

    /*
     * Case 1:
     *
     * path is a null pointer, or points ot an empty string.
     * In this case, dirname shall return a string representing
     * the current directory (".")
     */
    if (path == NULL || path[0] == '\0')
    {
        buffer[0] = '.';
        buffer[1] = '\0';
        return 2U;
    }

    char sepchar = separator[0];
    memset(buffer, '\0', buflen);
    strncpy(buffer, path, buflen - 1);
    
    /* get a pointer to the end of the copied path string */
    char *ptr = buffer + strlen(buffer);

    /* move past any trailing separators */
    while (ptr > buffer + 1 && *(ptr - 1) == sepchar)
    {
        ptr--;
    }

    /* move past any non-separator characters (last part of the path) */
    while (ptr > buffer && *(ptr - 1) != sepchar)
    {
        ptr--;
    }
    
    /*
     * Case 2:
     *
     * No separator found, i.e. no directory part detectable.
     * In this case, path needs to be treated as file name, residing
     * in the current directory (".")
     */
    if (ptr == buffer)
    {
        buffer[0] = '.';
        buffer[1] = '\0';
        return 2U;
    }

    /* move past any trailing separators (ensure at least one char remains) */
    while (ptr > buffer + 1 && *(ptr - 1) == sepchar)
    {
        ptr--;
    }

    /* terminate the directory name */
    *ptr = '\0';

    return (size_t)(buffer - ptr + 1U);
}
