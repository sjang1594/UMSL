/* 	Author : Seungho Jang
	Date   : 2/3/2020
*/

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

//#include "opencv2/core/mat.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void avg_intensity(Mat img_one, Mat img_two);

int main(){
	Mat img;
	Mat gray;
	img = imread("lena.jpg");

	//Check wehther the image is imtpy or not.
	if(img.empty()){
		cerr << "Image Load failed!"<<endl;
		return -1;
	}

	//First get the width and depth of the image.
	int img_height = img.size().height;
	int img_width = img.size().width;
	cout<<"height of the color image is : "<<img_height<<endl;
	cout<<"width of the color image is : "<<img_width<<endl;		
	//Convert it to grayscale using cvtColor
	cvtColor(img, gray, COLOR_BGR2GRAY);
	
	//Find the number of channels the image has.
	cout<<"original image channels :  "<<img.channels()<<endl;
	cout<<" gray image channels: "<<gray.channels()<<endl;
	
	avg_intensity(img, gray);
	//Read the pixel intensity 
	namedWindow("image");
	imshow("image", img);

	namedWindow("gray");
	imshow("gray", gray);

	waitKey(0);
	return 0;

}

void avg_intensity(Mat img_one, Mat img_two){

	//int img_one_intensity = 0;
	//int img_two_intensity = 0;
	double avg_dis_intensity;
	//Figure out the size of image.
	int rows, cols;
	
	//Since my project uses only one pictures, and image size is fixed.
	double img_size = ((double) img_one.rows) * ((double) img_one.cols);
	cout<<"The img_size is : "<<img_size<<endl;
	for(rows=0; rows < img_one.rows; rows++){
		for(cols=0; cols < img_one.cols; cols++){
			avg_dis_intensity = abs((((double) img_one.at<uchar>(rows, cols)) + ((double) img_two.at<uchar>(rows, cols)))/(img_size));
		}
	}
	//cout<<"The intensity of first image is : "<<img_one_intensity<<endl;
	//cout<<"The intensity of second image is : "<<img_two_intensity<<endl;
	//double avg_sum_one = ((double) img_one_intensity)/(img_size);
	//double avg_sum_two = ((double) img_two_intensity)/(img_size);
	//Get the image intensity for both of the image. 
	//cout<<"Avg_distance for first image :  "<<avg_sum_one<<endl;
	//cout<<"Avg_distance for second image : "<<avg_sum_two<<endl;

	//double avg_distance = abs(avg_sum_one - avg_sum_two);
	cout<<"Avg_distance : "<<avg_dis_intensity<<endl;
}
