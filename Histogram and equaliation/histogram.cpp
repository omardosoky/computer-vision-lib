#include "histogram.h"
#include <qmessagebox.h>
void::Histogram::CCHistogram(cv::Mat Image, int NumberOfBarsDecider, int Mode) {



	// Here the histogram we will get its distribuition and bars by using Qt charts
	// so keep in mind that it must have Qapplication app and app.exec() with no gui needed 
	std::vector<int>HistogramvectorAccumilatedTen;
	std::vector<int>CumilatedHisto;

	// The histo gram vector whic will contain all histogram data
	std::vector<int>Histogramvector(256, 0);


	for (int y = 0; y < Image.rows; y++)//To loop through all the pixels
	{
		for (int x = 0; x < Image.cols; x++)
		{

			// this is the only line needed to get histogram 
			// it says will make the point of which the grayscale value is take this point
			//and actually make the histogram value in this array +1 
			Histogramvector[Image.at<uchar>(x, y)]++;
		}
	}
	
	//we used the same qtcharts way scene+ viewer in spline visulaization of data and Bars visulaization
	
	int Accumilated = 0;
	int Cumulitive=0;
	for (int i = 0;i < Histogramvector.size();i++)
	{

		Accumilated += Histogramvector[i];
		Cumulitive += Histogramvector[i];
		CumilatedHisto.push_back(Cumulitive);
		if (i % NumberOfBarsDecider == 0)
		{
			// the way bars work is by accumilating each 10 ...5.......As the numberofBarsDecider and adding all the values in these points
			//so by modulising the values every 10..5 calues we will get the needed bar accumilated within them
			HistogramvectorAccumilatedTen.push_back(Accumilated);
			
			Accumilated = 0;
		}
	}
	if (Mode == 1)
	{

		HistogramvectorofVectors.push_back(Histogramvector);
		HistogramvectorofAccumilatedTenVectors.push_back(HistogramvectorAccumilatedTen);
		SupremeCumilatedHisto.push_back(CumilatedHisto);
	}
	QtCharts::QSplineSeries *series = new QtCharts::QSplineSeries();
	series->setName("spline");
	for (int i = 1; i < Histogramvector.size();i++) {


		//series is the  data needed for the histogram
		series->append(i, Histogramvector[i]);

	}

	QtCharts::QBarSeries *seriesBars = new QtCharts::QBarSeries();
	QtCharts::QChart *chartSpline = new QtCharts::QChart();

	chartSpline->legend()->hide();
	chartSpline->addSeries(series);
	chartSpline->setTitle("Here is the spline draw of histogram");
	chartSpline->createDefaultAxes();
	// after makeing the chart add its spline series to chart view which be added to scene in a viewer in window
	QtCharts::QChartView *chartView = new QtCharts::QChartView(chartSpline);
	chartView->setRenderHint(QPainter::Antialiasing);
	//QWidget *wdg = new QWidget;
	//wdg->show();
	//chartView->show();

	QGraphicsScene * OhMyHisto = new QGraphicsScene();
	QGraphicsView *Scenevieweeer = new QGraphicsView();

	QMainWindow *window779 = new QMainWindow;
	QRectF rc(QPoint(0, 0), window779->size());
	//inichialize the scene size is important more than window as its default value is 5*5 which will not be seen if removed

	chartSpline->resize(Scenevieweeer->size());
	OhMyHisto->addItem(chartSpline);
	OhMyHisto->setSceneRect(rc);
	Scenevieweeer->setScene(OhMyHisto);
	Scenevieweeer->fitInView(rc, Qt::KeepAspectRatio);
	window779->resize(400, 300);
	window779->setCentralWidget(Scenevieweeer);


	/////////////////////////////////////////////////////////////////////////////////
	// the exact same way is done in QBarseries	



	//make the set0 which will append the values needed
	QtCharts::QBarSet *set0 = new  QtCharts::QBarSet("");
	for (int i = 0; i < HistogramvectorAccumilatedTen.size();i++) {
		set0->append(HistogramvectorAccumilatedTen[i]);
	}
	seriesBars->append(set0);
	// same as splinechart
	QtCharts::QChart *chartBars = new QtCharts::QChart();
	chartBars->addSeries(seriesBars);
	chartBars->setTitle("Simple barchart example");
	chartBars->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
	QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
	//axisX->append(categories);
	chartBars->addAxis(axisX, Qt::AlignBottom);
	seriesBars->attachAxis(axisX);

	QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
	//axisY->setRange(0, 15);
	chartBars->addAxis(axisY, Qt::AlignLeft);
	seriesBars->attachAxis(axisY);
	chartBars->legend()->setVisible(true);
	chartBars->legend()->setAlignment(Qt::AlignBottom);
	QtCharts::QChartView *chartViewBars = new QtCharts::QChartView(chartBars);
	chartView->setRenderHint(QPainter::Antialiasing);


	QMainWindow *window800 = new QMainWindow;
	QRectF rc2(QPoint(0, 0), window800->size());
	QGraphicsScene * OhMyHistoBars = new QGraphicsScene();
	QGraphicsView *ScenevieweeerBars = new QGraphicsView();
	chartBars->resize(ScenevieweeerBars->size());
	OhMyHistoBars->addItem(chartBars);
	OhMyHistoBars->setSceneRect(rc2);
	ScenevieweeerBars->setScene(OhMyHistoBars);
	ScenevieweeerBars->fitInView(rc2, Qt::KeepAspectRatio);
	window800->resize(400, 300);
	window800->setCentralWidget(ScenevieweeerBars);

	if (Mode != 1) 
	{
		window779->show();
		window800->show();
	}


}


