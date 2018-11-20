cmake_minimum_required(VERSION 3.6)
project(udpserver)

set(CMAKE_CXX_STANDARD 11)
link_libraries(ws2_32 wsock32)
set(SOURCE_FILES main.cpp Command.cpp Command.h Client.cpp Client.h)
add_executable(udpserver ${SOURCE_FILES} Command.cpp Command.h Client.cpp Client.h)