cmake_minimum_required(VERSION 3.16)
project(slic)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)
ADD_COMPILE_OPTIONS(-g -Wall)


add_executable(slic
        src/slic.cpp
        src/slic.hpp
        src/utill.cpp
        src/utill.hpp)

target_link_libraries(slic ${OpenCV_LIBS})