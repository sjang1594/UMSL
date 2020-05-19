#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/core_c.h>

using namespace std;
using namespace cv;

Mat get_histo_Image(Mat input);

int main(int argc, char**argv){
    Mat img; Mat gray_img;
    img = imread(argv[1], 1);

    if(img.empty()){
        cerr<< "Image Load Failed!\n";
        return -1;
    }

    //Convert it to gray if it's color img
    if(img.channels() != -1)
        cvtColor(img, gray_img, COLOR_RGB2GRAY);
    else
        gray_img = img;

    //Show the gray img
    imshow("gray_img" , gray_img);
    Mat histImage = get_histo_Image(gray_img);

    //For Equalization
    Mat grayImg_stretch;
    normalize(gray_img, grayImg_stretch, 0, 255, CV_MINMAX);
    Mat histo_GrayImg_stretch = get_histo_Image(grayImg_stretch);
    imshow("Equalization", grayImg_stretch);

    namedWindow("calcHist", WINDOW_AUTOSIZE);
    imshow("calcHist", histImage);
    namedWindow("histGray_img_stretch", WINDOW_AUTOSIZE);
    imshow("histGray_img_stretch", histo_GrayImg_stretch);
    waitKey(0);

    return 0;
}

Mat get_histo_Image(Mat input){
    //Size of X axis of histogram.
    int hbins = 255;

    //Index of Channel
    int channels[] = { 0 };
    int histSize[] = { hbins };
    float hranges[] = {0, 255};
    const float * ranges[] = { hranges };

    MatND Hist;
    MatND nomHist;
    calcHist(&input, 1, channels, Mat(), Hist, 1, histSize, ranges,
             true,
             false);

    //normalize
    normalize(Hist, Hist, 0, 255, CV_MINMAX);

    //Create 500 x 255 histogram.
    int hist_w = 500; int hist_h = 255;
    //How much space one histogram can occupy
    int ratio = cvRound((double)hist_w / hbins);
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

    int x1, y1;
    int x2, y2;
    for(int i = 1; i < hbins; i++){
        x1 = ratio*(i-1);
        y1 = hist_h - cvRound(Hist.at<float>(i-1));

        x2 = ratio*(i);
        y2 = hist_h - cvRound(Hist.at<float>(i));

        //For the histogram.
        line(histImage, Point(x1, y1), Point(x2, y2),
             Scalar(255, 255, 255), 2, 8, 0);
    }
    return histImage;
}
