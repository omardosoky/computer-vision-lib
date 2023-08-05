#include "Threshold.hpp"

int MinIntensity = 255;
int MaxIntensity = 0;
int Threshold = 0;

int main()
{
	Mat Image = imread("C:\\Users\\Mahdy\\Pictures\\Grad.jpg");
	imshow("Original Image", Image);
	Mat DesImage = Image.clone();

	// Getting Old Minimum and Maximum Values of Intensity
	for (int i = 0; i < Image.rows; i++)
	{
		for (int j = 0; j < 3 * Image.cols; j++)
		{
			if (Image.at<uchar>(i, j) > MaxIntensity)
			{
				MaxIntensity = Image.at<uchar>(i, j);
			}

			if (Image.at<uchar>(i, j) < MinIntensity)
			{
				MinIntensity = Image.at<uchar>(i, j);
			}
		}
	}

	Threshold = (MinIntensity + MaxIntensity) / 2;


	//GlobalThreshold(Image, DesImage, Threshold, 255, BINARY);
	//GlobalThreshold(Image, DesImage, Threshold, 255, BINARY_INV);
	//GlobalThreshold(Image, DesImage, Threshold, 255, TRUNC);
	//GlobalThreshold(Image, DesImage, Threshold, 255, TOZERO);
	//GlobalThreshold(Image, DesImage, Threshold, 255, TOZERO_INV);


	//LocalThreshold(Image, DesImage, 9, Gaussian);
	//LocalThreshold(Image, DesImage, 9, Mean);

	waitKey(0);
}



