#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;


class Filtering {
private:
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
	//func to define kernels 
	Mat d_kernel(int k_width, int k_height, string type)
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
	void Sortting(double window[])
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
	double get_median(Mat win) {
		std::vector<double> vec;
		vec.assign((double*)win.data, (double*)win.data + win.total() * win.channels());
		double* a = &vec[0];
		int m = sizeof(a) / 2;
		Sortting(a);
		double median = a[m];
		return median;
	}
	// func to centerize image in the freq domain



public:
	// func to implement convolution
	void convolution(Mat scr, Mat& filterd_image, int k_w, int k_h, string filterType)
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
	void median(Mat scr, Mat& filterd_image, int k_w, int k_h)
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


};

class freq_filtering {

private:

	Mat shift(Mat& input_img)
	{
		Mat shifted;
		shifted = input_img.clone();
		int cx = shifted.cols / 2;
		int cy = shifted.rows / 2;
		Mat q1(shifted, Rect(0, 0, cx, cy));
		Mat q2(shifted, Rect(cx, 0, cx, cy));
		Mat q3(shifted, Rect(0, cy, cx, cy));
		Mat q4(shifted, Rect(cx, cy, cx, cy));

		Mat temp;
		q1.copyTo(temp);
		q4.copyTo(q1);
		temp.copyTo(q4);
		q2.copyTo(temp);
		q3.copyTo(q2);
		temp.copyTo(q3);
		return shifted;
	}

	//func to get spectrum diagram from complex img
	void get_mag(Mat& plane1, Mat& plane2, Mat& dst) {

		magnitude(plane1, plane2, dst);
		dst += Scalar(1);   // add 1 to all pixels to prevent log0
		log(dst, dst);
		normalize(dst, dst, 0, 1, NORM_MINMAX); //normalization
		dst = shift(dst);
	}
	// func to get complex img and img
	Mat DFT(Mat& scr, Mat& dst)
	{
		// define mat of two mat, one for real other for complex values
		Mat planes[] = { scr, Mat::zeros(scr.size(), CV_32F) };
		Mat comp_Img;
		merge(planes, 2, comp_Img);

		dft(comp_Img, comp_Img);
		split(comp_Img, planes);

		get_mag(planes[0], planes[1], dst);

		return comp_Img;
	}

	// func to get mask for  fitering
	Mat Mask(Mat& scr, String type, float D0)
	{
		Mat H(scr.size(), CV_32F, Scalar(1));
		float D = 0;
		if (type == "lowpass")
		{
			for (int u = 0; u < H.rows; u++)
			{
				for (int v = 0; v < H.cols; v++)
				{
					D = sqrt((u - scr.rows / 2) * (u - scr.rows / 2) + (v - scr.cols / 2) * (v - scr.cols / 2));
					if (D > D0)
					{
						H.at<float>(u, v) = 0;
					}
				}
			}
			return H;
		}
		if (type == "highpass")
		{
			for (int u = 0; u < H.rows; u++)
			{
				for (int v = 0; v < H.cols; v++)
				{
					D = sqrt((u - scr.rows / 2) * (u - scr.rows / 2) + (v - scr.cols / 2) * (v - scr.cols / 2));
					if (D <= D0)
					{
						H.at<float>(u, v) = 0;
					}
				}
			}
			return H;
		}
	}

public:

	// func to apply filtering on freq domain and get filtered and masked images
	Mat freq_filter(Mat& scr, Mat& freq, Mat& masked, String type, float D0)
	{
		scr.convertTo(scr, CV_32F);

		// DFT
		Mat DFT_image;
		DFT_image = DFT(scr, freq);

		// get mask 
		Mat M;
		M = Mask(scr, type, D0);

		Mat shifted = shift(M);
		Mat planesH[] = { Mat_<float>(shifted.clone()), Mat_<float>(shifted.clone()) };

		Mat planes_dft[] = { DFT_image, Mat::zeros(DFT_image.size(), CV_32F) };
		split(DFT_image, planes_dft);

		Mat planes_out[] = { Mat::zeros(scr.size(), CV_32F), Mat::zeros(scr.size(), CV_32F) };
		planes_out[0] = planesH[0].mul(planes_dft[0]);
		planes_out[1] = planesH[1].mul(planes_dft[1]);


		get_mag(planes_out[0], planes_out[1], masked);


		Mat filterd;
		merge(planes_out, 2, filterd);

		// IDFT
		Mat dst;
		dft(filterd, dst, DFT_INVERSE | DFT_REAL_OUTPUT);

		normalize(dst, dst, 0, 1, NORM_MINMAX);
		return dst;
	}

};
/*
int main() {
	Mat img, Magnitude_image, high_mask, low_mask, high, low;
	img = imread("E:\\forth year\\2nd sim\\cv\\task1\\assignment-1-cv-2022-sbe-404-team_12-main\\images\\1.png", 0);

	namedWindow("img", WINDOW_AUTOSIZE);
	imshow("img", img);

	freq_filtering F1;

	low = F1.freq_filter(img, Magnitude_image, low_mask, "lowpass", 40);
	imshow("Magnitude image", Magnitude_image);
	imshow("low_mask", low_mask);
	imshow("lowpass", low);


	//high = F1.freq_filter(img, Magnitude_image, high_mask, "highpass", 40);
	//
	//imshow("Magnitude_image", Magnitude_image);
	//imshow("high_mask", high_mask);
	//imshow("highpass", high);


	waitKey(0);
	return 0;
}*/