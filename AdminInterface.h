#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "OperationScreen.h"
using namespace std;
class AdminInterface : public clsScreen
{

	static void gobacktomeneu()
	{

		cout << "\n\t\t\t\t press any key to continuo...";
		system("pause>0(");
		showtypeEvent();
	}

	static void gobaacktorequiment(string t)
	{
		cout << "\n\t\t\t\t press any key to continuo...";
		system("pause>0(");
		operation(t);
	}


	static void operationmenue()
	{
		cout << "\t\t\t\t========================================================\n";
		cout << "\t\t\t\t[1] Add Event.\n";
		cout << "\t\t\t\t[2] Modify Event.\n";
		cout << "\t\t\t\t[3] Delete Event.\n";
		cout << "\t\t\t\t[4] show Events.\n";
		cout << "\t\t\t\t[5] End Program.\n";

		cout << "\t\t\t\t========================================================\n";
		cout << "\t\t\t\tenter number from [1] to [5]? ";
	}

	static void operation(string type)
	{
		system("cls");
		string title = type + "Screen";
		_DrawScreenHeader(title);
		operationmenue();
		int choice;
		try
		{
			choice = clsInputValidate::ReadIntNumber();
			if (choice < 1 || choice > 5)
				throw "error";
		}
		catch (...)
		{
			cout << "\n\t\t\t\terror, press any key to replay enter...";
			system("pause>0");
		}
		switch (choice)
		{
		case 1:
			system("cls");
			OperationScreen::AddEvent(type);
			gobaacktorequiment(type);
			break;
		case 2:
			system("cls");
			OperationScreen::ModifyEvent(type);
			gobaacktorequiment(type);
			break;
		case 3:
			system("cls");
			OperationScreen::DeleteEvent(type);
			gobaacktorequiment(type);
			break;
		case 4:
			system("cls");
			OperationScreen::ShowEvents(type);
			gobaacktorequiment(type);
			break;
		case 5:
			system("cls");
			gobacktomeneu();
			break;

		default:
			gobacktomeneu();
			break;

		}

	}

public:
	static void showtypeEvent()
	{
		system("cls");
		string title = "Events Screen";
		_DrawScreenHeader(title);
		cout << "\t\t\t\t========================================================\n";
		cout << "\t\t\t\t[1] Movie.\n";
		cout << "\t\t\t\t[2] Concert.\n";
		cout << "\t\t\t\t[3] Play.\n";
		cout << "\t\t\t\t[4] End Program.\n";
		cout << "\t\t\t\t========================================================\n";
		cout << "\t\t\t\tenter number from [1] to [4] ";
		int choice;
		try
		{
			choice = clsInputValidate::ReadIntNumber();
			if (choice < 1 || choice > 4)
				throw "error";
		}
		catch (...)
		{
			cout << "\n\t\t\t\terror, press any key to replay enter...";
			system("pause>0");
			showtypeEvent();
		}
		switch (choice)
		{
		case 1:
			system("cls");
			operation("Movie");
			gobacktomeneu();
			break;
		case 2:
			system("cls");
			operation("Concert");
			gobacktomeneu();
			break;
		case 3:
			system("cls");
			operation("Play");
			gobacktomeneu();
			break;
		case 4:
			return;

		default:
			break;
		}

	}

};

