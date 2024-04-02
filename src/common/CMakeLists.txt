#当前路径下所有的源文件
set (DIR_LIB_SRCS 
    ./common_utils.cpp
    ./common_json.cpp
    ./common_lockfree_queue.cpp
    ./common_msg_queue.cpp
    ./common_logger.cpp
    ./common_random.cpp
    ./common_random_device.cpp
    ./common_uuid.cpp
    ./common_utf8.cpp
    ./common_port_manager.cpp
    ./common_address_ipv4.cpp
    ./common_simple_timer.cpp
    )

# 生成链接库
add_library(common ${DIR_LIB_SRCS})

target_link_libraries(common
    uuid
)

