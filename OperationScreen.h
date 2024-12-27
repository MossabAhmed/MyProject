#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "GlobalEvent.h"
#include "Event.h"
#include "Movie.h"
#include "Concert.h"
#include "Play.h"
using namespace std;
class OperationScreen : public clsScreen
{

public:

	static void AddEvent(string type)
	{
		string title = "Add New Event";
		_DrawScreenHeader(title);
		if (type == "Movie")
		{
			Movie event;
			globEvent = &event;
		}
		else if (type == "Concert")
		{
			Concert event;
			globEvent = &event;
		}
		else
		{
			Play event;
			globEvent = &event;
		}
		globEvent->AddEvent();

	}
	static void DeleteEvent(string type)
	{

		string title = "Delete Event";
		_DrawScreenHeader(title);
		if (type == "Movie")
		{
			Movie event;
			globEvent = &event;
		}
		else if (type == "Concert")
		{
			Concert event;
			globEvent = &event;
		}
		else
		{
			Play event;
			globEvent = &event;
		}
		cout << "\t\t\t\tenter name of event? ";
		string name = clsInputValidate::ReadString();
		if (globEvent->DeleteEvent(name))
		{
			cout << "\n\t\t\t\tDelete Successfully!";
			Booking::deleteBook(name);
		}
	}
	static void ModifyEvent(string type)
	{

		string title = "Modify Event";
		_DrawScreenHeader(title);
		if (type == "Movie")
		{
			Movie event;
			globEvent = &event;
		}
		else if (type == "Concert")
		{
			Concert event;
			globEvent = &event;
		}
		else
		{
			Play event;
			globEvent = &event;
		}
		globEvent->ModifyEvent();
	}

	static void ShowEvents(string type)
	{
		string title = "Show Event";
		_DrawScreenHeader(title);
		if (type == "Movie")
		{
			Movie event;
			globEvent = &event;
		}
		else if (type == "Concert")
		{
			Concert event;
			globEvent = &event;
		}
		else
		{
			Play event;
			globEvent = &event;
		}
		globEvent->ShowEventList();

	}

};

