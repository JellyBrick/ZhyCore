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
#include <list>
class Server
{
public:
    std::vector<Player *>players;
    const char ADD = 1;

    std::list<std::pair<Session*,EncapsulatedPacket>> PacketsQueue;
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
        players.push_back(p);

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
        for(int i=0; i<20; i++)
        {
            total+=useAverage[i];

        }
        // std::cout<<total<<std::endl;
        return (total/20.0)*100.0;
    }
    titleTick()
    {
        char ch[32];
        char ch_[32];
        char show[100];
        sprintf(ch,"%.3f",getTicksPerSecondAverage());
        sprintf(ch_,"%.3f",getTickUsageAverage());
        int offset=0;

CharStrAppend(show,"TPS ",offset);
CharStrAppend(show,ch,offset);
CharStrAppend(show," | Load ",offset);
CharStrAppend(show,ch_,offset);
CharStrAppend(show,"%",offset);

        show[offset]='\0';

        SetConsoleTitle(show);
    }
    removePlayer(Player *p)
    {

        std::vector<Player *>::iterator iter= std::find(players.begin(),players.end(),p);
        if(iter!=players.end())
        {

            players.erase(iter);

        }

    }
    tickProcessor()
    {
        nextTick=GetStartTime();
        while(isRunning)
        {
            double wasteTime=GetStartTime();
            tick();
            //double next=nextTick-GetStartTime();buggy?
            wasteTime-=GetStartTime();
            double next=0.05+wasteTime;
            if(next>0)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds((int)ceil(next*1000)));

            }
        }

    }

    addToHandlePacketQueue(Session* ses,EncapsulatedPacket const & enpk_)
    {
        std::pair<Session*,EncapsulatedPacket> pks;
        pks.first=ses;
        pks.second=enpk_;
        PacketsQueue.push_back(pks);

    }
    processPackets()
    {

        while(PacketsQueue.size()>0)
        {
           std::pair<Session*,EncapsulatedPacket> pk=PacketsQueue.front();
           unsigned char pid=pk.second.buffer[0];
if(pid==255){//Special Inside Pakcet
switch( (unsigned char)pk.second.buffer[1]){
case 1: //OpenSession
pk.first->keepPlayerConnection();
    break;
case 2:
    std::string tmpstr;
    tmpstr.assign(pk.second.buffer,1,pk.second.buffer.size()-2);
pk.first->losePlayerConnection(tmpstr);

    break;
}

}else
            pk.first->streamEncapsulated(pk.second);
            PacketsQueue.pop_front();
        }
    }
    bool tick()
    {
        double tickTime=GetStartTime();
//if((tickTime - nextTick)<-0.025)return false;
//==============TickContent===============
        ++tickCounter;
        if((tickCounter & 0b1111)==0)
            titleTick();
//manager->processPackets();
        if(players.size()>0)
        {
            std::vector<Player *>::iterator iter;
            for(iter=players.begin(); iter != players.end(); ++iter)
            {
                (*iter)->checkNetwork();
            }
        }
        processPackets();

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
