#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "src/raknet/lib/udp_socket.h"
#include "src/raknet/lib/udp_packet.h"
#include "threadpool.h"
#include <string>
#include<cstring>
#define workernum 100;
using namespace std;
ThreadPool TotalPool=ThreadPool(4);
short port=8887;
udp_socket udp_socket(port);
class Debuger
{
public:
    Debuger(void){}
   char* bin2hex(char *chs,int chlen){
 char* strHex=(char *)malloc(chlen*2+1);
for (int i=0;i<chlen;i++){
char ch=chs[i];

for (int j=0;j<2;j++){
       char cCur= (ch&0x0f);
if(cCur<10)
    cCur+='0';
else cCur+='A'-10;
strHex[2*i+1-j]=cCur;
ch>>=4;
}
    }

    return strHex;
}
};
Debuger* debuger=(new Debuger());
class UDPWorker : public ThreadPoolWorker
{
public:
	UDPWorker(void)  { }
	void operator()()
	{

while(true){
shared_ptr<udp_packet> packet = udp_socket.receive();
		cout<<"len="<<packet->get_size()<<",data={"<<debuger->bin2hex(packet->get_data(),packet->get_size())<<"}"<< endl;
}
	}
};

int main()
{
cout<<"ZhyCore Test Async UDP Server Started\n";
UDPWorker* worker=new UDPWorker();
   TotalPool.enqueueWork(worker);
TotalPool.waitEnd();
    return 0;
}
