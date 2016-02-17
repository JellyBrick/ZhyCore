#ifndef playstatuspk
#define playstatuspk
#include <iostream>
#include "../protocol/Packet.hpp"
#include "../../../include/ExtraFuncs.h"
class PlayStatusPacket : public Packet
{
public:
    const static int ID=0x90;
    const char LOGIN_SUCCESS = 0;
    const char LOGIN_FAILED_CLIENT = 1;
    const char LOGIN_FAILED_SERVER = 2;
    const char PLAYER_SPAWN = 3;
    int status;

    PlayStatusPacket() {};
    encode()
    {
        Packet::encode();
        buffer+=ID;
        putInt(status);
    }
    decode()
    {
        Packet::decode();

    }

protected:

private:
};
#endif
