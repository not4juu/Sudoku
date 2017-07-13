#pragma once

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
#include"SudokuConf.h"

class MainBoard
{
private:
	cv::Mat board;
	cv::Rect borderContour;
	cv::Point2f corners[4];
	
	cv::Mat src;

	bool mainBoardExist;
	void findCorners();
	cv::Mat createBoard();

	int minX;
	int maxX;
	int minY;
	int maxY;

public:
	MainBoard(cv::Mat img);
	cv::Mat getBoard();

	cv::Rect getBorderContour();
	cv::Point2i getUpperLeftCorner();
};

