//
// Created by Erick Gonçalves on 18/11/2025.
//

#include <memory>
#include "../include/Sensor.h"

using namespace sensorSimulator;

int main() {
    static constexpr int sensorAmount{10};

    std::vector<std::shared_ptr<Sensor>> sensorsVector;

    for (int i = 0; i < sensorAmount; ++i) {
        std::shared_ptr<Sensor> sensor = std::make_shared<Sensor>(i);
        sensorsVector.push_back(sensor);
        sensor->start();
    }
    std::this_thread::sleep_for(std::chrono::seconds(100));
    return 0;
}