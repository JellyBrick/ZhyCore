#pragma once
#include "../../include/ExtraFuncs.h"
class Level
{
public:
    void Vector3() {};
    static int chunkHash(int64_t chunkX,int64_t chunkZ)
    {
        return ((chunkX&0xFFFFFFFF)<<32)|(chunkZ&0xFFFFFFFF);
    }
protected:

private:
};
