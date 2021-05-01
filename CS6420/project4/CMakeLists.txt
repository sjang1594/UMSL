cmake_minimum_required(VERSION 3.16)
project(map_segment)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)
ADD_COMPILE_OPTIONS(-g -Wall)

add_executable(map_segment
        src/map_segment.cpp
        src/map_segment.hpp
        src/utill.cpp
        src/utill.hpp)

target_link_libraries(map_segment ${OpenCV_LIBS})