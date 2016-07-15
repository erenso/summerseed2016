cmake_minimum_required(VERSION 3.5)
project(CHAT)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c mainHeader.h discovery.h discovery.c listenRequest.c listenRequest.h)
add_executable(CHAT ${SOURCE_FILES})