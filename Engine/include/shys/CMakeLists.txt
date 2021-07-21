cmake_minimum_required(VERSION 3.14)

project(SHYS VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(shys_src
    shys.cpp

    )

add_library(shys SHARED ${shys_src})

target_include_directories(shys PUBLIC ${CMAKE_CURRENT_DIR})
