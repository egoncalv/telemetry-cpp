//
// Created by Erick Gonçalves on 18/11/2025.
//

#include "../include/AppProperties.h"
#include "../include/Sensor.h"
#include "v1/SensorData.pb.h"

#include <iostream>
#include <google/protobuf/arena.h>

#define MAX_BYTES_ARENA (10 * 1024)

Sensor::Sensor(int id, std::shared_ptr<SafeQueue<std::string>> readingsQueue)
    : mSensorId(id), sensorReadings(std::move(readingsQueue)), isRunning(false) {}

Sensor::~Sensor() {
    stop();
}

void Sensor::start() {
    if (isRunning) {
        std::cout << "Sensor " << mSensorId << " is already running." << std::endl;
    }
    sensorThread = std::thread([this]() {
        isRunning = true;
        while (isRunning) {

            readSensorDataIntoQueue();
            std::this_thread::sleep_for(properties::sensorReadingFrequency);
        }
    });
}

void Sensor::readSensorDataIntoQueue() {
    std::lock_guard lock(mutex);
    SensorReading randomSensorData = generateRandomData();
    std::string logMessage = "Sensor " + std::to_string(mSensorId) + " reading: "
              + "Temperature: " + std::to_string(randomSensorData.temperature) + "C, "
              + "Humidity: " + std::to_string(randomSensorData.humidity) + "%, "
              + "Pressure: " + std::to_string(randomSensorData.pressure.value_or(0)) + "hPa, "
              + "Timestamp: " + std::to_string(randomSensorData.timestamp)
              + "\n";
    std::cout << logMessage;
    auto serializedData = serializeDataIntoProtobuf(randomSensorData);
    sensorReadings->push(serializedData);
}

void Sensor::stop() {
    isRunning = false;
}

SensorReading Sensor::generateRandomData() {
    SensorReading data;

    data.temperature = static_cast<double>(rand() % 4000) / 100.0;
    data.humidity = static_cast<double>(rand() % 10000) / 100.0;
    rand() % 2 == 0
        ? data.pressure = static_cast<double>(rand() % 20000) / 100.0
        : data.pressure = std::nullopt;
    data.timestamp = std::chrono::high_resolution_clock::now().time_since_epoch().count();

    return data;
}

std::string Sensor::serializeDataIntoProtobuf(const SensorReading& data) {
    thread_local google::protobuf::Arena arena;
    SensorData* sensorDataProto = google::protobuf::Arena::Create<SensorData>(&arena);
    sensorDataProto->set_sensor_id(mSensorId);
    sensorDataProto->set_timestamp(data.timestamp);
    sensorDataProto->set_temperature(data.temperature);
    sensorDataProto->set_humidity(data.humidity);
    if (data.pressure.has_value()) {
        sensorDataProto->set_pressure(data.pressure.value());
    }
    auto serializedString = sensorDataProto->SerializeAsString();
    clearArenaIfFull(arena, sensorDataProto->ByteSizeLong());
    return serializedString;
}

void Sensor::clearArenaIfFull(google::protobuf::Arena& arena, std::size_t bytesUsed) {
    thread_local size_t arenaBytesUsed = 0;
    arenaBytesUsed += bytesUsed;
    if (arenaBytesUsed >= MAX_BYTES_ARENA) {
        arena.Reset();
        arenaBytesUsed = 0;
    }
}