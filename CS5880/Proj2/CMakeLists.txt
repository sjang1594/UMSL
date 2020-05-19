cmake_minimum_required(VERSION 2.8)
project(P2)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_C_COMPILER "g++")

ADD_COMPILE_OPTIONS(-g -Wall)

add_executable(obj main.cpp)
add_executable(obj1 main1.cpp)
add_executable(obj2 main2.cpp)
add_executable(obj3 main3.cpp)
add_executable(obj4 main4.cpp)


target_link_libraries(obj ${OpenCV_LIBS})
target_link_libraries(obj1 ${OpenCV_LIBS})
target_link_libraries(obj2 ${OpenCV_LIBS})
target_link_libraries(obj3 ${OpenCV_LIBS})
target_link_libraries(obj4 ${OpenCV_LIBS})
