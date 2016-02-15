#ifndef binaryh
#define binaryh
#include "../../include/Debuger.h"
static std::string writeLong(__int64 v) {
std::string res;

        res+=((char)((v >> 56) & 0xFF));
		res+= ((char)((v >> 48) & 0xFF));
		res+= ((char)((v >> 40) & 0xFF));
		res+= ((char)((v >> 32) & 0xFF));
		res+= ((char)((v >> 24) & 0xFF));
		res+= ((char)((v >> 16) & 0xFF));
		res+=  ((char)((v >>  8) & 0xFF));
		res+= ((char)((v) & 0xFF));
		return res;
	}
	static std::string writeShort(short v) {
std::string res;
		res+=  ((char)((v >>  8) & 0xFF));
		res+= ((char)((v) & 0xFF));
		return res;
	}
	static std::string writeTriad(short v) {
std::string res;
res+=  ((char)((v >>  16) & 0xFF));
		res+=  ((char)((v >>  8) & 0xFF));
		res+= ((char)((v) & 0xFF));
		return res;
	}
	static std::string writeLTriad(short v) {
std::string res;
res+=  ((char)(v & 0xFF));
		res+=  ((char)((v >>  16) & 0xFF));
		res+= ((char)((v >> 24) & 0xFF));
		return res;
	}
static int readInt(std::string v){

 return ((v[0] & 0xff) << 24) +
        ((v[1] & 0xff) << 16) +
        ((v[2] & 0xff) << 8) +
         (v[3] & 0xff);

}
static int readLInt(std::string v){

 return ((v[0] & 0xff) ) +
        ((v[1] & 0xff) << 8) +
        ((v[2] & 0xff) << 16) +
         (v[3] & 0xff << 24);

}
static short readShort(std::string v){
   unsigned char aChar[2];

        aChar[1]=v[0];
        aChar[0]=v[1];

        return *(short*)aChar;
}
static std::string substr(std::string str,int start,int len){//wait to upgrade
const char* chs=str.c_str();
char* v= new char[str.size()];
memcpy(v,chs+start,len);
std::string res(v,len);
delete[] v;
return res;
}
static std::string writeInt(int v){
std::string res;
		res+= ((char)((v >> 24) & 0xFF));
		res+= ((char)((v >> 16) & 0xFF));
		res+=  ((char)((v >>  8) & 0xFF));
		res+= ((char)((v) & 0xFF));
		return res;
}

static int readTriad(std::string v){
    std::string vv;
    vv+='\0';
    vv+=v[0];
    vv+=v[1];
    vv+=v[2];
return readInt(vv);
    }

static int readLTriad(std::string v){
    std::string vv;
    vv+=v[0];
    vv+=v[1];
    vv+=v[2];
     vv+='\0';
return readLInt(vv);
    }





#endif
