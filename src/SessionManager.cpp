#ifndef ma
#define ma
#include "../src/raknet/lib/udpsocket.h"
#include "../src/raknet/lib/udppacket.h"
#include "raknet/protocol/UNCONNECTED_PING.hpp"
#include "raknet/protocol/UNCONNECTED_PONG.hpp"
#include "../include/ExtraFuncs.h"
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include "../include/SessionManager.h"
#include "../include/Debuger.h"
Debuger* buger=new Debuger();
  bool SessionManager::receivePacket(){
std::shared_ptr<udppacket> pk=socket->readPacket();
if(pk==NULL)return false;
char * buffer=pk->getdata();
char pid=*buffer;
if(pid==UNCONNECTED_PING::ID){
UNCONNECTED_PING* packet=new UNCONNECTED_PING();
packet->buffer=buffer;
packet->decode();
UNCONNECTED_PONG* pkk=new UNCONNECTED_PONG();
pkk->serverID=serverId;
pkk->pingID=packet->pingID;
pkk->serverName="MCPE;The Server is powered by c++ ZhyCore ;38;66666666;233;888";
//pkk->encode();
/*

One day work;

CPP 's objective is so happy to use;

                                ___Zhy
*/

sendPacket((Packet*)pkk,pk->getAddress(),pk->getPort());
delete packet;delete pkk;
}

  }
  SessionManager::sendPacket(Packet* packet,char* dest,int port){
      packet->encode();
//std::cout<<buger->bin2hex(packet->buffer,packet->offset)<<std::endl;
socket->writePacket(dest,port,packet->buffer,packet->offset);

  }
        int SessionManager::tickProcessor(){
while(true){
       double start=GetStartTime();
        int max=5000;
while(--max && receivePacket());
double time = GetStartTime()-start;
if(time<0.05)
Sleep(50-time*1000);
tick();

}

        }
SessionManager::SessionManager(udpsocket* _socket){
    serverId=mt_rand(0,INT_MAX);
    socket=_socket;
tickProcessor();
        }
        SessionManager::~SessionManager(){
        }

        int SessionManager::tick(){}
#endif
