#ifndef dp4
#define dp4
#include <iostream>
#include "Packet.hpp"
#include "DataPacket.hpp"
class DATA_PACKET_4 : public DataPacket
{
public:
    const static int ID=0x84;
    DATA_PACKET_4() {};
    int getID()
    {
        return ID;
    }
protected:

private:
};
#endif
