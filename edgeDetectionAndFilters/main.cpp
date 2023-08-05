#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <stdio.h>
#include <filter.h>

#define PI 3.14
using namespace cv;
using namespace std;

Mat padding(Mat img, int k_width, int k_height);
void convolve(Mat src, Mat& convolved, Mat kernel);
void gradTheta(Mat src, Mat dst, Mat xDir, Mat yDir, Mat& theta);
Mat sobelX(Mat src);
Mat sobelY(Mat src);
void sobel(Mat src, Mat& dst, Mat& theta);
Mat prewittX(Mat src);
Mat prewittY(Mat src);
void prewitt(Mat src, Mat& dst);
Mat robertY(Mat src);
Mat robertX(Mat src);
void robert(Mat src, Mat& dst);
void nonMaxSuppression(Mat intensity, Mat  theta, Mat& nonMaxSup);
void nonMaxSuppressionOrtho(Mat intensity, Mat  theta, Mat& nonMaxSup);
void doubleThreshold(Mat src, double lowerThresold, double higherThreshold, Mat& thresholded);
void trackByHysteresis(Mat src, Mat& tracked);
void cannyEdge(Mat src, Mat& cannyDetected);





int main() {


	Mat src, convolved, sobelImage, prewittImage, robertImage, theta, nonMaxSup, nonMaxSupOrth, thresholded, cannyDetected, tracked;

	string path = "C:\\Users\\EGYPT_LAPTOP\\Desktop\\Skeltonization\\Panorama20.jpg";
	src = imread(path, 0);
	imshow("src", src);


	// sobel(src, sobelImage, theta);

	// prewitt(src, prewittImage);
	 //robert( src, robertImage);

	 //nonMaxSuppression(sobelImage,  theta, nonMaxSup);
	 //imshow("nonMaxSup", nonMaxSup);
	// nonMaxSuppressionOrtho(sobelImage, theta, nonMaxSupOrth);



   //  doubleThreshold(nonMaxSup, 0.05, 0.09, thresholded);

	// trackByHysteresis(thresholded, tracked);
	// imshow("tracked", tracked);
	// imshow("thresh", thresholded);


	//imshow("ortho", convolved);
	//cannyEdge(src, cannyDetected);

	//imshow("sobelImage", sobelImage);
	//imshow("prewittImage", prewittImage);
	//imshow("robertImage", robertImage);
	//imshow("cannyDetected", cannyDetected);

	waitKey();
	return 0;
}




//  padding image 
Mat padding(Mat img, int k_width, int k_height)
{
	Mat scr;
	img.convertTo(scr, CV_64FC1);

	int p_rows, p_cols;
	p_rows = (k_height - 1) / 2;
	p_cols = (k_width - 1) / 2;
	// zero padding
	Mat p_image(Size(scr.cols + 2 * p_cols, scr.rows + 2 * p_rows), CV_64FC1, Scalar(0));
	scr.copyTo(p_image(Rect(p_cols, p_rows, scr.cols, scr.rows)));

	return p_image;
}
//convolution
void convolve(Mat src, Mat& convolved, Mat kernel) {
	Mat p_image;
	p_image = padding(src, 3, 3);


	Mat output = Mat::zeros(src.size(), CV_64FC1);

	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			output.at<double>(i, j) = sum(kernel.mul(p_image(Rect(j, i, 3, 3)))).val[0];
		}
	}

	output.convertTo(convolved, CV_8UC1);

};


void gradTheta(Mat src, Mat dst, Mat xDir, Mat yDir, Mat& theta) {


	theta = Mat::zeros(src.size(), CV_64FC1);
	for (int i = 0; i < dst.cols; i++) {
		for (int j = 0; j < dst.rows; j++) {
			// calculate sobel pixel value
			dst.at<uchar>(j, i) = sqrt(pow(xDir.at<uchar>(j, i), 2) + pow(yDir.at<uchar>(j, i), 2));

			//std::cout << "grad";
			// calculate orientation 
			if (yDir.at<uchar>(j, i) == 0) {
				theta.at<double>(j, i) = 90;

			}
			else {
				theta.at<double>(j, i) = atan((xDir.at<uchar>(j, i) / yDir.at<uchar>(j, i))) * 180 / PI;

			}


		}

	}

}
///////////////////////////////////////////////////////sobel///////////////////////////////////////////////////

// sobel x edge detection 
Mat sobelX(Mat src) {

	Mat_<double> sobelX(3, 3);

	sobelX << -1, -2, -1,
		0, 0, 0,
		1, 2, 1;



	Mat soblXResult;

	//convolve(src, sobelX, dst);
	convolve(src, soblXResult, sobelX);
	return soblXResult;
}

// sobel Y edge detection 
Mat sobelY(Mat src) {


	Mat_<double> sobelY(3, 3);

	sobelY << -1, 0, 1,
		-2, 0, 2,
		-1, 0, -1;

	Mat soblYResult;

	convolve(src, soblYResult, sobelY);
	return soblYResult;
}
// sobel edge detection 


