add_executable(backendService
        src/main.cpp
)

target_link_libraries(backendService PUBLIC protoLib PahoMqttCpp::paho-mqttpp3)
