#include "harris.hpp"

Mat ImagePadding(Mat Image, int Padding)
{
	Mat PaddedImage;
	PaddedImage.create(Image.rows + 2 * Padding, Image.cols + 2 * Padding, Image.type());
	PaddedImage.setTo(Scalar::all(0.0));
	Image.copyTo(PaddedImage(Rect(Padding, Padding, Image.cols, Image.rows)));
	return PaddedImage;
}

Mat SobelX(Mat src)
{
	double sobelX[3][3] = {
			{-1.0, 0.0, 1.0},
			{-2.0, 0.0, 2.0},
			{-1.0, 0.0, 1.0}
	};

	int rows = src.rows;
	int cols = src.cols;
	Mat dst = src.clone();
	double sum;

	for (int row = 1; row < rows - 1; row++)
	{
		for (int col = 1; col < cols - 1; col++)
		{
			sum = 0.0;
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					sum = sum + sobelX[i + 1][j + 1] * src.at<uchar>(row - i, col - j);
				}
			}
			dst.at<uchar>(row, col) = static_cast<uchar>(sum);
		}
	}

	return dst;
}

Mat SobelY(Mat src)
{
	double sobelY[3][3] = {
			{-1.0, -2.0, -1.0},
			{0.0, 0.0, 0.0},
			{1.0, 2.0, 1.0}
	};

	int rows = src.rows;
	int cols = src.cols;
	Mat dst = src.clone();
	double sum;

	for (int row = 1; row < rows - 1; row++)
	{
		for (int col = 1; col < cols - 1; col++)
		{
			sum = 0.0;
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					sum = sum + sobelY[i + 1][j + 1] * static_cast<double>(src.at<uchar>(row + i, col + j));
				}
			}
			dst.at<uchar>(row, col) = static_cast<uchar>(sum);
		}
	}

	return dst;
}

Mat Multiply(Mat src1, Mat src2)
{
	if (src1.rows != src2.rows && src1.cols != src2.cols)
	{
		std::cout << "Matrices shapes.png don't match" << std::endl;
		return src1;
	}

	int rows = src1.rows;
	int cols = src1.cols;

	Mat dst = Mat(rows, cols, CV_64FC1);
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			dst.at<double>(row, col) = static_cast<double>(src1.at<uchar>(row, col) * src2.at<uchar>(row, col));
		}
	}
	return dst;
}

Harris ApplyHarris(Mat Image, long long Threshold, int Padding)
{
	// *** Calculating Ix and Iy ***
	Mat Ix = SobelX(Image);
	Mat Iy = SobelY(Image);

	int rows = Image.rows;
	int cols = Image.cols;

	// *** Getting Absolute Values of Ix and Iy ***
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			if (Ix.at<uchar>(row, col) < 0)
			{
				Ix.at<uchar>(row, col) *= -1;
			}
			if (Iy.at<uchar>(row, col) < 0)
			{
				Iy.at<uchar>(row, col) *= -1;
			}
		}
	}

	// *** Calculating Gaussian Blurred Ixx, Iyy and Ixy ***
	Mat Ixx = Multiply(Ix, Ix);
	Mat Iyy = Multiply(Iy, Iy);
	Mat Ixy = Multiply(Ix, Iy);

	Mat IxxGaussian = Mat(rows, cols, CV_64FC1);
	Mat IyyGaussian = Mat(rows, cols, CV_64FC1);
	Mat IxyGaussian = Mat(rows, cols, CV_64FC1);

	GaussianBlur(Ixx, IxxGaussian, Size(9, 9), 0.0);
	GaussianBlur(Iyy, IyyGaussian, Size(9, 9), 0.0);
	GaussianBlur(Ixy, IxyGaussian, Size(9, 9), 0.0);

	Mat R = Mat(rows, cols, CV_64FC1);
	double detM, traceM;

	// *** R = det(M) - k * Trace(M)^2 ***
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			detM = IxxGaussian.at<double>(row, col) * IyyGaussian.at<double>(row, col) - IxyGaussian.at<double>(row, col) * IxyGaussian.at<double>(row, col);
			traceM = IxxGaussian.at<double>(row, col) + IyyGaussian.at<double>(row, col);

			// The varaible (K) is supposed to be in the range (0.05 : 0.06)
			// but these values greatly affects computation time
			// we used 0.2 , it gives an acceptable results
			R.at<double>(row, col) = detM - 0.2 * traceM * traceM;
		}
	}

	std::vector<CornerParameters> Pts;

	double NonMax;
	bool Skip;
	int WindowSize = Padding;

	for (int row = Padding; row < rows - Padding; row++)
	{
		for (int col = Padding; col < cols - Padding; col++)
		{
			if (R.at<double>(row, col) > static_cast<double>(Threshold))
			{
				// *** NonMax Suppression to catch the most accurate harris pts ***
				Skip = false;
				NonMax = R.at<double>(row, col);
				for (int i = -WindowSize; i <= WindowSize; i++) // Window Size = Padding Size
				{
					for (int j = -WindowSize; j <= WindowSize; j++)
					{
						if (R.at<double>(row + i, col + j) > NonMax)
						{
							Skip = true;
							break;
						}
					}
				}
				if (!Skip)
				{
					CornerParameters p2d{};
					p2d.x = col;
					p2d.y = row;
					p2d.r = R.at<double>(row, col);
					Pts.push_back(p2d);
				}
			}
		}
	}

	Harris Output;
	Output.R = R;
	Output.points = Pts;
	return Output;
}

void DrawCorners(Mat& Image, std::vector<CornerParameters> Points, int Padding)
{
	size_t size = Points.size();
	for (int i = 0; i < size; i++)
	{
		circle(Image, Point(Points[i].x - Padding, Points[i].y - Padding), 10, Scalar(0.0, 255.0, 0.0), 2, 7);
	}

	(void)imwrite("output.png", Image);
}

Mat DetectCorners(Mat src, int Padding, long long Threshold, Harris& Destination)
{
	Mat graySrc;
	if (src.channels() > 1)
	{
		cvtColor(src, graySrc, COLOR_BGR2GRAY);
	}
	else
	{
		graySrc = src;
	}

	Mat BlurredImage;
	GaussianBlur(graySrc, BlurredImage, Size(9, 9), 0.5);
	Mat PaddedImage = ImagePadding(BlurredImage, Padding);
	Destination = ApplyHarris(PaddedImage, Threshold, Padding);
	DrawCorners(src, Destination.points, Padding);
	return src;
}
