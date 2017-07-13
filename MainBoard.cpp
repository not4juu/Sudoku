#include "MainBoard.h"


MainBoard::MainBoard(cv::Mat img)
{
	src = img.clone();
	mainBoardExist = true;
	borderContour = cv::Rect();
	for (int i = 0; i < 4; ++i)corners[i] = cv::Point2f(0,0);
	minX = NULL; maxX = NULL; minY = NULL; minX = NULL;
}

void MainBoard::findCorners()
{

	cv::Mat gray, thr;
	cv::cvtColor(src, gray, CV_BGR2GRAY);
	cv::threshold(gray, thr, 100, 255, cv::THRESH_BINARY_INV);
	
#ifdef DEBUG
	cv::imshow(" MainBoard::findCorners : preaperd threshold to find max contour", thr);
#endif
	
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(thr, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	int biggestContourIdx = -1;
	float biggestContourArea = 0;

	for (int i = 0; i< contours.size(); i++)
	{
		float ctArea = cv::contourArea(contours[i]);
		if (ctArea > biggestContourArea)
		{
			biggestContourArea = ctArea;
			biggestContourIdx = i;
		}
	}

	if (biggestContourIdx < 0)
	{
		std::cout << "Algorithm could not find a main board" << std::endl;
		mainBoardExist = false;
	}
	else
	{
		cv::RotatedRect boundingBox = cv::minAreaRect(contours[biggestContourIdx]);
		boundingBox.points(corners);

		minX = src.rows; maxX = 0;
		minY = src.cols; maxY = 0;
		for (int i = 0; i < 4; ++i)
		{
			if (corners[i].x > maxX)
				maxX = corners[i].x;
			if (corners[i].x < minX)
				minX = corners[i].x;

			if (corners[i].y > maxY)
				maxY = corners[i].y;
			if (corners[i].y < minY)
				minY = corners[i].y;
		}	
	}

#ifdef DEBUG
	DEBUG_LOG("MainBoard::findCorners :  corners ");
	for (int i = 0; i < 4; ++i) DEBUG_LOG(i << " " << corners[i].x << " " << corners[i].y);
	DEBUG_LOG("MainBoard::findCorners : MIN(x,y) " << minX<<":"<<maxX<<" MAX(x,y) "<< minY<<":"<<maxY <<std::endl);
#endif
}

cv::Mat MainBoard::createBoard()
{
	int rows = abs(maxX - minX);
	int cols = abs(maxY - minY);
	borderContour = cv::Rect(minX, minY, rows, cols);
	cv::Mat mainBoard = src(borderContour);
	return mainBoard;
}

cv::Mat MainBoard::getBoard()
{
	findCorners();

	if(mainBoardExist)
		board = createBoard();
	else 
		board = cv::Mat();
	return board;
}

cv::Rect MainBoard::getBorderContour()
{
	return borderContour;
}

cv::Point2i MainBoard::getUpperLeftCorner()
{
	if (minX != NULL && minY != NULL)
		return cv::Point2f(minX, minY);
	else
		return cv::Point2f(0, 0);
}

