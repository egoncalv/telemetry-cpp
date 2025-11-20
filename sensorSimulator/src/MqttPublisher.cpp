//
// Created by Erick Gonçalves on 18/11/2025.
//

#include <utility>

#include "../include/MqttPublisher.h"

MqttPublisher::MqttPublisher(const std::string& brokerAddress, const std::string& clientId)
: AMqttClient(
    mqtt::create_options_builder()
    .client_id(clientId)
    .server_uri(brokerAddress)
    .send_while_disconnected(true, true)
    .finalize(),
    mqtt::connect_options_builder()
    .clean_session()
    .finalize()) {
}

MqttPublisher::~MqttPublisher() {
    disconnect();
}

void MqttPublisher::publish(const std::string& topic, const std::string& message) {
    auto messageToPublish = mqtt::make_message(topic, message);
    messageToPublish->set_qos(1);
    mMqttClient->publish(messageToPublish)->wait();
    std::cout << "Published message to topic " << topic << ": " << message << std::endl;
}