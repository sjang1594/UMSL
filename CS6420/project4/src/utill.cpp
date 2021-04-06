#include "utill.hpp"

void help(char** argv)
{
	std::cout << "\n This file demonstrate image segmentation algorithm. When one image"
		"is given, it will segment the states depending on user input \n" << std::endl;

	std::cout << "\n Usage example : \n" << argv[0] << " input_image " << std::endl;
}
