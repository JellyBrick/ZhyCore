#pragma once
#include "../../include/ExtraFuncs.h"
class Level
{
public:
    void Vector3() {};
    static int chunkHash(__int64 chunkX,__int64 chunkZ)
    {
        return ((chunkX&0xFFFFFFFF)<<32)|(chunkZ&0xFFFFFFFF);
    }
protected:

private:
};
