#include "slic.hpp"
#include "utill.hpp"

int main(int argc, char** argv) {
	cv::CommandLineParser parser(argc, argv, keys);

	int min_element_size = 25;
	int algorithm = parser.get<int>("algorithm"); // Algorithm. SLIC(0), SLICO(1), MSLIC(2)
	int region_size = parser.get<int>("size"); // size
	double ruler = parser.get<double>("ruler"); // ruler
	int num_iteration = parser.get<int>("iteration"); // number of iteration

	//Load the image, template path, and warp file path
	const cv::String img_path = parser.get<cv::String>("@input_image"); //0

	// Either argc is one or help, show help message
	parser.about("Use this script to run image segmentation.");
	if (argc < 1 || parser.get<bool>("help")) {
		parser.printMessage();
		help(argv);
		return 0;
	}

	// Parser Check
	if (!parser.check()) {
		parser.printErrors();
		return -1;
	}

	// Read Image
	Mat input_image, mask, dst;
	input_image = cv::imread(img_path);

	// Error Checking - input
	if (input_image.empty())
	{
		std::cout << "Could not open image ..." << img_path << "\n";
		return -1;
	}
	Mat result = input_image.clone();

	double t = (double)getTickCount();

	Ptr<SuperpixelSLIC> slic = createSuperpixelSLIC(input_image, algorithm+SLIC, region_size, (float)ruler);
	slic->iterate(num_iteration);
	if (min_element_size > 0) {
		slic->enforceLabelConnectivity(min_element_size);
	}
	
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "SLIC" << (algorithm ? 'O' : ' ')
		<< " segmentation took " << (int)(t * 1000)
		<< " ms with " << slic->getNumberOfSuperpixels() << " superpixels" << endl;

	// Get the contours for displaying
	slic->getLabelContourMask(mask, true);
	result.setTo(Scalar(0, 0, 0), mask);

	cv::Mat labels;
	slic->getLabels(labels);
	cv::Mat final_result(input_image.size(), input_image.type());
	averageIntensity(final_result, labels, input_image);
	cv::imwrite(cv::format("korea_slic_%s_%s.jpg", argv[1], argv[2]), final_result);

	return 0;
}

void averageIntensity(Mat& segImage, Mat& labels, Mat input_image) {
	std::map<int, Scalar> clusters;
	for (int i = 0; i < labels.cols; i++) {
		for (int j = 0; j < labels.rows; j++) {
			int key = labels.at<int>(j, i);
			if (clusters.count(key)) {

				segImage.at<Vec3b>(j, i) = Vec3b(clusters[key][0], clusters[key][1], clusters[key][2]);
			}
			else {
				// Average Intensity
				cv::Mat tempMask = Mat::zeros(Size(segImage.cols, segImage.rows), CV_8UC1);
				for (int x = 0; x < labels.cols; x++) {
					for (int y = 0; y < labels.rows; y++) {
						if (labels.at<int>(y, x) == key) {
							tempMask.at<uchar>(y, x) = uchar(255);
						}
					}
				}

				Scalar color = mean(input_image, tempMask);
				clusters[key] = color;
			}

		}
	}
}