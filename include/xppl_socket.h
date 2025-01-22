#ifndef _XPPL_SOCKET_H_
#define _XPPL_SOCKET_H_

#ifdef __cplusplus
extern "C" {
#endif

#if IBM
typedef unsigned long long xppl_socket_t;
#define XPPL_SOCKET_FAILED ~0ULL
#define xppl_socket_shutdown_receive(fd) shutdown(fd, SD_RECEIVE)
#define xppl_socket_shutdown_send(fd) shutdown(fd, SD_SEND)
#define xppl_socket_shutdown_both(fd) shutdown(fd, SD_BOTH)
#else /* !IBM */
typedef int xppl_socket_t;
#define XPPL_SOCKET_FAILED -1
#define xppl_socket_shutdown_receive(fd) shutdown(fd, SHUT_RD)
#define xppl_socket_shutdown_send(fd) shutdown(fd, SHUT_WR)
#define xppl_socket_shutdown_both(fd) shutdown(fd, SHUT_RDWR)
#endif

void xppl_socket_init(void);
void xppl_socket_destroy(void);
xppl_socket_t xppl_socket(int, int, int);
void xppl_socket_close(xppl_socket_t);
void xppl_socket_non_blocking(xppl_socket_t);

#ifdef	__cplusplus
}
#endif

#endif /* _XPPL_SOCKET_H_ */
