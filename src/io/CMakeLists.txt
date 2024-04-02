set (DIR_LIB_SRCS 
    ./io_utils.cpp
    ./io_socket_buffer.cpp
    ./io_socket_handler.cpp
    ./io_socket_handler_mgr.cpp
    ./io_udp_carrier.cpp
)

include_directories(
    ${PROJECT_SOURCE_DIR}/src/common
)

add_library(io ${DIR_LIB_SRCS})

target_link_libraries(io
    common
)


