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

void print_vector_info(std::vector<cv::Point> const vec)
{
	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec.at(i) << " ";
	}
	std::cout << "\n";
}

//bool check_warpType(const std::string warp_type) {
//	if (!(warp_type == "translation" || warp_type == "euclidean"
//		|| warp_type == "affine" || warp_type == "homography")) {
//		std::cerr << "Invalid motion transformation" << std::endl;
//		return 0;
//	}
//}

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

static void draw_warped_roi(cv::Mat& image, const int width, const int height, cv::Mat& W)
{
	cv::Point2f top_left, top_right, bottom_left, bottom_right;
	cv::Mat  H = cv::Mat(3, 1, CV_32F);
	cv::Mat  U = cv::Mat(3, 1, CV_32F);
	cv::Mat warp_mat = cv::Mat::eye(3, 3, CV_32F);
	for (int y = 0; y < W.rows; y++)
		for (int x = 0; x < W.cols; x++)
			warp_mat.at<float>(y, x) = W.at<float>(y, x);
	//warp the corners of rectangle
	// top-left
	HOMO_VECTOR(H, 1, 1);
	gemm(warp_mat, H, 1, 0, 0, U);
	GET_HOMO_VALUES(U, top_left.x, top_left.y);
	// top-right
	HOMO_VECTOR(H, width, 1);
	gemm(warp_mat, H, 1, 0, 0, U);
	GET_HOMO_VALUES(U, top_right.x, top_right.y);
	// bottom-left
	HOMO_VECTOR(H, 1, height);
	gemm(warp_mat, H, 1, 0, 0, U);
	GET_HOMO_VALUES(U, bottom_left.x, bottom_left.y);
	// bottom-right
	HOMO_VECTOR(H, width, height);
	gemm(warp_mat, H, 1, 0, 0, U);
	GET_HOMO_VALUES(U, bottom_right.x, bottom_right.y);
	// draw the warped perimeter
	line(image, top_left, top_right, cv::Scalar(255));
	line(image, top_right, bottom_right, cv::Scalar(255));
	line(image, bottom_right, bottom_left, cv::Scalar(255));
	line(image, bottom_left, top_left, cv::Scalar(255));
}
