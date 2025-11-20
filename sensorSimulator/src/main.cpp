//
// Created by Erick Gonçalves on 18/11/2025.
//

#include <memory>

#include "../include/AppProperties.h"
#include "../include/Sensor.h"
#include "../include/MqttPublisher.h"
#include "v1/SensorData.pb.h"

int main() {
    auto sensorReadingsQueue = std::make_shared<SafeQueue<std::string>>();
    auto mMqttPublisher = std::make_shared<MqttPublisher>(properties::brokerAddress, properties::mqttClientId);
    try {
        mMqttPublisher->connect();
    } catch (const std::exception &e) {
        std::cerr << "Error connecting to MQTT broker: " << e.what() << std::endl;
        return 1;
    }

    std::thread publisherThread([mMqttPublisher, sensorReadingsQueue]() {
        while (true) {
            auto messageToPublish = sensorReadingsQueue->pop();
            try {
                mMqttPublisher->publish("sensor/data", messageToPublish);
            } catch (const std::exception &e) {
                std::cerr << "Error publishing to MQTT broker: " << e.what() << std::endl;
            }
        }
    });

    std::vector<std::shared_ptr<Sensor>> sensors;
    for (int i = 0; i < properties::sensorAmount; ++i) {
        std::shared_ptr<Sensor> sensor = std::make_shared<Sensor>(i, sensorReadingsQueue);
        sensors.push_back(sensor);
        sensor->start();
    }
    std::this_thread::sleep_for(std::chrono::seconds(100));
    for (auto &sensor : sensors) {
        sensor->stop();
    }
    publisherThread.join();
    return 0;
}
