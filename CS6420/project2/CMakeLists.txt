cmake_minimum_required(VERSION 3.16)
project(register)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)
ADD_COMPILE_OPTIONS(-g -Wall)

add_executable(register
        register.cpp
        register.hpp
        utill.cpp
        utill.hpp)

target_link_libraries(register ${OpenCV_LIBS})
