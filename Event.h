#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream>
#include <random>
using namespace std;


class Event
{

	string _EventType;
	string _Name;
	string _Location;
	string _TimeDate;
	string _EventId;
	int _TotalTickets;
	int _TotalSeats;
	bool checkdel = false;

	static Event _ConvertLinetoEventObject(string Line, string Seperator = "#//#")
	{
		vector<string> vEventData;
		vEventData = clsString::Split(Line, Seperator);

		return Event(vEventData[0], vEventData[1], vEventData[2],
			vEventData[3], vEventData[4], stoi(vEventData[5]), stoi(vEventData[6]));

	}

	static string _ConverEventObjectToLine(Event event, string Seperator = "#//#")
	{

		string stEventRecord = "";
		stEventRecord += event.getEventType() + Seperator;
		stEventRecord += event.getName() + Seperator;
		stEventRecord += event.getLocation() + Seperator;
		stEventRecord += event.getDate() + Seperator;
		stEventRecord += event.getEventId() + Seperator;
		stEventRecord += to_string(event.getTotalTickets()) + Seperator;
		stEventRecord += to_string(event.getTotalSeats());



		return stEventRecord;

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

	static void _SaveEventsDataToFile(vector <Event> vEvent)
	{

		fstream MyFile;
		MyFile.open("Event.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (Event& C : vEvent)
			{
				if (C.checkdel == false)
				{
					DataLine = _ConverEventObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();

		}

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

	Event(string eventType, string name, string location, string date, string eventId, int totalTickets, int totalSeats)
	{
		_EventType = eventType;
		_Name = name;
		_Location = location;
		_TimeDate = date;
		_EventId = eventId;
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


	void setEventId(string eventId)
	{
		_EventId = eventId;
	}

	string getEventId()
	{
		return _EventId;
	}

	void setCheckdel(bool bl)
	{
		checkdel = bl;
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

	static Event FindName(string name)
	{



		fstream MyFile;
		MyFile.open("Event.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				Event event = _ConvertLinetoEventObject(Line);
				if (event.getName() == name)
				{
					MyFile.close();
					return event;
				}

			}

			MyFile.close();

		}
		return Event("", "", "", "", "", 0, 0 );
	}

	static bool IsEventNameExist(string name)
	{

		Event event = Event::FindName(name);

		return event.getName() == name;
	}

	static Event FindId(string eventId)
	{



		fstream MyFile;
		MyFile.open("Event.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				Event event = _ConvertLinetoEventObject(Line);
				if (event.getEventId() == eventId)
				{
					MyFile.close();
					return event;
				}

			}

			MyFile.close();

		}
		return Event("", "", "", "", "", 0, 0);
	}

	static bool IsEventIdExist(string eventId)
	{

		Event event = Event::FindId(eventId);

		return event.getEventId() == eventId;
	}

	static void AddEvent()
	{
		cout << "========================================================\n";
		cout << "Add Event\n";
		cout << "========================================================\n";
		cout << "enter name of event? ";
		string name = clsInputValidate::ReadString();
		while (Event::IsEventNameExist(name))
		{
			cout << "\nthis event already exit, enter another name: ";
			name = clsInputValidate::ReadString();
		}
		Event event("", "", "", "", "", 0, 0);
		event.setName(name);

		cout << "\nenter type of event? ";
		name = clsInputValidate::ReadString();
        event.setEventType(name);

		cout << "\nenter location of event? ";
		name = clsInputValidate::ReadString();
		event.setLocation(name);

		cout << "\nenter date of event? ";
		name = clsInputValidate::ReadString();
		event.setDate(name);

		random_device rd;
		uniform_int_distribution<int> dist(1000000, 1999999);
		name = to_string(dist(rd));

		while (IsEventIdExist(name))
		{
			name = to_string(dist(rd));

		}
		event.setEventId(name);

		cout << "enter total tickets? ";
		int total = clsInputValidate::ReadIntNumber();
		event.setTotalTickets(total);

		cout << "enter total seats? ";
		total = clsInputValidate::ReadIntNumber();
		event.setTotalSeats(total);

		event._AddDataLineToFile(_ConverEventObjectToLine(event));
		cout << "\nAdd Successfully!";
		cout << "\npress any key to continuo...";
		system("pause>0");
	}

	static void  modify(Event& event)
	{
		string name;
		cout << "enter location of event? ";
		name = clsInputValidate::ReadString();
		event.setLocation(name);

		cout << "enter date of event? ";
		name = clsInputValidate::ReadString();
		event.setDate(name);

		cout << "enter total tickets? ";
		int total = clsInputValidate::ReadIntNumber();
		event.setTotalTickets(total);

		cout << "enter total Seats? ";
		total = clsInputValidate::ReadIntNumber();
		event.setTotalSeats(total);
	}

	static void ModifyEvent()
	{
		cout << "========================================================\n";
		cout << "Modify Event\n";
		cout << "========================================================\n";
		cout << "enter name of event? ";
		string name = clsInputValidate::ReadString();

		while (!Event::IsEventNameExist(name))
		{
			cout << "\nthis event not exit, enter another name: ";
			name = clsInputValidate::ReadString();
		}

		vector <Event> vEvent = _LoadEventDataFromFile();
		
		for (Event& C : vEvent)
		{
			if (C.getName() == name)
			{
				Event::modify(C);
				_SaveEventsDataToFile(vEvent);
				break;
				
			}
		}

		cout << "\nModify Successfuly!";
		cout << "\npress any key to continuo...";
		system("pause>0");
        
	}

	static void DeleteEvent()
	{
		cout << "========================================================\n";
		cout << "Delete Event\n";
		cout << "========================================================\n";
		cout << "enter name of event? ";
		string name = clsInputValidate::ReadString();

		while (!Event::IsEventNameExist(name))
		{
			cout << "\nthis event not exit, enter another name: ";
			name = clsInputValidate::ReadString();
		}

		vector <Event> vEvent = _LoadEventDataFromFile();
		bool bl = false;

		for (Event& C : vEvent)
		{
			if (C.getName() == name)
			{
				cout << "\nAre you sure you want to delete this event? ";
				cin >> bl;
				if (bl)
				{
					C.checkdel = true;
					_SaveEventsDataToFile(vEvent);
				}
				else
					return;
				break;

			}
		}
		cout << "\nDelete Successfully!";
		cout << "\npress any key to continuo...";
		system("pause>0");
	}

};
