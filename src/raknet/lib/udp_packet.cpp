#include "udp_packet.h"
#include "string.h"
#include <iostream>
udp_packet::udp_packet(std::string host, int port, char *data, int size) {
	_host = host;
	_port = port;
	_data = data;
	_size = size;
}

udp_packet::~udp_packet() {
	delete[] _data;
}

char *udp_packet::get_data() {
	return _data;
}

int udp_packet::get_size() {
	return _size;
}
