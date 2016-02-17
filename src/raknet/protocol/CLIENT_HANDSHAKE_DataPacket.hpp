#ifndef clienthandshake
#define clienthandshake
#include <iostream>
#include "Packet.hpp"
class CLIENT_HANDSHAKE_DataPacket : public Packet
{
public:
    const static int ID=0x13;
    std::string address;
    unsigned int port=0;
    __int64 sendPing;
    __int64 sendPong;
    CLIENT_HANDSHAKE_DataPacket() {};
    encode()
    {
        Packet::encode();


    }
    decode()
    {
        Packet::decode();
        getAddress(address,port);
        offset+=(1+4+2)*10;//Jump SystemAddress
        sendPing=getLong();
        sendPong=getLong();

    }

protected:

private:
};
#endif
