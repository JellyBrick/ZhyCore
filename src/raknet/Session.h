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
    void process();
    void addEncapsulatedPacketToSendQueue(EncapsulatedPacket ENPK_);
    void addEncapsulatedPacketToHandleQueue(EncapsulatedPacket ENPK_);
    Player* PlayerClass=nullptr;
    void losePlayerConnection(std::string reason);
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
    bool Dead=false;
    Server *server;
    SessionManager* Manager;
    Session(SessionManager* sessionManager_,std::string address_,unsigned int port_,Server *ser);
    ~Session();
    void handleEncapsulatedPacketRoute(EncapsulatedPacket const & packet);
    void streamEncapsulated(EncapsulatedPacket const & packet);

    Packet* getPacket(unsigned char const & pid);
    void keepPlayerConnection();
    void processBatch(BATCH_PACKET *batchpk);

    bool IsKeptConnection();
    bool update(double time);
    void close();
    void disconnect(std::string reason);
    void addToQueue(EncapsulatedPacket const & pk);
    void sendPacket(Packet & packet);
    void handlePacket(Packet* packet);
protected:

private:

};
