#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/ml/ml.hpp>

#include<iostream>
#include<sstream>

#include "MainBoard.h"
#include "SudokuSolver.h"
#include "OCR.h"
#include "SmallBox.h"
#include "SudokuConf.h"



using namespace std;
using namespace cv;


int main() 
{
#ifdef TIME_MEASURMENT
	chrono::milliseconds startTime = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch());
#endif 


	//Upload the main imgae
	cv::String imgPath = "sudokuImg/3.jpg";
	cv::Mat src = cv::imread(imgPath);
	if (src.empty())
	{
		std::cout << "Image dose not exist " << imgPath << std::endl;
		return -1;
	}
	cv::imshow("Source img "+ std::to_string(src.cols) + ":" + std::to_string(src.rows), src);


	//Find the main sudoku board
	MainBoard board(src);
	cv::Mat mainBoard = board.getBoard();
	if ((mainBoard.rows * mainBoard.cols) < 1)
	{
		std::cout << "NO MIAN BOARD" << std::endl;
		cv::waitKey(0);
		return -1;
	}
	
#ifdef DEBUG
	cv::imshow("Main Board " + std::to_string(mainBoard.cols) + ":" + std::to_string(mainBoard.rows), mainBoard);
#endif
	
	//Draw main board frame 
	cv::Rect boardContour = board.getBorderContour();
	cv::rectangle(src, boardContour, cv::Scalar(0, 255, 0), 1);



	//Preaper image with morphological operations
	// there in threshold we can manipulate values to get as good as possible results 
	cv::Mat grey, thr, cdst;
	cv::cvtColor(mainBoard, grey, CV_BGR2GRAY);
	threshold(grey, thr, 70, 255, cv::THRESH_BINARY_INV);
	cvtColor(thr, cdst, CV_GRAY2BGR);

#ifdef DEBUG
	cv::imshow("Morphological operations : " + std::to_string(cdst.cols) + ":" + std::to_string(cdst.rows), cdst);
#endif
	
	//Delete main lines from sudoku - after it we should recevie only sudoku digits
	// there in HoughLinesP we can manipulate values to get as good as possible results 
	vector<Vec4i> lines;
	HoughLinesP(thr, lines, 1, CV_PI / 180, 20, 100, 5);

	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 0), 3, CV_AA);
	}
	bitwise_not(cdst, cdst);

#ifdef DEBUG
	cv::Mat test = cdst.clone();
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(test, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
	}
	cv::imshow("Deleted detected lines : " + std::to_string(test.cols) + ":" + std::to_string(test.rows), test);
	cv::imshow("Deleted detected lines orgin : " + std::to_string(cdst.cols) + ":" + std::to_string(cdst.rows), cdst);
#endif
	

	//Run OCR algorithm
	OCR ocr;
	ocr.run(cdst);

	std::vector<ContourWithData> rectData;
	std::vector<char> allChars;
	ocr.getData(rectData, allChars);

	
	//Search all small boxes at the mian board
	SmallBox allSmallBoxes(grey.rows, grey.cols);
	for (int i = 0; i < rectData.size(); i++)
	{
		bool decision = allSmallBoxes.pushRect(rectData[i].boundingRect, (int)allChars[i] - 48);
		if (!decision)
		{
			std::cout << "Error during pushing deteced digits" << std::endl;
			cv::waitKey(0);
			return -1;
		}
	}

	int sudoku[SUDOKU_SIZE][SUDOKU_SIZE] = {};
	bool existValue[SUDOKU_SIZE][SUDOKU_SIZE] = {};
	allSmallBoxes.getSudokuBoard(sudoku, existValue);


	//Run sudoku solver algorithm
	std::cout << std::endl;
	SudokuSolver::print(sudoku);
	int result[SUDOKU_SIZE][SUDOKU_SIZE] = {};
	SudokuSolver sudokuSolver(sudoku);
	std::cout << "-----------------------"<<std::endl;
	if (sudokuSolver.isSolved() == true)
	{
		sudokuSolver.getBoard(result);
		SudokuSolver::print(result);
	}
	else
	{
		printf("No solution exists for this sudoku");
		cv::waitKey(0);
		return -1;
	}

	
	//Insert sudoku solution into source image
	int width = floor(grey.rows / SUDOKU_SIZE);
	int height = floor(grey.cols / SUDOKU_SIZE);

	int smallWidthMove = floor(width / 3.0);
	int smallHeightMove = floor(height / 4.0);
	
	cv::Point2i upperLeftCorner = board.getUpperLeftCorner();


#ifdef DEBUG
	DEBUG_LOG("Matching to values " << width << " " << height << " shift" << smallWidthMove << " " << smallHeightMove << " upperLeftCorner " << upperLeftCorner.x << " " << upperLeftCorner.y << std::endl);
#endif


	for (int i = 0; i < SUDOKU_SIZE; ++i)
		for (int j = 0; j < SUDOKU_SIZE; ++j)
		{
			if (!existValue[i][j])
				cv::putText(src, std::to_string(result[i][j]), Point2i(j*width + smallWidthMove + upperLeftCorner.x, i*height + height - smallHeightMove + upperLeftCorner.y), cv::FONT_HERSHEY_TRIPLEX, 1, cv::Scalar(255,0, 0), 2);		
		}
		
#ifdef TIME_MEASURMENT
	std::cout << "TIME_MEASURMENT (milliseconds): " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch() - startTime).count() << std::endl;
#endif 


	//MAIN RESULT
	cv::imshow("Result : "+ std::to_string(src.cols) + ":" + std::to_string(src.rows), src);


	cv::waitKey(0);
	return(0);
}