void sobel(Mat src, Mat& dst, Mat& theta) {
	// apply gauessian blur first
	//apply sobel x
	Mat soblXResult, soblYResult;
	soblXResult = sobelX(src);


	//apply sobel y

	soblYResult = sobelY(src);
	dst = Mat::zeros(src.size(), CV_8UC1);

	gradTheta(src, dst, soblXResult, soblYResult, theta);


}
///////////////////////////////////////////////////////sobel end///////////////////////////////////////////////////



///////////////////////////////////////////////////rrewitt//////////////////////////////////////////////////////////
// prewitt x edge detection 
Mat prewittX(Mat src) {

	Mat_<double>prewittXfilter(3, 3);

	prewittXfilter << -1, -1, -1,
		0, 0, 0,
		1, 1, 1;



	Mat prewittXResult;

	convolve(src, prewittXResult, prewittXfilter);
	return prewittXResult;
}

// prewitt Y edge detection 
Mat prewittY(Mat src) {


	Mat_<double> prewittYfilter(3, 3);

	prewittYfilter << -1, 0, 1,
		-1, 0, 1,
		-1, 0, -1;

	Mat prewittYResult;

	convolve(src, prewittYResult, prewittYfilter);
	return prewittYResult;
}
// sobel edge detection 


void prewitt(Mat src, Mat& dst) {
	// apply gauessian blur first
	//apply sobel x
	Mat prewittXResult, prewittYResult;
	prewittXResult = prewittX(src);

	//apply sobel y

	prewittYResult = prewittY(src);


	dst = Mat::zeros(src.size(), CV_8UC1);
	Mat theta;
	gradTheta(src, dst, prewittXResult, prewittYResult, theta);



}







///////////////////////////////////////////////////prewitt end//////////////////////////////////////////////////////////





///////////////////////////////////////////////////////robert///////////////////////////////////////////////////

// robert x edge detection 
Mat robertX(Mat src) {

	Mat_<double> robertX(3, 3);

	robertX << 0, 0, 0,
		0, 1, 0,
		0, 0, -1;



	Mat soblXResult;

	//convolve(src, robertX, dst);
	convolve(src, soblXResult, robertX);
	return soblXResult;
}

// robert Y edge detection 
Mat robertY(Mat src) {


	Mat_<double> robertY(3, 3);

	robertY << 0, 0, 0,
		0, 0, 1,
		0, -1, 0;

	Mat robertYResult;

	convolve(src, robertYResult, robertY);
	return robertYResult;
}
// robert edge detection 


void robert(Mat src, Mat& dst) {
	// apply gauessian blur first
	//apply robert x
	Mat robertXResult, robertYResult;
	robertXResult = robertX(src);


	//apply robert y

	robertYResult = robertY(src);
	dst = Mat::zeros(src.size(), CV_8UC1);
	Mat theta;
	gradTheta(src, dst, robertXResult, robertYResult, theta);


}
///////////////////////////////////////////////////////robert end///////////////////////////////////////////////////

/////////////////////////////////////////////////////canny edge detection/////////////////////////////////////////////////////

void cannyEdge(Mat src, Mat& cannyDetected) {
	Mat intensity, theta, nonMaxSup, thresholded, tracked, gaw;
	// gauessian blur first
	Filtering f;
	f.convolution(src, gaw, 5, 5, "gaussian");
	// gradient and slope calculation

	cannyDetected = Mat::zeros(src.size(), CV_8UC1);
	sobel(src, intensity, theta);

	// non maximum suppression 
	nonMaxSuppression(intensity, theta, nonMaxSup);
	//double thresholding

	doubleThreshold(nonMaxSup, 0.05, 0.09, thresholded);
	//edge tracking by hysteresis
	trackByHysteresis(thresholded, cannyDetected);


}

void trackByHysteresis(Mat src, Mat& tracked) {
	tracked = Mat::zeros(src.size(), CV_8UC1);
	tracked = src;
	//100 weak 255 strong 
	for (int j = 1; j < tracked.cols - 1; j++) {
		for (int i = 1; i < tracked.rows - 1; i++) {
			if ((tracked.at<uchar>(i, j) == 100) && ((tracked.at<uchar>(i - 1, j - 1) == 255) || (tracked.at<uchar>(i + 1, j - 1) == 255)
				|| (tracked.at<uchar>(i - 1, j) == 255) || (tracked.at<uchar>(i + 1, j) == 255)
				|| (tracked.at<uchar>(i - 1, j + 1) == 255) || (tracked.at<uchar>(i + 1, j + 1) == 255)
				|| (tracked.at<uchar>(i, j - 1) == 255) || (tracked.at<uchar>(i, j + 1) == 255)))
			{
				tracked.at<uchar>(i, j) = 255;
			}
			else if ((tracked.at<uchar>(i, j) == 100)) {
				tracked.at<uchar>(i, j) = 0;
			}
		}
	}

}

