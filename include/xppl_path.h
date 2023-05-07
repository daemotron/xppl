#ifndef _XPPL_PATH_H_
#define _XPPL_PATH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>

bool xppl_path_exists(const char *);
void xppl_path_create_dir(const char *);
void xppl_path_create_dir_recursive(const char *, const char *);
size_t xppl_path_dirname(const char *, const char *, char *, size_t);

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_PATH_H_ */
