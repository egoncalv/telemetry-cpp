//
// Created by Erick Gonçalves on 20/11/2025.
//

#pragma once

#include <mqtt/async_client.h>

class AMqttClient {
public:
    AMqttClient(mqtt::create_options clientOptions, mqtt::connect_options connectOptions);
    ~AMqttClient();
    void connect();
    void disconnect();

protected:
    std::unique_ptr<mqtt::async_client> mMqttClient;
    std::string mClientId;

private:
    void setMqttCallbacks();
    mqtt::create_options mClientOptions;
    mqtt::connect_options mConnectionOptions;
};