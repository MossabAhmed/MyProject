#pragma once
#include <iostream>
#include "GlobalEvent.h"
#include <string>
#include "clsInputValidate.h"
#include "clsString.h"
#include <vector>
#include <iomanip>
using namespace std;

class Concert : public Event
{
	string _Band;
	string _MusicType;
	string _Album;

	static Concert _ConvertLinetoConcertObject(string Line, string Seperator = "#//#")
	{
		vector <string> vConcertData;
		vConcertData = clsString::Split(Line, Seperator);
		if (vConcertData.empty())
		{
			return Concert("", "", "", "", "", 0.0, 0, "", "", "");
		}
		return Concert(vConcertData[0], vConcertData[1], vConcertData[2], vConcertData[3],
			vConcertData[4], stod(vConcertData[5]), stoi(vConcertData[6]), vConcertData[7], vConcertData[8], vConcertData[9]);

	}



	static string _ConverConcertObjectToLine(Concert concert, string Seperator = "#//#")
	{

		string stConcertRecord = "";
		stConcertRecord += concert.getEventName() + Seperator;
		stConcertRecord += concert.getEventType() + Seperator;
		stConcertRecord += concert.getLocation() + Seperator;
		stConcertRecord += concert.getDate() + Seperator;
		stConcertRecord += concert.getEventId() + Seperator;
		stConcertRecord += to_string(concert.getPrice()) + Seperator;
		stConcertRecord += to_string(concert.getTotalSeats()) + Seperator;
		stConcertRecord += concert.getBand() + Seperator;
		stConcertRecord += concert.getMusicType() + Seperator;
		stConcertRecord += concert.getAlbum();

		return stConcertRecord;

	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Concert.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

public:

	Concert(string name, string eventType, string location, string date,
		string eventId, float price, int totalSeats, string Band,
		string musictype, string album) : Event(name, eventType, location,
			date, eventId, price, totalSeats)
	{
		_Band = Band;
		_MusicType = musictype;
		_Album = album;
	}

	Concert() {}

	void setBand(string band)
	{
		_Band = band;
	}

	string getBand()
	{
		return _Band;
	}

	void setMusicType(string type)
	{
		_MusicType = type;
	}

	string getMusicType()
	{
		return _MusicType;
	}

	void setAlbum(string album)
	{
		_Album = album;
	}

	string getAlbum()
	{
		return _Album;
	}


	static  vector <Concert> _LoadConcertDataFromFile()
	{

		vector <Concert> vConcert;

		fstream MyFile;
		MyFile.open("Concert.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				Concert concert = _ConvertLinetoConcertObject(Line);

				vConcert.push_back(concert);
			}

			MyFile.close();

		}

		return vConcert;

	}

	static void _SaveConcertDataToFile(vector <Concert> vConcert)
	{

		fstream MyFile;
		MyFile.open("Concert.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (Concert& C : vConcert)
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


	


	Concert FindEventName(string Name)
	{
		fstream MyFile;
		MyFile.open("Concert.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				Concert concert = _ConvertLinetoConcertObject(Line);
				if (concert.getEventName() == Name)
				{
					MyFile.close();
					return concert;
				}

			}

			MyFile.close();

		}
		return Concert("", "", "", "", "", 0.0, 0, "", "", "");
	}


	bool IsEventNameExist(string name)
	{

		Concert movie = FindEventName(name);

		return movie.getEventName() == name;
	}

	Concert FindEventId(string id)
	{

		fstream MyFile;
		MyFile.open("Concert.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				Concert movie = _ConvertLinetoConcertObject(Line);
				if (movie.getEventId() == id)
				{
					MyFile.close();
					return movie;
				}

			}

			MyFile.close();

		}
		return Concert("", "", "", "", "", 0.0, 0, "", "", "");
	}

	bool IsEventIdExist(string eventId)
	{

		Concert movie = FindEventId(eventId);

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
		Concert movie;
		movie.setEventName(name);
		movie.setEventType("Concert");

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

		cout << "\n\t\t\t\tenter Band name? ";
		name = clsInputValidate::ReadString();
		movie.setBand(name);

		cout << "\n\t\t\t\tenter Type of music? ";
		name = clsInputValidate::ReadString();
		movie.setMusicType(name);

		cout << "\n\t\t\t\tenter Album? ";
		name = clsInputValidate::ReadString();
		movie.setAlbum(name);

		movie._AddDataLineToFile(_ConverConcertObjectToLine(movie));
		cout << "\n\t\t\t\tAdd Successfully!";
	}

	static void  modify(Concert& event)
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

		cout << "\t\t\t\tenter Band name? ";
		name = clsInputValidate::ReadString();
		event.setBand(name);

		cout << "\t\t\t\tenter Music type? ";
		name = clsInputValidate::ReadString();
		event.setMusicType(name);

		cout << "\t\t\t\tenter Album? ";
		name = clsInputValidate::ReadString();
		event.setAlbum(name);

	}


	void ModifyEvent()
	{
		cout << "\t\t\t\tenter name of event? ";
		string name = clsInputValidate::ReadString();

		while (!Concert::IsEventNameExist(name))
		{
			cout << "\n\t\t\t\tthis event not exit, enter another name: ";
			name = clsInputValidate::ReadString();
		}

		vector <Concert> vEvent = _LoadConcertDataFromFile();

		for (Concert& C : vEvent)
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

		vector <Concert> vEvent = _LoadConcertDataFromFile();
		char bl;

		for (Concert& C : vEvent)
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

	static void PrintMovieRecordLine(Concert C)
	{

		cout << setw(8) << left << "" << "| " << setw(15) << left << C.getEventName();
		cout << "| " << setw(10) << left << C.getEventType();
		cout << "| " << setw(10) << left << C.getLocation();
		cout << "| " << setw(11) << left << C.getDate();
		cout << "| " << setw(10) << left << C.getEventId();
		cout << "| " << setw(10) << left << C.getPrice();
		cout << "| " << setw(3) << left << C.getTotalSeats();
		cout << "| " << setw(15) << left << C.getBand();
		cout << "| " << setw(10) << left << C.getMusicType();
		cout << "| " << setw(10) << left << C.getAlbum();

	}

	void ShowEventList()
	{

		vector <Concert> vMovies = _LoadConcertDataFromFile();
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(15) << "Event Name";
		cout << "| " << left << setw(10) << "Event Type";
		cout << "| " << left << setw(10) << "Location";
		cout << "| " << left << setw(11) << "Date";
		cout << "| " << left << setw(10) << "EventID";
		cout << "| " << left << setw(10) << "Price";
		cout << "| " << left << setw(3) << "Total Seats";
		cout << "| " << left << setw(15) << "Band";
		cout << "| " << left << setw(10) << "Music Type";
		cout << "| " << left << setw(10) << "Album";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vMovies.size() == 0)
			cout << "\t\t\t\tNo Concert Available In the System!";
		else

			for (Concert C : vMovies)
			{

				PrintMovieRecordLine(C);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

	}
};

