#ifndef MainServer
#define MainServer
#include <iostream>
#include <vector>
#include "../include/ExtraFuncs.h"
#include "Player.hpp"
#include "../include/SessionManager.h"

#include "windows.h"
#include "scheduler/ThreadPool.h"
#include "raknet/RakNetServer.hpp"
#include <chrono>
#include <thread>
#include <mutex>
#include <deque>
class Server
{
public:
    std::vector<Player *>players;
    const char ADD = 1;

    std::mutex lock;
    std::deque<std::pair<Session*,EncapsulatedPacket>> PacketsQueue;

    ThreadPool pool= ThreadPool(4);

    double nextTick=0;
    int tickCounter=0;
    bool isRunning=true;
    SessionManager* manager;
    Server()
    {
        RakNetServer r(this);
        pool.enqueueWork(&r);
        manager=r.getManager();
        tickProcessor();
    };

    double tickAverage[20]= {20.0,20.0,20.0,20.0,20.0,20.0,20.0,20.0,20.0,20.0,20.0,20.0,20.0,20.0,20.0,20.0,20.0,20.0,20.0,20.0};
    double useAverage[20]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    addPlayer(Player * p)
    {

    lock.lock();
        players.push_back(p);
       lock.unlock();
    }
    double getTicksPerSecondAverage()
    {
        double total=0;
        for(int i=0; i<20; i++)
            total+=tickAverage[i];
        return total/20.0;
    }
    double  getTickUsageAverage()
    {

        double total=0;
        for(int i=0; i<20; i++){
            total+=useAverage[i];

            }
  // std::cout<<total<<std::endl;
        return (total/20.0)*100.0;
    }
    titleTick()
    {
        char ch[32];
        char ch_[32];
        sprintf(ch,"%.3f",getTicksPerSecondAverage());
        sprintf(ch_,"%.3f",getTickUsageAverage());
        std::string str;
        str+="TPS ";
        str+=ch;
        str+=" | Load ";
        str+=ch_;
        str+="%";
        SetConsoleTitle(str.c_str());
    }
    removePlayer(Player *p){
lock.lock();
  std::vector<Player *>::iterator iter= std::find(players.begin(),players.end(),p);
if(iter!=players.end()){

players.erase(iter);

}
lock.unlock();
    }
    tickProcessor()
    {
        nextTick=GetStartTime();
        while(isRunning)
        {
            tick();
double next=nextTick-GetStartTime();
if(next>0){
            std::this_thread::sleep_for(std::chrono::milliseconds((int)ceil(next*1000)));

}
        }

    }
    addToHandlePacketQueue(Session* ses,EncapsulatedPacket enpk_){
 std::pair<Session*,EncapsulatedPacket> pks;
 pks.first=ses;
 pks.second=enpk_;
 PacketsQueue.push_back(pks);

    }
    processPackets(){
        if(PacketsQueue.size()>0){
    std::pair<Session*,EncapsulatedPacket> pks=PacketsQueue.front();
    pks.first->streamEncapsulated(pks.second);
PacketsQueue.pop_front();
        }
    }
    bool tick()
    {
        double tickTime=GetStartTime();
       if((tickTime - nextTick)<-0.025)return false;
//==============TickContent===============
        ++tickCounter;
        if((tickCounter & 0b1111)==0)
            titleTick();
//manager->processPackets();
lock.lock();

if(players.size()>0){
std::vector<Player *>::iterator iter;
for(iter=players.begin();iter != players.end();++iter)
{
   (*iter)->checkNetwork();
}
}
processPackets();

lock.unlock();
//==============TickContent===============
        double now = GetStartTime();
        double tick=std::min(20.0,1/std::max(0.001,now - tickTime));
        double use=std::min(1.0,(now-tickTime)/0.05);

 tickAverage[0]=tick;
  useAverage[0]=use;
        for(int i=18; i>=0; i--)
            tickAverage[i+1]=tickAverage[i];
        for(int i=18; i>=0; i--)
            useAverage[i+1]=useAverage[i];

        if((nextTick-tickTime)<-1)
        {
            nextTick=tickTime;
        }
        else nextTick+=0.05;


    }

protected:

private:
};

#endif
