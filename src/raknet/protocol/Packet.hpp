#ifndef PKAA
#define PKAA
#include <cstring>
#include "../../utils/Binary.hpp"
#define MAGIC "\x00\xff\xff\x00\xfe\xfe\xfe\xfe\xfd\xfd\xfd\xfd\x12\x34\x56\x78"
#include <iostream>
#include <string>
class Packet
{
    public:
   const static int ID=-1;
   int offset = 0;
        int sendTime=0;
        Packet(){};
       virtual ~Packet(){
       delete[] buffer;
       }
        char *buffer;
      virtual   encode(){
   offset=1;
   buffer=new char[1464];
        }
       virtual  decode(){
   offset=1;
        }
    put(char* str,int len){

        memcpy(buffer+offset,str,len);
        offset+=len;
    }
    putLong(long v){
        put(writeLong(v),8);
    }
    putString(std::string str){

putShort(str.length());
            put((char *)str.c_str(),str.length());

    }
      putShort(short v){
                 //std:: cout<<v<<std::endl;
buffer[offset]=v&0xFF00;
buffer[offset+1]=v&0x00FF;
offset+=2;

      }
    putMagic(){
   put(MAGIC,16);
    }

    __int64 getLong(){
char aChar[8];
aChar[7]=buffer[offset++];
aChar[6]=buffer[offset++];
aChar[5]=buffer[offset++];
aChar[4]=buffer[offset++];
aChar[3]=buffer[offset++];
aChar[2]=buffer[offset++];
aChar[1]=buffer[offset++];
aChar[0]=buffer[offset++];
     return (__int64)aChar;

    }
    protected:

    private:
};
#endif
