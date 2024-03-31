#include "mymqttsubscriber.h"
#include "dbworker.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    std::string serverAddress("tcp://172.17.0.2:1883");
    std::string clientId("subscriber");
    if (argc > 1){
        serverAddress = argv[1];
    }
    if (argc > 2) {
        clientId = argv[2];
    }
    std::cout << serverAddress << " " << clientId << std::endl;
    return MyMqttSubscriber::main_subscriber(serverAddress, clientId);
}
