#ifndef reply2
#define reply2
#include <iostream>
#include "Packet.hpp"
class OPEN_CONNECTION_REPLY_2 : public Packet
{
public:
    const static int ID=0x08;
    short mtuSize=0;
    __int64 serverId=0;
    std::string clientAddress;
    unsigned int clientPort;
    OPEN_CONNECTION_REPLY_2() {};
    encode()
    {
        Packet::encode();
        buffer+=ID;
        putMagic();
        putLong(serverId);
        putAddress(clientAddress,clientPort);
        putShort(mtuSize);
        putByte('\0');//server security
    }
    decode()
    {
        Packet::decode();

    }

protected:

private:
};
#endif
