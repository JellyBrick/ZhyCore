#ifndef RakNetServerHPP
#define RakNetServerHPP
#include "../scheduler/ThreadPool.h"
#include "../../include/SessionManager.h"
class RakNetServer : public ThreadPoolWorker
{
public:
    Server *r;
    SessionManager *sess;
    RakNetServer(Server *ser)  {r=ser;};

    void operator()(){
    sess=new SessionManager(new udpsocket(8888),r);
    }
    SessionManager* getManager(){
        return sess;
    }


protected:

private:
};
#endif
