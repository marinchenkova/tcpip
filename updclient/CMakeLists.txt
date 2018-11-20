cmake_minimum_required(VERSION 3.6)
project(updclient)

set(CMAKE_CXX_STANDARD 11)
link_libraries(ws2_32 wsock32)
set(SOURCE_FILES main.cpp Command.cpp Command.h)
add_executable(updclient ${SOURCE_FILES} Command.cpp Command.h)