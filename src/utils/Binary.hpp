#ifndef binaryh
#define binaryh

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
static std::string writeInt(int v){
std::string res;
		res+= ((char)((v >> 24) & 0xFF));
		res+= ((char)((v >> 16) & 0xFF));
		res+=  ((char)((v >>  8) & 0xFF));
		res+= ((char)((v) & 0xFF));
		return res;
}




#endif
