#include "../../src/raknet/Session.h"
#include <iostream>
Session::Session(SessionManager* sessionManager_,std::string address_,unsigned int port_){
SessionManager* Manager;
   Manager=sessionManager_;
    address=address_;
    port=port_;
     };
Session::handlePacket(Packet* packet){
    isActive=true;
    lastUpdate=GetStartTime();
   char ID=packet->buffer[0];
    if(ID>0x00 && ID<0x80){
        packet->decode();
        if(OPEN_CONNECTION_REQUEST_1* pk= dynamic_cast<OPEN_CONNECTION_REQUEST_1*>(packet)){
            std::cout<<"received a OPEN_CONNECTION_REQUEST_1 packet from ("<<address<<":"<<port<<")"<<std::endl;


        }
    }

}

