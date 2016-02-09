#ifndef UDP_PACKET_H
#define UDP_PACKET_H

#include <string>
#include <cstdint>

class udp_packet {

private:
	std::string _host;
	int _port;
	uint8_t *_data;
	int _size;
public:
	udp_packet(std::string host, int port, const char *data, int size);
	virtual ~udp_packet();
	uint8_t *get_data();
	int get_size();
};

#endif
