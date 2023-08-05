#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include<filter.h>
using namespace cv;
using namespace std;

	//  padding image 
	Mat Filtering::padding(Mat img, int k_width, int k_height)
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
	//func to define kernels 
	Mat  Filtering::d_kernel(int k_width, int k_height, string type)
	{
		// gaussian kernel
		if (type == "gaussian")
		{
			//w(i,j) = k*(exp((i^2+j^2)/(2*sig))
			// k = 1 and sigma = 1
			int p_rows = (k_height - 1) / 2;
			int p_cols = (k_width - 1) / 2;
			Mat kernel(k_height, k_width, CV_64FC1);
			for (int i = -p_rows; i <= p_rows; i++)
			{
				for (int j = -p_cols; j <= p_cols; j++)
				{
					kernel.at<double>(i + p_rows, j + p_cols) = exp(-(i * i + j * j) / 2.0);
				}
			}
			kernel = kernel / sum(kernel);
			return kernel;
		}

		// mean kernel
		else if (type == "mean")
		{
			Mat kernel(k_height, k_width, CV_64FC1, Scalar(1.0 / (k_width * k_height)));
			return kernel;
		}
	}
	//func to sort values for median
	void  Filtering::Sortting(double window[])
	{
		int temp, i, j;
		for (i = 0; i < sizeof(window); i++) {
			temp = window[i];
			for (j = i - 1; j >= 0 && temp < window[j]; j--) {
				window[j + 1] = window[j];
			}
			window[j + 1] = temp;
		}
	}
	//func to get median value
	double  Filtering::get_median(Mat win) {
		std::vector<double> vec;
		vec.assign((double*)win.data, (double*)win.data + win.total() * win.channels());
		double* a = &vec[0];
		int m = sizeof(a) / 2;
		Sortting(a);
		double median = a[m];
		return median;
	}

	void  Filtering::convolution(Mat scr, Mat& filterd_image, int k_w, int k_h, string filterType)
	{
		Mat p_image, kernel;
		p_image = padding(scr, k_w, k_h);
		kernel = d_kernel(k_w, k_h, filterType);

		Mat output = Mat::zeros(scr.size(), CV_64FC1);

		for (int i = 0; i < scr.rows; i++)
		{
			for (int j = 0; j < scr.cols; j++)
			{
				output.at<double>(i, j) = sum(kernel.mul(p_image(Rect(j, i, k_w, k_h)))).val[0];
			}
		}

		output.convertTo(filterd_image, CV_8UC1);
	}

	//func to implement median filter
	void  Filtering::median(Mat scr, Mat& filterd_image, int k_w, int k_h)
	{
		Mat p_image, kernel;
		p_image = padding(scr, k_w, k_h);

		Mat output = Mat::zeros(scr.size(), CV_64FC1);

		for (int i = 0; i < scr.rows; i++)
		{
			for (int j = 0; j < scr.cols; j++)
			{
				output.at<double>(i, j) = get_median(p_image(Rect(j, i, k_w, k_h)));
			}
		}
		output.convertTo(filterd_image, CV_8UC1);
	}
