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
	cv::Mat contour_result(src.size(), CV_8U, cv::Scalar(0)); //Final Mask Result

	std::vector<cv::Mat> every_contours;
	
	src.convertTo(img, CV_32FC3);
	std::vector<cv::Vec3f> sample;
	sample.assign((cv::Vec3f*)img.datastart, (cv::Vec3f*)img.dataend);

	int nClusters = 14; // # of clusters
	cv::Mat labels;
	cv::Mat centers;
	kmeans(sample, nClusters, labels, cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 10, 1.0), 3, cv::KMEANS_PP_CENTERS, centers);
	cv::Mat mask;

	cv::namedWindow("USA MAP", cv::WINDOW_NORMAL);
	imshow("USA MAP", src);
	cv::setMouseCallback("USA MAP", mouse_handler, (void*)&pt);
	cv::waitKey();
	int maxCluster = 0, ind = -1;
	for (int i = 0; i < nClusters; i++)
	{
		// Save all labels into Mat. 
		cv::Mat cloud = (labels == i);

		cv::namedWindow(cv::format("Cluster %d", i), cv::WINDOW_NORMAL);
		cv::Mat result = cv::Mat::zeros(src.rows, src.cols, CV_8UC3);

		if (cloud.isContinuous())
			mask = cloud.reshape(0, src.rows);
		else
			std::cout << "error";

		//----- Find the contours -----//
		std::vector<std::vector<cv::Point>> contours;
		cv::findContours(mask.clone(), contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
		contour_result.setTo(cv::Scalar(0));

		//----- Arc Length Threshold -----//
		int cmin = 500; 
		int cmax = 3000;
		std::vector<std::vector<cv::Point>>::const_iterator itc = contours.begin();
		while (itc != contours.end()) {
	
			if (itc->size() < cmin || itc->size() > cmax)
				itc = contours.erase(itc);
			else
				++itc;
		} 
		cv::drawContours(contour_result, contours, -1, cv::Scalar(255, 255, 255), cv::FILLED);       
		
		//----- Matching user-points and Contours -----//
		std::cout << contours.size() << std::endl;
		std::cout << "The Key Information" << std::endl;
		std::cout << " X : " << pt.x << " Y : " << pt.y << std::endl; // Look at the user input is available in this loop.

		//----- Check Each Contours to find whether the user-pixel "Inside of" Contours -----//
		for (size_t i = 0; i < contours.size(); i++) {

		}

		int m = countNonZero(contour_result);
		if (m > maxCluster)
		{
			maxCluster = m;
			ind = i;
		}
		src.copyTo(result, contour_result);
		imshow(cv::format("Cluster %d", i), result);
		imwrite(cv::format("Cluster%d.png", i), result);
	}
	std::cout << "Cluster max is " << ind << " with " << maxCluster << " pixels";
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