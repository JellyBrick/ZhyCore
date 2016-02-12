#ifndef Sessionh
#define Sessionh
#include <iostream>

#include "../../include/ExtraFuncs.h"
#include "protocol/OPEN_CONNECTION_REQUEST_1.hpp"
#include "../../include/SessionManager.h"
class SessionManager;
class Session
{
    public:
    std::string address;
    unsigned int port;
    double lastUpdate;

    bool isActive;
    SessionManager* Manager;
    Session(SessionManager* sessionManager_,std::string address_,unsigned int port_);
    handlePacket(Packet* packet);

    protected:

    private:
};
#endif
