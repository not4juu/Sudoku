#include "SudokuSolver.h"



bool SudokuSolver::solve(int row, int col)
{
	
	if (board[row][col] != EMPTY_VAL)
	{
		if(verifyValue(row, col)) 
		{
			if (row == 8 && col == 8) 
				return true;
			
			int nextRow = row + 1;
			int nextCol = col;


			if (nextRow >= 9) {
				nextRow = 0;
				++nextCol;
			}

			return solve(nextRow, nextCol);
		}
		else
			return false;
	}

	for (int val = 1; val < 10; ++val) {

		board[row][col] = val;

		if (verifyValue(row, col)) 
		{
			if (row == 8 && col == 8) 
				return true;
			
			int nextRow = row + 1;
			int nextCol = col;


			if (nextRow >= 9) {
				nextRow = 0;
				++nextCol;
			}

			if (solve(nextRow, nextCol)) 
				return true;
		}
	}

	board[row][col] = EMPTY_VAL;
	return false;
}

bool SudokuSolver::verifyValue(int row, int col)
{
	int value = board[row][col];

	//Vertical collision
	for (int rowVer = 0; rowVer < 9; ++rowVer)
	{
		if (rowVer == row)
			continue;

		if (board[rowVer][col] == value)
			return false;
	}

	// Horizontal collision
	for (int colVer = 0; colVer<9; ++colVer)
	{
		if (colVer == col)
			continue;
		
		if (board[row][colVer] == value)
			return false;	
	}

	//Box collision
	int rowBox = row / 3; 
	int colBox = col / 3; 

	for (int colVer = colBox * 3; colVer < colBox * 3 + 3; ++colVer)
	{
		for (int rowVer = rowBox * 3; rowVer < rowBox * 3 + 3; ++rowVer)
		{
			if (rowVer == row && colVer == col)
				continue;
					
			if (board[rowVer][colVer] == value)
				return false;
		}
	}
	return true;
}


SudokuSolver::SudokuSolver(int sudoku[SUDOKU_SIZE][SUDOKU_SIZE])
{
	for (int row = 0; row < SUDOKU_SIZE; ++row)
		for (int col = 0; col < SUDOKU_SIZE; ++col)
			board[row][col] = sudoku[row][col];
}

bool SudokuSolver::isSolved()
{
	return solve(0, 0);
}


void SudokuSolver::getBoard(int sudoku[SUDOKU_SIZE][SUDOKU_SIZE])
{
	for (int row = 0; row < SUDOKU_SIZE; ++row)
		for (int col = 0; col < SUDOKU_SIZE; ++col)
			sudoku[row][col] = board[row][col];
}


void SudokuSolver::print(int sudoku[SUDOKU_SIZE][SUDOKU_SIZE])
{
	for (int row = 0; row < SUDOKU_SIZE; ++row)
	{
		for (int col = 0; col < SUDOKU_SIZE; ++col)
		{
			std::cout << sudoku[row][col] << " ";
			if (!((col + 1) % 3))std::cout << " ";
		}
		if (!((row + 1) % 3))std::cout << std::endl;
		std::cout << std::endl;
	}
}
