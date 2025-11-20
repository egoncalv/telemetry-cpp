//
// Created by Erick Gonçalves on 20/11/2025.
//

#include "../include/MqttSubscriber.h"
#include <v1/SensorData.pb.h>

MqttSubscriber::MqttSubscriber(const std::string& brokerAddress, const std::string& clientId)
: AMqttClient(
    mqtt::create_options_builder()
    .client_id(clientId)
    .server_uri(brokerAddress)
    .finalize(),
    mqtt::connect_options_builder()
    .clean_session(true)
    .automatic_reconnect()
    .finalize()) {
    isReceivingMessages = false;
}

MqttSubscriber::~MqttSubscriber() {
    isReceivingMessages = false;
    mMqttClient->stop_consuming();
    if (messageReceiverThread.joinable()) {
        messageReceiverThread.join();
    }
    std::cout << "Stopped receiving messages." << std::endl;
}

void MqttSubscriber::startConsuming() {
    mMqttClient->start_consuming();
    std::cout << "Started consuming messages..." << std::endl;
}

void MqttSubscriber::subscribe(const std::string& topic) {
    mMqttClient->subscribe(topic, 1)->wait();
    std::cout << "Subscribed to topic: " << topic << std::endl;
}

void MqttSubscriber::startReceiveMessageLoop() {
    isReceivingMessages = true;
    messageReceiverThread = std::thread([this] () {
        while (isReceivingMessages.load()) {
            auto receivedMessage = mMqttClient->consume_message();
            if (receivedMessage) {
                parseAndLogMessage(receivedMessage);
            }
        }
    });
}

void MqttSubscriber::parseAndLogMessage(const mqtt::const_message_ptr& receivedMessage) {
    if (receivedMessage->get_topic_ref().to_string() == "sensor/data") {
        SensorData sensorData;
        sensorData.ParseFromString(receivedMessage->get_payload_str());
        std::string logMessage = "Received message: "
                    "SensorId: " + std::to_string(sensorData.sensor_id()) + ", "
                    "Temperature: " + std::to_string(sensorData.temperature()) + "C, "
                  + "Humidity: " + std::to_string(sensorData.humidity()) + "%, "
                  + "Pressure: " + std::to_string(sensorData.pressure()) + "hPa, "
                  + "Timestamp: " + std::to_string(sensorData.timestamp());
        std::cout << logMessage << std::endl;
    }
}
