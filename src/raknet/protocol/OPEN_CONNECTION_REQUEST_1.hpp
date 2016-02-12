#ifndef request1
#define request1
#include <iostream>
#include "Packet.hpp"
class OPEN_CONNECTION_REQUEST_1 : public Packet
{
public:
    const static int ID=0x05;
    int mtuSize=0;
    char protocol=Packet::PROTOCOL;
    OPEN_CONNECTION_REQUEST_1() {};
    encode()
    {
        Packet::encode();
        //TODO

    }
    decode()
    {
        Packet::decode();
        offset+=16;
        protocol=getByte();
        mtuSize=123;
    }

protected:

private:
};
#endif
