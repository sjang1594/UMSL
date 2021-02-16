/* Author		 : Seungho Jang
*  Class		 : CS6420
*  Reference	 : https://docs.opencv.org/master/dd/d93/samples_2cpp_2image_alignment_8cpp-example.html#a39
*/

#include "register.hpp"
#include "utill.hpp"


int main(int argc, char** argv) {

	cv::CommandLineParser parser(argc, argv, keys);
	
	double ep = parser.get<double>("e"); // epsilon
	std::string motion_type = parser.get<std::string>("m"); // motion type or warp type
	std::string final_warp = parser.get<std::string>("o"); // final output 
	std::string warp_img_file = parser.get<std::string>("w"); // warp image file 
	bool manual_option_key = parser.has("M"); // Manual option key

	//Load the image, template path, and warp file path
	const cv::String img_path = parser.get<cv::String>("@image_file"); //0
	const cv::String template_path = parser.get<cv::String>("@template_file"); //1
	const cv::String warp_file_path = parser.get<cv::String>("@warp_file"); //2

	// Either argc is one or help, show help message
	parser.about("Use this script to run image registeration.");
	if (argc < 1 || parser.get<bool>("help")) {
		parser.printMessage();
		help(argv);
		return 0;
	}

	//Parser Check
	//if (!parser.check()) {
	//	parser.printErrors();
	//	return -1;
	//}

	// Variables 
	cv::Mat src, copy_src, template_src, template_copy_src;

	/* ----------------------------------------------------------------------------------- */
	/* --------------------------------- Input Processing -------------------------------- */
	// Read an image with color and the template image as grayscale
	src = cv::imread(cv::samples::findFile(img_path), cv::IMREAD_COLOR);
	template_src = cv::imread(cv::samples::findFile(template_path), cv::IMREAD_GRAYSCALE);

	// Error Checking inputs
	if (src.empty() || template_src.empty()) {
		std::cout << "Error Occured while opening input files \n" << std::endl;
		// print out the help message

		return -1;
	}
	// Copy it into another image as gray scale
	cvtColor(src, copy_src, cv::COLOR_BGR2GRAY);

	// Check if the image has been eqaulized.
	//cv::imshow("Hist : before equalized", getGrayHistImage(calcGrayHist(copy_src)));

	// Apply histogram equalization to enhance the edges
	cv::equalizeHist(copy_src, copy_src);
	//cv::imshow("after equaliztion", copy_src);
	//cv::imshow("Hist : Copy_src", getGrayHistImage(calcGrayHist(copy_src)));

	// Apply historgram equalization to enhance the edges.
	cv::equalizeHist(template_src, template_copy_src);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------- Motion Type & Warp Type ----------------------------- */

	// Check the motion_type
	/*if (!(motion_type == "translation" || motion_type == "euclidean"
		|| motion_type == "affine" || motion_type == "homography"))
	{
		std::cerr << "Invalid motion transformation" << std::endl;
		return -1;
	}*/

	// Convert warp type from string to built-in enumerated type
	int warp_mode = get_warpMode(motion_type);

	// Warp matrix 
	cv::Mat warp_mat;

	// Specificy the number of iterations
	const int niters = 50;

	//Check the input image size
	std::cout << "Image Size : " << copy_src.size() << std::endl;
	//Check the template image size
	std::cout << "Template image Size : " << template_copy_src.size() << std::endl;


	/* ----------------------------------------------------------------------------------- */
	/* --------------------			Registration				-------------------------- */
	// Manual registration
	// - Take the user inputs for points on image. (How many points --> three points)
	// - Create the affine warp matrix for image.- 
	if (manual_option_key) {
		std::cout << "Manul Option Key has been pressed " << std::endl;
		std::cout << "(Source) Input three pairs of points within this size : "
			<< copy_src.size() << std::endl;
		
		//Mouse Control
		std::cout << "(Source) Input three pairs of points within this size : "
			<< template_copy_src.size() << std::endl;
		cv::namedWindow("src image", 1);
		cv::setMouseCallback("src image", CallBackFunc_1, &src);
		while (1){
			cv::imshow("src image", src);
			if (cv::waitKey(10) > 0 || input_points.size() == 3)
				break;

		}
		cv::destroyWindow("src image");

		std::cout << "(Template) Input three pairs of points within this size : "
			<< template_copy_src.size() << std::endl;
		cv::namedWindow("template image", 1);
		cv::setMouseCallback("template image", CallBackFunc_2, &template_src);
		while (1) {
			cv::imshow("template image", template_src);
			if (cv::waitKey(10) > 0 || template_points.size() == 3)
				break;

		}
		cv::destroyWindow("template image");
		

		// Copy over the vector vals into array.
		cv::Point2f input_pt[3];
		cv::Point2f template_pt[3];
		for (int i = 0; i < input_points.size(); i++) {
			input_pt[i] = input_points[i];
		}

		for (int i = 0; i < template_points.size(); i++) {
			template_pt[i] = template_points[i];
		}


		// Calculate the Affine Transform
		warp_mat = cv::getAffineTransform(input_pt, template_pt);
		std::cout << warp_mat << std::endl;
		
		// printing & saving warp image
		cv::Mat warp_dst = cv::Mat::zeros(src.rows, src.cols, src.type());
		cv::warpAffine(src, warp_dst, warp_mat, warp_dst.size());
		cv::imshow("Warp", warp_dst);
		cv::imwrite("warp_image.jpg", warp_dst);
		cv::waitKey();

	}
	else { // Automatic registration
		// Create the identity matrix depending on warp_mode
		/*
			cv::MOTION_TRANSLATION = 0,
			cv::MOTION_EUCLIDEAN = 1,
			cv::MOTION_AFFINE = 2,
			cv::MOTION_HOMOGRAPHY = 3
		*/

		// If warp_mode is 3 (Homography), then create (3, 3) matrix. 
		if (warp_mode == 3)
			warp_mat = cv::Mat::eye(3, 3, CV_32F);
		else
			warp_mat = cv::Mat::eye(2, 3, CV_32F);

		// If warp file doesn't exist, give an error msg. Otherwise, read warp matrix.
		if (warp_file_path != "") {
			int readflag = readWarp(warp_file_path, warp_mat, warp_mode);
			if ((!readflag) || warp_mat.empty()) {
				std::cerr << "Error Occured opening warp file " << std::endl << std::flush;
				return -1;
			}
		
		}
		else {
			std::cout << "\n ->Performance Warning: Identity warp ideally assumes images of "
				"similar size. If the deformation is strong, the identity warp may not "
				"be a good initialization. \n";
		}

		if (warp_mode != cv::MOTION_HOMOGRAPHY)
			warp_mat.rows = 2;

		//timing
		const double tic_init = (double)cv::getTickCount();
		//double cc = cv::findTransformECC(template_copy_src)

		const double toc_final = (double)cv::getTickCount();
		const double total_time = (toc_final - tic_init) / (cv::getTickFrequency());

		//saveWarp(final_warp, warp_mat, warp_mode);
	}
}

