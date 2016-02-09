#include <iostream>
#include <stdlib.h>
#include "src/raknet/lib/udp_socket.h"
#include "src/raknet/lib/udp_packet.h"
#include "threadpool.h"
#define workernum 100;
using namespace std;
ThreadPool TotalPool=ThreadPool(4);
short port=888;
udp_socket udp_socket(port);
class UDPWorker : public ThreadPoolWorker
{
public:
	UDPWorker(void)  { }
	void operator()()
	{

while(true){
	std::shared_ptr<udp_packet> packet = udp_socket.receive();
	//if(packet!=NULL)
		std::cout << packet->get_data() << std::endl;
}
	}
};
int main()
{

   TotalPool.enqueueWork(new UDPWorker());



    system("pause");
    return 0;
}
