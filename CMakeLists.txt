cmake_minimum_required(VERSION 3.28)
project(telemetry_cpp VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)

find_package(Protobuf REQUIRED)

add_subdirectory(protobuf)
add_subdirectory(sensorSimulator)
add_subdirectory(backendService)