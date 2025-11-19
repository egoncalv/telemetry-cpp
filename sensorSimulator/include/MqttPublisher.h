//
// Created by Erick Gonçalves on 18/11/2025.
//

#pragma once

#include <string>
#include <mqtt/async_client.h>

class MqttPublisher {
public:
    MqttPublisher(const std::string& brokerAddress, std::string  clientId);
    ~MqttPublisher();

    void connect();
    void publish(const std::string& topic, const std::string& message);
    void disconnect();
private:
    void setMqttCallbacks();

    std::string mClientId;

    mqtt::create_options mClientOptions;
    mqtt::connect_options mConnectionOptions;

    std::unique_ptr<mqtt::async_client> mMqttClient;
};