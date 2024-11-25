#pragma warning(disable : 4996)
#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <ctime>
#include <regex>
using namespace std;
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
			cout << ErrorMessage;
		}
		return Number;
	}

	static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		double Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
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

	static string ReadPassword()
	{
		string S1 = "";
		string message = "";
		bool len = false;
		bool upp = false;
		bool low = false;
		bool dig = false;
		bool spec = false;
		do
		{
			if (message != "")
				cout << "\t\t\t\t" << message;
			getline(cin >> ws, S1);
			message = "error, please try again!";
			if (S1.length() >= 8)
				len = true;
			for (char ch : S1)
			{
				if (isupper(ch))
					upp = true;
				else if (islower(ch))
					low = true;
				else if (isdigit(ch))
					dig = true;
				else if (!isalnum(ch))
					spec = true;
			}
		} while (!(len && upp && low && dig && spec));
		return S1;
	}

	static string ReadName()
	{
		string S1;
		bool len;
		string message = "";
		do
		{
			if (message != "")
				cout << "\t\t\t\t" << message;
			getline(cin >> ws, S1);
			message = "this name is exist, enter another namr? ";
			len = true;
			for (char ch : S1)
			{
				if (!isalpha(ch))
				{
					len = false;
					break;
				}

			}
		} while (!len);
		return S1;
	}

	static string ReadEmail()
	{
		string S1, message = "";
		regex pattern(R"(^[\w-\.]+@([\w-]+\.)+[\w-]{2,4}$)");
		do
		{
			if (message != "")
				cout << "\t\t\t\t" << message;
			getline(cin >> ws, S1);
			message = "invalidate email, please enter again! ";

		} while (!regex_match(S1, pattern));
		return S1;
	}
};
