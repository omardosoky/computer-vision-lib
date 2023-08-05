#pragma once
#ifndef FILTER_H
#define FILTER_H

#include<opencv2/opencv.hpp>
#include<string>
#include <iterator>
#include <random>
#include <iostream>
using namespace cv;
using namespace std;

class Filtering {

private:
	//  padding image 
	Mat padding(Mat img, int k_width, int k_height);
	Mat d_kernel(int k_width, int k_height, string type);
	void Sortting(double window[]);
	double get_median(Mat win);
public:
	void convolution(Mat scr, Mat& filterd_image, int k_w, int k_h, string filterType);
	void median(Mat scr, Mat& filterd_image, int k_w, int k_h);

};



#endif
