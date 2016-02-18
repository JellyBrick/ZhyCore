#ifndef reply1
#define reply1
#include <iostream>
#include "Packet.hpp"
class OPEN_CONNECTION_REPLY_1 : public Packet
{
public:
    const static int ID=0x06;
    short mtuSize=0;
    __int64 serverId=0;
    OPEN_CONNECTION_REPLY_1() {};
    void encode()
    {
        Packet::encode();
        buffer+=ID;
        putMagic();
        putLong(serverId);
        putByte('\0');
        putShort(mtuSize);

    }
    void decode()
    {
        Packet::decode();

    }

protected:

private:
};
#endif
