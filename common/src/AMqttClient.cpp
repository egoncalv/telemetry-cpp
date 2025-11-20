//
// Created by Erick Gonçalves on 20/11/2025.
//

#include "../include/AMqttClient.h"

AMqttClient::AMqttClient(mqtt::create_options clientOptions, mqtt::connect_options connectOptions)
: mClientId(clientOptions.get_client_id()),
  mClientOptions(std::move(clientOptions)),
  mConnectionOptions(std::move(connectOptions)) {
    mMqttClient = std::make_unique<mqtt::async_client>(mClientOptions);
    setMqttCallbacks();
}

AMqttClient::~AMqttClient() {
    disconnect();
}

void AMqttClient::connect() {
    if (mMqttClient->is_connected()) {
        std::string logMessage = "MQTT client with ID " + mClientId + " is already connected.";
        std::cout << logMessage << std::endl;
        return ;
    }
    std::string logMessage = "Connecting MQTT client with ID " + mClientId + " to broker " + mClientOptions.get_server_uri();
    std::cout << logMessage << std::endl;
    mMqttClient->connect(mConnectionOptions)->wait();
}

void AMqttClient::disconnect() {
    std::cout << "Disconnecting MQTT client..." << std::endl;
    if (mMqttClient->is_connected()) {
        mMqttClient->disconnect()->wait();
    }
    std::cout << "Disconnected MQTT client." << std::endl;
}

void AMqttClient::setMqttCallbacks() {
    mMqttClient->set_connected_handler([this](const std::string& cause) {
        std::string logMessage = "MQTT client with ID " + mClientId + " connected: " + cause;
        std::cout << logMessage << std::endl;
    });

    mMqttClient->set_connection_lost_handler([this] (const std::string& cause) {
        std::string logMessage = "MQTT client with ID " + mClientId + " connection lost: " + cause;
        std::cout << logMessage << std::endl;
    });
}
