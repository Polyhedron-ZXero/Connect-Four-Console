// ConnectFour.cpp - Game mainpulation class function implementation
// Written by Qiaoyi Chen

#include "ConnectFour.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
using namespace std;

#define MAX_ROW_SIZE 7
#define MAX_COL_SIZE 10
#define TITLE "\t¨X¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨[\n\t¨U£Ã£ï£î£î£å£ã£ô¡¡£Æ£ï£õ£ò¨U\n\t¨^¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨a\n"
#define BLACK "¡ð"
#define WHITE "¡ñ"
#define WIN "¡ò"
#define SPACE "¡¡"
#define ARROW "¡ý"
#define NORMAL 1
#define POP_OUT 2
#define POP_10 3
#define POP_10_WIN 10
#define SEMITONE_SCALE 1.05946
#define E6_FREQ 1318.510
const string w_numbers[10] = {"£±","£²","£³","£´","£µ","£¶","£·","£¸","£¹","¢º"};

// Init-constructor, initialize the Chessboard size (max Row index and max Column index), and Mode
ConnectFour::ConnectFour(const int &row, const int &column, const int &mode)
{
	Row = row - 1;
	Column = column - 1;
	Mode = mode;
	Turn = White;
	if (Mode != POP_10)
		WhiteScore = BlackScore = -1;
	else
		WhiteScore = BlackScore = 0;
	Initialize();
}

// Initialize Chessboard[][] and Last[]
void ConnectFour::Initialize()
{
	if (Mode != POP_10)
	{
		for (int i = 0; i <= Row; i++)
		{
			for (int j = 0; j <= Column; j++)
			{
				Chessboard[i][j] = None;
				Last[j] = false;
			}
		}
	}

	// Pop 10 initialize: fill the Chessboard with Black and White discs, and sort randomly
	else
	{
		// Use 1D array to fill and sort
		Chess tempArray[MAX_ROW_SIZE * MAX_COL_SIZE];
		int emptySpace = (Row+1) * (Column+1);

		RandomPlace(tempArray, emptySpace);
		// Convert 1D array into 2D array
		for (int i = 0; i < emptySpace; i++)
			Chessboard[i / (Column+1)][i % (Column+1)] = tempArray[i];
		for (int j = 0; j <= Column; j++)
			Last[j] = false;
	}
}

// Fill the targetArray with Chess, and sort randomly
void ConnectFour::RandomPlace(Chess targetArray[], const int &emptySpace) const
{
	// Fill the targetArray
	for (int i = 0; i < emptySpace; i++)
	{
		if (i % 2 == 0)
			targetArray[i] = White;
		else
			targetArray[i] = Black;
	}

	// Sort
	srand(time(0));
	for (int i = 0; i < emptySpace; i++)
	{
		if (emptySpace % 2 != 0)
			Swap(targetArray, i, rand() % (emptySpace - 1));
		else
			Swap(targetArray, i, rand() % emptySpace);
	}
	// When space is odd, insert an empty space and swap to the top row of Chessboard
	if (emptySpace % 2 != 0)
	{
		targetArray[emptySpace - 1] = None;
		Swap(targetArray, emptySpace - 1, rand() % (Column + 1));
	}
}

// Swap two array elements
void ConnectFour::Swap(Chess targetArray[], int i, int j) const
{
    Chess temp = targetArray[i];
    targetArray[i] = targetArray[j];
    targetArray[j] = temp;
}

