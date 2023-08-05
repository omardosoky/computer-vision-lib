#include <opencv2/opencv.hpp>
using namespace cv;

constexpr auto BINARY = 0;
constexpr auto BINARY_INV = 1;
constexpr auto TRUNC = 2;
constexpr auto TOZERO = 3;
constexpr auto TOZERO_INV = 4;
constexpr auto Mean = 5;
constexpr auto Gaussian = 6;


void GlobalThreshold(Mat Src, Mat Des, int Threshold, int MaxValue, int Mode);
void LocalThreshold(Mat Src, Mat Des, int KernalSize, int Mode);
Mat Padding(Mat Image, int KernalSize);
void Convolve(Mat Src, Mat& Convolved, Mat kernel);

