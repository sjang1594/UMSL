#pragma once
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
	"{h help         |false| This is help message }"
	"{M manual		 |<none>| Perform manual registration }"
	"{e epsilon      |0.0001| ECC's convergence epsilon }"
	"{m motion_type  |affine | type of motion (translation, euclidean, affine, homography)}"
	"{o output_warp  |out_warp.ecc| Output warp matrix filename }"
	"{w warp_img_file|warped_ecc.jpg| Warped Image }"
	"{@image_file    |home_day.jpg| input image }"
	"{@template_file |home_night.jpg| template image for alignment}"
	"{@warp_file     |<none>| Input file containing warp matrix}"
};

// Specificy the number of iterations
const int niters = 50;

// Traking points
static std::vector<cv::Point> input_points;
static std::vector<cv::Point> template_points;

// Callback function - mouse control.
void CallBackFunc_1(int event, int x, int y, int flags, void* userdata);
void CallBackFunc_2(int event, int x, int y, int flags, void* userdata);