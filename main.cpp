#include <iostream>
#include <stdlib.h>
#include <winsock2.h>
#include <thread>
using namespace std;
void test(){
}
class ZhyUDPServer{

private:
    int test1=999;
    string test2="666";
    std::thread th();
public:
    ZhyUDPServer(){

    }
    void StartThread(){

//th.join();
cout<<"This is from a class"+test2;
    }
void run(){
    WSADATA wsa;
cout<<"this is from a t::thread::hread"<<endl;
cout<<(WSAStartup(MAKEWORD(2,2),&wsa)==0?"³É¹¦":"Ê§°Ü");

}
};


int main()
{ZhyUDPServer UDP;
UDP.StartThread();
    system("pause");
    return 0;
}
