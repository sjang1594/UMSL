/* Author : Seungho Jang
*  Class  : CS6420
*  Reference : http://ssp.impulsetrain.com/porterduff.html
*/

//OpenCV Libraries
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

// C++ Std Library
#include <iostream>

// Console Size
const int window_width = 640;
const int window_height = 480;

// Circle of Diameter.
const int radius = 150;

// Rectangle 1 Size
const int rect1_width = 512;
const int rect1_height = 96;

// Rectangle 2 Size
const int rect2_width = 128;
const int rect2_height = 548;

int main(int argc, char** argv) {

	// Just working with two images.
	// Create two images 640 x 480 pixels if the no arguments are given.
	
	/* Create Circle : 
						First image should be a circle in the center with radius 150 in blue color
	*/
	cv::Point mid_point = cv::Point(window_width / 2, window_height / 2);
	//std::cout << mid_point.x << " " << mid_point.y << "\n";
	cv::Mat img1 = cv::Mat::zeros(window_height, window_width , CV_8UC3);
	
	cv::circle(img1, mid_point, radius, cv::Scalar(255, 0, 0), cv::FILLED, cv::LINE_8);
	
	/*   Create Cross  :
						Second image contains a cross, created by two rectangles perpednicular to each other.
						Size of first rectangle is 512 x 96 & second rectangle is 128 x 548 pixels
						Both rectangle are centered into the image and are colored red
	*/
	
	cv::Mat img2 = cv::Mat::zeros(window_height, window_width, CV_8UC3);
	cv::Point rect1_point1 = cv::Point((mid_point.x - rect1_width / 2), (mid_point.y - rect1_height / 2));
	cv::Point rect1_point2 = cv::Point((mid_point.x + rect1_width / 2), (mid_point.y + rect1_height / 2));
	//std::cout << rect1_point1.x << " " << rect1_point1.y << "\n";
	//std::cout << rect1_point2.x << " " << rect1_point2.y << "\n";
	cv::rectangle(img2, rect1_point1, rect1_point2, cv::Scalar(0, 255, 0), -1, cv::LINE_8);
	
	cv::Point rect2_point1 = cv::Point((mid_point.x - rect2_width / 2), (mid_point.y - rect2_height / 2));
	cv::Point rect2_point2 = cv::Point((mid_point.x + rect2_width / 2), (mid_point.y + rect2_height / 2));
	cv::rectangle(img2, rect2_point1, rect2_point2, cv::Scalar(0, 255, 0), -1, cv::LINE_8);

	cv::imshow("img1", img1);
	cv::imshow("img2", img2);
	cv::waitKey(0);
		
}