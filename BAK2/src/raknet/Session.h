#pragma once
#include "../../include/Debuger.h"
#include "protocol/BATCH_PACKET.hpp"
#include "stdlib.h"
#include "../../include/ExtraFuncs.h"
#include "protocol/OPEN_CONNECTION_REQUEST_1.hpp"
#include "protocol/OPEN_CONNECTION_REQUEST_2.hpp"
#include "../../include/SessionManager.h"
#include "protocol/OPEN_CONNECTION_REPLY_1.hpp"
#include "protocol/OPEN_CONNECTION_REPLY_2.hpp"
#include "protocol/DATA_PACKET_4.hpp"
#include "protocol/DATA_PACKET_0.hpp"
#include "protocol/EncapsulatedPacket.hpp"
#include "protocol/CLIENT_CONNECT_DataPacket.hpp"
#include "protocol/SERVER_HANDSHAKE_DataPacket.hpp"
#include "protocol/CLIENT_HANDSHAKE_DataPacket.hpp"
#include <vector>
#include "protocol/ACK.hpp"
#include <iostream>
class Server;
class SessionManager;
class Player;//Amazing
class Session
{
    public:
    process();
    addEncapsulatedPacketToSendQueue(EncapsulatedPacket ENPK_);
    addEncapsulatedPacketToHandleQueue(EncapsulatedPacket ENPK_);
    Player* PlayerClass=nullptr;
    std::string address;
    unsigned int port;
    double lastUpdate;
    const char STATE_CONNECTING_1=1;
    const char STATE_CONNECTING_2=2;
    const char STATE_CONNECTED=3;
    short mtuSize=512;
    char status=-1;
    __int64 id=0;
    int sendSeqNumber=0;
    bool isActive;
    std::vector<int> ACKQueue;
    Server *server;
SessionManager* Manager;
Session(SessionManager* sessionManager_,std::string address_,unsigned int port_,Server *ser);
~Session();
handleEncapsulatedPacketRoute(EncapsulatedPacket packet);
streamEncapsulated(EncapsulatedPacket packet);

Packet* getPacket(unsigned char pid);
keepPlayerConnection();
processBatch(BATCH_PACKET *batchpk);

IsKeptConnection();
bool update(double time);
close();
disconnect(std::string reason);
addToQueue(EncapsulatedPacket pk);
sendPacket(Packet packet);
handlePacket(Packet* packet);
    protected:

    private:

};
