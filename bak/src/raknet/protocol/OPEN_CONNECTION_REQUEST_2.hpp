#ifndef request2
#define request2
#include <iostream>
#include "Packet.hpp"
class OPEN_CONNECTION_REQUEST_2 : public Packet
{
public:
    const static int ID=0x07;
    short mtuSize=0;
    std::string serverAddress;
    unsigned int serverPort;
    __int64 clientID;

    char protocol=Packet::PROTOCOL;
    OPEN_CONNECTION_REQUEST_2() {};
    encode()
    {
        Packet::encode();
        //TODO

    }
    decode()
    {
        Packet::decode();
        offset+=16  ;//???
        getAddress(serverAddress,serverPort);
        mtuSize=getShort();
        clientID=getLong();
    }

protected:

private:
};
#endif
