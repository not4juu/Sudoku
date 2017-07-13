#pragma once

#include "SudokuConf.h"
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include <math.h>

class SmallBox
{
private:
	int value[SUDOKU_SIZE][SUDOKU_SIZE];
	bool existVal[SUDOKU_SIZE][SUDOKU_SIZE];
	cv::Rect rect[SUDOKU_SIZE][SUDOKU_SIZE];

	int rows;
	int cols;

	int width;
	int height;

public:

	SmallBox(int rows, int cols);
	bool pushRect(cv::Rect rectangle, int val);
	void getSudokuBoard(int sudokuBoard[SUDOKU_SIZE][SUDOKU_SIZE], bool existValue[SUDOKU_SIZE][SUDOKU_SIZE]);
	
};

