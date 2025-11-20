//
// Created by Erick Gonçalves on 18/11/2025.
//

#include "../include/MqttSubscriber.h"
#include <v1/SensorData.pb.h>

int main() {
    auto mMqttSubscriber = std::make_unique<MqttSubscriber>("tcp://localhost:1883", "backend_service_client");
    try {
        mMqttSubscriber->startConsuming();
        mMqttSubscriber->connect();
        mMqttSubscriber->subscribe("sensor/data");
        mMqttSubscriber->startReceiveMessageLoop();
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "Error in MQTT client: " << exc.what() << std::endl;
        return 1;
    }
    std::this_thread::sleep_for(std::chrono::seconds(100));
    mMqttSubscriber->stopReceiveMessageLoop();
    mMqttSubscriber->disconnect();
    return 0;
}
