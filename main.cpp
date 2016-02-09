#include <iostream>
#include <stdlib.h>
#include <winsock2.h>
#include "threadpool.h"
#define workernum 100;
using namespace std;
class UDPWorker : public ThreadPoolWorker
{
private:
	unsigned long pos;
	unsigned long samples;
public:
	UDPWorker(void)  { }
	void operator()()
	{
		cout<<"test";
	}
};
int main()
{
ThreadPool pool=ThreadPool(4);

for(int i=0;i<5;i++){
   pool.enqueueWork(new UDPWorker());
}


    system("pause");
    return 0;
}
