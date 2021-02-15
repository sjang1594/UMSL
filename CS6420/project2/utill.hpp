// OpenCV Libraries
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>
#include <opencv2/core/utility.hpp>

// C++ Standard Libraries
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

const int niters = 50;

// Help message
void help(char** argv);

// This is helper function to see whether the image has been equalized 
cv::Mat calcGrayHist(const cv::Mat& );
cv::Mat getGrayHistImage(const cv::Mat& );

// callback function - mouse control.
void CallBackFunc(int, int, int, int, void* );

// Warp Utility
int get_warpMode(const std::string);
bool check_warpType(const std::string);

// ReadWarp
const int readWarp(std::string Filename, cv::Mat& warp, int motionType);