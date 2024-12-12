#pragma once
#include <iostream>
#include <string>
#include "GlobalEvent.h"
#include "clsInputValidate.h"
#include "clsString.h"
#include <vector>
#include <iomanip>
using namespace std;

class Play : public Event
{
	string _Director;
	string _Author;

	static Play _ConvertLinetoConcertObject(string Line, string Seperator = "#//#")
	{

		vector <string> vConcertData;
		vConcertData = clsString::Split(Line, Seperator);

		return Play(vConcertData[0], vConcertData[1], vConcertData[2], vConcertData[3],
			vConcertData[4], stod(vConcertData[5]), stoi(vConcertData[6]), vConcertData[7], vConcertData[8]);

	}


	static string _ConverConcertObjectToLine(Play concert, string Seperator = "#//#")
	{

		string stConcertRecord = "";
		stConcertRecord += concert.getEventName() + Seperator;
		stConcertRecord += concert.getEventType() + Seperator;
		stConcertRecord += concert.getLocation() + Seperator;
		stConcertRecord += concert.getDate() + Seperator;
		stConcertRecord += concert.getEventId() + Seperator;
		stConcertRecord += to_string(concert.getPrice()) + Seperator;
		stConcertRecord += to_string(concert.getTotalSeats()) + Seperator;
		stConcertRecord += concert.getDirector() + Seperator;
		stConcertRecord += concert.getAuthor();
		return stConcertRecord;

	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Play.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

public:

	Play(string name, string eventType, string location, string date,
		string eventId, float price, int totalSeats,
		string director, string author) : Event(name,
			eventType, location, date, eventId, price, totalSeats)
	{
		_Director = director;
		_Author = author;
	}

	Play() {}


	void setDirector(string director)
	{
		_Director = director;

	}

	string getDirector()
	{
		return _Director;
	}

	void setAuthor(string author)
	{
		_Author = author;

	}

	string getAuthor()
	{
		return _Author;
	}


	static  vector <Play> _LoadConcertDataFromFile()
	{

		vector <Play> vConcert;

		fstream MyFile;
		MyFile.open("Play.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				Play concert = _ConvertLinetoConcertObject(Line);

				vConcert.push_back(concert);
			}

			MyFile.close();

		}

		return vConcert;

	}

	

	static void _SaveConcertDataToFile(vector <Play> vConcert)
	{

		fstream MyFile;
		MyFile.open("Play.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (Play& C : vConcert)
			{
				if (C.getCheckdel() == false)
				{
					DataLine = _ConverConcertObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();

		}

	}

	Play FindEventName(string Name)
	{
		fstream MyFile;
		MyFile.open("Play.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				Play concert = _ConvertLinetoConcertObject(Line);
				if (concert.getEventName() == Name)
				{
					MyFile.close();
					return concert;
				}

			}

			MyFile.close();

		}
		return Play("", "", "", "", "", 0.0, 0, "", "");
	}


	bool IsEventNameExist(string name)
	{

		Play movie = FindEventName(name);

		return movie.getEventName() == name;
	}

	Play FindEventId(string id)
	{

		fstream MyFile;
		MyFile.open("Play.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				Play movie = _ConvertLinetoConcertObject(Line);
				if (movie.getEventId() == id)
				{
					MyFile.close();
					return movie;
				}

			}

			MyFile.close();

		}
		return Play("", "", "", "", "", 0.0, 0, "", "");
	}

	bool IsEventIdExist(string eventId)
	{

		Play movie = FindEventId(eventId);

		return movie.getEventId() == eventId;

	}

