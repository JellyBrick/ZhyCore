
#include "../../src/raknet/lib/udpsocket.h"
#include "../../include/ExtraFuncs.h"
#include <stdio.h>
#include <windows.h>
#include <iostream>

#include "../../include/SessionManager.h"
#include "../../include/Debuger.h"
#include "protocol/DATA_PACKET_4.hpp"
#include "../Server.hpp"

using namespace std;
map<string,Session*> Sessions;
Server *server;
SessionManager::SessionManager(udpsocket* _socket,Server *ser)
{
    server=ser;
    serverId=mt_rand(0,INT_MAX);
    socket=_socket;
    tickProcessor();
//    server=getTotalServer();
}
unsigned int SessionManager::getPort()
{
    return socket->getPort();
}
SessionManager::~SessionManager()
{
}
Session* SessionManager::getSession(string source,unsigned int port)
{

    map<string,Session*>::iterator iter;
    iter=Sessions.find(source
                       +':'+writeInt(port));
    if(iter==Sessions.end())
    {

        Session *newsess=new Session(this,source,port,server);
        string key=source+':'+writeInt(port);
        Sessions.insert(pair<string,Session*>(key,newsess));
        return newsess;
    }
    else
    {
        if(       iter->second->IsKeptConnection())
        {

        }

        ;
        return iter->second;
    }

}

Packet *SessionManager::getPacketFromPool(unsigned char pid)//factory create refletion
{
//    std::cout<<(int)pid<<std::endl;
    switch(pid)
    {
    case 0x05:
        return new OPEN_CONNECTION_REQUEST_1();
        break;
    case 0x07:
        return new OPEN_CONNECTION_REQUEST_2();
        break;
    case 0x84:
        return new DATA_PACKET_4();
        break;
    default:
        return nullptr;
    }
    return nullptr;
}
/*
SessionManager::processPackets(){
std::map<string,Session *>::iterator iter;
iter=Sessions.begin();
int count=Sessions.size();
while(iter != Sessions.end()){
std::map<string,Session *>::iterator bak=++iter;--iter;
        if(count!=Sessions.size()){iter=bak;count=Sessions.size();}
   iter->second->process();
iter++;
}

}*/
bool SessionManager::receivePacket()
{
    string source;
    unsigned int port;
    string buffer=socket->readPacket(&source,port);
    if(buffer=="")return false;

    unsigned char pid=buffer[0];
    Packet* p= getPacketFromPool(pid);

    if(p != nullptr)
    {

        p->buffer=buffer;
        getSession(source,port)->handlePacket(p);
        delete p; //pay attention to here;

    }

    else if(pid==UNCONNECTED_PING::ID)
    {
        UNCONNECTED_PING packet;
        packet.buffer=buffer;
        packet.decode();
        UNCONNECTED_PONG pkk;
        pkk.serverID=serverId;
        pkk.pingID=packet.pingID;
        pkk.serverName="MCPE;The Server is powered by c++ ZhyCore ;38;66666666;233;888";
        pkk.encode();
        sendPacket(&pkk,source,port);

    }



}
__int64 SessionManager::getID()
{
    return serverId;
}
SessionManager::sendPacket(Packet* packet,std::string dest,int port)
{

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
            std::this_thread::sleep_for(std::chrono::milliseconds((int)ceil(50-time*1000)));
        tick();

    }

}
/*Server* SessionManager::getServer(){
return server;
}*/
SessionManager::removeSession(Session* session,std::string reason)
{
    std::string addr = session->address;
    unsigned int port = session->port;
    string key=addr
               +':'
               +(char)((port>>24)&0xFF)
               +(char)((port>>16)&0xFF)
               +(char)((port>>8)&0xFF)
               +(char)(port&0xFF);
    session->close();
    map<string,Session*>::iterator iter= Sessions.find(key);
    if(iter!=Sessions.end())
    {
        Sessions.erase(iter);
        delete session;
    }
    /*

     map<string ,Session*>::iterator iter=Sessions.find(key);
    if(iter!=Sessions.end()){
       //  iter->second->close();

    }*/


}

int SessionManager::tick()
{
    double time=GetStartTime();
     int count=0;
     if(Sessions.size()>0)
    for(map<string,Session*>::iterator itr=Sessions.begin(); itr != Sessions.end(); ++itr)
    {

        map<string,Session*>::iterator bakup=++itr;
        itr--;
        if(!(itr->second->update(time)))itr=bakup;
        count++;
        if(count>=Sessions.size())break;
    }

}
