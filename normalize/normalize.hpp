#ifndef NORM_H
#define NORM_H
#include <opencv2/opencv.hpp>
using namespace cv;
class Normalize{
	public :
		Normalize();
		cv::Mat NormalizeImage(cv::Mat img);
}
#endif
