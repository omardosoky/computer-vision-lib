#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <chrono>

using namespace std::chrono;
using namespace cv;

struct CornerParameters {
	int x;
	int y;
	double r;
};

struct Harris {
	Mat R;
	std::vector<CornerParameters> points;
};

Mat ImagePadding(Mat Image, int Padding);
Mat SobelX(Mat src);
Mat SobelY(Mat src);
Mat Multiply(Mat src1, Mat src2);
Harris ApplyHarris(Mat Image, long long Threshold, int Padding);
void DrawCorners(Mat& Image, std::vector<CornerParameters> Points, int Padding);
Mat DetectCorners(Mat src, int Padding, long long Threshold, Harris& Destination);
