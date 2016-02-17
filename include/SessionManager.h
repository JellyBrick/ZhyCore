#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H
#include "../src/raknet/lib/udpsocket.h"
#include "ExtraFuncs.h"
#include "../src/raknet/protocol/Packet.hpp"
#include <map>
#include "../src/raknet/Session.h"
#include "../src/raknet/protocol/UNCONNECTED_PING.hpp"
#include "../src/raknet/protocol/UNCONNECTED_PONG.hpp"
#include "../src/raknet/protocol/OPEN_CONNECTION_REQUEST_1.hpp"
#include "../src/raknet/protocol/OPEN_CONNECTION_REQUEST_2.hpp"
#include "../src/raknet/protocol/DataPacket.hpp"
class Server;
class Session;
class SessionManager
{
public:
    Packet* getPacketFromPool(unsigned char pid);
    sendPacket(Packet* packet,std::string dest,int port);
    SessionManager(udpsocket* _socket,Server *ser);
    int tickProcessor(void);
    bool receivePacket();
    virtual ~SessionManager();
    udpsocket* socket;
    __int64 serverId;
    bool shutdown=false;
    __int64 getID();
    Session* getSession(std::string source,unsigned int port);
    double lastMeasure;
    unsigned int getPort();
    int tick();
    removeSession(Session* session,std::string reason);
    processPackets();
protected:

private:
};

#endif // SESSIONMANAGER_H
