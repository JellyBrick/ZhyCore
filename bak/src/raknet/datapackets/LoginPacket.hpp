#ifndef loginPK
#define loginPK
#include <iostream>
#include "../protocol/Packet.hpp"
#include "../../../include/ExtraFuncs.h"
class LoginPacket : public Packet
{
public:
    const static int ID=0x8f;
    std::string username;
    int protocol1;
    int protocol2;
    __int64 clientId;
    UUiD clientUUID;
    std::string serverAddress;
    std::string clientSecret;

    std::string skinName;
    std::string skin;

    LoginPacket() {};
    encode()
    {
        Packet::encode();
        //TODO

    }
    decode()
    {
        Packet::decode();
        username=getString();
        protocol1=getInt();
        protocol2=getInt();
        clientId=getLong();
        clientUUID=getUUID();
        serverAddress=getString();
        clientSecret=getString();
        skinName=getString();
        skin=getString();

    }

protected:

private:
};
#endif
