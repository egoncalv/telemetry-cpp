//
// Created by Erick Gonçalves on 19/11/2025.
//

#pragma once
#include "mqtt/async_client.h"
#include "../../common/include/AMqttClient.h"

class MqttSubscriber : public AMqttClient {
public:
    MqttSubscriber(const std::string& brokerAddress, const std::string& clientId);
    ~MqttSubscriber();

    void startConsuming();
    void subscribe(const std::string& topic);
    void startReceiveMessageLoop();
    void parseAndLogMessage(const mqtt::const_message_ptr& receivedMessage);

private:
    std::thread messageReceiverThread;
    std::atomic<bool> isReceivingMessages;
};