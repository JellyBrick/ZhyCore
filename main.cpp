#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "src/Server.hpp"
#define workernum 100;
using namespace std;
Server *ser;

int main()
{
    cout <<"ZhyCore Test Async UDP Server Started\n";
ser=new Server();

    return 0;
}
Server* getTotalServer(){
return ser;
}
