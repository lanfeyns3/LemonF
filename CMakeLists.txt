cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(DEMO "Builds Demo" OFF)

project(LemonF)

file(GLOB LEMON_FILES 
    *.cpp
)

add_library(LemonF STATIC ${LEMON_FILES})

if (DEMO)
    add_executable(LemonF-Demo "demo/main.cpp")
    target_link_libraries(LemonF-Demo PUBLIC LemonF)
endif()