/* ----------------------------------------------------------------------------------- */
/* ---------------------------------  Mouse Control	 -------------------------------- */
void CallBackFunc_1(int event, int x, int y, int flags, void* userdata)
{
	if (event == cv::EVENT_LBUTTONDOWN) {
		std::cout << " Press three points with left click" << std::endl;
		printf("lLBUTTONDOWN down %d, %d \n", x, y);
		cv::circle(*(cv::Mat*)userdata, cv::Point2f((float)x, (float)y), 2, CV_RGB(255, 0, 0), 3);

		input_points.push_back(cv::Point2f((float)x, (float)y));

		// You might be able to push some x and y coordinates to vector.
	}
	//print_array_info(input_points);
}

void CallBackFunc_2(int event, int x, int y, int flags, void* userdata)
{
	if (event == cv::EVENT_LBUTTONDOWN) {
		std::cout << " Press three points with left click" << std::endl;
		printf("lLBUTTONDOWN down %d, %d \n", x, y);
		cv::circle(*(cv::Mat*)userdata, cv::Point2f((float)x, (float)y), 2, CV_RGB(255, 255, 255), 3);

		template_points.push_back(cv::Point2f((float)x, (float)y));
		// You might be able to push some x and y coordinates to vector.
	}
	//print_array_info(template_points);
}