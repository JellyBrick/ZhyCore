#ifndef dp0
#define dp0
#include <iostream>
#include "Packet.hpp"
#include "DataPacket.hpp"
class DATA_PACKET_0 : public DataPacket
{
public:
    const static int ID=0x80;
    DATA_PACKET_0() {};
    int getID()
    {
        return ID;
    }
protected:

private:
};
#endif
