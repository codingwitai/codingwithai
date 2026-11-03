cmake_minimum_required(VERSION 3.20)
project(DarkFantasyEngine CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/O2 /W4 /EHsc)
else()
    add_compile_options(-O3 -Wall -Wextra -std=c++20)
endif()

include_directories(include)

# Defines the executable target and points directly to src/main.cpp
add_executable(DarkFantasyEngine ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)