#include "cross_platform_socket.h"

static void sockets_layer_init(void);
static bool tried = false;

void try_sockets_layer_init()
{
    if (!tried)
    {
        sockets_layer_init();
    }
    tried = true;
}

void sockets_layer_cleanup()
{
#if PLATFORM == PLATFORM_WINDOWS
   WSACleanup();
#endif
}

static void sockets_layer_init()
{
#if PLATFORM == PLATFORM_WINDOWS
    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(2, 2), &wsadata) != NO_ERROR)
    {
        //throw new wsastartup_exception();
    }
#endif
}
