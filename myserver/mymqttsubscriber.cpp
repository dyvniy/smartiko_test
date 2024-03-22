#include "mymqttsubscriber.h"

#include <iostream>
#include "mqtt/async_client.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "dbworker.h"


namespace MyMqttSubscriber_ns {

DbWorker db;

boost::property_tree::ptree parceJson(std::string json)
{
  std::stringstream ss;
  ss << json;

  boost::property_tree::ptree pt;
  boost::property_tree::read_json(ss, pt);
  //std::cout << pt.get<std::string>("foo") << std::endl;

  return pt;
}

class SubscriberCallback : public virtual mqtt::callback
{
public:
    void connection_lost(const std::string& cause) override
    {
        std::cout << "Connection lost: " << cause << std::endl;
    }

    void message_arrived(mqtt::const_message_ptr message) override
    {
        const std::string& payload = message->get_payload_str();
        std::cout << "Message arrived: " << payload << std::endl;
        if (payload.find("{") == 0) {
            // json
            boost::property_tree::ptree pt = parceJson(payload);
            db.exec(pt);
            std::cout << "json" << std::endl;
        }
        else if (payload.find("GET") == 0){
            db.get(payload);
            std::cout << "read" << std::endl;
        }
        else if (payload.find("POST") == 0){
            db.insert(payload);
            std::cout << "inserted" << std::endl;
        }
        else if (payload.find("DELETE") == 0){
            db.delete_(payload);
            std::cout << "deleted" << std::endl;
        }
    }

    void delivery_complete(mqtt::delivery_token_ptr token) override
    {
        std::cout << "Message delivered" << std::endl;
    }
};

} // MyMqttSubscriber_ns


int MyMqttSubscriber::main_subscriber()
{
    const std::string SERVER_ADDRESS("tcp://localhost:1883");
    const std::string CLIENT_ID("subscriber");
    const std::string TOPIC("test/topic");
    const int QOS = 1;
    const int TIMEOUT = 10000;

    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);

    mqtt::connect_options connOpts;
    connOpts.set_keep_alive_interval(20);
    connOpts.set_clean_session(true);

    try
    {
        MyMqttSubscriber_ns::SubscriberCallback callback;
        client.set_callback(callback);

        mqtt::token_ptr connectionToken = client.connect(connOpts);
        connectionToken->wait();

        mqtt::token_ptr subToken = client.subscribe(TOPIC, QOS);
        subToken->wait();

        while (true)
        {
            // Wait for messages
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

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
