#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include "clsInputValidate.h"
#include <vector>
#include <fstream>
#include <random>
#include <memory>
using namespace std;


class Event
{

	string _Name;
	string _EventType;
	string _Location;
	string _TimeDate;
	string _EventId;
	float _Price;
	int _TotalSeats;
	bool checkdel = false;
public:
	Event(string name, string eventType, string location, string date, string eventId, float price, int totalSeats)
	{
		_EventType = eventType;
		_Name = name;
		_Location = location;
		_TimeDate = date;
		_EventId = eventId;
		_Price = price;
		_TotalSeats = totalSeats;
	}
	Event() {}
	void setEventName(string name)
	{
		_Name = name;
	}

	string getEventName()
	{
		return _Name;
	}

	void setEventType(string eventType)
	{
		_EventType = eventType;
	}

	string getEventType()
	{
		return _EventType;
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

	void setCheckdel()
	{
		checkdel = true;
	}

	bool getCheckdel()
	{
		return checkdel;
	}


	virtual bool IsEventNameExist(string name) = 0;

	virtual bool IsEventIdExist(string eventId) = 0;

	virtual void AddEvent() = 0;

	virtual void ModifyEvent() = 0;

	virtual void DeleteEvent() = 0;

	virtual void ShowEventList() = 0;


};
