#include "udpsocket.h"

#include "cross_platform_socket.h"
#include "socket_exception.h"
#include <iostream>
#include <cstdint>
#include "udppacket.h"
#include <stdio.h>
#define MAX_BUFF 2048

udpsocket::udpsocket() : udpsocket(0) {

}

udpsocket::udpsocket(int port) {
    try_sockets_layer_init();
    _handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (_handle <= 0) {
        throw socket_exception();
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons((unsigned short) port);
u_long mode = 1;
ioctlsocket(_handle,FIONBIO,&mode);
    if (bind(_handle, (const sockaddr *) &address, sizeof(sockaddr_in)) < 0) {
        throw socket_exception();
    }
}

void udpsocket::writePacket(char* address, unsigned short port, const char *data,int buflen) {
   // unsigned int address = (byte[0] << 24) | (byte[1] << 16) | (byte[2] << 8) | byte[3];
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(address);
    addr.sin_port = htons(port);
    int sent_bytes = sendto(_handle,
                            data,
                            buflen,
                            0,
                            (sockaddr *) &addr,
                            sizeof(sockaddr_in));
    if (sent_bytes != buflen) {
        throw socket_exception();
    }
}

std::shared_ptr<udppacket> udpsocket::readPacket() {
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
                         if(bytes<=0)return NULL;
    char *from_address = inet_ntoa(from.sin_addr);
    unsigned int from_port = ntohs(from.sin_port);
    return std::shared_ptr<udppacket>(new udppacket(from_address, from_port, (char *)packet_data, bytes));
}

