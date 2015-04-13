// ConnectFour.h - Game mainpulation class
// Written by Qiaoyi Chen

#pragma once
#include <string>
using std::string;

#define MAX_ROW_SIZE 7
#define MAX_COL_SIZE 10

enum Chess {Black, White, None, Winner};

class ConnectFour
{
private:
	Chess Chessboard[MAX_ROW_SIZE][MAX_COL_SIZE];
	bool Last[MAX_COL_SIZE]; // Indicates the last action
	int Row; // Max row index
	int Column; // Max column index
	int Mode;
	Chess Turn; // Indicates whose turn
	int WhiteScore; // Score in Pop 10 mode
	int BlackScore; // Score in Pop 10 mode

	// Initialize ChessBoard[][] and Last[]
	void Initialize();

	// Fill the targetArray with Chess, and sort randomly
	void RandomPlace(Chess targetArray[], const int &emptySpace) const;

	// Swap two array elements
	void Swap(Chess targetArray[], int i, int j) const;

public:
	// Init-constructor, initialize the Chessboard size (max Row index and max Column index), and Mode
	ConnectFour(const int &row, const int &column, const int &mode);

	// Print the current interface and chess board
	void Print() const;

	// Change private member: Turn
	void ChangeTurn();

	// Get private member: Turn
	string GetTurn() const;

	// Return true if the column is full
	bool FullColumn(const int &column) const;

	// Return true if the column is empty
	bool EmptyColumn(const int &column) const;

	// Return true if the whole Chessboard is full (!= None)
	bool Full() const;

	// Return true if bottommost disc's color of column matches current Turn 
	bool ColorMatch(const int &column) const;

	// Push a disc from the top into column
	void Push(const int &column);

	// Pop a disc from the bottom of column
	void Pop(const int &column);

	// Return true if there are four discs connected
	// Change the connected four discs to Winner
	bool Win();

	// Return true if the bottommost disc of column is part of a connect four
	bool PartOfFour(const int &column) const;

	// Return true if the discs in the bottommost line are all opponent's color
	bool PopNotAvailable() const;

	// Increment the count by 1 and play sound (frequency according to score)
	void IncrementBlackScore();
	void IncrementWhiteScore();
};