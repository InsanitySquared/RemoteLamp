cmake_minimum_required(VERSION 3.10)
project(RemoteLamp_Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(RemoteLamp_Server ipConnection.cpp ipConnection.h main.cpp listenner.cpp listenner.h)

target_link_libraries( RemoteLamp_Server pthread )