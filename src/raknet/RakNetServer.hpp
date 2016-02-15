#ifndef RakNetServerHPP
#define RakNetServerHPP
#include "../scheduler/ThreadPool.h"
#include "../../include/SessionManager.h"
class RakNetServer : public ThreadPoolWorker
{
public:
    RakNetServer()  {};
    SessionManager *r;
    void operator()(){
    r=new SessionManager(new udpsocket(8888));
    }
    SessionManager* getManager(){
    return r;
    }



protected:

private:
};
#endif
