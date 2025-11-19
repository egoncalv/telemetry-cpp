//
// Created by Erick Gonçalves on 19/11/2025.
//
#include <string>

namespace properties {
    static constexpr int sensorAmount{10};
    static constexpr std::chrono::milliseconds sensorReadingFrequency{500};

    static constexpr std::string mqttClientId{"sensor_simulator"};
    static constexpr std::string brokerAddress{"tcp://localhost:1883"};
}