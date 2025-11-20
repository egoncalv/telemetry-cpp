add_executable(sensorSimulator
        include/Sensor.h
        include/MqttPublisher.h
        include/SafeQueue.h

        src/Sensor.cpp
        src/MqttPublisher.cpp
        main.cpp
)

target_link_libraries(sensorSimulator
        PUBLIC
        common
        protoLib)