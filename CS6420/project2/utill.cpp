#include "utill.hpp"

void help(char** argv)
{
	std::cout << "\n This file demonstrate manual and automatic image registeration algorithm. When one image"
		"image is given, the template image is artificially formed by a random warp. When both images are given"
		", the initialization of the warp by command line parsing is possible. "
		"If inputWarp is missing, the identity transofrmation initializess the algorithm. \n" << std::endl;

	//Usage Message example 1.(One image)
	std::cout << "\n Usage example (one image): \n" << argv[0] << "home_day.jpg -o=outWarp.ecc "
		"-m=euclidean -e=1e-6 \n" << std::endl;

	//Usage Message example 2.(Two image)
	std::cout << "\n Usage example (two image): \n" << argv[0] << "home_day.jpg home_night.jpg (template_image.jpg)"
		"initialWarp.ecc -o=outWarp.ecc -m=homography -e=1e-6 -w=finalimage.jpg \n" << std::endl;
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

// Mouse Control
void CallBackFunc(int event, float x, float y, int flags,  void* userdata)
{
	if (event == cv::EVENT_LBUTTONDOWN) {
		std::cout << " Press three points with left click" << std::endl;
		std::cout << "Lbuttondown down" << x << y << std::endl;;
		cv::circle(*(cv::Mat*)userdata, cv::Point(x, y), 2, CV_RGB(255, 0, 0), 3);

		// You might be able to push some x and y coordinates to vector.
	}
}
void print_array_info(cv::Point2f point[])
{
	for (int i = 0; i < 3; i++) {
		std::cout << point[i] << " ";
	}
	std::cout << "\n";
}

bool check_warpType(const std::string warp_type) {
	if (!(warp_type == "translation" || warp_type == "euclidean"
		|| warp_type == "affine" || warp_type == "homography")) {
		std::cerr << "Invalid motion transformation" << std::endl;
		return 0;
	}
}

// Return the warp type
int get_warpMode(const std::string warp_type) {
	if (warp_type == "translation")
		return(cv::MOTION_TRANSLATION);
	else if (warp_type == "euclidean")
		return(cv::MOTION_EUCLIDEAN);
	else if (warp_type == "affine")
		return(cv::MOTION_AFFINE);
	else
		return(cv::MOTION_HOMOGRAPHY);
}

// Reading Warp image
const int readWarp(std::string Filename, cv::Mat& warp, int motionType) {
	CV_Assert(warp.type() == CV_32FC1);
	int numOfElm;
	if (motionType == cv::MOTION_HOMOGRAPHY)
		numOfElm = 9; // (3 x 3)
	else
		numOfElm = 6; // (2 x 3)

	int i;
	int ret_value;

	std::ifstream myFile(Filename.c_str());
	if (myFile.is_open()) {
		float* matPtr = warp.ptr<float>(0);
		
		// Read file's content
		for (i = 0; i < numOfElm; i++) {
			myFile >> matPtr[i];
		}
		ret_value = 1;
	}
	else {
		std::cout << "Unable to open file " << Filename.c_str() << std::endl;
		ret_value = 0;
	}

	return ret_value;
}

// Save warp image
int saveWarp(std::string Filename, const cv::Mat& warp, int motionType)
{
	CV_Assert(warp.type() == CV_32FC1);
	
	const float* matPtr = warp.ptr<float>(0);
	int ret_value;

	std::ofstream outFile(Filename.c_str());
	if (!outFile) {
		std::cerr << "Error Occured for saving warp image" << Filename.c_str() << std::endl;
		ret_value = 0;
	}
	else{ // save the warp's element
		outFile << matPtr[0] << " " << matPtr[1] << " " << matPtr[2] << std::endl;
		outFile << matPtr[3] << " " << matPtr[4] << " " << matPtr[5] << std::endl;

		// if homography, add three more elements 
		if (motionType == cv::MOTION_HOMOGRAPHY) {
			outFile << matPtr[6] << " " << matPtr[7] << " " << matPtr[8] << std::endl;
		}

		ret_value = 1;
	}

	return ret_value;
}
