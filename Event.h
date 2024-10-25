#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream>
using namespace std;


class Event
{
	string _EventType;
	string _Name;
	string _Location;
	string _TimeDate;
	int _TotalTickets;
	int _TotalSeats;

	static Event _ConvertLinetoEventObject(string Line, string Seperator = "#//#")
	{
		vector<string> vEventData;
		vEventData = clsString::Split(Line, Seperator);

		return Event(vEventData[0], vEventData[1], vEventData[2],
			vEventData[3], stoi(vEventData[4]), stoi(vEventData[5]));

	}

	static  vector <Event> _LoadEventDataFromFile()
	{

		vector <Event> vEvent;

		fstream MyFile;
		MyFile.open("Event.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				Event event = _ConvertLinetoEventObject(Line);

				vEvent.push_back(event);
			}

			MyFile.close();

		}

		return vEvent;

	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Event.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}
public:

	Event(string eventType, string name, string location, string date, int totalTickets, int totalSeats)
	{
		_EventType = eventType;
		_Name = name;
		_Location = location;
		_TimeDate = date;
		_TotalTickets = totalTickets;
		_TotalSeats = totalSeats;
	}
	void setEventType(string eventType)
	{
		_EventType = eventType;
	}

	string getEventType()
	{
		return _EventType;
	}

	void setName(string name)
	{
		_Name = name;
	}

	string getName()
	{
		return _Name;
	}

	void setLocation(string location)
	{
		_Location = location;
	}

	string getLocation()
	{
		return _Location;
	}
	void setDate(string date)
	{
		_TimeDate = date;
	}
	string getDate()
	{
		return _TimeDate;
	}

	void setTotalTickets(int totalTickets)
	{
		_TotalTickets = totalTickets;
	}

	int getTotalTickets()
	{
		return _TotalTickets;
	}

	void setTotalSeats(int totalSeats)
	{
		_TotalSeats = totalSeats;
	}

	int getTotalSeats()
	{
		return _TotalSeats;
	}
	void AddEvent()
	{

	}

};
