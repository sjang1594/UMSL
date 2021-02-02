/* Author : Seungho Jang
*  Class  : CS6420
*  Reference : http://ssp.impulsetrain.com/porterduff.html
*/

#include "porter_duff.hpp"

// Key for commandline parser
const char* keys =
"{help h | | Print help message }"
"{@image1 | <none> | input image1 }"
"{@image2 | <none> | input image2 }"
"{mask1  | | mask 1       }"
"{mask2  | | mask 2       }";

int main(int argc, char** argv) {
	cv::Mat img1 = cv::Mat::zeros(sz, CV_8UC3);
	cv::Mat img2 = cv::Mat::zeros(sz, CV_8UC3);
	
	//Command Line Argument 
	cv::CommandLineParser parser(argc, argv, keys);

	// Read help
	if (parser.has("help")) {
		//parser.printMessage();
		help(argv);
		return 0;
	}
	
	// Read Image.
	cv::Mat input_img1, input_img2;
	cv::String input_path1 = parser.get<cv::String>(0);
	cv::String input_path2 = parser.get<cv::String>(1);

	input_img1 = cv::imread(input_path1);
	input_img2 = cv::imread(input_path2);

	cv::imshow("image1", input_img1);
	cv::imshow("image2", input_img2);
	cv::waitKey();

	// If both images are empty, then make a default
	if (input_img1.empty() && input_img2.empty()) {
		//input_img1 = img1;
		//input_img2 = img2;
		/*std::cout << "Creating Default Picture because the srcs are empty images" << std::endl;
		std::cout << " Image 1. Blue Circle" << std::endl;
		std::cout << " IMage 2. Green Cross" << std::endl;*/
		// Draw difault pictures.

		return 0;
	}

	// Create Circle : First image should be a circle in the center with radius 150 in blue color
	cv::circle(img1, center, radius, cv::Scalar(255, 0, 0), cv::FILLED);

	//   Create Cross 
	cv::rectangle(img2, rect1, cv::Scalar(0, 255, 0), cv::FILLED);
	cv::rectangle(img2, rect2, cv::Scalar(0, 255, 0), cv::FILLED);

	//Check input image
	cv::imshow("img1", img1);
	cv::imshow("img2", img2);
	cv::waitKey();
	
	// Porter - Duff Operation.
	cv::Mat mask1, mask2;
	//cv::Mat mask2; = make_mask(img2);

	// Processing the input masks
	bool hasMask1 = parser.has("mask1");
	bool hasMask2 = parser.has("mask2");
	cv::String mask1_path = parser.get<cv::String>("mask1");
	cv::String mask2_path = parser.get<cv::String>("mask2");
	if (hasMask1) {
		mask1 = cv::imread(mask1_path);
		mask1 = make_mask(mask1);
	}
	else {
		mask1 = make_mask(img1);
	}

	if (hasMask2) {
		mask2 = cv::imread(mask2_path);
		mask2 = make_mask(mask2);
	}
	else {
		mask2 = make_mask(img2);
	}

	// Porter - Duff Operation.

	// Over Operation
	cv::Mat over_img1 = over(img1, img2, mask1, mask2);
	cv::imshow("img1 over img2", over_img1);
	cv::Mat over_img2 = over(img2, img1, mask2, mask1);
	cv::imshow("img2 over img1", over_img2);
	cv::waitKey();
	
	// inside Operation
	cv::Mat inside_img1 = inside(img1, img2, mask1, mask2);
	cv::imshow("img1 inside of img2", inside_img1);
	cv::Mat inside_img2 = inside(img2, img1, mask2, mask1);
	cv::imshow("img2 inside of img2", inside_img2);
	cv::waitKey();

	// Out Operation
	cv::Mat outside_img1 = out(img1, img2, mask1, mask2);
	cv::imshow("img1 outside of img2", outside_img1);
	cv::Mat outside_img2 = out(img2, img1, mask2, mask1);
	cv::imshow("img2 outside of img1", outside_img2);
	cv::waitKey();

	// Atop Operation
	cv::Mat atop_img1 = atop(img1, img2, mask1, mask2);
	cv::imshow("img1 topof img2 ", atop_img1);
	cv::Mat atop_img2 = atop(img2, img1, mask2, mask1);
	cv::imshow("img2 topof img1 ", atop_img2);
	cv::waitKey();

	// XOR Operation
	cv::Mat xor_img1 = XOR(img1, img2, mask1, mask2);
	cv::imshow("img1 xor img2", xor_img1);
	cv::Mat xor_img2 = XOR(img2, img1, mask2, mask1);
	cv::imshow("im2 xor img1", xor_img2);
	cv::waitKey();

	// Extra
	cv::Mat mask_img1 = cv::Mat::zeros(input_img1.size(), CV_8UC3);
	cv::Mat final_mask1 = cv::Mat::zeros(input_img1.size(), CV_8UC1);
	cv::Mat mask_bernie = make_mask(input_img1);


	cv::imshow("Bernie Mask", mask_bernie);
	cv::waitKey();
}

