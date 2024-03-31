#ifndef MYMQTTSUBSCRIBER_H
#define MYMQTTSUBSCRIBER_H

#include <string>

class MyMqttSubscriber
{
public:
    static int main_subscriber(std::string serverAddress, std::string clientId);
};

#endif // MYMQTTSUBSCRIBER_H
