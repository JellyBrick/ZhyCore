#ifndef ACKpacket
#define ACKpacket
#include <iostream>
#include "Packet.hpp"
#include <vector>
#include <algorithm>
class ACK : public Packet
{
public:
    const static int ID=0xC0;
    std::vector<int> needACK;
    std::string payload="";
    ACK() {};
    void encode()
    {

        Packet::encode();
        buffer+=ID;
        std::vector<int>::iterator iter= needACK.begin();
        std::sort(iter,needACK.end());
        int count=needACK.size();
        int records=0;
        if(count>0)
        {
            //int pointer=1;
            int start = *iter;
            int last = *iter;

            while(iter != needACK.end())
            {
                iter++;
                int current=*iter;
                int diff=current-last;
                if(diff==1)
                {
                    last = current;
                }
                else if(diff>1)
                {
                    if(start==last)
                    {
                        payload+="\x01";
                        payload+=writeLTriad(start);
                        start=last=current;
                    }
                    else
                    {
                        payload+="\x00";
                        payload+=writeLTriad(start);
                        payload+=writeLTriad(last);
                        start=last=current;
                    }
                    ++records;
                }

            }
            if(start==last)
            {
                payload += "\x01";
                payload += writeLTriad(start);
            }
            else
            {
                payload += "\x00";
                payload += writeLTriad(start);
                payload += writeLTriad(last);
            }
            ++records;
        }
        putShort(records);

        buffer+=payload;
    }
    void decode()
    {
        Packet::decode();

    }

protected:

private:
};
#endif
