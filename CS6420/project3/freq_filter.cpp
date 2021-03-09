/* Author		 : Seungho Jang
*  Class		 : CS6420
*  Reference	 : http://www.cs.umsl.edu/~sanjiv/classes/cs6420/assignments/ass3.pdf
*				 : https://docs.opencv.org/3.4/de/dbc/tutorial_py_fourier_transform.html
*/

#include "utill.hpp"
#include "freq_filter.hpp"

int main(int argc, char** argv) {
	cv::CommandLineParser parser(argc, argv, keys);
	bool manual_option_key = parser.has("M");

	// I/O image path
	const cv::String img_path = parser.get<cv::String>("@input_image"); //0
	
	parser.about("Use this script to run the frequency filtering"); // Parser Message
	// If argc is one or argv[1] is help, show help message
	if (argc < 1 || parser.get<bool>("help")) {
		parser.printMessage();
		help(argv);
		return 0;
	}

	// Parser Check
	if (!parser.check()) {
		parser.printErrors();
		return -1;
	}

	// Variables 
	cv::Mat src, padded;

	/* ----------------------------------------------------------------------------------- */
	/* --------------------------------- Input Processing -------------------------------- */
	// Read an image with Gray scale 
	src = cv::imread(cv::samples::findFile(img_path), cv::IMREAD_GRAYSCALE);

	// Input Image Error Check
	if (src.empty()) {
		std::cout << "Error while opening a image \n";
		return EXIT_FAILURE;
	}

	// Compute the optimal size for DFT
	int m = cv::getOptimalDFTSize(src.rows);
	int n = cv::getOptimalDFTSize(src.cols);
	cv::copyMakeBorder(src, padded, 0, m - src.rows, 0, n - src.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

	/* ----------------------------------------------------------------------------------- */
	/* -------------------------- Calculate Power Density -------------------------------- */
	// Create Planes to store the real and imaginary image in frequency domain.
	cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };
	cv::Mat complexI;
	cv::merge(planes, 2, complexI);
	cv::dft(complexI, complexI);						// discrete fourier transform 
	cv::Mat swapped_img = swap_coordinate(complexI);	// swap the coordinate 
	cv::split(swapped_img.clone(), planes);				// Plane[0] = RE(DFT(I), planes[1] = Im(DFT(I))
	
	cv::Mat real_part = planes[0];
	cv::Mat img_part = planes[1];
	cv::Mat magI;
	cv::magnitude(real_part, img_part, magI);		// planes[0] = magnitude
	magI += cv::Scalar::all(1);

	cv::log(magI, magI);								//Perform log(1+magI).
	cv::normalize(magI, magI, 0, 1, cv::NORM_MINMAX);
	cv::Mat conv_8U = magI * 255;
	conv_8U.convertTo(conv_8U, CV_8U);
	cv::Mat dst;											//Threshold the image
	//cv::Mat hist = plotHistogram(conv_8U);					// Plot the histogram
	
	/* ------------------------------------------------------------------------------------ */
	/* --------------------------   Manual Option Key      -------------------------------- */
	if (manual_option_key) {
		std::cout << "Manual Option Key has been pressed" << std::endl;
		cv::Mat H = cv::Mat(planes[0].size(), CV_32F, cv::Scalar(1)); // For creating the mask
		const int r = 4; // radius

		// Mouse Control
		cv::namedWindow("Magnitude Image", 1);
		cv::setMouseCallback("Magnitude Image", mouse_handler, &magI);
		while (1) {
			cv::imshow("Magnitude Image", magI);
			if(cv::waitKey(10) > 0)
				break;
		}
		cv::destroyWindow("Magnitude Image");

		// Acess all the points & use those point for filtering (including Thresholding)
		for (unsigned int i = 0; i < input_points.size(); i++) {
			manual_filter(H, input_points[i], r);
		}

		cv::Mat final_plane_c1, final_plane_c2;
		cv::multiply(planes[0].clone(), H.clone(), final_plane_c1);
		cv::multiply(planes[1].clone(), H.clone(), final_plane_c2);

		cv::Mat final_result;
		cv::Mat final_plane[] = { final_plane_c1, final_plane_c2 };
		cv::merge(final_plane, 2, final_result);

		cv::Mat inverseTransform;
		final_result = swap_coordinate(final_result);
		cv::idft(final_result, inverseTransform);
		cv::Mat real_plane[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };
		cv::split(inverseTransform, real_plane);

		cv::Mat filtered_img = real_plane[0];
		cv::normalize(filtered_img, filtered_img, 0, 1, cv::NORM_MINMAX);
		filtered_img *= 255;
		filtered_img.convertTo(filtered_img, CV_8U);

		/* ------------------------------------------------------------------------------------ */
		/* ------------------------ Display & Save filtered Img-------------------------------- */
		cv::namedWindow("Filtered Image", cv::WINDOW_AUTOSIZE);
		cv::imshow("Filtered Image", filtered_img);
		cv::imwrite("Filtered_img.jpg", filtered_img);

		cv::waitKey();
	}
	else {
		/* ------------------------------------------------------------------------------------ */
		/* -------------------------- Filtering	& Find Contour -------------------------------- */
		cv::threshold(conv_8U.clone(), dst, 200.0, 255.0, cv::THRESH_BINARY );

		// Contour
		std::vector<std::vector<cv::Point>> contours;
		std::vector<cv::Vec4i> hierarchy;
		cv::findContours(dst, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

		//TODO: It might be better to use arc length than the finding the maximum area. 
		//		the reasons is because it can observe contour area with two parameter (min & Max arclength)
		// To way to solve this, use either arc length or the area
		//for ( size_t i = 0; i < contours.size(); i++) {
		//	std::cout << "The arc Length : " << cv::arcLength(contours[i], false) << "\n";
		//}

		// Find the maximum area
		//cv::Mat H = cv::Mat(planes[0].size(), CV_32F, cv::Scalar(1));
		double maxArea = 0.0;
		int savedContours = -1;
		cv::Mat contour_result(dst.size(), CV_32F, cv::Scalar(1));
		cv::Mat mask(dst.size(), CV_32F, cv::Scalar(1));
		for (unsigned int i = 0; i < contours.size(); i++) {
			double area = cv::contourArea(contours[i], false);

			if (area > maxArea) {
				maxArea = area;
				savedContours = i;
				contours.erase(contours.begin() + i);
			}
			
		}
		std::cout << savedContours << std::endl;

		// Draw Contour.
		cv::drawContours(mask, contours, -1, cv::Scalar(0), cv::FILLED);
		cv::drawContours(contour_result, contours, savedContours, cv::Scalar(0), cv::FILLED);

		mask.convertTo(mask, CV_32F);
		cv::normalize(mask, mask, 0, 1, cv::NORM_MINMAX);
		

		cv::Mat final_plane_c1, final_plane_c2;
		cv::multiply(planes[0].clone(), mask.clone(), final_plane_c1);
		cv::multiply(planes[1].clone(), mask.clone(), final_plane_c2);
		cv::Mat final_result;
		cv::Mat final_plane[] = { final_plane_c1, final_plane_c2 };
		cv::merge(final_plane, 2, final_result);

		/* ------------------------------------------------------------------------------------ */
		/* ------------------------ Inverse Descrete Transform -------------------------------- */
		cv::Mat inverseTransform;
		final_result = swap_coordinate(final_result);
		cv::idft(final_result, inverseTransform);
		cv::Mat real_plane[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };
		cv::split(inverseTransform, real_plane);

		cv::Mat filtered_img = real_plane[0];
		cv::normalize(filtered_img, filtered_img, 0, 1, cv::NORM_MINMAX);
		filtered_img *= 255;
		filtered_img.convertTo(filtered_img, CV_8U);

		/* ------------------------------------------------------------------------------------ */
		/* ------------------------ Display & Save filtered Img-------------------------------- */
		cv::namedWindow("Filtered Image", cv::WINDOW_AUTOSIZE);
		cv::imshow("Filtered Image", filtered_img);
		cv::imwrite("Filtered_img.jpg", filtered_img);
		cv::waitKey();
	}
	return 0;
}


/* ----------------------------------------------------------------------------------- */
/* ---------------------------------  Mouse Controls  -------------------------------- */
void mouse_handler(int event, int x, int y, int flags, void* userdata)
{
	if (event == cv::EVENT_LBUTTONDOWN) {
		cv::circle(*(cv::Mat*)userdata, cv::Point(x, y), 1, CV_RGB(255, 0, 0), 3);
		input_points.push_back(cv::Point(x, y));
	}
}
