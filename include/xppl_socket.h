#ifndef _XPPL_SOCKET_H_
#define _XPPL_SOCKET_H_

#ifdef __cplusplus
extern "C" {
#endif

#if IBM
typedef unsigned long long socket_t;
#define XPPL_SOCKET_FAILED ~0ULL
#else /* !IBM */
typedef int xppl_socket_t;
#define XPPL_SOCKET_FAILED -1
#endif

xppl_socket_t xppl_socket(int, int, int);

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_SOCKET_H_ */
