cmake_minimum_required(VERSION 3.16)
project(project2)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)
ADD_COMPILE_OPTIONS(-g -Wall)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(project2
        register.cpp
        register.hpp
        utill.cpp
        utill.hpp)

target_link_libraries(project2 ${OpenCV_LIBS})