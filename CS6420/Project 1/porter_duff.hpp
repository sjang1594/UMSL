//OpenCV Libraries
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

// C++ Std Library
#include <iostream>
#include <vector>

// Circle of Diameter.
const int radius = 150;

// Default setting 
// Create two images 640 x 480 pixels if the no arguments are given.
const cv::Size sz(640, 480);
const cv::Point center(sz.width / 2, sz.height / 2);
const cv::Point rect1_tl(center.x - static_cast<int>(0.8 * center.x), center.y - static_cast<int>(0.2 * center.y));
const cv::Point rect1_br(center.x + static_cast<int>(0.8 * center.x), center.y + static_cast<int>(0.2 * center.y));
const cv::Rect rect1(rect1_tl, rect1_br);
const cv::Point rect2_tl(center.x - static_cast<int>(0.2 * center.x), center.y - static_cast<int>(0.8 * center.y));
const cv::Point rect2_br(center.x + static_cast<int>(0.2 * center.x), center.y + static_cast<int>(0.8 * center.y));
const cv::Rect rect2(rect2_tl, rect2_br);

// Help - h function
void help(char** );

// Function Prototypes for porter duff operation.
cv::Mat make_mask(cv::Mat );
cv::Mat inverse(cv::Mat);
cv::Mat clear(cv::Mat );
cv::Mat copy(cv::Mat );
cv::Mat over(cv::Mat, cv::Mat, cv::Mat, cv::Mat);
cv::Mat inside(cv::Mat, cv::Mat, cv::Mat, cv::Mat);
cv::Mat out(cv::Mat, cv::Mat, cv::Mat, cv::Mat);
cv::Mat atop(cv::Mat, cv::Mat, cv::Mat, cv::Mat);
cv::Mat XOR(cv::Mat, cv::Mat, cv::Mat, cv::Mat);