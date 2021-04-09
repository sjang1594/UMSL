/* Author		 : Seungho Jang
*  Class		 : CS6420
*  Reference	 :
*				 :
*/

#include "utill.hpp"
#include "map_segment.hpp"

int click_x = 0, click_y = 0;

int main(int argc, char** argv) 
{
	cv::CommandLineParser parser(argc, argv, keys);

	// I/O Image Path
	const cv::String img_path = parser.get<cv::String>("@input_image"); //0

	parser.about("Use this script to run the image segmentation");

	// Help Message & #arguments check
	if(argc < 1 || parser.get<bool>("help")) 
	{
		parser.printMessage();
		help(argv);
		return 0;
	}

	// Checking the parser
	if (!parser.check()) 
	{
		parser.printErrors();
		return -1;
	}

	cv::Mat src;
	src = cv::imread(cv::samples::findFile(img_path), cv::IMREAD_COLOR);

	// Src image check
	if (src.empty()) 
	{
		std::cout << "Error while opening a image \n";
		return EXIT_FAILURE;
	}

	// --------------------- Cluster image (K-Mean) -------------------------- //
	cv::Mat img;
	cv::Point2i pt(-1, -1); // User Point initialization
	//cv::Mat contour_result(src.size(), CV_8U, cv::Scalar(0)); //Final Mask Result

	std::vector<cv::Mat> images;
	cv::Mat final_result = cv::Mat::zeros(src.rows, src.cols, CV_8UC3);

	src.convertTo(img, CV_32FC3);
	std::vector<cv::Vec3f> sample;
	sample.assign((cv::Vec3f*)img.datastart, (cv::Vec3f*)img.dataend);

	std::cout << "--- K mean ---" << std::endl;
	int nClusters = 13; // # of clusters
	cv::Mat labels;
	cv::Mat centers;
	kmeans(sample, nClusters, labels, cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 10, 1.0), 3, cv::KMEANS_PP_CENTERS, centers);
	cv::Mat mask;

	cv::namedWindow("USA MAP", cv::WINDOW_NORMAL);
	cv::imshow("USA MAP", src);
	cv::setMouseCallback("USA MAP", mouse_handler, (void*)&pt);
	double flag = -1;

	for (int i = 0; i < nClusters; i++)
	{
		// Save all labels into Mat. 
		cv::Mat cloud = (labels == i);

		//cv::namedWindow(cv::format("Cluster %d", i), cv::WINDOW_NORMAL);
		cv::Mat result = cv::Mat::zeros(src.rows, src.cols, CV_8UC3);

		if (cloud.isContinuous())
			mask = cloud.reshape(0, src.rows);
		else
			std::cout << "error";

		//----- Find the contours -----//
		std::vector<std::vector<cv::Point>> contours;
		cv::findContours(mask.clone(), contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
		cv::Mat contour_result(src.size(), CV_8U, cv::Scalar(0)); //Final Mask Result
		contour_result.setTo(cv::Scalar(0));

		//----- Arc Length Threshold -----//
		int cmin = 200; 
		int cmax = 4000;
		std::vector<std::vector<cv::Point>>::const_iterator itc = contours.begin();
		while (itc != contours.end()) {
	
			if (itc->size() < cmin || itc->size() > cmax)
				itc = contours.erase(itc);
			else
				++itc;
		} 
		cv::drawContours(contour_result, contours, -1, cv::Scalar(255, 255, 255), cv::FILLED);       
		images.push_back(contour_result);
	}

	cv::waitKey();
	std::cout << src.size() << std::endl;
	std::cout << "The Key Information" << std::endl;
	std::cout << " X : " << pt.x << " Y : " << pt.y << std::endl;

	std::vector<std::vector<cv::Point>> last_contours;
	//std::vector<std::vector<cv::Point>> contours_final;
	//std::vector<cv::Rect> contour_rect;
	
	// Images are consist of cluster of mask. 
	for (int i = 0; i < nClusters; i++) {
		std::vector<std::vector<cv::Point>> contours_final;
		cv::findContours(images[i], contours_final, cv::RETR_CCOMP, cv::CHAIN_APPROX_NONE);

		if (contours_final.size() == 0) {
			continue;
		}
		else {
			for (size_t j = 0; j < contours_final.size(); j++) {
				flag = cv::pointPolygonTest(contours_final[j], cv::Point2f((float)pt.x, (float)pt.y), false);

				// If it is inside of circle, then push it t
				if (flag == 1) {
					//contour_rect.push_back(boundRect[j]);
					last_contours.push_back(contours_final[j]);
				}
			}
		}
	}

	// Extract the color information from the user
	cv::Vec3b color = src.at<cv::Vec3b>(cv::Point(pt.x, pt.y));

	// Resizing the contours
	double scale = 2.0;
	cv::Moments contour_center = cv::moments(last_contours[0]);
	int center_x = (int)(contour_center.m10 / contour_center.m00);
	int center_y = (int)(contour_center.m01 / contour_center.m00);

	// Increase the region of interests ( Contours )
	std::vector<cv::Point> final_contour(last_contours[0].size());
	for (size_t i = 0; i < last_contours[0].size(); i++) {
		final_contour[i] = last_contours[0][i] - cv::Point(center_x, center_y);
		final_contour[i] *= 2;
		final_contour[i] = final_contour[i] + cv::Point(center_x, center_y);
	}
	cv::fillPoly(src, final_contour, color, cv::LINE_8);

	// Increase the region of interest
	cv::namedWindow("Output_Window", cv::WINDOW_NORMAL);
	cv::imshow("Output_Window", src);
	cv::waitKey();
	return 0;
}

void mouse_handler(int event, int x, int y, int flags, void* userdata)
{
	if (event == cv::EVENT_LBUTTONDOWN) {
		printf("lLBUTTONDOWN down %d, %d \n", x, y);
		cv::Point* pt_Ptr = (cv::Point*)userdata;
		pt_Ptr->x = x;
		pt_Ptr->y = y;
	}
}