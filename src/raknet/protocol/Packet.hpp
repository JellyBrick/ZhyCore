#ifndef PKAA
#define PKAA
#include <cstring>
#include "../../utils/Binary.hpp"
#include <vector>
#include <iostream>
#include <string>
#include "../../../include/ExtraFuncs.h"
#include <stdio.h>
class Packet
{
public:
    const static int ID=-1;
    const static char PROTOCOL=6;
    int offset = 0;
    int sendTime=0;
    const std::string MAGIC= std::string ("\x00\xff\xff\x00\xfe\xfe\xfe\xfe\xfd\xfd\xfd\xfd\x12\x34\x56\x78",16);
    Packet() { };
    virtual ~Packet()
    {


    }
    std::string buffer="";
    virtual   encode()
    {
        offset=1;
    }
    virtual  decode()
    {
        offset=1;
    }
    putByte(char byte){
    buffer[offset++]=byte;
    }
    char getByte(){
    return buffer[offset++];
    }
    std::string get(bool b){
        if(!b)return "";
       return buffer.substr(0,offset);
    }

    put(std::string str)
    {

buffer+=str;
        offset+=str.size();
    }
    putLong(long v)
    {
        put(writeLong(v));
    }
    putString(std::string str)
    {
        putShort(str.size());
        put(str);

    }
    putShort(short v)
    {
        //std:: cout<<v<<std::endl;
        buffer+=v&0xFF00;
        buffer+=v&0x00FF;
        offset+=2;

    }
    putMagic()
    {
        put(MAGIC);
    }
    hexdump(unsigned char *buf, const int num)
{
    int i;
    for(i = 0; i < num; i++)
    {
        printf("%02X ", buf[i]);
        if ((i+1)%8 == 0)
            printf("\n");
    }
    printf("\n");
}

    __int64 getLong()
    {
        unsigned char aChar[8];
        aChar[7]=buffer[offset++];
        aChar[6]=buffer[offset++];
        aChar[5]=buffer[offset++];
        aChar[4]=buffer[offset++];
        aChar[3]=buffer[offset++];
        aChar[2]=buffer[offset++];
        aChar[1]=buffer[offset++];
        aChar[0]=buffer[offset++];

        return *(__int64*)aChar;

    }

protected:

private:
};
#endif
