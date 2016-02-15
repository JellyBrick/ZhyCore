#ifndef MainPlayer
#define MainPlayer
#include <iostream>
#include <vector>
#include "raknet/protocol/Packet.hpp"
#include "raknet/protocol/BATCH_PACKET.hpp"
class Player
{
public:
    Player(__int64 clientID_,std::string address_,unsigned int port_) {};
    handleDataPacket(Packet* packet){
        if(BATCH_PACKET* pk=dynamic_cast<BATCH_PACKET*>(packet)){
std::cout<<Debuger::bin2hex(pk->payload)<<std::endl;
        }
    }
protected:

private:
};
#endif
