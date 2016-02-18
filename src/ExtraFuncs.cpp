#ifndef ex
#define ex
#include "../include/ExtraFuncs.h"
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <cstring>
#include "utils/zlib.h"
#define BUFLEN 17000
Byte uncompr[BUFLEN];

unsigned long long nanotime( void )
{
    unsigned long long result=0;
    __asm__ __volatile__ ("rdtsc" : "=A" (result));
    return result;
}

float getMs()
{
    return nanotime()/1000000.0;
}
double GetStartTime()
{

    return nanotime()/1000000000.0;
}
unsigned char atoc(char *p) //return stream bytes
{
    short len=strlen(p);

    switch(len)
    {
    case 1:
        return(p[0]-'0');
        break;
    case 2:
        return
            (p[0]-'0')*10
            +p[1]-'0';
    case 3:
        return (p[0]-'0')*100+
               +(p[1]-'0')*10
               +p[2]-'0';
    }
    return 0;
}
std::string zlib_decode(std::string const& data)
{
    uLongf len=BUFLEN;
    uncompress(uncompr,&len,(Bytef*)data.c_str(),data.size());
    return std::string((char*)uncompr,len);
}
CharStrAppend(char charstr[],const char beapped[] ,int & offset){
    int len=strlen(beapped);
memcpy(charstr+offset,beapped,len);
offset+=len;
}

std::string ctos(unsigned char i)
{
    if(i<=0)return "0";
    std::string res;
    int a=i/100;
    int b=(i/10)%10;
    int c=i%10;
    res+=(a==0)?:'0'+a;
    res+=(b==0 && a==0)?:'0'+b;
    res+='0'+c;
    return res;
}

int mt_rand(int min,int max)
{
    srand(time(NULL));
    return min+rand()%(max-min);
}
#endif
