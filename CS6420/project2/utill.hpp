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
#include <vector>

// Help message
void help(char** argv);

// This is helper function to see whether the image has been equalized 
cv::Mat calcGrayHist(const cv::Mat& );
cv::Mat getGrayHistImage(const cv::Mat& );

// callback function - mouse control.
void CallBackFunc(int, float, float, int, void* );
float x1, y1, x2, y2;
cv::Point2f input_points[3];
cv::Point2f template_points[3];

// print the content of vector
void print_array_info(cv::Point2f point[]);

// Warp Utility
int get_warpMode(const std::string);
bool check_warpType(const std::string);

// ReadWarp & SaveWarp - Automatic Registration.
const int readWarp(std::string Filename, cv::Mat& warp, int motionType);
static int saveWarp(std::string Filename, const cv::Mat& warp, int motionType);
