#include "porter_duff.hpp"

// This functions is for help message 
void help(char** argv) {
	std::cout << "\n This program demonstatrates the porter duff operator in image\n"
		"Usage:\n" << argv[0] << "[image_name1] [image_name2] [mask1] [mask2] -- [mask1] & [mask2] can create a default mask \n" << std::endl;

	//Just to check the OpenCV version.
	std::cout << "The version of your OpenCV is " << CV_VERSION << "\n";
}

// This function is to create the mask 
cv::Mat make_mask(cv::Mat mask)
{
	//Check image dimension. 
	if (mask.depth() != 1) {
		cv::cvtColor(mask, mask, cv::COLOR_BGR2GRAY, 0);
		// Using the treshold to obtain the mask
		cv::threshold(mask, mask, 0, 255, cv::THRESH_BINARY);
	}
	else {
		// If the image is gray scale, create the mask, using threshold.
		// I don't think this is correct way. Maybe morphology would be better way to do it. 
		cv::threshold(mask, mask, 0, 255, cv::THRESH_BINARY); 
	}
	return mask;
}

// This function is to create the mask that contains the negated version of mask.
cv::Mat inverse(cv::Mat mask) {
	cv::Mat inversed_mask = cv::Mat::ones(mask.size(), mask.type()) * 255 - mask;
	return inversed_mask;
}

// This function is for clear operation.
cv::Mat clear(cv::Mat input)
{	
	cv::Mat img;
	input.copyTo(img);
	//Set to all zeros.
	img.setTo(cv::Scalar(0, 0, 0)); //This one should be editted.
	return img;
}

// This function is for copy operation. Similar to copyTo function. 
// Please Look at the reference : https://docs.opencv.org/master/d3/d63/classcv_1_1Mat.html
cv::Mat copy(cv::Mat input){	
	// Copy img
	cv::Mat copy_img;

	// Create Mask
	cv::Mat mask_img = make_mask(input);

	// Count non zero values.
	// Make a deep copy if there is mask.
	if (cv::countNonZero(mask_img) == 0) {
		std::cout << "Image is all black " << std::endl;
		input.copyTo(copy_img);
		return copy_img;
	}
	else {
		input.copyTo(copy_img, mask_img);
		return copy_img;
	}
}

// Over Operation 
cv::Mat over(cv::Mat i1, cv::Mat i2, cv::Mat m1, cv::Mat m2) {
	//This is like clear operation
	cv::Mat output_img1 = cv::Mat::zeros(i1.size(), i1.type());
	cv::Mat output_img2 = cv::Mat::zeros(i2.size(), i2.type());
	cv::Mat result_img = clear(i1);
	output_img1 = copy(i1);
	output_img2 = copy(i2);
	
	cv::Mat inverse_mask = inverse(m1);
	cv::Mat mask;
	//cv::bitwise_or(m1, m2, mask1);

	//Save it into result image
	cv::bitwise_and(output_img1, output_img1, result_img, m1);
	
	//Create a mask
	cv::bitwise_and(m2, inverse_mask, mask);
	cv::bitwise_and(output_img2, output_img2, result_img, mask);
	
	return result_img;
}

// Inside Operation. 
cv::Mat inside(cv::Mat i1, cv::Mat i2, cv::Mat m1, cv::Mat m2) {
	//This is like clear operation
	cv::Mat output_img = cv::Mat::zeros(i1.size(), i1.type());
	cv::Mat result_img = clear(i1);
	output_img = copy(i1);

	cv::Mat mask;
	// Create a mask
	cv::bitwise_and(m1, m2, mask);
	cv::bitwise_or(output_img, output_img, result_img, mask);

	return result_img;
}

// Outside operation
cv::Mat out(cv::Mat i1, cv::Mat i2, cv::Mat m1, cv::Mat m2) {
	//This is like clear operation
	cv::Mat output_img = cv::Mat::zeros(i1.size(), i1.type());
	cv::Mat result_img = clear(i1);
	output_img = copy(i1);

	// Create the mask that has fliped their pixels
	cv::Mat inversed_mask = inverse(m2);
	
	//bitwise_and 
	cv::Mat mask;
	cv::bitwise_and(m1, inversed_mask, mask);
	cv::bitwise_or(output_img, output_img, result_img, mask);

	return result_img;
}

// Atop operation :  the concatenation of "out" and "inside" Operation. 
//					1. first find the inversed mask of m1, then find the area then intersect with m2. 
//					2. After finding the outer mask of m2, then find outer_mask for m2.
//					3. Then loop through the images, put the color in the corresponding area.
cv::Mat atop(cv::Mat i1, cv::Mat i2, cv::Mat m1, cv::Mat m2) {
	//This is like clear operation
	cv::Mat output_img1 = cv::Mat::zeros(i1.size(), i1.type());
	cv::Mat output_img2 = cv::Mat::zeros(i2.size(), i2.type());
	cv::Mat result_output1 = clear(i1);
	cv::Mat result_output2 = clear(i2);
	cv::Mat final_output = clear(i1);
	output_img1 = copy(i1);  
	output_img2 = copy(i2);

	// Create the mask that has fliped their pixels
	cv::Mat inverse_mask = inverse(m1);
	cv::Mat outer_mask, inner_mask;
	cv::bitwise_and(inverse_mask, m2, outer_mask, m2);
	cv::bitwise_and(m1, m2, inner_mask, m2);

	cv::bitwise_and(output_img2, output_img2, result_output1, outer_mask);
	cv::bitwise_and(output_img1, output_img1, result_output2, inner_mask);
	cv::bitwise_or(result_output1, result_output2, final_output, m2);
	cv::waitKey();

	return final_output;
}

// XOR operation : 
//					1. first find the mask that intersect with m1 and negated m2, then loop through image 1 and fill in the image 1 color
//					2. find the mask that intersect with m2 and neagted m1, then loop through image 2 and fill in the image 2 color
//					3. Lastly, concatenate them.
// Note				: XOR operations are commutative if the size of both images are same.
cv::Mat XOR(cv::Mat i1, cv::Mat i2, cv::Mat m1, cv::Mat m2) {
	//This is like clear operation
	cv::Mat output_img1 = cv::Mat::zeros(i1.size(), i1.type());
	cv::Mat output_img2 = cv::Mat::zeros(i2.size(), i2.type());
	cv::Mat result_output1 = clear(i1);
	cv::Mat result_output2 = clear(i2);
	cv::Mat final_output = clear(i1);
	output_img1 = copy(i1);
	output_img2 = copy(i2);

	// Create a mask for xor operation. 
	cv::Mat inversed_mask1 = inverse(m1);
	cv::Mat inversed_mask2 = inverse(m2);

	// This method is naively constructed from description.
	// Bitwise_and & Bitwise_or
	cv::Mat inner_mask, outer_mask, result_mask;
	cv::bitwise_and(m1, inversed_mask2, inner_mask);
	cv::bitwise_and(inversed_mask1, m2, outer_mask);
	cv::bitwise_or(inner_mask, outer_mask, result_mask);

	cv::bitwise_and(output_img1, output_img1, result_output1, inner_mask);
	cv::bitwise_and(output_img2, output_img2, result_output2, outer_mask);
	cv::bitwise_or(result_output1, result_output2, final_output, result_mask);

	return final_output;
}