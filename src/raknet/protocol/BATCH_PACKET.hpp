#ifndef BATCH_PH
#define BATCH_PH
#include <iostream>
#include "Packet.hpp"
class BATCH_PACKET : public Packet
{
public:
    const static int ID=0x92;
    std::string payload;
    BATCH_PACKET() {};
    void encode()
    {
        Packet::encode();

    }
    void decode()
    {
        Packet::decode();
        int size=getInt();
        payload=get(size);

    }

protected:

private:
};
#endif
