/* Author		 : Seungho Jang
*  Class		 : CS6420
*  Reference	 : https://docs.opencv.org/master/dd/d93/samples_2cpp_2image_alignment_8cpp-example.html#a39
*/

#include "register.hpp"
#include "utill.hpp"

// CommandLineparser Keys
std::string keys =
"{h help         |    false			| This is help message }"
"{M              |					| Perform manual registration }"
"{e epsilon      |    0.0001		| ECC's convergence epsilon }"
"{m motion_type  |    affine		| type of motion : translation, euclidean, affine, homography}"
"{o output_warp  |  out_warp.ecc    | warped image}"
"{@image_file    |  home_day.jpg    | input image }"
"{@template_file |  home_night.jpg  | template image for alignment}"
"{@warp_file     |		            | Input file containing warp matrix}";


int main(int argc, char** argv) {

	cv::CommandLineParser parser(argc, argv, keys);

	//Load the image path & template path
	const cv::String img_path = parser.get<cv::String>("@image_file"); //0
	const cv::String template_path = parser.get<cv::String>("@template_file"); //1
	const cv::String warp_file_path = parser.get<cv::String>("@warp_file"); //2

	// Either argc is one or help, show help message
	parser.about("Use this script to run image registeration.");
	if (argc < 1 || parser.get<bool>("help")){
		parser.printMessage();
		help(argv);
		return 0;
	}

	double ep = parser.get<double>("e"); // epsilon
	std::string motion_type = parser.get<std::string>("m"); // motion type or warp type
	bool manual_option_key = parser.has("M"); // Manual option key

	//Parser Check
	//if (!parser.check()) {
	//	parser.printErrors();
	//	return -1;
	//}

	// Variables 
	cv::Mat src, copy_src, template_src, template_copy_src, image_aligned;

	// Warp matrix
	cv::Mat warp_matrix;

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
	cv::imshow("after equaliztion", copy_src);
	cv::imshow("Hist : Copy_src", getGrayHistImage(calcGrayHist(copy_src)));
	
	// Apply historgram equalization to enhance the edges.
	cv::equalizeHist(template_src, template_copy_src);
	//cv::waitKey();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------- Motion Type & Warp Type ----------------------------- */
	// Check the motion_type
	if (!(motion_type == "translation" || motion_type == "euclidean"
		|| motion_type == "affine" || motion_type == "homography")) {
		std::cerr << "Invalid motion transformation" << std::endl;
		return -1;
	}
	// Convert warp type from string to built-in enumerated type
	int mode_temp;
	if (motion_type == "translation")
		mode_temp = cv::MOTION_TRANSLATION;
	else if (motion_type == "euclidean")
		mode_temp = cv::MOTION_EUCLIDEAN;
	else if (motion_type == "affine")
		mode_temp = cv::MOTION_AFFINE;
	else
		mode_temp = cv::MOTION_HOMOGRAPHY;

	/* ----------------------------------------------------------------------------------- */
	//Manual registration
	if (manual_option_key) {
		std::cout << "Manul Option Key has been pressed " << std::endl;
		// do something with manual option key --> use mouse control. callbackfunction ?
		// or just take the point as cin.
	}
	else {
		//Automatic registration
		//do something
	}

	/* ----------------------------------------------------------------------------------- */

}