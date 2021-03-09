#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>
#include <opencv2/core/utility.hpp>

// CommandLineparser Keys
const std::string keys =
{
	"{h help        |false| This is help message }"
	"{M | | Perform manual frequency filtering }"
	"{@input_image  |pnois2.jpg| Name of file containing image with periodic noise }"
	"{output_image  |output_image.jpg| Name of file to save the image; select some default name }"
};

// Vector to store all input point
static std::vector<cv::Point> input_points;

// Mousecall back
void mouse_handler(int event, int x, int y, int flags, void* userdata);
