#ifndef Histo_Gra_M
#define Histo_Gra_M
#include "All_Librarries.h"
class Histogram
{

public:
	void CCHistogram(cv::Mat Image, int NumberOfBarsDecider, int Mode);
	void RGBHistogram(std::vector<cv::Mat> SplitVector, int NumberOfBarsDecider);
	std::vector<std::vector<int>>HistogramvectorofVectors;
	std::vector<std::vector<int>> HistogramvectorofAccumilatedTenVectors;
	std::vector<std::vector<int>> SupremeCumilatedHisto;


};

class Equalization
{


public:
	void EqualizingImage(cv::Mat Image);



};


class Splitter 
{
public:
	std::vector <cv::Mat> Split_Image(cv::Mat Image);

};



class Grayer 
{
public:
		void RGBtoGRAY(cv::Mat Image);


};
#endif // !