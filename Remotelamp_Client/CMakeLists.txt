cmake_minimum_required(VERSION 3.15)
project(Remotelamp_Client)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(Remotelamp_Client serverCon.cpp serverCon.h main.cpp)

target_link_libraries(Remotelamp_Client wsock32 ws2_32)