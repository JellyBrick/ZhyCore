#ifndef PKAA
#define PKAA
#include <cstring>
#include "../../utils/Binary.hpp"
#include <vector>
#include <iostream>
#include <string>
#include "../../../include/ExtraFuncs.h"
#include <stdio.h>
#include <sstream>
#include "../../../include/Debuger.h"
class Packet
{
public:
    const static int ID=-1;
    const static char PROTOCOL=6;
    unsigned int offset = 0;
    int sendTime=0;
    const std::string MAGIC= std::string ("\x00\xff\xff\x00\xfe\xfe\xfe\xfe\xfd\xfd\xfd\xfd\x12\x34\x56\x78",16);
    Packet() { };
    virtual ~Packet()
    {


    }
    std::string buffer="";
    virtual void encode()
    {
        offset=1;
    }
    virtual void decode()
    {
        offset=1;
    }
    void putByte(char byte)
    {

        buffer+=byte;
        offset++;
    }
    unsigned char getByte()
    {
//offset+=1;

        return buffer[offset++];
    }
    UUiD getUUID()
    {
        UUiD res;
        res.data1=getLong();
        res.data2=getLong();
        return res;
    }
    std::string getString()
    {
        return get(getShort());
    }
    void putInt(int v)
    {
        buffer+=writeInt(v);
        offset+=4;
    }
    void putFloat(float v)
    {
        int r;
        unsigned char ch[4];
        memcpy(ch,&v,4);
        memcpy(&r,ch,4);
        buffer+=writeInt(r);
        offset+=4;

    }
    std::string get(bool b)
    {
        if(!b)return "";
        return substr(buffer,0,offset);

    }
    std::string get(int num)
    {
        offset+=num;
        return substr(buffer,offset-num,num);
    }
    void put(std::string const & str)
    {

        buffer+=str;
        offset+=str.size();
    }
    void putLong(long v)
    {
        put(writeLong(v));
    }
    void putString(std::string const & str)
    {
        putShort(str.size());
        put(str);

    }
    void getAddress(std::string& addr,unsigned int& port)
    {
        unsigned char version=getByte();

        if(version==4)
        {

            addr=ctos((~getByte())&0xff)+".";
            addr+=ctos((~getByte())&0xff)+".";
            addr+=ctos((~getByte())&0xff)+".";
            addr+=ctos((~getByte())&0xff);
            port=getShort();
        }
        else
        {
//TODO: IPV6
        }

    }
    void putAddress(std::string const & addr,unsigned int port,char version=4)
    {
        putByte(version);
        if(version==4)
        {
            char *str=new char[addr.length()+1];
            strcpy(str,addr.c_str());
            char *p = strtok(str,".");
            while(p!=NULL)
            {
                putByte(~atoc(p));
                p = strtok(NULL,".");
            }
            putShort(port);

            delete[] str;
        }
        else
        {
//IPV6
        }

    }
    bool feof()
    {
        return offset>=buffer.size();
    }
    int getTriad()
    {
        return readTriad(get(3));
    }
    int getInt()
    {
        return readInt(get(4));
    }
    int getLTriad()
    {
        return readLTriad(get(3));
    }
    void putLTriad(int v)
    {
        return put(writeLTriad(v));
    }

    void putShort(short v)
    {
        buffer+=(char)((v>>8)&0xFF);
        buffer+=(char)(v&0xFF);
        offset+=2;

    }
    void putMagic()
    {
        put(MAGIC);
    }
    void hexdump(unsigned char *buf, const int num)
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
    short getShort()
    {
        unsigned char aChar[2];

        aChar[1]=buffer[offset++];
        aChar[0]=buffer[offset++];
        short* res=(short*)aChar;
        return *res;
    }
    int64_t getLong()
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
        int64_t* res=(int64_t*)aChar;
        return *res;

    }

protected:

private:
};
#endif
