#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "Booking.h"

using namespace std;

class RequimentScreen : public clsScreen
{
public:
	static void Purchase(string type)
	{
		system("cls");
		string title = "Purchase Screen";
		_DrawScreenHeader(title);


		if (type == "Movie")
		{
			Booking::moviepurchase();
		}
		else if (type == "Concert")
		{
			Booking::Concertpurchase();
		}
		else
		{
			Booking::Playpurchase();
		}
		cout << "\n\t\t\t\t Booking Done!";

	}

	static void Cancellation(string type)
	{
		system("cls");
		string title = "Cancellation Screen";
		_DrawScreenHeader(title);
		if (!Booking::ShowBookingList())
		{
			cout << "\n\t\t\t\tYou have not book...";
			return;
		}

		if (type == "Movie")
		{

			Booking::CancelMovie();
		}
		else if (type == "Concert")
		{
			Booking::CancelConcert();
		}
		else
		{
			Booking::CancelPlay();
		}
		cout << "\n\t\t\t\tRemove Successfuly!";

	}

	static void showBooking()
	{
		system("cls");
		string title = "show all Booking ";
		string sub = globCustomer.getName();
		_DrawScreenHeader(title, sub);
		Booking::ShowBookingList();
	}
};

