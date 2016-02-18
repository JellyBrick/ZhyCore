#ifndef ping
#define ping
#include <iostream>
#include "Packet.hpp"
class UNCONNECTED_PING : public Packet
{
public:
    const static int ID=0x01;
    int64_t pingID=0;
    UNCONNECTED_PING() {};
    void encode()
    {

        Packet::encode();

    }
    void decode()
    {
        Packet::decode();
        pingID=getLong();
    }

protected:

private:
};
#endif
