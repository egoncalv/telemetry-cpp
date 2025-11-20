# Telemetry POC with C++
This repository contains a Proof of Concept (POC) for a telemetry system implemented in C++. 
The system is designed to generate, serialize, and transmit fake telemetry data.
It uses Protobuf, MQTT, multithreading and a safe queue for efficient data handling.

## Features
- **Cmake Build System**: Uses CMake for building the project.
- **Fake Telemetry Data Generation**: Simulates telemetry data for testing purposes.
- **Protobuf Serialization**: Uses Protocol Buffers for efficient data serialization, using arenas to optimize memory usage.
- **MQTT Communication**: Transmits serialized data over MQTT protocol.
- **Multithreading**: Utilizes multiple threads for data generation, serialization, and transmission.
- **Safe Queue**: Implements a thread-safe queue to manage data flow between threads.

## Prerequisites
- C++17 compatible compiler
- CMake 3.10 or higher
- Protobuf library

## How to run:
1. Build and run backendService application
2. Build and run sensorSimulator application
3. Run an MQTT broker (using Docker for example):
```bash
     docker run -d --name emqx -p 1883:1883 -p 8083:8083 -p 8883:8883 -p 18083:18083 emqx/emqx:latest
