#include "../include/Debuger.h"
#include <iostream>

  char strHex[1464]={0};

Debuger::Debuger()
{
    //ctor
}

Debuger::~Debuger()
{
    //dtor
}


   char* Debuger::bin2hex(char *chs,int chlen){
       if(chlen>1464)return "";
 //char* strHex=(char *)malloc(chlen*2+1);

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

