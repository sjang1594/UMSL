// OpenCV Libraries
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ximgproc/slic.hpp>

// C++ Standard Libraries
#include <iostream>
#include <string>
#include <map>

using namespace std;
using namespace cv::ximgproc;
using namespace cv;

// Key for CommandLine Parser
const string keys =
{
	"{h help        |false| This is help message}"
	"{a algorithm|1| SLIC(0), SLICO(1), MSLIC(2)}"
	"{s size  |10| Chooses an average superpixel size measured in pixels }"
	"{r ruler |10.0| Chooses the enforcement of superpixel smoothness }"
	"{n iteration |5| Number of iterations for SLIC Algorithm }"
	"{@input_image  |korea.jpg| The street view of korea [default] }"
};

void averageIntensity(Mat& segImage, Mat& labels, Mat input_image);