// Print the current interface and chess board
void ConnectFour::Print() const
{
	system("cls");
	cout << TITLE << endl;
	cout << "\t¡¡¡¡";

	// The row indicates last put-in chess
	for (int i = 0; i <= Column; i++)
	{
		if (!Last[i])
			cout << SPACE;
		else
			cout << ARROW;
	}
	cout << endl;

	// The chessboard
	for (int i = 0; i <= Row; i++)
	{
		cout << "\t¡¡©§";
		for (int j = 0; j <= Column; j++)
		{
			if (Chessboard[i][j] == Black)
				cout << BLACK;
			else if (Chessboard[i][j] == White)
				cout << WHITE;
			else if (Chessboard[i][j] == None)
				cout << SPACE;
			else if (Chessboard[i][j] == Winner)
				cout << WIN;
		}
		cout << "©§\n";
	}
	cout << "\t¡¡©»";
	for (int j = 0; j <= Column; j++)
		cout << "©¥";
	cout << "©¿\n";

	// The column number
	cout << "\t¡¡¡¡";
	for (int j = 0; j <= Column; j++)
		cout << w_numbers[j];
	cout << endl << endl;

	// The turn (and score in POP_10 mode)
	if (WhiteScore == -1 && BlackScore == -1)
	{
		if (Turn == White)
			cout << "©°©¤©¤©¤©¤©´\n©¦¡ñ White©¦\n©¸©¤©¤©¤©¤©¼\n¡¡¡¡ Black\n\n";
		else if (Turn == Black)
			cout << "\n¡¡¡¡ White\n©°©¤©¤©¤©¤©´\n©¦¡ð Black©¦\n©¸©¤©¤©¤©¤©¼\n";
	}
	else
	{
		if (Turn == White)
			cout << "©°©¤©¤©¤©¤©´\n©¦¡ñ White©¦ " << WhiteScore << "\n©¸©¤©¤©¤©¤©¼\n¡¡¡¡ Black¡¡ " << BlackScore << endl << endl;
		else if (Turn == Black)
			cout << "\n¡¡¡¡ White¡¡ " << WhiteScore << "\n©°©¤©¤©¤©¤©´\n©¦¡ð Black©¦ " << BlackScore << "\n©¸©¤©¤©¤©¤©¼\n";
	}

	cout << "©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥\n";
}

// Change private member: Turn
void ConnectFour::ChangeTurn()
{
	if (Turn == White)
		Turn = Black;
	else if (Turn == Black)
		Turn = White;
}

// Get private member: Turn
string ConnectFour::GetTurn() const
{
	if (Turn == Black)
		return "¡ðBlack";
	else if (Turn == White)
		return "¡ñWhite";
}

// Return true if the column is full
bool ConnectFour::FullColumn(const int &column) const
{
	return Chessboard[0][column - 1] != None;
}

// Return true if the column is empty
bool ConnectFour::EmptyColumn(const int &column) const
{
	return Chessboard[Row][column - 1] == None;
}

// Return true if the whole Chessboard is full (!= None)
bool ConnectFour::Full() const
{
	bool full = false;
	for (int i = 0; i <= Column; i++)
	{
		if (!FullColumn(i + 1))
			return false;
	}
	return true;
}

// Return true if bottommost disc's color of column matches current Turn 
bool ConnectFour::ColorMatch(const int &column) const
{
	return Chessboard[Row][column - 1] == Turn;
}

// Push a disc from the top into column
void ConnectFour::Push(const int &column)
{
	int row = Row;
	while (Chessboard[row][column - 1] != None)
		row--;
	Chessboard[row][column - 1] = Turn;

	// Change the arrow position which indicates the last action
	for (int j = 0; j <= Column ; j++)
	{
		if (j != column - 1)
			Last[j] = false;
		else
			Last[j] = true;
	}
}

// Pop a disc from the bottom of column
void ConnectFour::Pop(const int &column)
{
	for (int i = 0; i < Row; i++)
		Chessboard[Row - i][column - 1] = Chessboard[Row - i - 1][column - 1];
	Chessboard[0][column - 1] = None;

	// Change the arrow position which indicates the last action
	for (int j = 0; j <= Column ; j++)
	{
		if (j != column - 1)
			Last[j] = false;
		else
			Last[j] = true;
	}
}

