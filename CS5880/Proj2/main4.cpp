#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <bitset>

using namespace std;
using namespace cv;

/* One pixel from 8 bit gray image, it consist 8 bits
 * which means that the pixel value 00000000(0) ~ 1111111111(256)
 * Within 8 bit, there are most significant bit and least significant bit
 * So the concept is to extract the bits I want by using AND operation.
 *
 * For example, if we want to extract most 4 bits, you use 'AND' operation
 * 11110000 and all pixel value.
 *
 */

void bp_slicing(Mat, Mat&, int);
void disp_img(const char*, Mat);

int main(int argc, char**argv){

	Mat img, gray_scale;
	img = imread(argv[1], 1);

	if(img.empty()){
		cerr << "Image Load Failed!\n"<<endl;
		return -1;
	}

	if(img.channels() != 1)
		cvtColor(img, gray_scale, COLOR_RGB2GRAY);
	else
		gray_scale = img;

	
	int width = img.size().width;
	int height = img.size().height;


	Mat bit_plane_7 = Mat(height, width, CV_8UC1);
	Mat bit_plane_6 = Mat(height, width, CV_8UC1);
	Mat bit_plane_5 = Mat(height, width, CV_8UC1);
	Mat bit_plane_4 = Mat(height, width, CV_8UC1);
	Mat bit_plane_3 = Mat(height, width, CV_8UC1);
	Mat bit_plane_2 = Mat(height, width, CV_8UC1);
	Mat bit_plane_1 = Mat(height, width, CV_8UC1);
	Mat bit_plane_0 = Mat(height, width, CV_8UC1);

	bp_slicing(gray_scale, bit_plane_7, 7);
        
	disp_img("BIT PLANE7", bit_plane_7);	
	waitKey(0);
	return 0;
}

void bp_slicing(Mat input, Mat& output, int bit_plane){

	for(int rows=0; rows<input.rows; rows++){
		for(int cols=0; cols<input.cols; cols++){
			bitset<8> bin_pixel(input.at<uchar>(rows, cols));

			if(bin_pixel[bit_plane] == 1)
				output.at<uchar>(rows, cols) = 255;
			else
				output.at<uchar>(rows, cols) = 0;
		}
	}
}

void disp_img(const char* WINDOW_NAME, Mat img){
	namedWindow(WINDOW_NAME);

	imshow(WINDOW_NAME, img);
}
