#pragma once
#include<iostream>
#include"SudokuConf.h"

/*
int sud[9][9] = {
{ 0, 0, 0,		0, 0, 0,	0, 0, 0 },
{ 0, 0, 0,		0, 0, 0,	0, 0, 0 },
{ 0, 0, 0,		0, 0, 0,	0, 0, 0 },

{ 0, 0, 0,		0, 0, 0,	0, 0, 0 },
{ 0, 0, 0,		0, 0, 0,	0, 0, 0 },
{ 0, 0, 0,		0, 0, 0,	0, 0, 0 },

{ 0, 0, 0,		0, 0, 0,	0, 0, 0 },
{ 0, 0, 0,		0, 0, 0,	0, 0, 0 },
{ 0, 0, 0,		0, 0, 0,	0, 0, 0 } };*/

class SudokuSolver
{
private:
	
	int board[SUDOKU_SIZE][SUDOKU_SIZE];

	bool solve(int x_cord, int y_cord);
	bool verifyValue(int x_cord, int y_cord);

public:

	SudokuSolver(int sudoku[SUDOKU_SIZE][SUDOKU_SIZE]);
	bool isSolved();
	void getBoard(int sudoku[SUDOKU_SIZE][SUDOKU_SIZE]);

	static void print(int sudoku[SUDOKU_SIZE][SUDOKU_SIZE]);
	
};

