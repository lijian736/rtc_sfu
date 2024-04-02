set (DIR_LIB_SRCS 
    ./app_config.cpp
    ./app_forward_unit.cpp
    )

include_directories(
    ${PROJECT_SOURCE_DIR}/src/common
    ${PROJECT_SOURCE_DIR}/src/io
)

add_library(application ${DIR_LIB_SRCS})

target_link_libraries(application
    common
    io
)