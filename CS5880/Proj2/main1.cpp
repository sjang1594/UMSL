/*	Author : Seungho Jang
	Date   : 2/3/2020
*/

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void avg_intensity(Mat img_one, Mat Img_two);
//The RGB vector.
const double R_CHANNEL = 0.30;
const double G_CHANNEL = 0.59;
const double B_CHANNEL = 0.11;

int main(){
	int img_height;
	int img_width;
	int rows, cols;

	Mat img;
	img = imread("lena.jpg");

	//Error Checking if img doesn't load
	if(img.empty()){
		cerr << "Image Load Failed"<<endl;
		return -1;
	}

	//Get the width/height
	img_height = img.size().height;
	img_width = img.size().width;
  	cout<<"img_height : "<<img_height<<endl;
	cout<<"img_width  : "<<img_width<<endl;
	//Create a new gray scale images, which it will be the same size of lena.jpg
	Mat gray(img_height, img_width, CV_8UC1);

	//Find the intensity in color image and multiplied by given vector
	//It will make smaller because of the elements in the vector are pretty small. 
	//Then add all the RGB channel assigned to one pixel values.
	for(rows=0; rows < img_height; rows++){
		for(cols=0; cols <img_width; cols++){
			Vec3b intensity = img.at<Vec3b>(rows, cols);
			
			uchar red = intensity.val[2] * R_CHANNEL;
			uchar green = intensity.val[1] * G_CHANNEL;
			uchar blue = intensity.val[0] * B_CHANNEL;
			gray.at<uchar>(rows, cols) =red+green+blue; 
		}
	}

	
	//Then convert img to gray scale by OpenCV function cvtColor
	Mat cvt_gray_scale_img;
	cvtColor(img, cvt_gray_scale_img, COLOR_BGR2GRAY);
	avg_intensity(gray, cvt_gray_scale_img);
	
	imshow("Gray_img",gray);
	
	imshow("cvt_Gray_img", cvt_gray_scale_img);
	waitKey(0);
	return 0;
}

void avg_intensity(Mat img_one, Mat img_two){
	int rows, cols;
	//Type casting for the image 
	double img_size = ((double)img_one.size().height) *((double) img_one.size().width);
	//int img_one_intensity = 0;
	//int img_two_intensity = 0;
	
	double avg_dis_intensity;
	//For the debugging purpose
	//Can you use the Mat class then divided by double?
	cout<<"The size of img is : "<<img_size<<endl;
	for(rows = 0; rows < img_one.rows; rows++){
		for(cols = 0; cols < img_one.cols; cols++){
			avg_dis_intensity = abs((((double) img_one.at<uchar>(rows,cols)) - ((double) img_two.at<uchar>(rows, cols)))/img_size);
		}
	}

	//double sum_one = ((double) img_one_intensity)/(img_size);
	//double sum_two = ((double) img_two_intensity)/(img_size);
	

	//Another try
	Mat total_img = (img_one - img_two)/2;
	//double avg_distance = abs(sum_one - sum_two);
	cout<<"Avg_distance is : "<<avg_dis_intensity<<endl;

}
