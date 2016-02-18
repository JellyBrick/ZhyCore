#ifndef cliconect
#define cliconect
#include <iostream>
#include "Packet.hpp"
class CLIENT_CONNECT_DataPacket : public Packet
{
public:
    const static int ID=0x09;
    __int64 clientID=0;
    __int64 sendPing=0;
    bool useSecurity=false;
    CLIENT_CONNECT_DataPacket() {};
    encode()
    {
        Packet::encode();
        //TODO

    }
    decode()
    {
        Packet::decode();
        clientID=getLong();
        sendPing=getLong();
        useSecurity=getByte()>0;
    }

protected:

private:
};
#endif
