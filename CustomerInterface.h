#pragma once
#include <iostream>
#include "clsScreen.h"
#include "RequimentScreen.h"
using namespace std;
class CustomerInterface : public clsScreen
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
		Requiment(t);
	}

	static void RequimentMenue()
	{
		cout << "\n\t\t\t\t========================================================\n";
		cout << "\t\t\t\t[1] Purchase Ticket.\n";
		cout << "\t\t\t\t[2] Cancel Booking.\n";
		cout << "\t\t\t\t[3] Show All Bookings.\n";
		cout << "\t\t\t\t[4] Events Screen.\n";
		cout << "\t\t\t\t========================================================\n";
		cout << "\t\t\t\tenter number from [1] to [4]? ";
	}

	static void Requiment(string type)
	{
		system("cls");
		string title = type + "Screen";
		_DrawScreenHeader(title);
		RequimentMenue();
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
		}
		switch (choice)
		{
		case 1:
			system("cls");
			RequimentScreen::Purchase(type);
			gobaacktorequiment(type);
			break;
		case 2:
			system("cls");
			RequimentScreen::Cancellation(type);
			gobaacktorequiment(type);
			break;
		case 3:
			system("cls");
			RequimentScreen::showBooking();
			gobaacktorequiment(type);
			break;
		case 4:
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
			Requiment("Movie");
			gobacktomeneu();
			break;
		case 2:
			system("cls");
			Requiment("Concert");
			gobacktomeneu();
			break;
		case 3:
			system("cls");
			Requiment("Play");
			gobacktomeneu();
			break;
		case 4:
			return;

		default:
			break;
		}

	}
};

