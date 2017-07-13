#pragma once

#include "ContourWithData.h"
#include "SudokuConf.h"
#include<opencv2/ml/ml.hpp>

class OCR
{

private:
	std::vector<ContourWithData> allContoursWithData;          
	std::vector<ContourWithData> validContoursWithData;
	std::vector<char> allFoundChars;

	cv::Mat matClassificationInts;
	cv::Mat matTrainingImagesAsFlattenedFloats;

	int RESIZED_IMAGE_WIDTH = 20;
	int RESIZED_IMAGE_HEIGHT = 30;

public:
	void run(cv::Mat ocrImg);
	void getData(std::vector<ContourWithData> &getAllContours, std::vector<char> &allChars);

};

