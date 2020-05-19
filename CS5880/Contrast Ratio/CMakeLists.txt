cmake_minimum_required(VERSION 2.8)
project(proj)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_C_COMPILER "g++")

ADD_COMPILE_OPTIONS(-g -Wall)

add_executable(obj main.cpp)

target_link_libraries(obj ${OpenCV_LIBS})
