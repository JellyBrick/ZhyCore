#ifndef playstatuspk
#define playstatuspk
#include <iostream>
#include "../protocol/Packet.hpp"
#include "../../../include/ExtraFuncs.h"
class PlayStatusPacket : public Packet
{
public:
    const int ID=0x90;
    const static unsigned char LOGIN_SUCCESS = 0;
    const static unsigned char LOGIN_FAILED_CLIENT = 1;
    const static unsigned char LOGIN_FAILED_SERVER = 2;
    const static unsigned char PLAYER_SPAWN = 3;
    unsigned char status;

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
