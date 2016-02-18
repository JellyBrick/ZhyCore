#ifndef SOCKET_H
#define SOCKET_H
#include <vector>
#include <memory>

class udppacket;

class udpsocket
{

private:
    int _handle;
public:
    udpsocket();
    udpsocket(int port);
    unsigned int Port_;
    unsigned int getPort();
    void writePacket(std::string address, unsigned short port,std::string data);
    std::string readPacket(std::string *addr,unsigned int  &port);
};

#endif
