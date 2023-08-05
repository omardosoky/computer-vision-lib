#include "Threshold.hpp"


void GlobalThreshold(Mat Src, Mat Des, int Threshold, int MaxValue, int Mode)
{
	switch (Mode)
	{

	case BINARY:
		for (int i = 0; i < Src.rows; i++)
		{
			for (int j = 0; j < 3 * Src.cols; j++)
			{
				if (Src.at<uchar>(i, j) > Threshold)
				{
					Des.at<uchar>(i, j) = MaxValue;
				}
				else
				{
					Des.at<uchar>(i, j) = 0;
				}
			}
		}
		imshow("Binary Thesholded Image", Des);
		imwrite("C:\\Users\\Mahdy\\Pictures\\CV Thresholding\\Binary Thesholded Image.jpg", Des);
		break;

	case BINARY_INV:
		for (int i = 0; i < Src.rows; i++)
		{
			for (int j = 0; j < 3 * Src.cols; j++)
			{
				if (Src.at<uchar>(i, j) > Threshold)
				{
					Des.at<uchar>(i, j) = 0;
				}
				else
				{
					Des.at<uchar>(i, j) = MaxValue;
				}
			}
		}
		imshow("Inverted Binary Thesholded Image", Des);
		imwrite("C:\\Users\\Mahdy\\Pictures\\CV Thresholding\\Inverted Binary Thesholded Image.jpg", Des);
		break;

	case TRUNC:
		for (int i = 0; i < Src.rows; i++)
		{
			for (int j = 0; j < 3 * Src.cols; j++)
			{
				if (Src.at<uchar>(i, j) > Threshold)
				{
					Des.at<uchar>(i, j) = Threshold;
				}
				else
				{
					Des.at<uchar>(i, j) = Src.at<uchar>(i, j);
				}
			}
		}
		imshow("Truncated Thesholded Image", Des);
		imwrite("C:\\Users\\Mahdy\\Pictures\\CV Thresholding\\Truncated Thesholded Image.jpg", Des);
		break;

	case TOZERO:
		for (int i = 0; i < Src.rows; i++)
		{
			for (int j = 0; j < 3 * Src.cols; j++)
			{
				if (Src.at<uchar>(i, j) <= Threshold)
				{
					Des.at<uchar>(i, j) = 0;
				}
				else
				{
					Des.at<uchar>(i, j) = Src.at<uchar>(i, j);
				}
			}
		}
		imshow("Zero Thesholded Image", Des);
		imwrite("C:\\Users\\Mahdy\\Pictures\\CV Thresholding\\Zero Thesholded Image.jpg", Des);
		break;

	case TOZERO_INV:
		for (int i = 0; i < Src.rows; i++)
		{
			for (int j = 0; j < 3 * Src.cols; j++)
			{
				if (Src.at<uchar>(i, j) > Threshold)
				{
					Des.at<uchar>(i, j) = 0;
				}
				else
				{
					Des.at<uchar>(i, j) = Src.at<uchar>(i, j);
				}
			}
		}
		imshow("Inverted Zero Thesholded Image", Des);
		imwrite("C:\\Users\\Mahdy\\Pictures\\CV Thresholding\\Inverted Zero Thesholded Image.jpg", Des);
		break;

	default:
		break;
	}
}

void LocalThreshold(Mat Src, Mat Des, int KernelSize, int Mode)
{
	Mat Kernel(KernelSize, KernelSize, CV_64FC1);

	// *** Choosing and Intalizing The Kernel ***
	if (Mode == Gaussian)
	{
		int p_rows = (KernelSize - 1) / 2;
		int p_cols = (KernelSize - 1) / 2;

		for (int i = -p_rows; i <= p_rows; i++)
		{
			for (int j = -p_cols; j <= p_cols; j++)
			{
				Kernel.at<double>(i + p_rows, j + p_cols) = exp(-(i * i + j * j) / 2.0);
			}
		}

		Kernel = Kernel / sum(Kernel);
	}
	else if (Mode == Mean)
	{
		Kernel.setTo(Scalar(1.0 / (KernelSize * KernelSize)));
	}

	// *** Implementing Convoltion ***
	Mat CImage = Mat::zeros(Src.size(), CV_64FC1);
	filter2D(Src, CImage, -1, Kernel, Point(-1, -1), 0, BORDER_DEFAULT);


	// *** Implementing Threshold ***
	for (int i = 0; i < Src.rows; i++)
	{
		for (int j = 0; j < 3 * Src.cols; j++)
		{
			if (Src.at<uchar>(i, j) > CImage.at<uchar>(i, j))
			{
				Des.at<uchar>(i, j) = 255;
			}
			else
			{
				Des.at<uchar>(i, j) = 0;
			}
		}
	}

	if (Mode == Gaussian)
	{
		imshow("Local Thesholded (Gaussian)", Des);
		imwrite("C:\\Users\\Mahdy\\Pictures\\CV Thresholding\\Local Thesholded (Gaussian).jpg", Des);

	}
	else if (Mode == Mean)
	{
		imshow("Local Thesholded (Mean)", Des);
		imwrite("C:\\Users\\Mahdy\\Pictures\\CV Thresholding\\Local Thesholded (Mean).jpg", Des);

	}

	
}