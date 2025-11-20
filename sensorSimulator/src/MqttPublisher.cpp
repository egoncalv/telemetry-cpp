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
    isPublishingMessages = false;
    if (messagePublisherThread.joinable()) {
        messagePublisherThread.join();
    }
    std::cout << "Stopped publishing messages." << std::endl;
}

void MqttPublisher::publish(const std::string& topic, const std::string& message) {
    auto messageToPublish = mqtt::make_message(topic, message);
    messageToPublish->set_qos(1);
    try {
        mMqttClient->publish(messageToPublish);
    } catch (const mqtt::exception& e) {
        std::cerr << "Error publishing message: " << e.what() << std::endl;
        throw;
    }
    std::cout << "Published message to topic " << topic << std::endl;
}

void MqttPublisher::startPublishLoopFromQueue(const std::string& topic,
                                              const std::shared_ptr<SafeQueue<std::string>>& messageQueue) {
    isPublishingMessages = true;
    messagePublisherThread = std::thread([&]() {
        while (isPublishingMessages.load()) {
            std::string message;
            try {
                message = messageQueue->tryPopFor(std::chrono::milliseconds(100));
            }
            catch (const std::runtime_error&) {
                continue;
            }
            if (message.empty()) {
                continue;
            }
            publish(topic, message);
        }
    });
}
