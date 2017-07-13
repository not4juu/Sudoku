#pragma once

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>

class Squares
{
private:
	cv::Mat src;
	std::vector<std::vector<cv::Point> > squares;

	double threshold1;
	double threshold2;
	int apertureSize;

	void findSquares();
	double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0);
	void uniqueSquares(int neighbour);
	cv::Mat drawSquares();


public:
	void run();
	Squares(cv::Mat img, double threshold1=0, double threshold2=255, int apertureSize=3);
};

