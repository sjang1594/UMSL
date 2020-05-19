#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdlib.h> //For random
#include <time.h>

using namespace std;
using namespace cv;


Point get_random_pos(int, int);

//Console Size
const int WIDTH = 640;
const int LENGTH = 480;

//Width & Length for Rectagular
const int RECT_WIDTH = 200;
const int RECT_LENGTH = 160;

//Square Size = 100x100
const int SQUARE_DIM = 100;

//Circl of Diameter.
const int DIAMETER_CIRCLE = 70;


int main(){

	srand(time(NULL));
	//To Create the Image with 640 by 480 pixel image with 8 bit single-channel

	Mat img(LENGTH, WIDTH, CV_8UC3);

	//Square
	//If you get the random position of top-left for squre
	Point sqr_tl_pos = get_random_pos(SQUARE_DIM, SQUARE_DIM);
	cout << "The random position of top left in square is : "<<sqr_tl_pos <<endl;

	Point sqr_br_pos = Point(sqr_tl_pos.x + SQUARE_DIM, sqr_tl_pos.y + SQUARE_DIM);
	cout << "The random position of botom right in square is : "<<sqr_br_pos <<endl; 
	
	//print out the square.
	rectangle(img, sqr_tl_pos, sqr_br_pos, Scalar(0XFF, 0, 0), -1, 8);
	
	//This would calculate the middle point
	//First of all, calculate the distance from tl and bf. 
	//Then add top left points 
	Point mid_point = ((sqr_br_pos- sqr_tl_pos)/2) + sqr_tl_pos;
	cout << "midpoint is "<<mid_point<<endl;
	
	//Assign the mid_point pixel value as 1(Black)
	img.at<uchar>(mid_point.y, mid_point.x) = 1;

	//Rectangle
	//I could also use Rect Class.
	Point rec_pos_tl = get_random_pos(RECT_WIDTH, RECT_LENGTH);
	Point rec_pos_br = Point(rec_pos_tl.x + RECT_WIDTH, rec_pos_tl.y + RECT_LENGTH);
	cout << "The random position of top left in rectangle is : "<<rec_pos_tl<<endl;
	cout << "The random position of bottom right in rectangle is : "<<rec_pos_br<<endl;

	rectangle(img, rec_pos_tl, rec_pos_br, Scalar(0, 0XFF, 0), -1 , 8);
	
	//Find the mid_point of rectangle is the same way for square.
	Point mid_point_rec = ((rec_pos_br - rec_pos_tl)/2) + rec_pos_tl;
	cout << "mid_point for rec is : "<<mid_point_rec<<endl;
	//Assign the mid_point pixel value as 1(Black)
	img.at<uchar>(mid_point_rec.y, mid_point_rec.x) = 1;

	//Circle
	Point circle_point1 = get_random_pos(DIAMETER_CIRCLE, DIAMETER_CIRCLE);
	Point circle_point2 = Point(circle_point1.x + DIAMETER_CIRCLE, circle_point1.y + DIAMETER_CIRCLE);
		
	Point mid_point_cr = Point((circle_point1.x + circle_point2.x)/2, (circle_point1.y + circle_point2.y)/2);
	cout << "mid_point_cr is : "<<mid_point_cr<<endl;
	
	circle(img, mid_point_cr, DIAMETER_CIRCLE/2, Scalar(0, 0, 0XFF), -1);
	img.at<uchar>(mid_point_cr.y, mid_point_cr.x);

	
	
	namedWindow("640 x 480");
	imshow("640 x 480", img);

	waitKey(0);
	return 0;
}

Point get_random_pos(int width, int length){
	int rand_pos_x, rand_pos_y;
	
	bool flag = 1;

	while(flag){
		rand_pos_x = rand() % width + 1;
		rand_pos_y = rand() % length + 1;
		
		if(rand_pos_x + width > width || rand_pos_y + length > length)
			flag = 0;
		else
			flag = 1;
		
	}
	
	return Point(rand_pos_x, rand_pos_y);
}
