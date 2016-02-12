#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H
#include "../src/raknet/lib/udpsocket.h"
#include "ExtraFuncs.h"
#include "../src/raknet/protocol/Packet.hpp"
#include <map>
#include "../src/raknet/Session.h"
class Session;
class SessionManager
{
public:
    Packet* getPacketFromPool(char pid);
    sendPacket(Packet* packet,std::string dest,int port);
    SessionManager(udpsocket* _socket);
    int tickProcessor(void);
    bool receivePacket();
    virtual ~SessionManager();
    udpsocket* socket;
    unsigned int serverId;
    bool shutdown=false;
    Session* getSession(std::string source,unsigned int port);
    double lastMeasure;

    int tick();

protected:

private:
};

#endif // SESSIONMANAGER_H