// Return true if there are four discs connected
// Change the connected four discs to Winner
bool ConnectFour::Win()
{
	// NORMAL and POP_OUT: Check connect four
	if (Mode != POP_10)
	{
		// Horizontal
		for (int i = 0; i <= Row; i++)
		{
			for (int j = 0; j <= Column - 3; j++)
			{
				if (Chessboard[i][j] != None)
					if (Chessboard[i][j] == Chessboard[i][j + 1])
						if (Chessboard[i][j + 1] == Chessboard[i][j + 2])
							if (Chessboard[i][j + 2] == Chessboard[i][j + 3])
							{
								Chessboard[i][j] = Chessboard[i][j + 1] = Chessboard[i][j + 2] = Chessboard[i][j + 3] = Winner; 
								return true;
							}
			}
		}

		// Vertical
		for (int i = 0; i <= Row - 3; i++)
		{
			for (int j = 0; j <= Column; j++)
			{
				if (Chessboard[i][j] != None)
					if (Chessboard[i][j] == Chessboard[i + 1][j])
						if (Chessboard[i + 1][j] == Chessboard[i + 2][j])
							if (Chessboard[i + 2][j] == Chessboard[i + 3][j])
							{
								Chessboard[i][j] = Chessboard[i + 1][j] = Chessboard[i + 2][j] = Chessboard[i + 3][j] = Winner; 
								return true;
							}
			}
		}

		// Diagonal
		for (int i = 0; i <= Row - 3; i++)
		{
			for (int j = 0; j <= Column - 3; j++)
			{
				if (Chessboard[i][j] != None)
				{
					// Top-left to bottom-right
					if (Chessboard[i][j] == Chessboard[i + 1][j + 1])
						if (Chessboard[i + 1][j + 1] == Chessboard[i + 2][j + 2])
							if (Chessboard[i + 2][j + 2] == Chessboard[i + 3][j + 3])
							{
								Chessboard[i][j] = Chessboard[i + 1][j + 1] = Chessboard[i + 2][j + 2] = Chessboard[i + 3][j + 3] = Winner; 
								return true;
							}
				}
				if (Chessboard[Row - i][j] != None)
				{
					// Bottom-left to top-right
					if (Chessboard[Row - i][j] == Chessboard[Row - i - 1][j + 1])
						if (Chessboard[Row - i - 1][j + 1] == Chessboard[Row - i - 2][j + 2])
							if (Chessboard[Row - i - 2][j + 2] == Chessboard[Row - i - 3][j + 3])
							{
								Chessboard[Row - i][j] = Chessboard[Row - i - 1][j + 1] = Chessboard[Row - i - 2][j + 2] = Chessboard[Row - i - 3][j + 3] = Winner; 
								return true;
							}
				}
			}
		}
		return false;
	}
	// POP_10: Check Score == 10 (POP_10_WIN);
	else
	{
		if (WhiteScore == POP_10_WIN || BlackScore == POP_10_WIN)
			return true;
		else
			return false;
	}
}

// Return true if the bottommost disc of column is part of a connect four
bool ConnectFour::PartOfFour(const int &column) const
{
	// Vertical
	if (Chessboard[Row][column - 1] == Chessboard[Row - 1][column - 1])
		if (Chessboard[Row - 1][column - 1] == Chessboard[Row - 2][column - 1])
			if (Chessboard[Row - 2][column - 1] == Chessboard[Row - 3][column - 1])
				return true;

	// Diagonal (bottom-left to top-right)
	if (column - 1 <= Column - 3)
		if (Chessboard[Row][column - 1] == Chessboard[Row - 1][column])
			if (Chessboard[Row - 1][column] == Chessboard[Row - 2][column + 1])
				if (Chessboard[Row - 2][column + 1] == Chessboard[Row - 3][column + 2])
					return true;

	// Diagonal (bottom-right to top-left)
	if (column - 1 >= 3)
		if (Chessboard[Row][column - 1] == Chessboard[Row - 1][column - 2])
			if (Chessboard[Row - 1][column - 2] == Chessboard[Row - 2][column - 3])
				if (Chessboard[Row - 2][column - 3] == Chessboard[Row - 3][column - 4])
					return true;

	// Horizontal
	int leftCount = 0, rightCount = 0;
	// Left
	if (column - 2 >= 0 && Chessboard[Row][column - 1] == Chessboard[Row][column - 2])
	{
		leftCount++;
		if (column - 3 >= 0 && Chessboard[Row][column - 2] == Chessboard[Row][column - 3])
		{
			leftCount++;
			if (column - 4 >= 0 && Chessboard[Row][column - 3] == Chessboard[Row][column - 4])
				leftCount++;
		}
	}
	// Right
	if (column <= Column && Chessboard[Row][column - 1] == Chessboard[Row][column])
	{
		rightCount++;
		if (column + 1 <= Column && Chessboard[Row][column] == Chessboard[Row][column + 1])
		{
			rightCount++;
			if (column + 2 <= Column && Chessboard[Row][column + 1] == Chessboard[Row][column + 2])
				rightCount++;
		}
	}
	// Add up
	if (leftCount + rightCount >= 3)
		return true;
	else
		return false;
}

// Return true if the discs in the bottommost line are all opponent's color
bool ConnectFour::PopNotAvailable() const
{
	bool notAvailable = true;
	for (int i = 0; i <= Column; i++)
	{
		if (Chessboard[Row][i] == Turn)
			notAvailable = false;
	}
	return notAvailable;
}

// Increment the count by 1 and play sound (frequency according to score)
void ConnectFour::IncrementBlackScore()
{
	BlackScore++;
	Beep(E6_FREQ * pow(SEMITONE_SCALE, BlackScore), 300);
}
void ConnectFour::IncrementWhiteScore()
{
	WhiteScore++;
	Beep(E6_FREQ * pow(SEMITONE_SCALE, WhiteScore), 300);
}