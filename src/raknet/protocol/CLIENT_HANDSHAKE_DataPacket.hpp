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
    int64_t sendPing;
    int64_t sendPong;
    CLIENT_HANDSHAKE_DataPacket() {};
    void encode()
    {
        Packet::encode();


    }
    void decode()
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
