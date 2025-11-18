add_executable(sensorSimulator
        include/Sensor.h

        src/Sensor.cpp
        src/main.cpp
)

target_link_libraries(sensorSimulator PUBLIC protoLib PahoMqttCpp::paho-mqttpp3)