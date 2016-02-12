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
int main()
{
    cout<<"ZhyCore Test Async UDP Server Started\n";
       SessionManager* manager= new SessionManager(new udpsocket(8888));

    return 0;
}
