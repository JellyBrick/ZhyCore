#ifndef pong
#define pong
#include <iostream>
#include "Packet.hpp"
#include <string>
class UNCONNECTED_PONG : public Packet
{
public:
    int serverID;
    const static int ID=0x1c;
    std::string serverName;

    __int64 pingID;
    UNCONNECTED_PONG() {};
    void encode()
    {
        Packet::encode();
        buffer+=ID;
        putLong(pingID);
        putLong(serverID);
        putMagic();
        putString(serverName);
    }
    void decode()
    {
        Packet::decode();

    }

protected:

private:
};
#endif