	void AddEvent()
	{
		cout << "\t\t\t\tenter name of event? ";
		string name = clsInputValidate::ReadString();
		while (IsEventNameExist(name))
		{
			cout << "\n\t\t\t\tthis event already exit, enter another name: ";
			name = clsInputValidate::ReadString();
		}
		Play movie;
		movie.setEventName(name);

		movie.setEventType("Play");

		cout << "\n\t\t\t\tenter location of event? ";
		name = clsInputValidate::ReadString();
		movie.setLocation(name);

		cout << "\n\t\t\t\tenter date of event? ";
		name = clsInputValidate::ReadString();
		movie.setDate(name);

		random_device rd;
		uniform_int_distribution<int> dist(4000000, 4999999);
		name = to_string(dist(rd));

		while (IsEventIdExist(name))
		{
			name = to_string(dist(rd));

		}
		movie.setEventId(name);

		cout << "\t\t\t\tenter price? ";
		float price = clsInputValidate::ReadDblNumber();
		movie.setPrice(price);

		cout << "\t\t\t\tenter total seats? ";
		int total = clsInputValidate::ReadIntNumber();
		movie.setTotalSeats(total);

		cout << "\n\t\t\t\tenter Director? ";
		name = clsInputValidate::ReadString();
		movie.setDirector(name);

		cout << "\n\t\t\t\tenter Author of Play? ";
		name = clsInputValidate::ReadString();
		movie.setAuthor(name);

		movie._AddDataLineToFile(_ConverConcertObjectToLine(movie));
		cout << "\n\t\t\t\tAdd Successfully!";
	}

	static void  modify(Play& event)
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

		cout << "\t\t\t\tenter direction? ";
		name = clsInputValidate::ReadString();
		event.setDirector(name);

		cout << "\t\t\t\tenter Author? ";
		name = clsInputValidate::ReadString();
		event.setAuthor(name);


	}


	void ModifyEvent()
	{
		cout << "\t\t\t\tenter name of event? ";
		string name = clsInputValidate::ReadString();

		while (!Play::IsEventNameExist(name))
		{
			cout << "\n\t\t\t\tthis event not exit, enter another name: ";
			name = clsInputValidate::ReadString();
		}

		vector <Play> vEvent = _LoadConcertDataFromFile();

		for (Play& C : vEvent)
		{
			if (C.getEventName() == name)
			{
				modify(C);
				_SaveConcertDataToFile(vEvent);
				break;
			}
		}

		cout << "\n\t\t\t\tModify Successfuly!";
	}

	void DeleteEvent()
	{

		cout << "\t\t\t\tenter name of event? ";
		string name = clsInputValidate::ReadString();

		while (!IsEventNameExist(name))
		{
			cout << "\n\t\t\t\tthis event not exit, enter another name: ";
			name = clsInputValidate::ReadString();
		}

		vector <Play> vEvent = _LoadConcertDataFromFile();
		char bl;

		for (Play& C : vEvent)
		{
			if (C.getEventName() == name)
			{
				cout << "\n\t\t\t\tAre you sure you want to delete this event? Y/N? ";
				cin >> bl;
				if (toupper(bl) == 'Y')
				{
					C.setCheckdel();
					_SaveConcertDataToFile(vEvent);
				}
				else
					return;
				break;

			}
		}
		cout << "\n\t\t\t\tDelete Successfully!";
	}

	static void PrintMovieRecordLine(Play C)
	{

		cout << setw(8) << left << "" << "| " << setw(15) << left << C.getEventName();
		cout << "| " << setw(10) << left << C.getEventType();
		cout << "| " << setw(10) << left << C.getLocation();
		cout << "| " << setw(11) << left << C.getDate();
		cout << "| " << setw(10) << left << C.getEventId();
		cout << "| " << setw(10) << left << C.getPrice();
		cout << "| " << setw(3) << left << C.getTotalSeats();
		cout << "| " << setw(15) << left << C.getDirector();
		cout << "| " << setw(15) << left << C.getAuthor();

	}

	void ShowEventList()
	{

		vector <Play> vMovies = _LoadConcertDataFromFile();
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(15) << "Event Name";
		cout << "| " << left << setw(10) << "Event Type";
		cout << "| " << left << setw(10) << "Location";
		cout << "| " << left << setw(11) << "Date";
		cout << "| " << left << setw(10) << "EventID";
		cout << "| " << left << setw(10) << "Price";
		cout << "| " << left << setw(3) << "Total Seats";
		cout << "| " << left << setw(15) << "Director";
		cout << "| " << left << setw(15) << "Author";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vMovies.size() == 0)
			cout << "\t\t\t\tNo Play Available In the System!";
		else

			for (Play C : vMovies)
			{

				PrintMovieRecordLine(C);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

	}
};

