add_library(common
        include/AMqttClient.h

        src/AMqttClient.cpp
)

target_link_libraries(common PUBLIC PahoMqttCpp::paho-mqttpp3)
