// main.cpp - Connect Four game main function
// Written by Qiaoyi Chen

/* This program uses Unicode characters, 
   please make sure that the operating system supports 
   code page 936 (GB2312 - ANSI/OEM Simplified Chinese)
   in order to display the Unicode characters properly. */

#include "ConnectFour.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <clocale>
using namespace std;

#define TITLE "\t¨X¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨[\n\t¨U£Ã£ï£î£î£å£ã£ô¡¡£Æ£ï£õ£ò¨U\n\t¨^¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨a\n"
#define UNKNOWN 0
#define MENU 0
#define PLAY 1
#define HELP 2
#define EXIT 3
#define NORMAL 1
#define POP_OUT 2
#define POP_10 3
#define SIZE_7x6 1
#define SIZE_8x7 2
#define SIZE_9x7 3
#define SIZE_10x7 4
const float D_MAJOR_CHORD[5] = {880.000, 1174.659, 1479.978, 1760.000, 2349.318};

// Print out an error message temporarily, reset and clear keyboard buffer
void DisplayError(const string &error);

// Print out game instructions and explanations
void DisplayHelp();

void main()
{
	setlocale(LC_ALL, "chs");

	int status = MENU;
	string command;
	bool exit = false;

	while (!exit)
	{
		switch (status)
		{
		case MENU: // Game menu screen
			{
menu:
				status = MENU;
				system("cls");
				while (status != PLAY && status != HELP && status != EXIT)
				{
					cout << TITLE << endl;
					cout << "\t\t[1] Play\n\n\t\t[2] Help\n\n\t\t[3] Exit\n\n©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥\n";
					cout << "Choose an option:\n";
					cin >> status;
					if (status != PLAY && status != HELP && status != EXIT)
						DisplayError("\aInvalid input!");
				}
				break;
			}
		case PLAY: // Game playing screen
			{
				int mode = UNKNOWN;
				int boardSize = UNKNOWN;
				int row = UNKNOWN;
				int column = UNKNOWN;
				system("cls");

				// Choose game mode
				while (mode != NORMAL && mode != POP_OUT && mode != POP_10)
				{
					cout << TITLE << endl;
					cout << "Choose game mode:\n\n";
					cout << "\t\t[1] Normal\n\n\t\t[2] Pop Out\n\n\t\t[3] Pop 10\n\n©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥\n";
					cout << "Choose an option:\n";
					cin >> mode;
					
					if (mode == 0)
					{
						cin >> command;
						if (command == "exit")
							goto menu;
					}

					if (mode != NORMAL && mode != POP_OUT && mode != POP_10)
						DisplayError("\aInvalid input!");
				}
				system("cls");

				// Choose board size
				while (boardSize != SIZE_7x6 && boardSize != SIZE_8x7 && boardSize != SIZE_9x7 && boardSize != SIZE_10x7)
				{
					cout << TITLE << endl;
					cout << "Choose board size:\n\n";
					cout << "\t\t[1] 7 x 6\n\n\t\t[2] 8 x 7\n\n\t\t[3] 9 x 7\n\n\t\t[4] 10 x 7\n\n©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥\n";
					cout << "Choose an option:\n";
					cin >> boardSize;

					if (boardSize == 0)
					{
						cin >> command;
						if (command == "exit")
							goto menu;
					}

					if (boardSize == SIZE_7x6)
					{
						row = 6;
						column = 7;
					}
					else if (boardSize == SIZE_8x7)
					{
						row = 7;
						column = 8;
					}
					else if (boardSize == SIZE_9x7)
					{
						row = 7;
						column = 9;
					}
					else if (boardSize == SIZE_10x7)
					{
						row = 7;
						column = 10;
					}
					else
						DisplayError("\aInvalid input!");
				}
				system("cls");

				while (status == PLAY)
				{
restart:
					if (mode != POP_10) // Begin: normal & pop out
					{
						// Initialize game
						ConnectFour game(row, column, mode);
						bool win = false, draw = false;
						int dropDisc = UNKNOWN;

						while (!win)
						{
							// Display interface and detect input error
							while (dropDisc == UNKNOWN)
							{
								game.Print();
								// Normal mode
								if (mode == NORMAL)
								{
									cout << "Enter column number:\n";
									cin >> dropDisc;

									if (dropDisc == 0)
									{
										cin >> command;
										if (command == "restart")
											goto restart;
										if (command == "exit")
											goto menu;
									}

									if (dropDisc < 1 || dropDisc > column)
									{
										DisplayError("\aInvalid column number!");
										dropDisc = UNKNOWN;
									}
									else if (game.FullColumn(dropDisc))
									{
										DisplayError("\aThis column is full!");
										dropDisc = UNKNOWN;
									}
								}
								// Pop out mode
								else if (mode == POP_OUT)
								{
									cout << "Enter column number to drop, or negative column number to pop:\n";
									cin >> dropDisc;

									if (dropDisc == 0)
									{
										cin >> command;
										if (command == "restart")
											goto restart;
										if (command == "exit")
											goto menu;
									}

									if (dropDisc > 0)
									{
										if (dropDisc > column)
										{
											DisplayError("\aInvalid column number!");
											dropDisc = UNKNOWN;
										}
										else if (game.FullColumn(dropDisc))
										{
											DisplayError("\aThis column is full!");
											dropDisc = UNKNOWN;
										}
									}
									else
									{
										if (dropDisc == 0 || dropDisc < 0 - column)
										{
											DisplayError("\aInvalid column number!");
											dropDisc = UNKNOWN;
										}
										else if (game.EmptyColumn(0 - dropDisc))
										{
											DisplayError("\aThis column is empty!");
											dropDisc = UNKNOWN;
										}
										else if (!game.ColorMatch(0 - dropDisc))
										{
											DisplayError("\aYou can only pop disc of your own color!");
											dropDisc = UNKNOWN;
										}
									}
								}
							}

							// Store a disc into chessboard to the top
							if (mode == NORMAL || (mode == POP_OUT && dropDisc > 0))
								game.Push(dropDisc);
							// Pop out a disc from chessboard from the bottom
							else if (mode == POP_OUT && dropDisc < 0)
								game.Pop(0 - dropDisc);

							// Check if anyone wins or draw
							if (game.Win())
								win = true;
							else if (game.Full())
							{
								win = true;
								draw = true;
							}
							else
							{
								game.ChangeTurn();
								dropDisc = UNKNOWN;
							}
						} // End: while (!win)

						// Win or draw, game over
						status = EXIT;
						bool sound = true;
						while (status != MENU && status != PLAY)
						{
							
							game.Print();
							if (!draw)
								cout << " ***** Congratulations! " << game.GetTurn() << " wins! *****\n©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥\n";
							else
								cout << " *****             Draw!             *****\n©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥\n";
							
							// D Major arpeggio (V-I cadence)
							if (sound)
							{
								Beep(D_MAJOR_CHORD[0], 200);
								Beep(D_MAJOR_CHORD[1], 200);
								Beep(D_MAJOR_CHORD[2], 200);
								Beep(D_MAJOR_CHORD[3], 200);
								Beep(D_MAJOR_CHORD[4], 500);
								sound = false;
							}
							cout << "\rChoose an option: [1] Play again  [2] Exit to menu\n";
							cin >> status;
							if (status == 1)
								status = PLAY;
							else if (status == 2)
								status = MENU;
							else
							{
								DisplayError("\aInvalid input!");
								status = EXIT;
							}
						}
					} // End: normal & pop out

					else // Being: pop 10
					{
						ConnectFour game(row, column, mode);
						bool win = false;
						bool drop = false; // If drop == true, popDisc means dropDisc
						int popDisc = UNKNOWN;
						
						while (!win)
						{
							// If the discs in the bottommost line are all opponent's color
							if (game.PopNotAvailable() && drop == false)
							{
								cout << game.GetTurn() << "\a cannot pop!";
								Sleep(1500);
								game.ChangeTurn();
							}
							else
							{
								while (popDisc == UNKNOWN)
								{
									game.Print();
									if (!drop)
									{
										cout << "Enter column number to pop a disc:\n";
										cin >> popDisc;

										if (popDisc == 0)
										{
											cin >> command;
											if (command == "restart")
												goto restart;
											if (command == "exit")
												goto menu;
										}

										if (popDisc < 1 || popDisc > column)
										{
											DisplayError("\aInvalid column number!");
											popDisc = UNKNOWN;
										}
										else if (game.EmptyColumn(popDisc))
										{
											DisplayError("\aThis column is empty!");
											popDisc = UNKNOWN;
										}
										else if (!game.ColorMatch(popDisc))
										{
											DisplayError("\aYou can only pop disc of your own color!");
											popDisc = UNKNOWN;
										}
									}
									else
									{
										cout << "Put the disc back into a column:\n";
										cin >> popDisc;

										if (popDisc == 0)
										{
											cin >> command;
											if (command == "restart")
												goto restart;
											if (command == "exit")
												goto menu;
										}

										if (popDisc < 1 || popDisc > column)
										{
											DisplayError("\aInvalid column number!");
											popDisc = UNKNOWN;
										}
										else if (game.FullColumn(popDisc))
										{
											DisplayError("\aThis column is full!");
											popDisc = UNKNOWN;
										}
									}	
								}

								// Pop time
								if (!drop)
								{
									// Pop from a connect-four, add 1 score and continue (not change turn)
									if (game.PartOfFour(popDisc))
									{
										game.Pop(popDisc);
										cout << game.GetTurn() << " scores a point!\n";
										if (game.GetTurn() == "¡ðBlack")
											game.IncrementBlackScore();
										else
											game.IncrementWhiteScore();
										Sleep(1000);

										// Check winner
										if (game.Win())
											win = true;
										else
											popDisc = UNKNOWN;
									}
									// Else, pop and go to drop
									else
									{
										game.Pop(popDisc);
										drop = true;
										popDisc = UNKNOWN;
									}
								}
								// Drop time
								else
								{
									game.Push(popDisc);
									game.ChangeTurn();
									popDisc = UNKNOWN;
									drop = false;
								}
							}// End: if (game.PopNotAvailable())
						} // End: while (!win)

						status = EXIT;
						bool sound = true;
						while (status != MENU && status != PLAY)
						{
							game.Print();
							cout << " ***** Congratulations! " << game.GetTurn() << " wins! *****\n©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥\n";

							// D Major arpeggio (V-I cadence)
							if (sound)
							{
								Beep(D_MAJOR_CHORD[0], 200);
								Beep(D_MAJOR_CHORD[1], 200);
								Beep(D_MAJOR_CHORD[2], 200);
								Beep(D_MAJOR_CHORD[3], 200);
								Beep(D_MAJOR_CHORD[4], 500);
								sound = false;
							}
							cout << "\rChoose an option: [1] Play again  [2] Exit to menu\n";
							cin >> status;
							if (status == 1)
								status = PLAY;
							else if (status == 2)
								status = MENU;
							else
							{
								DisplayError("\aInvalid input!");
								status = EXIT;
							}
						}
					} // End: pop 10
				} // End: while (status == PLAY)
				break;
			}
		case HELP: // Help screen
			{
				DisplayHelp();
				status = MENU;
				break;
			}
		case EXIT: // Exit
			{
				exit = true;
				system("cls");
				cout << "Bye!";
				Sleep(1500);
				break;
			}
		}
	} // End: while (!exit)
}