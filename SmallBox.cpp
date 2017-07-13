#include "SmallBox.h"


SmallBox::SmallBox(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;

	for(int i = 0; i < SUDOKU_SIZE ; ++i)
		for (int j = 0; j < SUDOKU_SIZE; ++j)
		{
			value[i][j] = EMPTY_VAL;
			existVal[i][j] = EMPTY_VAL;
		}

	width = floor(rows / SUDOKU_SIZE);
	height = floor(cols / SUDOKU_SIZE);


	for (int i = 0; i < SUDOKU_SIZE; ++i)
		for (int j = 0; j < SUDOKU_SIZE; ++j)
			rect[i][j] = cv::Rect(i * width ,j * height, width * i + width, height * j + height);
	
	
#ifdef DEBUG
	DEBUG_LOG("SmallBox::Constructor : small box size " << width << " " << height);
	cv::Mat test(rows, cols, CV_8UC3);
	cv::RNG rng(12345);
	for (int i = 0; i < SUDOKU_SIZE; ++i)
		for (int j = 0; j < SUDOKU_SIZE; ++j)
			cv::rectangle(test, rect[i][j], cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), CV_FILLED);
	cv::imshow("SmallBox::Constructor : detected small boxes", test);
#endif
	
}

bool SmallBox::pushRect(cv::Rect rectangle, int val)
{
	int foundRow=-1, foundCol= -1;

	for (int range = 0; range < SUDOKU_SIZE; ++range)
	{
		if (rectangle.y >= range * height && rectangle.y <= range * height + height)
			foundRow = range;

		if (rectangle.x >= range * width && rectangle.x <= range * width + width)
			foundCol = range;
	}

	if (foundRow == -1 || foundCol == -1)
		return false;

	value[foundRow][foundCol] = val;
	existVal[foundRow][foundCol] = true;

#ifdef DEBUG
	DEBUG_LOG("SmallBox::pushRect : " << foundRow << " " << foundCol );
#endif

	return true;
}

void SmallBox::getSudokuBoard(int sudokuBoard[SUDOKU_SIZE][SUDOKU_SIZE], bool existValue[SUDOKU_SIZE][SUDOKU_SIZE])
{
	for (int i = 0; i < SUDOKU_SIZE; ++i)
		for (int j = 0; j < SUDOKU_SIZE; ++j)
		{
			sudokuBoard[i][j] = value[i][j];
			existValue[i][j] = existVal[i][j];
 		}
}


