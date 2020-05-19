/* 	Author 	: Seungho Jang
	Date	: 2/3/2020
*/


#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


const int HIST_DIM = 256;

void show_histogram(string const& name, Mat const&img);

int main(int argc, char** argv){
	//Create input img, gray_scale_img, and histogram
	Mat img, gray_scale;
       	img = imread(argv[1], 1);

	/* This would work as well for the command line argument
	 * if(!img.data)
	 * {return -1;}
	*/

	//Check if the image can be loadable.
	if(img.empty()){
		cerr << "Image Load Failed!\n"<<endl;
		return -1;
	}

	//If the channels is 3, then convert it to gray scale, if not just use img as gray scale. 
	if(img.channels() != 1)
		cvtColor(img, gray_scale, COLOR_RGB2GRAY);
	else
		gray_scale = img;


	imshow("original image", gray_scale);

	show_histogram("Lena hist", gray_scale);
	waitKey(0);	
	return 0;
}

void show_histogram(string const& name, Mat const& image){
	MatND histogram;
	//Channel Number for gray image
	const int* channel_num = {0};
	float channel_range[] = {0.0, 255.0};
	
	const float* channel_ranges = channel_range;
	int number_bins = 255;

	calcHist(&image, 1, channel_num, Mat(), histogram, 1, &number_bins, &channel_ranges, true, false);

	//For printing the histogram.
	int hist_w = HIST_DIM; int hist_h = HIST_DIM;
	int bin_w = cvRound((double)hist_w / number_bins);

	Mat hist_Image(hist_h, hist_w, CV_8UC1, Scalar(0,0,0));

	normalize(histogram, histogram, 0, hist_Image.rows, NORM_MINMAX, -1, Mat());
	
	for(int i = 1; i < number_bins; i++){
		line(hist_Image, Point(bin_w*(i-1), hist_h - cvRound(histogram.at<float>(i-1))),
				Point(bin_w*(i), hist_h - cvRound(histogram.at<float>(i))),
				Scalar(255, 0, 0), 2, 8, 0);
	}
	
	imshow(name, hist_Image);
}

