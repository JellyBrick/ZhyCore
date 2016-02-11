#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "src/raknet/lib/udpsocket.h"
#include "src/raknet/lib/udppacket.h"
#include "include/Debuger.h"
#include "src/scheduler/threadpool.h"
#include <string>
#include <cstring>
#include "include/SessionManager.h"
#define workernum 100;
using namespace std;
ThreadPool TotalPool=ThreadPool(4);

//Debuger* debuger=(new Debuger());
class UDPWorker : public ThreadPoolWorker
{
public:
    UDPWorker(void)  { }
    void operator()()
    {

        while(true)
        {
//            shared_ptr<udppacket> packet = udpsocket.readPacket();
//            if(packet==NULL)continue;

  //          cout<<"Address="<<packet->getAddress();


//                <<":"<<packet->getPort()<<endl<<"len="<<packet->getsize()<<",data={"<<debuger->bin2hex(packet->getdata(),packet->getsize())<<"}"<< endl;

//udp_socket.send_to(packet->getAddress(),packet->getPort(),"\x1C\x00\x00\x00\x00\x00\x39\xDD\xDB\x18\x29\x17\xBB\x63\x89\xE3\x27\x00\xFF\xFF\x00\xFE\xFE\xFE\xFE\xFD\xFD\xFD\xFD\x12\x34\x56\x78\x00\x52\x4D\x43\x50\x45\x3B\x54\x68\x65\x20\x53\x65\x72\x76\x65\xC2\xA7\x64\xE4\xB8\xAD\xE6\x96\x87\xE6\xB5\x8B\xE8\xAF\x95\xC2\xA7\x63\x72\x20\x69\x73\x20\x70\x6F\x77\x65\x72\x65\x64\x20\x62\x79\x20\x5A\x68\x79\x43\x6F\xC2\xA7\x34\x74\x65\x73\x74\x72\x65\x3B\x33\x38\x3B\x30\x2E\x31\x34\x2E\x30\x2E\x31\x3B\x32\x33\x33\x3B\x38\x38\x38",117);
        }
    }
};

int main()
{
    cout<<"ZhyCore Test Async UDP Server Started\n";
    //UDPWorker* worker=new UDPWorker();
    //TotalPool.enqueueWork(worker);
    //TotalPool.waitEnd();

    new SessionManager(new udpsocket(8888));

    return 0;
}
