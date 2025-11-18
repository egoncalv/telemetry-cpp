find_package(Protobuf REQUIRED)

add_library(proto_files
        v1/SensorData.proto
)

protobuf_generate(
        TARGET proto_files
)

target_link_libraries(proto_files
        PUBLIC
            protobuf::libprotobuf)

target_include_directories(proto_files PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
)