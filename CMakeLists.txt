cmake_minimum_required(VERSION 3.28)
project(telemetry_cpp VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)

set(PAHO_WITH_MQTT_C ON)

find_package(Protobuf CONFIG REQUIRED)

add_subdirectory(common)
add_subdirectory(paho.mqtt.cpp)
add_subdirectory(protobuf)
add_subdirectory(sensorSimulator)
add_subdirectory(backendService)