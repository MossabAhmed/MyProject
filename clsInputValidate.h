#pragma warning(disable : 4996)
#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <ctime>

class clsInputValidate
{

public:
	 
	static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		int Number;
		while (!(cin >> Number)) 
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\t\t\t\t" << ErrorMessage;
		}
		return Number;
	}

	static double ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		float Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\t\t\t\t" << ErrorMessage;
		}
		return Number;
	}

	static string Datetime()
	{
		time_t now = time(0);
		tm* t = localtime(&now);
		string date = to_string(t->tm_mday) + '/' + to_string(t->tm_mon + 1) + '/' + to_string(t->tm_year + 1900);
		return date;
	}

	static string ReadString()
	{
		string  S1 = "";
		getline(cin >> ws, S1);
		return S1;
	}
};
