## i have cmake 3.5
cmake_minimum_required(VERSION 3.5)
project(zmq_proto_test)

## use this to globally use C++11 with in our project
set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_COMPILER_FLAGS "--disable-shared")

## load in pkg-config support
find_package(PkgConfig)
## use pkg-config to get hints for 0mq locations
pkg_check_modules(PC_ZeroMQ QUIET zmq)

## use the hint from above to find where 'zmq.hpp' is located
find_path(ZeroMQ_INCLUDE_DIR
    NAMES zmq.hpp
    PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
    )

## use the hint from about to find the location of libzmq
find_library(ZeroMQ_LIBRARY
    NAMES zmq
    PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
    )


add_subdirectory(msgs)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

add_executable(node1 src/node1.cpp)
target_include_directories(node1 PUBLIC ${ZeroMQ_INCLUDE_DIR})
target_link_libraries(node1 PUBLIC ${ZeroMQ_LIBRARY} proto ${PROTOBUF_LIBRARY})

add_executable(node2 src/node2.cpp)
target_include_directories(node2 PUBLIC ${ZeroMQ_INCLUDE_DIR})
target_link_libraries(node2 PUBLIC ${ZeroMQ_LIBRARY} proto ${PROTOBUF_LIBRARY})
