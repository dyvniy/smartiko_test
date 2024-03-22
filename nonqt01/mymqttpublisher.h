#ifndef MYMQTTPUBLISHER_H
#define MYMQTTPUBLISHER_H

#include <string>
#include <memory>

int main_pub(int argc, char* argv[]);

class MyMqttPublisher
{
    struct Impl;
    std::shared_ptr<Impl> pImpl;
public:
    MyMqttPublisher();
    virtual ~MyMqttPublisher();

    virtual void send(std::string message);
};

#endif // MYMQTTPUBLISHER_H