void::Histogram::RGBHistogram(std::vector<cv::Mat> SplitVector, int NumberOfBarsDecider) 
{


	// The main Idea about RGB Histogram is the exact same thing as CC gray scale
	// but in three channels so we made Split function to return a vector of the image
	// this vector then will be the input to our function by making a mode
	// this mode let us save in a public vector of vectors our needed 
	// either distribution or accumilated and then use this vector of vectors in our function
	// Again by applying the exact same method as before
	
	CCHistogram(SplitVector[0], NumberOfBarsDecider, 1);
	CCHistogram(SplitVector[1], NumberOfBarsDecider, 1);
	CCHistogram(SplitVector[2], NumberOfBarsDecider, 1);

	QtCharts::QSplineSeries *seriesBlue = new QtCharts::QSplineSeries();
	seriesBlue->setName("Blue");
	seriesBlue->setColor(Qt::blue);


	QtCharts::QSplineSeries *seriesGreen = new QtCharts::QSplineSeries();
	seriesGreen->setName("Green");
	seriesGreen->setColor(Qt::green);


	QtCharts::QSplineSeries *seriesRed = new QtCharts::QSplineSeries();
	seriesRed->setName("Red");
	seriesRed->setColor(Qt::red);



	std::vector<QtCharts::QSplineSeries *> SSseries;
	SSseries.push_back(seriesBlue);
	SSseries.push_back(seriesGreen);
	SSseries.push_back(seriesRed);

	// we just instead of using histogram[i] we will use histogram[z][i] where z is RGB scaled
	for (int z = 0; z < HistogramvectorofVectors.size();z++) {
		for (int i = 1; i < HistogramvectorofVectors[z].size();i++) {


			//series is the  data needed for the histogram
			SSseries[z]->append(i, HistogramvectorofVectors[z][i]);

		}
	}

	QtCharts::QBarSeries *seriesBars = new QtCharts::QBarSeries();
	QtCharts::QChart *chartSpline = new QtCharts::QChart();

	chartSpline->legend()->hide();
	chartSpline->addSeries(SSseries[0]);
	chartSpline->addSeries(SSseries[1]);
	chartSpline->addSeries(SSseries[2]);

	chartSpline->setTitle("RGB Combined");
	chartSpline->createDefaultAxes();
	// after makeing the chart add its spline series to chart view which be added to scene in a viewer in window
	QtCharts::QChartView *chartView = new QtCharts::QChartView(chartSpline);
	chartView->setRenderHint(QPainter::Antialiasing);
	//QWidget *wdg = new QWidget;
	//wdg->show();
	//chartView->show();

	QGraphicsScene * OhMyHisto = new QGraphicsScene();
	QGraphicsView *Scenevieweeer = new QGraphicsView();

	QMainWindow *window7792 = new QMainWindow;
	QRectF rc(QPoint(0, 0), window7792->size());
	//inichialize the scene size is important more than window as its default value is 5*5 which will not be seen if removed

	chartSpline->resize(Scenevieweeer->size());
	OhMyHisto->addItem(chartSpline);
	OhMyHisto->setSceneRect(rc);
	Scenevieweeer->setScene(OhMyHisto);
	Scenevieweeer->fitInView(rc, Qt::KeepAspectRatio);
	window7792->resize(400, 300);
	window7792->setCentralWidget(Scenevieweeer);
	window7792->show();

	//////////////////////////////////////////////////////////////////////////////////////////////

	
	// Bars are also the exact same thing done with them as before

	QtCharts::QBarSet *setG = new  QtCharts::QBarSet("");
	QtCharts::QBarSet *setB = new  QtCharts::QBarSet("");
	QtCharts::QBarSet *setR = new  QtCharts::QBarSet("");

	std::vector <QtCharts::QBarSet *> SSsets;
	SSsets.push_back(setG);
	SSsets.push_back(setB);
	SSsets.push_back(setR);


	

	for (int z = 0; z < HistogramvectorofAccumilatedTenVectors.size();z++) {
		for (int i = 0; i < HistogramvectorofAccumilatedTenVectors[z].size();i++) {
			SSsets[z]->append(HistogramvectorofAccumilatedTenVectors[z][i]);
		}
	}
	seriesBars->append(SSsets[0]);
	seriesBars->append(SSsets[1]);
	seriesBars->append(SSsets[2]);

	// same as splinechart
	QtCharts::QChart *chartBars = new QtCharts::QChart();
	chartBars->addSeries(seriesBars);
	chartBars->setTitle("Simple barchart example");
	chartBars->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
	QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
	//axisX->append(categories);
	chartBars->addAxis(axisX, Qt::AlignBottom);
	seriesBars->attachAxis(axisX);

	QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
	//axisY->setRange(0, 15);
	chartBars->addAxis(axisY, Qt::AlignLeft);
	seriesBars->attachAxis(axisY);
	chartBars->legend()->setVisible(true);
	chartBars->legend()->setAlignment(Qt::AlignBottom);
	QtCharts::QChartView *chartViewBars = new QtCharts::QChartView(chartBars);
	chartView->setRenderHint(QPainter::Antialiasing);


	QMainWindow *window800 = new QMainWindow;
	QRectF rc2(QPoint(0, 0), window800->size());
	QGraphicsScene * OhMyHistoBars = new QGraphicsScene();
	QGraphicsView *ScenevieweeerBars = new QGraphicsView();
	chartBars->resize(ScenevieweeerBars->size());
	OhMyHistoBars->addItem(chartBars);
	OhMyHistoBars->setSceneRect(rc2);
	ScenevieweeerBars->setScene(OhMyHistoBars);
	ScenevieweeerBars->fitInView(rc2, Qt::KeepAspectRatio);
	window800->resize(400, 300);
	window800->setCentralWidget(ScenevieweeerBars);
	window800->show();


	//////////////////////////////////////////////////////////////Cumilative


	// the accumilated 
	// NOTE////////////////////////////////////////////////////////
	// the accumilated is take as it is because the scale will  be in equalization function is not added here
	std::vector<QtCharts::QSplineSeries *> SSseriesCumilated;
	QtCharts::QSplineSeries *seriesBlueCumilated = new QtCharts::QSplineSeries();
	seriesBlueCumilated->setName("Blue");
	seriesBlueCumilated->setColor(Qt::blue);


	QtCharts::QSplineSeries *seriesGreenCumilated = new QtCharts::QSplineSeries();
	seriesGreenCumilated->setName("Green");
	seriesGreenCumilated->setColor(Qt::green);


	QtCharts::QSplineSeries *seriesRedCumilated = new QtCharts::QSplineSeries();
	seriesRedCumilated->setName("Red");
	seriesRedCumilated->setColor(Qt::red);

	SSseriesCumilated.push_back(seriesBlueCumilated);
	SSseriesCumilated.push_back(seriesGreenCumilated);
	SSseriesCumilated.push_back(seriesRedCumilated);

	

	for (int z = 0; z < SupremeCumilatedHisto.size();z++) {
		for (int i = 1; i < SupremeCumilatedHisto[z].size();i++) {


			//series is the  data needed for the histogram
			SSseriesCumilated[z]->append(i, SupremeCumilatedHisto[z][i]);

		}
	}

	QtCharts::QBarSeries *seriesBarsCumilated = new QtCharts::QBarSeries();
	QtCharts::QChart *chartSplineCumilated = new QtCharts::QChart();

	chartSplineCumilated->legend()->hide();
	chartSplineCumilated->addSeries(SSseriesCumilated[0]);
	chartSplineCumilated->addSeries(SSseriesCumilated[1]);
	chartSplineCumilated->addSeries(SSseriesCumilated[2]);

	chartSplineCumilated->setTitle("RGB Cumilated ");
	chartSplineCumilated->createDefaultAxes();
	// after makeing the chart add its spline series to chart view which be added to scene in a viewer in window
	QtCharts::QChartView *chartViewCumilated = new QtCharts::QChartView(chartSplineCumilated);
	chartViewCumilated->setRenderHint(QPainter::Antialiasing);
	

	QGraphicsScene * OhMyHistoCumilated = new QGraphicsScene();
	QGraphicsView *ScenevieweeerCumilated = new QGraphicsView();

	QMainWindow *window7792Cumilated = new QMainWindow;
	QRectF rcCumilated(QPoint(0, 0), window7792Cumilated->size());
	//inichialize the scene size is important more than window as its default value is 5*5 which will not be seen if removed

	chartSplineCumilated->resize(ScenevieweeerCumilated->size());
	OhMyHistoCumilated->addItem(chartSplineCumilated);
	OhMyHistoCumilated->setSceneRect(rcCumilated);
	ScenevieweeerCumilated->setScene(OhMyHistoCumilated);
	ScenevieweeerCumilated->fitInView(rcCumilated, Qt::KeepAspectRatio);
	window7792Cumilated->resize(400, 300);
	window7792Cumilated->setCentralWidget(ScenevieweeerCumilated);
	window7792Cumilated->show();



























}

