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
	float _Price;
	int _TotalSeats;
	bool checkdel = false;

	static Event _ConvertLinetoEventObject(string Line, string Seperator = "#//#")
	{
		vector<string> vEventData;
		vEventData = clsString::Split(Line, Seperator);

		return Event(vEventData[0], vEventData[1], vEventData[2],
			vEventData[3], vEventData[4], stod(vEventData[5]),stoi(vEventData[6]));

	}

	static string _ConverEventObjectToLine(Event event, string Seperator = "#//#")
	{

		string stEventRecord = "";
		stEventRecord += event.getEventType() + Seperator;
		stEventRecord += event.getName() + Seperator;
		stEventRecord += event.getLocation() + Seperator;
		stEventRecord += event.getDate() + Seperator;
		stEventRecord += event.getEventId() + Seperator;
		stEventRecord += to_string(event.getPrice()) + Seperator;
		stEventRecord += to_string(event.getTotalSeats());

		return stEventRecord;

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

	Event(string eventType, string name, string location, string date, string eventId, float price, int totalSeats)
	{
		_EventType = eventType;
		_Name = name;
		_Location = location;
		_TimeDate = date;
		_EventId = eventId;
		_Price = price;
		_TotalSeats = totalSeats;
	}

	Event(){}


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

	void setPrice(float price)
	{
		_Price = price;
	}

	float getPrice()
	{
		return _Price;
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
		return Event("", "", "", "", "", 0.0 , 0);
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
		return Event("", "", "", "", "", 0.0, 0);
	}

	static bool IsEventIdExist(string eventId)
	{

		Event event = Event::FindId(eventId);

		return event.getEventId() == eventId;
	}

	static void AddEvent()
	{
		cout << "\n\n\t\t\t\t========================================================\n";
		cout << "\t\t\t\t\tAdd Event\n";
		cout << "\t\t\t\t========================================================\n";
		cout << "\t\t\t\tenter name of event? ";
		string name = clsInputValidate::ReadString();
		while (Event::IsEventNameExist(name))
		{
			cout << "\n\t\t\t\tthis event already exit, enter another name: ";
			name = clsInputValidate::ReadString();
		}
		Event event("", "", "", "", "", 0.0, 0);
		event.setName(name);

		cout << "\n\t\t\t\tenter type of event? ";
		name = clsInputValidate::ReadString();
        event.setEventType(name);

		cout << "\n\t\t\t\tenter location of event? ";
		name = clsInputValidate::ReadString();
		event.setLocation(name);

		cout << "\n\t\t\t\tenter date of event? ";
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

		cout << "\t\t\t\tenter price? ";
		float price = clsInputValidate::ReadDblNumber();
		event.setPrice(price);

		cout << "\t\t\t\tenter total seats? ";
		int total = clsInputValidate::ReadIntNumber();
		event.setTotalSeats(total);

		event._AddDataLineToFile(_ConverEventObjectToLine(event));
		cout << "\n\t\t\t\tAdd Successfully!";
		cout << "\n\t\t\t\tpress any key to continuo...";
		system("pause>0");
	}

	static void  modify(Event& event)
	{
		string name;
		cout << "\t\t\t\tenter location of event? ";
		name = clsInputValidate::ReadString();
		event.setLocation(name);

		cout << "\t\t\t\tenter date of event? ";
		name = clsInputValidate::ReadString();
		event.setDate(name);

		cout << "\t\t\t\tenter price? ";
		float price = clsInputValidate::ReadDblNumber();
		event.setPrice(price);

		cout << "\t\t\t\tenter total Seats? ";
		int total = clsInputValidate::ReadIntNumber();
		event.setTotalSeats(total);
	}

	static void ModifyEvent()
	{
		cout << "\n\n\t\t\t\t========================================================\n";
		cout << "\t\t\t\t\tModify Event\n";
		cout << "\t\t\t\t========================================================\n";
		cout << "\t\t\t\tenter name of event? ";
		string name = clsInputValidate::ReadString();

		while (!Event::IsEventNameExist(name))
		{
			cout << "\n\t\t\t\tthis event not exit, enter another name: ";
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

		cout << "\n\t\t\t\tModify Successfuly!";
		cout << "\n\t\t\t\tpress any key to continuo...";
		system("pause>0");
        
	}

	static void DeleteEvent()
	{
		cout << "\n\n\t\t\t\t========================================================\n";
		cout << "\t\t\t\t\tDelete Event\n";
		cout << "\t\t\t\t========================================================\n";
		cout << "\t\t\t\tenter name of event? ";
		string name = clsInputValidate::ReadString();

		while (!Event::IsEventNameExist(name))
		{
			cout << "\n\t\t\t\tthis event not exit, enter another name: ";
			name = clsInputValidate::ReadString();
		}

		vector <Event> vEvent = _LoadEventDataFromFile();
		char bl;

		for (Event& C : vEvent)
		{
			if (C.getName() == name)
			{
				cout << "\n\t\t\t\tAre you sure you want to delete this event? Y/N? ";
				cin >> bl;
				if (toupper(bl) == 'Y')
				{
					C.checkdel = true;
					_SaveEventsDataToFile(vEvent);
				}
				else
					return;
				break;

			}
		}
		cout << "\n\t\t\t\tDelete Successfully!";
		cout << "\n\t\t\t\tpress any key to continuo...";
		system("pause>0");
	}
	static void PrintEventRecordLine(Event event)
	{

		cout << setw(8) << left << "" << "| " << setw(10) << left << event.getEventId();
		cout << "| " << setw(11) << left << event.getDate();
		cout << "| " << setw(15) << left << event.getName();
		cout << "| " << setw(12) << left << event.getLocation();
		cout << "| " << setw(15) << left << event.getEventType();
		cout << "| " << setw(12) << left << event.getTotalSeats();
		cout << "| " << setw(12) << left << event.getPrice();

	}


	static void ShowEventList()
	{
		vector <Event> vEvent = _LoadEventDataFromFile();
		cout << "\t\t\t\t\==========================================\n";
		cout << "\t\t\t\t\tEvent List" <<endl;
		cout << "\t\t\t\t==========================================\n";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(10) << "ID";
		cout << "| " << left << setw(11) << "Date";
		cout << "| " << left << setw(15) << "Name";
		cout << "| " << left << setw(12) << "Location";
		cout << "| " << left << setw(15) << "Type";
		cout << "| " << left << setw(12) << "Seat Number";
		cout << "| " << left << setw(12) << "Price";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (!vEvent.empty())
		{
			for (Event& C : vEvent)
			{

				PrintEventRecordLine(C);
				cout << endl;
			}
		}
		else
			cout << "\n\t\t\t\tNo Event to show!";

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		cout << "\n\t\t\t\tpress any key...";
		system("pause>0");
	}
};
