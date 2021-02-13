#include "utill.hpp"

void help(char** argv)
{
	std::cout << "\n This file demonstrate manual and automatic image registeration algorithm. When one image"
		"image is given, the template image is artificially formed by a random warp. When both images are given"
		", the initialization of the warp by command line parsing is possible. "
		"If inputWarp is missing, the identity transofrmation initializess the algorithm. \n" << std::endl;

	//Usage message

	//Usage Example
}

cv::Mat calcGrayHist(const cv::Mat& img)
{
	CV_Assert(img.type() == CV_8UC1);

	cv::Mat hist;
	int channels[] = { 0 };
	int dims = 1;
	const int histSize[] = { 256 };
	float graylevel[] = { 0, 256 };
	const float* ranges[] = { graylevel };

	calcHist(&img, 1, channels, cv::noArray(), hist, dims, histSize, ranges);

	return hist;
}

cv::Mat getGrayHistImage(const cv::Mat& hist)
{
	CV_Assert(hist.type() == CV_32FC1);
	//CV_Assert(hist.size() == Size(1, 256));

	double histMax;
	minMaxLoc(hist, 0, &histMax);

	cv::Mat imgHist(100, 256, CV_8UC1, cv::Scalar(255));
	for (int i = 0; i < 256; i++) {
		line(imgHist, cv::Point(i, 100),
			cv::Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), cv::Scalar(0));
	}

	return imgHist;
}

void CallBackFunc(int event, int x, int y, int flags,  void* userdata)
{
	if (event == cv::EVENT_LBUTTONDOWN) {
		std::cout << " Press three points with left click" << std::endl;
		std::cout << "Lbuttondown down" << x << y << std::endl;;
		cv::circle(*(cv::Mat*)userdata, cv::Point(x, y), 2, CV_RGB(255, 0, 0), 3);

		// You might be able to push some x and y coordinates to vector.
	}
}

