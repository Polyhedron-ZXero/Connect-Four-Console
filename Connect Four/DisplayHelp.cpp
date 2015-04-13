// DisplayHelp.cpp - Print out game instructions and explanations
// Written by Qiaoyi Chen

#include <iostream>
using namespace std;

#define TITLE "\t¨X¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨[\n\t¨U£Ã£ï£î£î£å£ã£ô¡¡£Æ£ï£õ£ò¨U\n\t¨^¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨a\n"
#define UNKNOWN 0
#define WIKIPEDIA 1
#define CONTROL 2
#define EXIT 3

// Print out an error message temporarily, reset and clear keyboard buffer
void DisplayError(const string &error);

void DisplayHelp()
{
	bool exit = false;
	int option = UNKNOWN;

	while (!exit)
	{
		while (option != EXIT)
		{
			system("cls");
			cout << TITLE << "\t¡¾Developed by Qiaoyi Chen¡¿\n\n";
			cout << "Connect Four is a two-player chess game which wins\nby connecting four discs of the same color next to\neach other vertically, horizontally, or diagonally.\n\n";
			cout << "©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥\n";
			cout << "There are 3 game modes: Normal, Pop Out, Pop 10\nIf you want to know more,\nchoose the options below:\n\n";
			cout << "\t[1] See details of the rules on Wikipedia\n\n\t[2] Controls & commands\n\n\t[3] Go back to menu\n\n©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥\n";
			cout << "Choose an option:\n";
			cin >> option;

			if (option == WIKIPEDIA)
				system("explorer http://en.wikipedia.org/wiki/Connect_Four");
			else if (option == CONTROL)
			{
				system("cls");
				cout << TITLE << endl;
				cout << "¡ñ: white chess (disc)\n";
				cout << "¡ð: black chess (disc)\n";
				cout << "¡ý: indicates the column where last action takes place\n\n";
				cout << "General control:\nTo drop a disc from the top, enter a column number and press \"Enter\"\n\n";
				cout << "Pop Out mode:\nTo pop out a disc from the bottom, enter a negative sign \"-\" before\nthe column number and press \"Enter\"\n\n\n";
				cout << "Special commands\n©¥©¥©¥©¥©¥©¥©¥©¥\nType \"0\" followed by commands:\n\n";
				cout << "\"exit\" - Exit to the menu immediately\n\"restart\" - Restart a game immediately during game playing\n\n";
				cout << "\t\t\t\t\t\tPress \"Enter\" to continue ...";
				
				cin.ignore();
				cin.get();
				cin.sync();
				option = UNKNOWN;
			}
			else if (option == EXIT)
				exit = true;
			else
				DisplayError("\aInvalid input!");
		}

	}
}