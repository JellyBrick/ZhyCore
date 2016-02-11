#ifndef UDP_PACKET_H
#define UDP_PACKET_H

#include <string>
#include <cstdint>

class udppacket {

private:
	char* _address;
	int _port;
	char *_data;
	int _size;
public:
	udppacket(char* address, int port, char *data, int size);
	virtual ~udppacket();
	char *getdata();
	int getsize();
	int getPort();
	char* getAddress();
	int getSize();
};

#endif
