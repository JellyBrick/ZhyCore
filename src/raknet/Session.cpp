#include "../../src/raknet/Session.h"
#include "../../include/Debuger.h"
#include "protocol/BATCH_PACKET.hpp"
#include "stdlib.h"
#include <iostream>
Session::Session(SessionManager* sessionManager_,std::string address_,unsigned int port_){
   Manager=sessionManager_;
    address=address_;
    port=port_;
     };
Session::~Session(){
delete PlayerClass;
}
Session::handleEncapsulatedPacketRoute(EncapsulatedPacket packet){


unsigned char pid=packet.buffer[0];
if(pid<0x80){
    if(status==STATE_CONNECTING_2){
    if(pid==CLIENT_CONNECT_DataPacket::ID){
CLIENT_CONNECT_DataPacket dataPacket;
dataPacket.buffer=packet.buffer;
dataPacket.decode();
SERVER_HANDSHAKE_DataPacket pk__;
pk__.address=address;
pk__.port=port;
pk__.sendPing=dataPacket.sendPing;
pk__.sendPong=dataPacket.sendPing+1000;
pk__.encode();
EncapsulatedPacket sendPacket;
sendPacket.reliability=0;
sendPacket.buffer=pk__.buffer;
addToQueue(sendPacket);

    }else if(pid==CLIENT_HANDSHAKE_DataPacket::ID){
CLIENT_HANDSHAKE_DataPacket dataPacket;
dataPacket.buffer=packet.buffer;
dataPacket.decode();
if(dataPacket.port==Manager->getPort()){
    status = STATE_CONNECTED;
    //isTemporal


keepPlayerConnection();

}
    }
    }else if(pid == 0x15)//disconnect
    {
        disconnect("clientDisconnect");

    }

}else if (status == STATE_CONNECTED){
streamEncapsulated(packet);
}

}
Session::streamEncapsulated(EncapsulatedPacket packet){
    if(!IsKeptConnection())return 0;
Packet* pk=getPacket(packet.buffer[0]);
pk->buffer=packet.buffer;
pk->decode();
PlayerClass->handleDataPacket(pk);
delete pk;
}
Packet* Session::getPacket(unsigned char pid){
switch(pid){
case BATCH_PACKET::ID://BATCH_PACKET
BATCH_PACKET* pk = new BATCH_PACKET();
return pk;
    break;
}
}
Session::keepPlayerConnection(){
 if(IsKeptConnection())return 0;
PlayerClass=new Player(id,address,port);
//getTotalServer()->addPlayer(PlayerClass);


}
Session::IsKeptConnection(){
return PlayerClass!=nullptr;
}
bool Session::update(double time){
    	if(!isActive and (lastUpdate + 5.0) < time){

			disconnect("timeout");
			return false;
		}
		isActive=false;
		int size=ACKQueue.size();
if(size>0){
ACK ackpk;
ackpk.needACK=ACKQueue;
ackpk.encode();
sendPacket(ackpk);
//std::cout<<Debuger::bin2hex(ackpk.buffer)<<std::endl;
ACKQueue.clear();
}
		return true;
}
Session::close(){

int offset=0;
EncapsulatedPacket epk=EncapsulatedPacket::fromBinary(std::string("\x00\x00\x08\x15",4),false,offset);
addToQueue(epk);

}
Session::disconnect(std::string reason){
Manager->removeSession(this,reason);
}
Session::addToQueue(EncapsulatedPacket pk){
DATA_PACKET_0 packet;
packet.seqNumber=sendSeqNumber++;
packet.packets.push_back(pk);
packet.encode();
sendPacket(packet);

}
Session::sendPacket(Packet packet){
Manager->sendPacket(&packet,address,port);
}

Session::handlePacket(Packet* packet){

    isActive=true;
    lastUpdate=GetStartTime();
 unsigned char ID=packet->buffer[0];

if(status == STATE_CONNECTING_2 || status == STATE_CONNECTED){
        packet->decode();

if(ID>=0x80 && ID<=0x8f)
{
if(DATA_PACKET_4* datapk=dynamic_cast<DATA_PACKET_4*>(packet)){
              int SeqNum=datapk->seqNumber;
        ACKQueue.push_back(SeqNum);
std::vector<EncapsulatedPacket> packets=datapk->packets;
for(auto iter=packets.cbegin();iter!=packets.cend();iter++)
handleEncapsulatedPacketRoute(*iter);

}

}


}
   else if(ID>0x00 && ID<0x80){
        packet->decode();

        if(OPEN_CONNECTION_REQUEST_1* pk_=dynamic_cast<OPEN_CONNECTION_REQUEST_1*>(packet)){
          //  std::cout<<"received a OPEN_CONNECTION_REQUEST_1 packet from ("<<address<<":"<<port<<")"<<std::endl;
                OPEN_CONNECTION_REPLY_1 reply;
                reply.mtuSize=pk_->mtuSize;
                reply.serverId=Manager->getID();
                reply.encode();
                sendPacket(reply);
                status=STATE_CONNECTING_1;


        }else{

           if((status==STATE_CONNECTING_1 ))


            if(OPEN_CONNECTION_REQUEST_2* pk=dynamic_cast<OPEN_CONNECTION_REQUEST_2*>(packet) ){
                id=pk->clientID;

            if(pk->serverPort == Manager->getPort()){
                mtuSize=std::max(abs(pk->mtuSize),1464);
                OPEN_CONNECTION_REPLY_2 replyt;
                replyt.mtuSize=mtuSize;
                replyt.serverId=Manager->getID();
                replyt.clientAddress=address;
                replyt.clientPort=port;
                replyt.encode();
                sendPacket(replyt);
                status=STATE_CONNECTING_2;
            }
            }

        }

    }

}

