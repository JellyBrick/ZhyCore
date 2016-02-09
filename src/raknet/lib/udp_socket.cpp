#include "udp_socket.h"

#include "cross_platform_socket.h"
#include "socket_exception.h"
#include <iostream>
#include <cstdint>
#include "udp_packet.h"



udp_socket::udp_socket() : udp_socket(0) {

}

udp_socket::udp_socket(int port) {
    try_sockets_layer_init();
    _handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (_handle <= 0) {
        throw socket_exception();
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons((unsigned short) port);

    if (bind(_handle, (const sockaddr *) &address, sizeof(sockaddr_in)) < 0) {
        throw socket_exception();
    }
}

void udp_socket::send_to(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned short port, const char *data) {
    unsigned int address = (a << 24) | (b << 16) | (c << 8) | d;
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(address);
    addr.sin_port = htons(port);
    int packet_size = strlen(data) + 1;
    int sent_bytes = sendto(_handle,
                            data,
                            packet_size,
                            0,
                            (sockaddr *) &addr,
                            sizeof(sockaddr_in));
    if (sent_bytes != packet_size) {
        throw socket_exception();
    }
}

std::shared_ptr<udp_packet> udp_socket::receive() {
    uint8_t packet_data[1500];
memset(packet_data,0,sizeof(packet_data));
    unsigned int max_packet_size = sizeof(packet_data);

    sockaddr_in from;
    socklen_t fromLength = sizeof(from);
    int bytes=0;
do{
  bytes = recvfrom(_handle,
                         (char *) packet_data,
                         max_packet_size,
                         0,
                         (sockaddr *) &from,
                         &fromLength);
//std::cout<<bytes<<std::endl;
}
    while (bytes <= 0);

    unsigned int from_address = ntohl(from.sin_addr.s_addr);

    unsigned int from_port = ntohs(from.sin_port);
    return std::shared_ptr<udp_packet>(new udp_packet("host", from_port, (const char *) packet_data, bytes));
}

