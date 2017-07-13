#include "Squares.h"


Squares::Squares(cv::Mat img, double threshold1,  double threshold2, int apertureSize)
{
	this->src = img;
	this->threshold1 = threshold1;
	this->threshold2 = threshold2;
	this->apertureSize = apertureSize;
}


void Squares::findSquares()
{
	squares.clear();
	squares.clear();

	cv::Mat pyr, timg, gray0(src.size(), CV_8U), gray;

	// down-scale and upscale the image to filter out the noise
	pyrDown(src, pyr, cv::Size(src.cols / 2, src.rows / 2));
	pyrUp(pyr, timg, src.size());
	std::vector<std::vector<cv::Point> > contours;

	//TODO:
	int ch[] = { 1, 0 };
	mixChannels(&timg, 1, &gray0, 1, ch, 1);

	
	Canny(gray0, gray, threshold1, threshold2, apertureSize);
	dilate(gray, gray, cv::Mat(), cv::Point(-1, -1));
	//erode(gray, gray, Mat());
	imshow("checker", gray);
			
			
	findContours(gray, contours, CV_RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
	std::vector<cv::Point> approx;
	std::cout << contours.size() << std::endl;
	for (size_t i = 0; i < contours.size(); i++)
	{

		approxPolyDP(cv::Mat(contours[i]), approx, arcLength(cv::Mat(contours[i]), true)*0.02, true);

		if (	approx.size() == 4 &&
				fabs(contourArea(cv::Mat(approx))) > 1000 &&
				isContourConvex(cv::Mat(approx))
			)
		{

			double maxCosine = 0;
			for (int j = 2; j < 5; j++)
			{
				// find the maximum cosine of the angle between joint edges
				double cosine = fabs(angle(approx[j % 4], approx[j - 2], approx[j - 1]));
				maxCosine = MAX(maxCosine, cosine);
			}

					// if cosines of all angles are small
					// (all angles are ~90 degree) then write quandrange
					// vertices to resultant sequence
			if (maxCosine < 0.3) squares.push_back(approx);
		}		
	}
}

double Squares::angle(cv::Point pt1, cv::Point pt2, cv::Point pt0)
{
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1*dx2 + dy1*dy2) / sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

//TODO:
void Squares::uniqueSquares(int neighbour)
{
	for (size_t i = 0; i < squares.size(); i++)
	{
		for (size_t j = 0; j < squares[i].size(); j++)
		{
			const cv::Point p = squares[i][j];
			std::cout << i << ":" << p.x << " " << p.y << " " << squares[i].size() << "\n";
		}
	}
}

cv::Mat Squares::drawSquares()
{
	//cv::Mat img = src.clone();
	cv::Mat img(src.size(), src.type(), cv::Scalar(0, 0, 0));
//	cv::Mat img(src.size(), src.type, cv::Scalar(0));
	for (size_t i = 0; i < squares.size(); i++)
	{
		const cv::Point* p = &squares[i][0];
		int n = (int)squares[i].size();
		polylines(img, &p, &n, 1, true, cv::Scalar(255, 255, 255), 1, cv::LINE_AA);
	}
	return img;
}

void Squares::run()
{
	findSquares();
	cv::Mat img = drawSquares();
	cv::imshow("Sqaures ORG ", img);
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT,
		cv::Size(3, 3));
	dilate(img, img, element);
	cv::imshow("Sqaures ", img);
	
	src = img.clone();
	findSquares();
	cv::Mat img1 = drawSquares();
	cv::imshow("Sqaures 1", img1);
	//uniqueSquares();
	

}

