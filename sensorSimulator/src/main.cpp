//
// Created by Erick Gonçalves on 18/11/2025.
//

#include <memory>

#include "../include/AppProperties.h"
#include "../include/Sensor.h"
#include "../include/MqttPublisher.h"
#include "v1/SensorData.pb.h"

std::atomic_bool shutdownRequested = false;

void registerSigIntHandler() {
    signal(SIGINT, [](int) {
        shutdownRequested = true;
        std::cout << "Shutting down Backend Service..." << std::endl;
    });
}

std::vector<std::shared_ptr<Sensor>> createSensors(int sensorAmount, const std::shared_ptr<SafeQueue<std::string>>& sensorReadingsQueue) {
    std::vector<std::shared_ptr<Sensor>> sensors;
    for (int i = 1; i <= sensorAmount; i++) {
        std::shared_ptr<Sensor> sensor = std::make_shared<Sensor>(i, sensorReadingsQueue);
        sensors.push_back(sensor);
    }
    return sensors;
}

void startSensors(const std::vector<std::shared_ptr<Sensor>>& sensors) {
    for (auto& sensor : sensors) {
        sensor->start();
    }
}

void stopSensors(const std::vector<std::shared_ptr<Sensor>>& sensors) {
    for (auto& sensor : sensors) {
        sensor->stop();
    }
}

int main() {
    std::cout << "Starting Sensor Simulator..." << std::endl;

    registerSigIntHandler();

    auto sensorReadingsQueue = std::make_shared<SafeQueue<std::string>>();
    auto mMqttPublisher = std::make_shared<MqttPublisher>(properties::brokerAddress, properties::mqttClientId);

    try {
        mMqttPublisher->connect();
    } catch (const std::exception &e) {
        std::cerr << "Error connecting to MQTT broker: " << e.what() << std::endl;
        return 1;
    }
    mMqttPublisher->startPublishLoopFromQueue(properties::sensorDataTopic, sensorReadingsQueue);

    auto sensors = createSensors(properties::sensorAmount, sensorReadingsQueue);
    startSensors(sensors);

    while (!shutdownRequested.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    stopSensors(sensors);
    return 0;
}
