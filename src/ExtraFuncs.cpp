#ifndef ex
#define ex
#include "../include/ExtraFuncs.h"
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <unistd.h>

char* makeIPhash(char *,int port){


}
unsigned long long nanotime( void )
{
    asm
    ("rdtsc");

}
float getMs(){
return nanotime()/1000000.0;
}
double GetStartTime(){
return nanotime()/1000000000.0;
}



int mt_rand(int min,int max){
    srand(time(NULL));
return min+rand()%(max-min);
}
#endif
