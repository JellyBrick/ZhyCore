#include "../../src/raknet/Session.h"
#include "../../include/Debuger.h"
#include "protocol/BATCH_PACKET.hpp"
#include "datapackets/LoginPacket.hpp"
#include "../Player.hpp"
#include "stdlib.h"
#include "../Server.hpp"
#include <list>
#include <iostream>
#include <mutex>

Session::Session(SessionManager* sessionManager_,std::string address_,unsigned int port_,Server *ser)
{
    Manager=sessionManager_;
    address=address_;
    port=port_;
    server=ser;
};
Session::~Session()
{
    if(PlayerClass!=nullptr)
    {

        delete PlayerClass;

        PlayerClass=nullptr;
    }
}
void Session::handleEncapsulatedPacketRoute(EncapsulatedPacket const & packet)
{


    unsigned char pid=packet.buffer[0];
    if(pid<0x80)
    {
        if(status==STATE_CONNECTING_2)
        {
            if(pid==CLIENT_CONNECT_DataPacket::ID)
            {
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

            }
            else if(pid==CLIENT_HANDSHAKE_DataPacket::ID)
            {
                CLIENT_HANDSHAKE_DataPacket dataPacket;
                dataPacket.buffer=packet.buffer;
                dataPacket.decode();
                if(dataPacket.port==Manager->getPort())
                {
                    status = STATE_CONNECTED;
                    //isTemporal
                    EncapsulatedPacket tmppk;
                    tmppk.buffer="\xFF\x01";
                    if(!Dead)
                        server->addToHandlePacketQueue(this,tmppk);
                    //  keepPlayerConnection();
                }
            }
        }
        else if(pid == 0x15) //disconnect
        {
            disconnect("clientDisconnect");

        }

    }
    else if (status == STATE_CONNECTED)
    {
        if(!Dead)
            server->addToHandlePacketQueue(this,packet);

        //    EncapsulatedPacketsToHandle.push_back(packet);
    }

}
void Session::streamEncapsulated(EncapsulatedPacket const & packet)
{
    if(!IsKeptConnection())return;
    Packet* pk=getPacket(packet.buffer[0]);
    if(pk!=nullptr)
    {
        pk->buffer=packet.buffer;
        pk->decode();


       PlayerClass->handleDataPacket(pk);
        delete pk;
    }
}
Packet* Session::getPacket(unsigned char const & pid)
{
    switch(pid)
    {
    case BATCH_PACKET::ID://BATCH_PACKET
    {

        return new BATCH_PACKET();
    }
    break;
    case LoginPacket::ID:
    {
        return new LoginPacket();
        break;
    }
    default:
    {
        return nullptr;
    }
    }
    return nullptr;
}
void Session::keepPlayerConnection()
{

    if(IsKeptConnection())return;

    PlayerClass=new Player(id,address,port,this);
    server->addPlayer(PlayerClass);

}
void Session::processBatch(BATCH_PACKET *batchpk)
{
    std::string str(zlib_decode(batchpk->payload));

    int offset=0;
    int len=str.size();
    while(offset<len)
    {
        int pkLen=readInt(substr(str,offset,4));
        if(pkLen==0)break;
        offset+=4;
        std::string buf;
        buf.resize(pkLen);
        buf.assign(str,offset,pkLen);
        offset+=pkLen;
        if(buf[0]==BATCH_PACKET::ID)continue;//INVAILD batchpacket inside batchpacket
        Packet* pk=getPacket(buf[0]);
        if(pk!=nullptr)
        {
            pk->buffer=buf;
            pk->decode();

            PlayerClass->handleDataPacket(pk);

            delete pk;
        }


    }

}

bool Session::IsKeptConnection()
{
    return PlayerClass!=nullptr;
}
bool Session::update(double time)
{
    if(Dead)return 0;
    if(!isActive and (lastUpdate + 10.0) < time)
    {

        disconnect("timeout");
        return false;
    }
    isActive=false;
    int size=ACKQueue.size();

    if(size>0)
    {
        ACK ackpk;
        ackpk.needACK=ACKQueue;
        ackpk.encode();
        sendPacket(ackpk);
//std::cout<<Debuger::bin2hex(ackpk.buffer)<<std::endl;
        ACKQueue.clear();

    }
    return true;
}
void Session::close()
{

    int offset=0;
    EncapsulatedPacket epk=EncapsulatedPacket::fromBinary(std::string("\x00\x00\x08\x15",4),false,offset);
    addToQueue(epk);

}
void Session::disconnect(std::string reason)
{
    if(!Dead)
    {


        EncapsulatedPacket tmppk;
        tmppk.buffer="\xFF\x02"+reason;
        server->addToHandlePacketQueue(this,tmppk);
        Dead=true;
    }
}
void Session::losePlayerConnection(std::string reason)
{

    if(IsKeptConnection())
    {
        PlayerClass->close();
        server->removePlayer(PlayerClass);
    }

    status=0;
    Manager->removeSession(this,reason);
}

void Session::addToQueue(EncapsulatedPacket const & pk)
{
    DATA_PACKET_0 packet;
    packet.seqNumber=sendSeqNumber++;
    packet.packets.push_back(pk);
    packet.encode();
    sendPacket(packet);

}
void Session::sendPacket(Packet & packet)
{

    Manager->sendPacket(&packet,address,port);
}

void Session::handlePacket(Packet* packet)
{

    isActive=true;
    lastUpdate=GetStartTime();
    unsigned char ID=packet->buffer[0];

    if(status == STATE_CONNECTING_2 || status == STATE_CONNECTED)
    {
        packet->decode();

        if(ID>=0x80 && ID<=0x8f)
        {
            if(DATA_PACKET_4* datapk=dynamic_cast<DATA_PACKET_4*>(packet))
            {
                int SeqNum=datapk->seqNumber;
                ACKQueue.push_back(SeqNum);
                std::vector<EncapsulatedPacket> packets=datapk->packets;
                for(auto iter=packets.cbegin(); iter!=packets.cend(); iter++)
                    handleEncapsulatedPacketRoute(*iter);

            }

        }


    }
    else if(ID>0x00 && ID<0x80)
    {
        packet->decode();

        if(OPEN_CONNECTION_REQUEST_1* pk_=dynamic_cast<OPEN_CONNECTION_REQUEST_1*>(packet))
        {
            //  std::cout<<"received a OPEN_CONNECTION_REQUEST_1 packet from ("<<address<<":"<<port<<")"<<std::endl;
            OPEN_CONNECTION_REPLY_1 reply;
            reply.mtuSize=pk_->mtuSize;
            reply.serverId=Manager->getID();
            reply.encode();
            sendPacket(reply);
            status=STATE_CONNECTING_1;


        }
        else
        {

            if((status==STATE_CONNECTING_1 ))


                if(OPEN_CONNECTION_REQUEST_2* pk=dynamic_cast<OPEN_CONNECTION_REQUEST_2*>(packet) )
                {
                    id=pk->clientID;

                    if(pk->serverPort == Manager->getPort())
                    {
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


