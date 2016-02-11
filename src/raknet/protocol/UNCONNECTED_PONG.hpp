#ifndef pong
#define pong
#include <iostream>
#include "Packet.hpp"
#include <string>
class UNCONNECTED_PONG : public Packet
{
    public:
            int serverID;
            std::string serverName="";
   const static int ID=0x1c;
     __int64 pingID;
     UNCONNECTED_PONG(){};
        encode(){


                      Packet::encode();
                              buffer[0]=ID;
putLong(pingID);
putLong(serverID);
putMagic();
putString(serverName);


        }
         decode(){
                      Packet::decode();

        }

    protected:

    private:
};
#endif
