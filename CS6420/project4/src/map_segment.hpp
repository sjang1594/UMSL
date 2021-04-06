// OpenCV Libraries

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>
#include <opencv2/core/utility.hpp>

// C++ Standard Libraries
#include <string>
#include <vector>

// Key for command line parser
const std::string keys =
{
	"{h help        |false| This is help message }"
	"{@input_image  |usa.png| United States Map }"
};


// Mousecall back
void mouse_handler(int, int, int, int, void* );
