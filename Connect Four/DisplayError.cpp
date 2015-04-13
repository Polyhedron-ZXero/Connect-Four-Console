// DisplayError.cpp - Print out an error message temporarily, reset and clear keyboard buffer
// Written by Qiaoyi Chen

#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;

void DisplayError(const string &error)
{
	cout << error;
	cin.clear();
	cin.sync();
	Sleep(1200);
	system("cls");
}