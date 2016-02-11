#include "udppacket.h"
#include "string.h"
#include <iostream>
#include <malloc.h>
udppacket::udppacket(char* address, int port, char *data,int size) {
    _address=address;
	_port = port;
	_data=new char[size];
	memcpy(_data,data,size);
	_size = size;
	free(data);
}

udppacket::~udppacket() {
	delete[] _data;
}

char *udppacket::getdata() {
	return _data;
}
char* udppacket::getAddress(){
    return _address;
}
int udppacket::getPort(){
    return _port;
}
int udppacket::getSize(){
    return _size;
}
