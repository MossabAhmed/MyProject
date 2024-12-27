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

		cout << "\t\t\t\tenter name of event? ";
		string name = clsInputValidate::ReadString();


		if (type == "Movie")
		{
			if (Booking::moviepurchase(name))
				cout << "\n\t\t\t\t Booking Done!";

		}
		else if (type == "Concert")
		{
			if (Booking::Concertpurchase(name))
				cout << "\n\t\t\t\t Booking Done!";

		}
		else
		{
			if (Booking::Playpurchase(name))
				cout << "\n\t\t\t\t Booking Done!";

		}

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

		cout << "\t\t\t\tenter name of event? ";
		string name = clsInputValidate::ReadString();


		if (type == "Movie")
		{

			if (Booking::CancelMovie(name))
				cout << "\n\t\t\t\tRemove Successfuly!";

		}
		else if (type == "Concert")
		{
			if (Booking::CancelConcert(name))
				cout << "\n\t\t\t\tRemove Successfuly!";

		}
		else
		{
			if (Booking::CancelPlay(name))
				cout << "\n\t\t\t\tRemove Successfuly!";

		}

	}

	static void showBooking()
	{
		system("cls");
		string title = "show all Booking ";
		string sub = globCustomer.getName();
		_DrawScreenHeader(title, sub);
		Booking::ShowBookingList();
	}

	static void showEvent(string type)
	{
		system("cls");
		string title = type + "Screen";
		_DrawScreenHeader(title);
		if (type == "Movie")
		{
			Movie movie;
			movie.ShowEventList();
		}
		else if (type == "Concert")
		{
			Concert concert;
			concert.ShowEventList();
		}
		else
		{
			Play play;
			play.ShowEventList();

		}
	}

	static void PayTicket()
	{
		system("cls");
		string title = "Pay Ticket Screen";
		_DrawScreenHeader(title);
		if (!Booking::ShowBookingList(false))
		{
			cout << "\n\t\t\t\tYou have not book...";
			return;
		}

		cout << "\t\t\t\tenter name of event? ";
		string name = clsInputValidate::ReadString();

		if (Booking::PayTicket(name))
			cout << "\n\t\t\t\tPay Done!";
		else
			cout << "\n\t\t\t\tPay not Done!";
	}
};

