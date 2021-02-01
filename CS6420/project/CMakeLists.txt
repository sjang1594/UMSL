cmake_minimum_required(VERSION 3.3)
project(porter_duff)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(poter_duff porter_duff.cpp)

target_link_libraries(poter_duff ${OpenCV_LIBS})