#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void contrast_testing(Mat );
void contrast_testing_1(Mat );

int main(int argc, char** argv){

	Mat img, gray_img;
	//Read image from arguments.
	img = imread(argv[1], 1);
	
	//Error Checking if input image is not given.
	if(img.empty()){
		cerr<<"Image Load Failed"<<endl;
		return -1;
	}

	//If color image, change gray image
	if(img.channels() != 1)
		cvtColor(img, gray_img, COLOR_BGR2GRAY);
	else
		gray_img = img;

	imshow("Original Gray Image", gray_img);

	//contrast_testing(gray_img);
    contrast_testing_1(gray_img);

	return 0;
}

void contrast_testing(Mat img){
	float s = 2.f;
	Mat dst = s * img;
	imshow("contrast Manip 1", dst);
	waitKey();
	destroyAllWindows();
}

void contrast_testing_1(Mat img){
	float alpha = 1.f;
	Mat dst = img + (img - 128) * alpha;
	imshow("contrast Manip 2", dst);
	waitKey();

	destroyAllWindows();
}
