//
// Created by Erick Gonçalves on 18/11/2025.
//

#include <csignal>

#include "../include/MqttSubscriber.h"
#include <v1/SensorData.pb.h>

std::atomic_bool shutdownRequested = false;

void registerSigIntHandler() {
    signal(SIGINT, [](int) {
        shutdownRequested = true;
        std::cout << "Shutting down Backend Service..." << std::endl;
    });
}

int main() {
    std::cout << "Starting Backend Service..." << std::endl;

    registerSigIntHandler();

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

    while (!shutdownRequested.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    return 0;
}
