#ifndef Sessionh
#define Sessionh
#include <iostream>

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
#include "../Player.hpp"
#include <vector>
#include "protocol/ACK.hpp"

class SessionManager;
class Session
{
    public:
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
    sendPacket(Packet packet);
    SessionManager* Manager;
    handleEncapsulatedPacketRoute(EncapsulatedPacket packet);
    Session(SessionManager* sessionManager_,std::string address_,unsigned int port_);
    ~Session();
    handlePacket(Packet* packet);
    addToQueue(EncapsulatedPacket pk);
    disconnect(std::string reason = "Unknown");
    bool update(double time);
    close();
    Player *PlayerClass=nullptr;
    keepPlayerConnection();
    IsKeptConnection();
    streamEncapsulated(EncapsulatedPacket packet);
    Packet* getPacket(unsigned char pid1);
    std::vector<int> ACKQueue;

    protected:

    private:
};
#endif
