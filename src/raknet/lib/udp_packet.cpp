#include "udp_packet.h"
#include "string.h"

udp_packet::udp_packet(std::string host, int port, const char *data, int size) {
	_host = host;
	_port = port;
	_data = new uint8_t[size+1];
	//memset(_data,0,size+1);
	memcpy(_data, data, size+1);

	_size = size;
}

udp_packet::~udp_packet() {
	delete[] _data;
}

uint8_t *udp_packet::get_data() {
	return _data;
}

int udp_packet::get_size() {
	return _size;
}