void::Grayer::RGBtoGRAY(cv::Mat Image) 
{

	//// we choose to use the wiegted method as there are alot of ways to change the weight but in our case the weighted
	// method is applied
	cv::Mat Grayer = Image.clone();

	Grayer.setTo(cv::Scalar(0, 0, 0));
	// not used for change only used
	// Just to make sure opencv is talking uchar when appling color
	// wew can also read any image in local and set read("",0);
	cv::cvtColor(Grayer, Grayer, cv::COLOR_RGB2GRAY);

	for (int y = 0;y < Image.rows-1;y++)
	{
		for (int x = 0;x < Image.cols-1;x++)
		{
			cv::Vec3b color = Image.at<cv::Vec3b>(cv::Point(x, y));
			// 0.299R + 0.587G + 0.114B
			// again these values can change if wanted to change the way of image representation
			int GrayValue = (int)round(color[0] * 0.299 + color[1] * 0.587 + color[2] * 0.114);

			if (GrayValue >= 255)
			{
				
				GrayValue = 255;
			}
			
			Grayer.at<uchar>(y, x) =GrayValue ;
		}
	}


	cv::imshow("Before Image", Image);
	cv::imshow("Gray chaned", Grayer);

	cv::waitKey();
}


std::vector<cv::Mat> Splitter::Split_Image(cv::Mat Image) 
{



	cv::Mat Splitted[3];
	cv::split(Image, Splitted);

	std::vector<cv::Mat> SplittedVector;
	

	//////////B
	SplittedVector.push_back(Splitted[0]);
	//////////////G
	SplittedVector.push_back(Splitted[1]);
	//////////////R
	SplittedVector.push_back(Splitted[2]);
	cv::Mat Merged;
	cv::merge(SplittedVector, Merged);




	return SplittedVector;



}


