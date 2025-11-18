//
// Created by Erick Gonçalves on 18/11/2025.
//

#include "../include/Sensor.h"

#include <iostream>

Sensor::Sensor(int id)
    : isRunning(false), sensorId(id), sensorReading() {}

Sensor::~Sensor() {
    stop();
}

void Sensor::start() {
    if (isRunning) {
        std::cout << "Sensor " << sensorId << " is already running." << std::endl;
    }
    sensorThread = std::thread([this]() {
        isRunning = true;
        while (isRunning) {
            safePopulateData();
            std::this_thread::sleep_for(sensorReadingFrequency);
        }
    });
}

void Sensor::safePopulateData() {
    std::lock_guard lock(mutex);
    sensorReading = generateRandomData();
    std::string logMessage = "Sensor " + std::to_string(sensorId) + " reading: "
              + "Temperature: " + std::to_string(sensorReading.temperature) + "C, "
              + "Humidity: " + std::to_string(sensorReading.humidity) + "%, "
              + "Pressure: " + std::to_string(sensorReading.pressure.value_or(0)) + "hPa, "
              + "Timestamp: " + std::to_string(sensorReading.timestamp)
              + "\n";
    std::cout << logMessage;
}

void Sensor::stop() {
    isRunning = false;
}

SensorData Sensor::readData() {
    std::lock_guard lock(mutex);
    return sensorReading;
}

SensorData Sensor::generateRandomData() {
    SensorData data;

    data.temperature = static_cast<double>(rand() % 4000) / 100.0;
    data.humidity = static_cast<double>(rand() % 10000) / 100.0;
    rand() % 2 == 0
        ? data.pressure = static_cast<double>(rand() % 20000) / 100.0
        : data.pressure = std::nullopt;
    data.timestamp = std::chrono::high_resolution_clock::now().time_since_epoch().count();

    return data;
}
