cmake_minimum_required(VERSION 3.10)
project(awurudu_RemoteLamp_Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(awurudu_RemoteLamp_Server ipConnection.cpp ipConnection.h main.cpp listenner.cpp listenner.h)

target_link_libraries( awurudu_RemoteLamp_Server pthread )