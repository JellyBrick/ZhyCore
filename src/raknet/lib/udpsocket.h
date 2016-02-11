#ifndef SOCKET_H
#define SOCKET_H

#include <memory>

class udppacket;

class udpsocket {

private:
    int _handle;
public:
    udpsocket();
    udpsocket(int port);
    void writePacket(char* address, unsigned short port, const char *data,int buflen);
    std::shared_ptr<udppacket> readPacket();
};

#endif