void nonMaxSuppression(Mat intensity, Mat  theta, Mat& nonMaxSup) {
	// check what is the maximum on the same directionand delete any pixel else
	// pixle's right and left
	uchar right = 255;
	uchar left = 255;

	nonMaxSup = Mat::zeros(intensity.size(), CV_8UC1);
	//nonMaxSup = intensity;
	for (int i = 1; i < intensity.cols - 1; i++) {
		for (int j = 1; j < intensity.rows - 1; j++) {


			// angle 0
			if ((theta.at<double>(j, i) >= 0 && theta.at<double>(j, i) < 22.5) ||
				(theta.at<double>(j, i) >= 157.5 && theta.at<double>(j, i) <= 180)) {
				right = intensity.at<uchar>(j, i + 1);
				left = intensity.at<uchar>(j, i - 1);

			}

			// angle 45
			else if ((theta.at<double>(j, i) >= 22.5 && theta.at<double>(j, i) < 67.5)) {
				right = intensity.at<uchar>(j + 1, i - 1);
				left = intensity.at<uchar>(j - 1, i + 1);

			}
			// angle 90
			else if ((theta.at<double>(j, i) >= 67.5 && theta.at<double>(j, i) < 112.5)) {
				right = intensity.at<uchar>(j + 1, i);
				left = intensity.at<uchar>(j - 1, i);
			}
			// angle 135
			else if ((theta.at<double>(j, i) >= 112.5 && theta.at<double>(j, i) < 157.5)) {
				right = intensity.at<uchar>(j - 1, i - 1);
				left = intensity.at<uchar>(j + 1, i + 1);


			}

			if ((right >= intensity.at<uchar>(j, i)) || (left >= intensity.at<uchar>(j, i))) {
				nonMaxSup.at<uchar>(j, i) = 0;

			}
			else {
				nonMaxSup.at<uchar>(j, i) = intensity.at<uchar>(j, i);

			}

		}
	}

}


void nonMaxSuppressionOrtho(Mat intensity, Mat  theta, Mat& nonMaxSup) {
	// check what is the maximum on the same directionand delete any pixel else
	// pixle's right and left
	uchar right = 255;
	uchar left = 255;

	nonMaxSup = Mat::zeros(intensity.size(), CV_8UC1);
	//nonMaxSup = intensity;
	for (int i = 1; i < intensity.cols - 1; i++) {
		for (int j = 1; j < intensity.rows - 1; j++) {


			// angle 0
			if ((theta.at<double>(j, i) >= 0 && theta.at<double>(j, i) < 22.5) ||
				(theta.at<double>(j, i) >= 157.5 && theta.at<double>(j, i) <= 180)) {
				right = intensity.at<uchar>(j + 1, i);
				left = intensity.at<uchar>(j - 1, i);

			}

			// angle 45
			else if ((theta.at<double>(j, i) >= 22.5 && theta.at<double>(j, i) < 67.5)) {

				right = intensity.at<uchar>(j - 1, i - 1);
				left = intensity.at<uchar>(j + 1, i + 1);



			}
			// angle 90
			else if ((theta.at<double>(j, i) >= 67.5 && theta.at<double>(j, i) < 112.5)) {
				right = intensity.at<uchar>(j, i + 1);
				left = intensity.at<uchar>(j, i - 1);
			}
			// angle 135
			else if ((theta.at<double>(j, i) >= 112.5 && theta.at<double>(j, i) < 157.5)) {
				right = intensity.at<uchar>(j + 1, i - 1);
				left = intensity.at<uchar>(j - 1, i + 1);


			}

			if ((right >= intensity.at<uchar>(j, i)) || (left >= intensity.at<uchar>(j, i))) {
				nonMaxSup.at<uchar>(j, i) = 0;

			}
			else {
				nonMaxSup.at<uchar>(j, i) = intensity.at<uchar>(j, i);

			}

		}
	}

}



void doubleThreshold(Mat src, double lowerThresold, double higherThreshold, Mat& thresholded) {
	// 0.05 , 0.09
	double imgMax = 0;

	thresholded = src;

	//theta = Mat::zeros(src.size(), CV_64FC1);
	for (int j = 0; j < src.cols; j++) {
		for (int i = 0; i < src.rows; i++) {
			// calculate max pixel value
			if (src.at<uchar>(i, j) > imgMax) { imgMax = src.at<uchar>(i, j); }

		}
	}

	//mark upper thresholds as strong.. mark middle as weak .. below threshold is set to 0
	double high = imgMax * higherThreshold;
	std::cout << high << endl;
	double low = high * lowerThresold;
	std::cout << low;
	for (int j = 0; j < thresholded.cols; j++) {
		for (int i = 0; i < thresholded.rows; i++) {
			// calculate max pixel value
			if (thresholded.at<uchar>(i, j) >= high) {
				thresholded.at<uchar>(i, j) = 255;

			}
			else if (thresholded.at<uchar>(i, j) < low) {
				thresholded.at<uchar>(i, j) = 0;
			}
			else if ((thresholded.at<uchar>(i, j) >= low) && (thresholded.at<uchar>(i, j) < high)) {
				thresholded.at<uchar>(i, j) = 100;
			}
		}
	}

}