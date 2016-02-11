#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H
#include "../src/raknet/lib/udpsocket.h"
#include "ExtraFuncs.h"
#include "../src/raknet/protocol/Packet.hpp"
class SessionManager
{
    public:
         sendPacket(Packet* packet,char* dest,int port);
         SessionManager(udpsocket* _socket);
         int tickProcessor(void);
        bool receivePacket();

        virtual ~SessionManager();
        udpsocket* socket;
        unsigned int serverId;
        bool shutdown=false;

         double lastMeasure;

        int tick();

    protected:

    private:
};

#endif // SESSIONMANAGER_H
