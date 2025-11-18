add_executable(sensorSimulator
        src/main.cpp
)

target_link_libraries(sensorSimulator PUBLIC protoLib)