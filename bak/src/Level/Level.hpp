#pragma once
#include "../../include/ExtraFuncs.h"
class Level
{
public:
    Vector3() {};
    static int chunkHash(int chunkX,int chunkZ)
    {
        return ((chunkX&0xFFFFFFFF)<<32)|(chunkZ&0xFFFFFFFF);
    }
protected:

private:
};
