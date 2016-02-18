#pragma once
#include <iostream>
#include <vector>
#include "raknet/protocol/Packet.hpp"
#include "raknet/protocol/BATCH_PACKET.hpp"
#include "raknet/datapackets/LoginPacket.hpp"
#include "raknet/datapackets/PlayStatusPacket.hpp"
#include "raknet/datapackets/StartGamePacket.hpp"
#include "raknet/protocol/EncapsulatedPacket.hpp"
#include "raknet/Session.h"
#include "Level/Level.hpp"
#include "Level/Vector3.hpp"
class Session;
class Player
{
public:
    std::vector<int> usedChunks;
    std::vector<int> loadQueue;
    std::string username;

    const char DIMENSION_NORMAL = 0;
    int nextChunkOrderRun=5;
    int gamemode=0;
    float x=0;
    float y=64;
    float z=0;
    unsigned short viewDistance=256;
    Session *connection;
    Vector3 getSpawn()
    {
        Vector3 v3;
        v3.x=0;
        v3.y=64;
        v3.z=0;
        return v3;

    }
    checkNetwork()
    {

        nextChunkOrderRun--;
// std::cout<<nextChunkOrderRun<<std::endl;
        if(nextChunkOrderRun<=0)
            orderChunks();

    }
    bool orderChunks()
    {

        nextChunkOrderRun=200;
        int centerX=(int)ceil(x)>>4;
        int centerZ=(int)ceil(z)>>4;
        std::vector<int> newOrder;
        std::vector<int> lastChunk=usedChunks;

        int layer=1;
        int leg=0;
        int x_=0;
        int z_=0;
        int chunkX;
        int chunkZ;

        for(int i=0; i<viewDistance; ++i)
        {
            chunkX=x_+centerX;
            chunkZ=z_+centerZ;
            int index=Level::chunkHash(chunkX,chunkZ);
            if(std::find(usedChunks.begin(),usedChunks.end(),index)==usedChunks.end())
                newOrder.push_back(index);
            std::vector<int>::iterator it= std::find(lastChunk.begin(),lastChunk.end(),index);
            if(it!=lastChunk.end())
                lastChunk.erase(it);

            switch(leg)
            {
            case 0:
                ++x_;
                if(x_==layer)++leg;
                break;
            case 1:
                ++z_;
                if(z_==layer)++leg;
                break;
            case 2:
                --x_;
                if(-x_==layer)++leg;
                break;
            case 3:
                --z_;
                if(-z_==layer)
                {
                    leg=0;
                    ++layer;
                }
                break;
            }

        }

        loadQueue=newOrder;
        return true;
    }
    processPackets()
    {

        connection->process();
    }
    directDataPacket(Packet pk)
    {
        pk.encode();
        EncapsulatedPacket enpka;
        enpka.reliability=0;
        enpka.orderChannel=0;
        enpka.buffer=pk.buffer;
        connection->addToQueue(enpka);


    }
    Player(__int64 clientID_,std::string address_,unsigned int port_,Session *sess)
    {
        connection=sess;
        gamemode=1;
    };

    handleDataPacket(Packet* packet)
    {
        //std::cout<<(int)(unsigned char)packet->buffer[0]<<std::endl;

        unsigned char pid=packet->buffer[0];

        if(pid==BATCH_PACKET::ID)
        {
            connection->processBatch(dynamic_cast<BATCH_PACKET*>(packet));
            return 0;
        }


        switch(pid)
        {
        case LoginPacket::ID:

            LoginPacket*lgpk=dynamic_cast<LoginPacket*>(packet);
            username=lgpk->username;

            std::cout<<"[Info]"<<username<<" 加入了服务器"<<std::endl;

            PlayStatusPacket PSP;
            PSP.status=0;
            PSP.encode();
            directDataPacket(PSP);

            Vector3 spawnPosition=getSpawn();

            StartGamePacket SGPK;
            SGPK.seed=-1;
            SGPK.dimension=DIMENSION_NORMAL;
            SGPK.generator=1;
            SGPK.gamemode=gamemode;
            SGPK.eid=0;
            SGPK.spawnX=spawnPosition.x;
            SGPK.spawnY=spawnPosition.y;
            SGPK.spawnZ=spawnPosition.z;
            SGPK.x=x;
            SGPK.y=y;
            SGPK.z=z;
            SGPK.encode();
            directDataPacket(SGPK);


            break;
        }

    }
    close(std::string message = "", std::string reason = "generic reason", bool notify = true)
    {

        std::cout<<"[Info]"<<username<<" 退出了服务器"<<std::endl;
        connection=nullptr;

    }

protected:

private:
};
