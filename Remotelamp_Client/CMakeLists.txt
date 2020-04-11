cmake_minimum_required(VERSION 3.15)
project(awurudu_Remotelamp_Client)

set(CMAKE_CXX_STANDARD 14)

add_executable(awurudu_Remotelamp_Client serverCon.cpp serverCon.h main.cpp)

target_link_libraries(awurudu_Remotelamp_Client wsock32 ws2_32)