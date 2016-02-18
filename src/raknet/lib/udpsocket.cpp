#include "udpsocket.h"

#include "cross_platform_socket.h"
#include "socket_exception.h"
#include <iostream>
#include <cstdint>
#include <stdio.h>
#define MAX_BUFF 2048

udpsocket::udpsocket() : udpsocket(0)
{

}
unsigned int udpsocket::getPort()
{
    return Port_;
}
udpsocket::udpsocket(int port)
{
    try_sockets_layer_init();
    _handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (_handle <= 0)
    {
        throw socket_exception();
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons((unsigned short) port);
#if PLATFORM == PLATFORM_WINDOWS
    u_long mode = 1;
    ioctlsocket(_handle,FIONBIO,&mode);
#elif PLATFORM == PLATFORM_UNIX
    int flags = fcntl(_handle, F_GETFL, 0);
    fcntl(_handle, F_SETFL, flags | O_NONBLOCK);
#endif // PLATFORM

    if (bind(_handle, (const sockaddr *) &address, sizeof(sockaddr_in)) < 0)
    {
        throw socket_exception();
    }
    Port_=port;
}

void udpsocket::writePacket(std::string address, unsigned short port,std::string data)
{
    // unsigned int address = (byte[0] << 24) | (byte[1] << 16) | (byte[2] << 8) | byte[3];
    sockaddr_in addr;
    addr.sin_family = AF_INET;

    addr.sin_addr.s_addr = inet_addr(address.c_str());
    addr.sin_port = htons(port);

    unsigned int sent_bytes = sendto(_handle,
                                     data.c_str(),
                                     data.length(),
                                     0,
                                     (sockaddr *) &addr,
                                     sizeof(sockaddr_in));
//                           int sent_bytes=data.length();
    if (sent_bytes != data.length())
    {
        throw socket_exception();
    }
}

std::string udpsocket::readPacket(std::string *addr,unsigned int  &port)
{
    char packet_data[MAX_BUFF];
    // memset(packet_data, '\0', MAX_BUFF);
    sockaddr_in from;
    socklen_t fromLength = sizeof(from);
    int bytes=0;

    bytes = recvfrom(_handle,
                     packet_data,
                     MAX_BUFF,
                     0,
                     (sockaddr *) &from,
                     &fromLength);
    if(bytes<=0)return "";

    * addr=inet_ntoa(from.sin_addr); //amazing

    port = (unsigned int)ntohs(from.sin_port);
    return std::string (packet_data,bytes);
    // return std::shared_ptr<udppacket>(new udppacket(from_address, from_port, (char *)packet_data, bytes));

}

