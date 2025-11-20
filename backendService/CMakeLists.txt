add_executable(backendService
        include/MqttSubscriber.h

        src/MqttSubscriber.cpp
        src/main.cpp
)

target_link_libraries(backendService
        PUBLIC
        common
        protoLib)
