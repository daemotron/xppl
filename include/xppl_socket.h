#ifndef _XPPL_SOCKET_H_
#define _XPPL_SOCKET_H_

#ifdef __cplusplus
extern "C" {
#endif

#if IBM
typedef unsigned long long xppl_socket_t;
#define XPPL_SOCKET_FAILED ~0ULL
#else /* !IBM */
typedef int xppl_socket_t;
#define XPPL_SOCKET_FAILED -1
#endif

void xppl_socket_init(void);
void xppl_socket_destroy(void);
xppl_socket_t xppl_socket(int, int, int);
void xppl_socket_non_blocking(xppl_socket_t);

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_SOCKET_H_ */
