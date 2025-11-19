//
// Created by Erick Gonçalves on 18/11/2025.
//

#include <memory>

#include "../include/AppProperties.h"
#include "../include/Sensor.h"
#include "../include/MqttPublisher.h"
#include "v1/SensorData.pb.h"

int main() {
    std::vector<std::shared_ptr<Sensor>> sensors;
    auto sensorReadingsQueue = std::make_shared<SafeQueue<std::string>>();

    for (int i = 0; i < properties::sensorAmount; ++i) {
        std::shared_ptr<Sensor> sensor = std::make_shared<Sensor>(i, sensorReadingsQueue);
        sensors.push_back(sensor);
        sensor->start();
    }
    // try {
    //     auto mMqttPublisher = std::make_shared<MqttPublisher>(properties::brokerAddress, properties::mqttClientId);
    //     mMqttPublisher->connect();
    //     mMqttPublisher->publish("topic", "message");
    // } catch (const mqtt::exception& exc) {
    //     std::cerr << "Error: " << exc.what() << " [" << exc.get_reason_code() << "]" << std::endl;
    //     return 1;
    // }
    std::this_thread::sleep_for(std::chrono::seconds(100));
    return 0;
}
