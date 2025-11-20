add_library(protoLib
        v1/SensorData.proto
)

set(CURRENT_PROTO_VERSION "v1")

protobuf_generate(
        TARGET protoLib
)

target_link_libraries(protoLib
        PUBLIC
        protobuf::libprotobuf
)

target_include_directories(protoLib PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
)