void Equalization::EqualizingImage(cv::Mat Image)
{

	//in equlaization the point is to make the image equalized meanining 
	// we want the image that its histogram in certain point high become equlaized low..
	// for example if image have 200 out of 600 pixels value is zero 
	// we will take this value and but it into near pixels to make as rounded to them 
	// so we first start with histogram same method as above
	std::vector<int>Histogramvector;
	cv::imshow("Image", Image);
	cv::waitKey();
	for (int i = 0; i < 256;i++)
	{

		Histogramvector.push_back(0);
	}

	for (int y = 0; y < Image.rows; y++)//To loop through all the pixels
	{
		for (int x = 0; x < Image.cols; x++)
		{

			Histogramvector[Image.at<uchar>(x, y)]++;
		}
	}
	int i = 0;
	// we don't want to make i=0 as scaling we want the first one we see to make the scale
	// based on which can be changed aswell 

	int total = Image.rows*Image.cols;


	// we want to round the values to sepecific scale this scale is applied by
	// before we say the equation imagine all the image had 255 pixels of 255 difrent grayscale
	// so equalization should do nothing
	// meaning the scale of change should be one
	// this one idicated the relation between the histogram vector size 255 to
	// the total - histogramvector at any point 
	// that in ideal ... mon ideeal we will have to substract histogramvector[i] of max i from total
	// keep in mind this scale can be changed from default
	// in fact in most cases they neglect the effect of this value
	// so we will do
	// for normalizing equation it is said to subsitue 1 from size 
	// 
	float scale = (Histogramvector.size() - 1.f) / (total);
	// what happens if we multiplied scale * total we will get size of histogram
	// the scale is as if we wanted that value that we erased to make impact of 0.1 for example
	// in all pixels near it so we will get that scale.....
	std::vector<int> lut(Histogramvector.size(), 0);


	int sum = 0;
	for (int i = 0; i < Histogramvector.size(); ++i) {
		sum += Histogramvector[i];
		//.....and multiply it by sum of values before it to equalize them in regard of how much they are in repect to before them sum
		lut[i] = std::max(0, std::min(int(round(sum * scale)), 255));
	}


	for (int y = 0; y < Image.rows; y++)//To loop through all the pixels
	{
		for (int x = 0; x < Image.cols; x++)
		{
			// then we want to make the value of the image at certain pixel
			// become the value crossbonding to the index of lut 
			Image.at<uchar>(x, y) = lut[Image.at<uchar>(x, y)];
		}
	}


	// in short it is as 0.1 * 20000 will have loss impact more way more than 20 *0.1 
	// although this will affect 20 aswell but the bigger the value the biggeer the sum 
	// and the more the sum the more it will affect smaller values as well

	cv::imshow("Image", Image);
	cv::waitKey();

}



