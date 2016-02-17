#ifndef startgamepk
#define startgamepk
#include <iostream>
#include "../protocol/Packet.hpp"
#include "../../../include/ExtraFuncs.h"
class StartGamePacket : public Packet
{
public:
     const static int ID=0x95;
	 int seed;
	 unsigned char dimension;
	 int generator;
	 int gamemode;
	 __int64 eid;
	 int spawnX;
	 int spawnY;
	 int spawnZ;
	 float x;
	 float y;
	 float z;

    StartGamePacket() {};
    encode()
    {
        Packet::encode();
        buffer+=ID;
        putInt(seed);
        putByte(dimension);
        putInt(generator);
        putInt(gamemode);
        putLong(eid);
        putInt(spawnX);
        putInt(spawnY);
        putInt(spawnZ);
        putFloat(x);
        putFloat(y);
        putFloat(z);
        putByte('\0');


    }
    decode()
    {
        Packet::decode();

    }

protected:

private:
};
#endif
