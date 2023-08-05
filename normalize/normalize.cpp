#include "normalize.hpp"
cv::Mat Normalize::NormalizeImage(cv::Mat img){
	//need to find the min and max pixel values first in the original image
	int min, max;
   min = img.at<uchar>(1, 1);
	max = min;
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			if (Image.at<uchar>(i, j) < min)
				min = img.at<uchar>(i, j);
			else if (img.at<uchar>(i, j) > max)
				max = img.at<uchar>(i, j);
		}
	}
	// we loop through the whole image and apply the normalize equation
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			int pixel = int(((img.at<uchar>(i, j) - min) / (float(max - min))) * 255);
			img.at<uchar>(i, j) = pixel;
		}
	}
	return img;
}
