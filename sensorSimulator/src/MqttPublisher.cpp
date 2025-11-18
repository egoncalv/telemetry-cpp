//
// Created by Erick Gonçalves on 18/11/2025.
//

#include "../include/MqttPublisher.h"

MqttPublisher::MqttPublisher(const std::string& brokerAddress, const std::string& clientId)
    : mClientId(clientId) {
    mClientOptions = mqtt::create_options_builder()
                        .client_id(mClientId)
                        .server_uri(brokerAddress)
                        .send_while_disconnected(true, true)
                        .finalize();
    mMqttClient = std::make_unique<mqtt::async_client>(mClientOptions);
    setMqttCallbacks();
    mConnectionOptions = mqtt::connect_options_builder()
                                .clean_session()
                                .finalize();
}

MqttPublisher::~MqttPublisher() {
    disconnect();
}

void MqttPublisher::connect() {
    if (mMqttClient->is_connected()) {
        std::string logMessage = "MQTT client with ID " + mClientId + " is already connected.";
        std::cout << logMessage << std::endl;
        return ;
    }
    std::string logMessage = "Connecting MQTT client with ID " + mClientId + " to broker " + mClientOptions.get_server_uri();
    std::cout << logMessage << std::endl;
    mMqttClient->connect(mConnectionOptions)->wait();
}

void MqttPublisher::publish(const std::string& topic, const std::string& message) {
    auto messageToPublish = mqtt::make_message(topic, message);
    messageToPublish->set_qos(1);
    mMqttClient->publish(messageToPublish)->wait();
    std::cout << "Published message to topic " << topic << ": " << message << std::endl;
}

void MqttPublisher::disconnect() {
    std::cout << "Disconnecting MQTT client..." << std::endl;
    if (mMqttClient->is_connected()) {
        mMqttClient->disconnect()->wait();
    }
    std::cout << "Disconnected MQTT client." << std::endl;
}

void MqttPublisher::setMqttCallbacks() {
    mMqttClient->set_connected_handler([this](const std::string& cause) {
        std::string logMessage = "MQTT client with ID " + mClientId + " connected: " + cause;
        std::cout << logMessage << std::endl;
    });

    mMqttClient->set_connection_lost_handler([this] (const std::string& cause) {
        std::string logMessage = "MQTT client with ID " + mClientId + " connection lost: " + cause;
        std::cout << logMessage << std::endl;
    });
}