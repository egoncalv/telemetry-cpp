//
// Created by Erick Gonçalves on 18/11/2025.
//

#pragma once
#include <string>
#include <vector>
#include <thread>

namespace sensorSimulator {
    struct SensorData {
        uint64_t timestamp;
        double temperature;
        double humidity;
        std::optional<double> pressure;
    };

    class Sensor {
    public:
        Sensor(int id);
        ~Sensor();
        void start();
        void stop();
        SensorData readData();

    private:
        static SensorData generateRandomData();
        void safePopulateData();
        int sensorId;

        std::mutex mutex;
        SensorData sensorReading;

        std::atomic_bool isRunning;
        std::thread sensorThread;

        static constexpr std::chrono::milliseconds sensorReadingFrequency{500};
    };
}