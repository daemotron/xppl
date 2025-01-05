#include <stdbool.h>

#if IBM
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else /* !IBM */
#include <sys/socket.h>
#include <fcntl.h>
#endif

#include <xppl_socket.h>
#include <xppl_log.h>


static volatile bool __xppl_socket_initialized = false;


void
xppl_socket_init(void)
{
#if IBM
    WSADATA wsa;
    int start_result = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (start_result != 0)
    {
        log_error("WSAStartup failed with error code %i", start_result);
        return;
    }
#endif /* IBM */
    __xppl_socket_initialized = true;
}


void
xppl_socket_destroy(void)
{
#if IBM
    WSACleanup();
#endif /* IBM */
}


xppl_socket_t
xppl_socket(int af, int type, int protocol)
{
    if (!__xppl_socket_initialized)
    {
        xppl_socket_initialize();
        if (!__xppl_socket_initialized)
        {
            xppl_log_error("Unable to initialize socket system");
            return XPPL_SOCKET_FAILED;
        }
    }
    return socket(af, type, protocol);
}


void
xppl_socket_close(xppl_socket_t socket_fd)
{
#if IBM
    closesocket(socket_fd);
#else /* !IBM */
    close(socket_fd);
#endif
}


void
xppl_socket_non_blocking(xppl_socket_t socket_fd) {
#if IBM
    u_long mode = 1;
    ioctlsocket(socket_fd, FIONBIO, &mode);
#else /* !IBM */
    int flags = fcntl(socket_fd, F_GETFL, 0);
    fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK);
#endif
}
