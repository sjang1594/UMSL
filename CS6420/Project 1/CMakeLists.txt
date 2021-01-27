cmake_minimum_required(VERSION 3.14.1)

project(porter_duff)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 14)

ADD_COMPILE_OPTIONS(-g -Wall)

add_executable(poter_duff porter_duff.cpp)

target_link_libraries(poter_duff ${OpenCV_LIBs})