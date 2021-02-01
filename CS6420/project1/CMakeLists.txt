cmake_minimum_required(VERSION 3.16)
project(Porter_Duff_OP)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)
ADD_COMPILE_OPTIONS(-g -Wall)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Porter_Duff_OP
        operator.cpp
        porter_duff.cpp
        porter_duff.hpp)

target_link_libraries(Porter_Duff_OP ${OpenCV_LIBS})