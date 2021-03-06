#include "utill.hpp"

void help(char** argv)
{
	std::cout << "\n This file demonstrate filtering frqeuncy domain algorithm. When one image"
		"is given, it will convert to frequency domain, then use a dft algorithm to filter out \n" << std::endl;

	std::cout << "\n Usage example : \n" << argv[0] << "input_image [output_image] " << std::endl;
}

cv::Mat swap_coordinate(const cv::Mat &img)
{
	cv::Mat tmp;
	int cx = img.cols / 2;
	int cy = img.rows / 2;

	cv::Mat q0(img, cv::Rect(0, 0, cx, cy));  // Top - Left (First quadrant)
	cv::Mat q1(img, cv::Rect(cx, 0, cx, cy)); // Top - Right (Second quadrant)
	cv::Mat q2(img, cv::Rect(0, cy, cx, cy)); // Bottom - Left (Third quadrant)
	cv::Mat q3(img, cv::Rect(cx, cy, cx, cy)); // Bottom - Right (Forth quadrant)
	
	// sqwap quadrants (Top-Left with Bottom Right) //
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	//----------------------------------------------//
	
	// swap qudrants (Top-right with Bottom Left    //
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
	//----------------------------------------------//

	return img;
}

cv::Mat plotHistogram(cv::Mat& img)
{
	const unsigned int NUMBER_OF_BINS = 256;
	const unsigned int WINDOW_HEIGHT = NUMBER_OF_BINS;
	const unsigned int WINDOW_WIDTH = NUMBER_OF_BINS;
	cv::Mat histogramImage = cv::Mat::zeros(WINDOW_HEIGHT, WINDOW_WIDTH, CV_8UC1);

	double hist[NUMBER_OF_BINS] = { 0 };

	// Let's compute the histogram.
	cv::MatIterator_<uchar> it, end;
	for (it = img.begin<uchar>(), end = img.end<uchar>();
		it != end;
		++it)
	{
		hist[*it]++;
	}

	// Let's find the max bin amount in the histogram, so that we can scale the rest of the histogram accordingly.
	double max = 0;
	for (unsigned int bin = 0; bin < NUMBER_OF_BINS; ++bin)
	{
		const double binValue = hist[bin];
		if (binValue > max)
			max = binValue;
	}

	// Let's plot the histogram.
	for (unsigned int bin = 0; bin < NUMBER_OF_BINS; ++bin)
	{
		const int binHeight = static_cast<int>(hist[bin] * WINDOW_HEIGHT / max);

		line(histogramImage, cv::Point(bin, WINDOW_HEIGHT - binHeight), cv::Point(bin, WINDOW_HEIGHT), cv::Scalar(255, 255, 255));
	}

	return histogramImage;
}

void manual_filter(cv::Mat& inputOutput, cv::Point center, int radius)
{
	cv::circle(inputOutput, center, radius, 0, -1, 8);
}

cv::Mat hist_helper(cv::Mat& img) {
	cv::Mat dst, hist;
	cv::normalize(img, dst, 0, 1, cv::NORM_MINMAX);
	dst *= 255;
	dst.convertTo(dst, CV_8U);
	hist = plotHistogram(dst);
	return hist;
}