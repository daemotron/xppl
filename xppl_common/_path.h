#ifndef _XPPL_PATH_H_
#define _XPPL_PATH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

bool _path_exists(const char *);
void _path_create_dir(const char *);
void _path_create_dir_recursive(const char *, const char *);

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_PATH_H_ */
