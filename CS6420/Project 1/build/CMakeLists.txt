cmake_minimum_required(VERSION 3.14.1)
project(Hello_OpenCV)
set(CMAKE_CXX_STANDARD 14)

# OpenCV Setup
set(OpenCV_DIR $ENV{OPENCV_4.1.1_HOME})
set(OpenCV_INCLUDE ${OpenCV_DIR}/include)
set(OpenCV_BIN ${OpenCV_DIR}/x64/mingw/bin)

include_directories(${OpenCV_INCLUDE})
add_link_options(-L ${OpenCV_BIN}
        -llibopencv_calib3d411
        -llibopencv_core411
        -llibopencv_dnn411
        -llibopencv_features2d411
        -llibopencv_flann411
        -llibopencv_gapi411
        -llibopencv_highgui411
        -llibopencv_imgcodecs411
        -llibopencv_imgproc411
        -llibopencv_ml411
        -llibopencv_objdetect411
        -llibopencv_photo411
        -llibopencv_stitching411
        -llibopencv_video411
        -llibopencv_videoio411)
find_package(OpenCV REQUIRED)