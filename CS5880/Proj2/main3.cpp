#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


//Subsampling is the same thing as resizing it. 
//It can be done resize. Following command resize(Mat img, Mat img, Size(100,100)).
using namespace std;
using namespace cv;

const int SUBSAMPLE_FACTOR = 5;

void mannual_subsample(Mat, Mat&, int);

int main(int argc, char*argv[]){
	Mat img = imread(argv[1], 1);
	Mat gray_scale;

	//If image cannot be loadable, Throw an Error
	if(img.empty()){
		cerr << "Image Load Failed!\n"<<endl;
		return -1;
	}

	//If image is color, change it to grayscale, if not stay as it is.
	if(img.channels() != 1)
		cvtColor(img, gray_scale, COLOR_RGB2GRAY);
	else
		gray_scale = img;

	//Figure out the height and width of the image by subsample factor
	int height = ((img.size().height) / SUBSAMPLE_FACTOR);
	int width = ((img.size().height) / SUBSAMPLE_FACTOR);

	Mat subsample_img = Mat(height, width, CV_8UC1);

	mannual_subsample(gray_scale, subsample_img, SUBSAMPLE_FACTOR);
        
	//namedWindow("original img");
	imshow("original image", gray_scale);

	//namedWindow("subSample img");
	imshow("subsample img", subsample_img);

	waitKey(0);	
	return 0;
}

void mannual_subsample(Mat img, Mat &output_img, int fac){
	for(int rows = 0; rows < output_img.rows; rows++){
		for(int cols = 0; cols < output_img.cols; cols++){
		
		output_img.at<uchar>(rows, cols) = 
			img.at<uchar>(rows * fac, cols*fac);
		}
	}
}
