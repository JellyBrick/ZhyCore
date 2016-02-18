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
    void encode()
    {
        Packet::encode();
        //TODO

    }
    void decode()
    {
        Packet::decode();
        offset+=16;
        protocol=getByte();
        mtuSize=get(true).size()+18;
    }

protected:

private:
};
#endif
