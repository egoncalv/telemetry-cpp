add_executable(sensorSimulator
        include/Sensor.h
        include/MqttPublisher.h

        src/Sensor.cpp
        src/MqttPublisher.cpp
        src/main.cpp
)

target_link_libraries(sensorSimulator PUBLIC protoLib PahoMqttCpp::paho-mqttpp3)