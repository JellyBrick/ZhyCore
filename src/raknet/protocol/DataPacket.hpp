#ifndef datapacket
#define datapacket
#include <iostream>
#include "Packet.hpp"
#include <vector>
#include "../../utils/Binary.hpp"
#include "EncapsulatedPacket.hpp"
class DataPacket : public Packet
{
public:
    unsigned int seqNumber = 0;
    std::vector<EncapsulatedPacket> packets;
    const char ID=-1;
    DataPacket() {};
    virtual getID()
    {
        return ID;
    }

    encode()
    {
        buffer+=getID();
        Packet::encode();

        putLTriad(seqNumber);
        for(auto iter:packets)
            put(iter.toBinary());

    }


    decode()
    {
        Packet::decode();
        seqNumber=getLTriad();
        while(!feof())
        {
            int off=0;
            std::string data=substr(buffer,offset,buffer.size()-offset);
            EncapsulatedPacket packet=EncapsulatedPacket::fromBinary(data,false,off);
            offset+=off;
            if(buffer.size()==0)break;
            packets.push_back(packet);
        }

    }

protected:

private:
};
#endif
