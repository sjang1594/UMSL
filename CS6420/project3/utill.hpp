// OpenCV Libraries
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// C++ Standard Libraries
#include <iostream>
#include <string>
#include <vector>

// Help Message
void help(char** );

// Swap Coordinates
cv::Mat swap_coordinate(const cv::Mat& img);

// Draw the histogram
// This is helper function to see whether the image has been equalized 
cv::Mat plotHistogram(cv::Mat& img);

cv::Mat hist_helper(cv::Mat& img);

// Manual Filter like Notch reject filter
void manual_filter(cv::Mat& inputOutput, cv::Point center, int radius);