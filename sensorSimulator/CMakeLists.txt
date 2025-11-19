add_executable(sensorSimulator
        include/Sensor.h
        include/MqttPublisher.h
        include/SafeQueue.h

        src/Sensor.cpp
        src/MqttPublisher.cpp
        src/main.cpp
        src/SafeQueue.cpp
)

target_link_libraries(sensorSimulator PUBLIC protoLib PahoMqttCpp::paho-mqttpp3)