cmake_minimum_required(VERSION 3.28)
project(telemetry_cpp)
set(CMAKE_CXX_STANDARD 20)

add_executable(telemetry_cpp)
target_sources(telemetry_cpp
    PRIVATE
        main.cpp
)

add_subdirectory(protobuf)

target_link_libraries(telemetry_cpp PUBLIC proto_files)

target_include_directories(telemetry_cpp PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/protobuf/v1
)