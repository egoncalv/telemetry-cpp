//
// Created by Erick Gonçalves on 18/11/2025.
//

#pragma once

#include <string>
#include "../../common/include/AMqttClient.h"
#include "SafeQueue.h"

class MqttPublisher : public AMqttClient {
public:
    MqttPublisher(const std::string& brokerAddress, const std::string&  clientId);
    ~MqttPublisher();

    void publish(const std::string& topic, const std::string& message);
    void startPublishLoopFromQueue(const std::string& topic, const std::shared_ptr<SafeQueue<std::string>>& messageQueue);
private:
    std::thread messagePublisherThread;
    std::atomic_bool isPublishingMessages;
};