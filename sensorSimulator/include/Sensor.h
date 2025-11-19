//
// Created by Erick Gonçalves on 18/11/2025.
//

#pragma once
#include <vector>
#include <thread>
#include <google/protobuf/arena.h>

#include "SafeQueue.h"

struct SensorReading {
    uint64_t timestamp;
    double temperature;
    double humidity;
    std::optional<double> pressure;
};

class Sensor {
public:
    Sensor(int id, std::shared_ptr<SafeQueue<std::string>> readingsQueue);
    ~Sensor();
    void start();
    void stop();

private:
    void readSensorDataIntoQueue();
    static SensorReading generateRandomData();

    std::string serializeDataIntoProtobuf(const SensorReading& data);
    void clearArenaIfFull(google::protobuf::Arena& arena, std::size_t bytesUsed);

    int mSensorId;

    std::mutex mutex;
    std::shared_ptr<SafeQueue<std::string>> sensorReadings;

    std::atomic_bool isRunning;
    std::thread sensorThread;
};