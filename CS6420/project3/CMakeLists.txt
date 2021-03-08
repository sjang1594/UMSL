cmake_minimum_required(VERSION 3.16)
project(freq_filter)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)
ADD_COMPILE_OPTIONS(-g -Wall)

add_executable(freq_filter
        freq_filter.cpp
        freq_filter.hpp
        utill.cpp
        utill.hpp)


target_link_libraries(freq_filter ${OpenCV_LIBS})