
#include "../../src/raknet/lib/udpsocket.h"
#include "../../src/raknet/lib/udppacket.h"
#include "../raknet/protocol/UNCONNECTED_PING.hpp"
#include "../raknet/protocol/UNCONNECTED_PONG.hpp"
#include "../raknet/protocol/OPEN_CONNECTION_REQUEST_1.hpp"
#include "../../include/ExtraFuncs.h"
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include "../../include/SessionManager.h"
#include "../../include/Debuger.h"

using namespace std;
Debuger* buger=new Debuger();

map<string ,Session*> Sessions;
SessionManager::SessionManager(udpsocket* _socket)
{
    serverId=mt_rand(0,INT_MAX);
    socket=_socket;
    tickProcessor();
}
SessionManager::~SessionManager()
{
}
Session* SessionManager::getSession(string source,unsigned int port)
{
    map<string ,Session*>::iterator iter;
     iter=Sessions.find(source
  +':'
  +(char)((port>>24)&0xFF)
  +(char)((port>>16)&0xFF)
  +(char)((port>>8)&0xFF)
  +(char)(port&0xFF)
                            );

    if(iter==Sessions.end())
    {
        Session *newsess=new Session(this,source,port);
  string key=source
  +':'
  +(char)((port>>24)&0xFF)
  +(char)((port>>16)&0xFF)
  +(char)((port>>8)&0xFF)
  +(char)(port&0xFF);

        Sessions.insert(pair<string,Session*>(key,newsess));
        return newsess;
    }
    else {return iter->second;}
}

Packet *SessionManager::getPacketFromPool(char pid)
{
    switch(pid)
    {
    case 5:
        return  new OPEN_CONNECTION_REQUEST_1();
        break;
    default:
        return NULL;
    }
    return NULL;
}

bool SessionManager::receivePacket()
{
     string source;
    unsigned int port;
    string buffer=socket->readPacket(&source,port);
    if(buffer=="")return false;
    char pid=buffer[0];


    Packet* p= getPacketFromPool(pid);
    if(p != NULL)
    {

        p->buffer=buffer;

    getSession(source,port)->handlePacket(p);
 delete p; //pay attention to here;

    }

    else if(pid==UNCONNECTED_PING::ID)
    {
        UNCONNECTED_PING* packet=new UNCONNECTED_PING();
        packet->buffer=buffer;
        packet->decode();
        UNCONNECTED_PONG* pkk=new UNCONNECTED_PONG();
        pkk->serverID=serverId;
        pkk->pingID=packet->pingID;
        pkk->serverName="MCPE;The Server is powered by c++ ZhyCore ;38;66666666;233;888";

        sendPacket((Packet*)pkk,source,port);
        delete packet;
        delete pkk;


    }



}
SessionManager::sendPacket(Packet* packet,std::string dest,int port)
{
    packet->encode();
    cout<<buger->bin2hex(packet->buffer)<<endl;
    socket->writePacket(dest,port,packet->buffer);
}



int SessionManager::tickProcessor()
{
    while(true)
    {
        double start=GetStartTime();
        int max=5000;
        while(--max && receivePacket());
        double time = GetStartTime()-start;
        if(time<0.05)
            Sleep(50-time*1000);
        tick();

    }

}


int SessionManager::tick() {}
