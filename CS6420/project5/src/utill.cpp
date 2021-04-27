#include "utill.hpp"

void help(char** argv)
{
	std::cout << "\n This file demonstrate SLIC image segmentation algorithm. When one image"
		"image is given, the output image will consist of superpixel \n " << std::endl;

	//Usage Message example
	std::cout << "\n Usage example (one image): \n" << argv[0] << "korea.jpg -a=slic "
		"-size=10 -ruler=10.0 \n" << std::endl;
}