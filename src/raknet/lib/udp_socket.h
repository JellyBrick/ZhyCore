#ifndef SOCKET_H
#define SOCKET_H

#include <memory>

class udp_packet;

class udp_socket {

private:
    int _handle;
public:
    udp_socket();
    udp_socket(int port);
    void send_to(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned short port, const char *data);
    std::shared_ptr<udp_packet> receive();
};

#endif
