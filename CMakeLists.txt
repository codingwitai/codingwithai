cmake_minimum_required(VERSION 3.20)
project(DarkFantasyEngine CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/O2 /W4 /EHsc)
endif()

include_directories(include)

add_executable(DarkFantasyEngine src/main.cpp)
