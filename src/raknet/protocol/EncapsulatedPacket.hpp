#ifndef enpk
#define enpk
#include <iostream>
#include "Packet.hpp"
#include "../../../include/ExtraFuncs.h"
#include "math.h"
#include "../../../include/Debuger.h"
#include "../../utils/Binary.hpp"
class EncapsulatedPacket
{
public:

    int reliability;
    bool hasSplit = false;
    int length = 0;
    int messageIndex = 0;
    int orderIndex = 0;
    int orderChannel = 0;
    int splitCount = 0;
    int splitID = 0;
    int splitIndex = 0;
    std::string buffer;
    bool needACK = false;
    int identifierACK = 0;

    EncapsulatedPacket() {};
    std::string toBinary(bool internal=false)
    {
        return (char)((reliability << 5) | (hasSplit ? 0b00010000 : 0)) +
               (internal ? writeInt(buffer.size()) + writeInt(identifierACK) : writeShort(buffer.size() << 3)) +
               (reliability > 0 ?
                ((reliability >= 2 and reliability != 5) ? writeLTriad(messageIndex) : "") +
                ((reliability <= 4 and reliability != 2) ? writeLTriad(orderIndex) + (char)(orderChannel) : "")
                : ""
               ) +
               (hasSplit ? writeInt(splitCount) + writeShort(splitID) + writeInt(splitIndex) : "")
               + buffer;
    }
    static EncapsulatedPacket fromBinary(std::string binary,bool internal,int &offset)
    {
        EncapsulatedPacket packet;
        int flags = binary[0];
        int reliability_;
        bool hasSplit_;
        packet.reliability=reliability_=(flags & 0b11100000)>>5;
        packet.hasSplit=hasSplit_=(flags & 0b00010000)>0;
        int length_;
        if(internal)
        {
            length_=readInt(substr(binary,1,4));
            packet.identifierACK=readInt(substr(binary,5,4));
            offset=9;

        }
        else
        {

            length_=ceil(readShort(substr(binary,1,2))/8.0);
            offset=3;
            packet.identifierACK=0;
        }


        if(reliability_ > 0)
        {
            if(reliability_ >= 2 && reliability_ != 5)
            {
                packet.messageIndex = readLTriad(substr(binary, offset, 3));

                offset += 3;
            }

            if(reliability_ <= 4 && reliability_ != 2)
            {
                packet.orderIndex = readLTriad(substr(binary, offset, 3));

                offset += 3;

                packet.orderChannel = binary[(offset)++];
            }
        }

        if(hasSplit_)
        {
            packet.splitCount=readInt(substr(binary,offset,4));
            offset+=4;
            packet.splitID=readShort(substr(binary,offset,2));
            offset+=2;
            packet.splitIndex=readInt(substr(binary,offset,4));
            offset+=4;
        }

        packet.buffer=substr(binary,offset,length_);
        (offset)+=length_;

        return packet;
    }
protected:

private:
};
#endif
