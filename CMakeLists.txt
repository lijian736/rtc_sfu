#cmake min version
cmake_minimum_required (VERSION 3.5.1)

#project name
project(rtc_sfu)

#output the compilation info
message(STATUS "------The minimum cmake version is 3.5.1, CMAKE_VERSION is ${CMAKE_VERSION}")
message(STATUS "------The CMAKE_SOURCE_DIR is ${CMAKE_SOURCE_DIR}")

#check if C++11 is supported
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    message(STATUS "------The compiler ${CMAKE_CXX_COMPILER} supports C++11.")
else()
    message(FATAL_ERROR "------The compiler ${CMAKE_CXX_COMPILER} has NO C++11 support. Please select a different C++ compiler.")
endif() 


#byte order checking
option (SYS_BIG_ENDIAN "The system compiling byte-order option" OFF)
if (SYS_BIG_ENDIAN)
    add_definitions(-DSYS_BIG_ENDIAN)
endif(SYS_BIG_ENDIAN)

# c++11 thread support
set(CMAKE_CXX_FLAGS   "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_subdirectory(src)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)