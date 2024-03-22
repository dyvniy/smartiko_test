#include "mymqttpublisher.h"

#include <iostream>
#include <cstring>
#include "mqtt/async_client.h"


namespace MyMqttPublisher_ns {

const std::string SERVER_ADDRESS("tcp://localhost:1883");
const std::string CLIENT_ID("publisher");
const std::string TOPIC("test/topic");
mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);
const int QOS = 1;
const int TIMEOUT = 10000;

class PublisherCallback : public virtual mqtt::callback
{
public:
    void connection_lost(const std::string& cause) override
    {
        std::cout << "Connection lost: " << cause << std::endl;
    }

    void delivery_complete(mqtt::delivery_token_ptr token) override
    {
        std::cout << "Message delivered" << std::endl;
    }
};  // PublisherCallback

int main_pub(std::string message = "test msg")
{
    mqtt::connect_options connOpts;
    connOpts.set_keep_alive_interval(20);
    connOpts.set_clean_session(true);

    try
    {
        PublisherCallback callback;
        client.set_callback(callback);

        mqtt::token_ptr connectionToken = client.connect(connOpts);
        connectionToken->wait();

        mqtt::message_ptr pubMessage = mqtt::make_message(TOPIC, message, QOS, false);
        client.publish(pubMessage)->wait();
        std::cout << "Message: " << message << " published" << std::endl;

        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        mqtt::token_ptr disconnectionToken = client.disconnect();
        disconnectionToken->wait();
    }
    catch (const mqtt::exception& ex)
    {
        std::cerr << "MQTT Exception: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}

} // MyMqttPublisher_ns

struct MyMqttPublisher::Impl {

};


MyMqttPublisher::MyMqttPublisher()
    :pImpl(new Impl())
{
}

MyMqttPublisher::~MyMqttPublisher()
{
}

void MyMqttPublisher::send(std::string message)
{
    MyMqttPublisher_ns::main_pub(message);
}
