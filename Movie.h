#pragma once
#include <iostream>
#include <string>
#include "GlobalEvent.h"
#include "clsInputValidate.h"
#include "clsString.h"
#include <vector>
#include <iomanip>
using namespace std;
class Movie : public Event
{

	string _Director;
	string _MovieType;
	string _AgeRating;

	static Movie _ConvertLinetoMovieObject(string Line, string Seperator = "#//#")
	{
		vector <string> vMovieData;
		vMovieData = clsString::Split(Line, Seperator);
		if (vMovieData.empty())
		{
			return Movie("", "", "", "", "", 0.0, 0, "", "", "");

		}

		return Movie(vMovieData[0], vMovieData[1], vMovieData[2], vMovieData[3],
			vMovieData[4], stod(vMovieData[5]), stoi(vMovieData[6]),
			vMovieData[7], vMovieData[8], vMovieData[9]);

	}



	static string _ConverMovieObjectToLine(Movie movie, string Seperator = "#//#")
	{

		string stMovieRecord = "";
		stMovieRecord += movie.getEventName() + Seperator;
		stMovieRecord += movie.getEventType() + Seperator;
		stMovieRecord += movie.getLocation() + Seperator;
		stMovieRecord += movie.getDate() + Seperator;
		stMovieRecord += movie.getEventId() + Seperator;
		stMovieRecord += to_string(movie.getPrice()) + Seperator;
		stMovieRecord += to_string(movie.getTotalSeats()) + Seperator;
		stMovieRecord += movie.getDirector() + Seperator;
		stMovieRecord += movie.getType() + Seperator;
		stMovieRecord += movie.getAge();

		return stMovieRecord;

	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Movie.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

public:

	Movie(string name, string eventType, string location, string date,
		string eventId, float price, int totalSeats, string director,
		string type, string age) : Event(name, eventType, location,
			date, eventId, price, totalSeats)
	{
		_Director = director;
		_MovieType = type;
		_AgeRating = age;
	}


	Movie() {}

	void setDirector(string director)
	{
		_Director = director;
	}

	string getDirector()
	{
		return _Director;
	}

	void setType(string type)
	{
		_MovieType = type;
	}

	string getType()
	{
		return _MovieType;
	}

	void setAge(string age)
	{
		_AgeRating = age;
	}

	string getAge()
	{
		return _AgeRating;
	}


	static  vector <Movie> _LoadMovieDataFromFile()
	{

		vector <Movie> vMovie;

		fstream MyFile;
		MyFile.open("Movie.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				Movie movie = _ConvertLinetoMovieObject(Line);

				vMovie.push_back(movie);
			}

			MyFile.close();

		}

		return vMovie;

	}

	static void _SaveMoviesDataToFile(vector <Movie> vMovie)
	{

		fstream MyFile;
		MyFile.open("Movie.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (Movie& C : vMovie)
			{
				if (C.getCheckdel() == false)
				{
					DataLine = _ConverMovieObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();

		}

	}

	Movie FindEventName(string Name)
	{
		fstream MyFile;
		MyFile.open("Movie.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				Movie movie = _ConvertLinetoMovieObject(Line);
				if (movie.getEventName() == Name)
				{
					MyFile.close();
					return movie;
				}

			}

			MyFile.close();

		}
		return Movie("", "", "", "", "", 0.0, 0, "", "", "");
	}

	bool IsEventNameExist(string name)
	{

		Movie movie = FindEventName(name);

		return movie.getEventName() == name;
	}

	static Movie FindEventId(string id)
	{

		fstream MyFile;
		MyFile.open("Movie.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				Movie movie = _ConvertLinetoMovieObject(Line);
				if (movie.getEventId() == id)
				{
					MyFile.close();
					return movie;
				}

			}

			MyFile.close();

		}
		return Movie("", "", "", "", "", 0.0, 0, "", "", "");
	}

	bool IsEventIdExist(string eventId)
	{

		Movie movie = FindEventId(eventId);

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
		Movie movie;
		movie.setEventName(name);

		movie.setEventType("Movie");
		cout << "\n\t\t\t\tenter location of event? ";
		string name1 = clsInputValidate::ReadString();
		movie.setLocation(name1);

		cout << "\n\t\t\t\tenter date of event? ";
		string name2 = clsInputValidate::ReadString();
		movie.setDate(name2);

		random_device rd;
		uniform_int_distribution<int> dist(1000000, 1999999);
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

		cout << "\n\t\t\t\tenter director? ";
		string name3 = clsInputValidate::ReadString();
		movie.setDirector(name3);

		cout << "\n\t\t\t\tenter Type of movie? ";
		string name4 = clsInputValidate::ReadString();
		movie.setType(name4);

		cout << "\n\t\t\t\tenter Age Rating? ";
		string name5 = clsInputValidate::ReadString();
		movie.setAge(name5);
		_AddDataLineToFile(_ConverMovieObjectToLine(movie));
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

	static void  modify(Movie& event)
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

		cout << "\t\t\t\tenter Age Rating? ";
		name = clsInputValidate::ReadString();
		event.setAge(name);


	}


	void ModifyEvent()
	{
		cout << "\t\t\t\tenter name of event? ";
		string name = clsInputValidate::ReadString();

		while (!Movie::IsEventNameExist(name))
		{
			cout << "\n\t\t\t\tthis event not exit, enter another name: ";
			name = clsInputValidate::ReadString();
		}

		vector <Movie> vEvent = _LoadMovieDataFromFile();

		for (Movie& C : vEvent)
		{
			if (C.getEventName() == name)
			{
				modify(C);
				_SaveMoviesDataToFile(vEvent);
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

		vector <Movie> vEvent = _LoadMovieDataFromFile();
		char bl;

		for (Movie& C : vEvent)
		{
			if (C.getEventName() == name)
			{
				cout << "\n\t\t\t\tAre you sure you want to delete this event? Y/N? ";
				cin >> bl;
				if (toupper(bl) == 'Y')
				{
					C.setCheckdel();
					_SaveMoviesDataToFile(vEvent);
				}
				else
					return;
				break;

			}
		}
		cout << "\n\t\t\t\tDelete Successfully!";
	}


	static void PrintMovieRecordLine(Movie C)
	{

		cout << setw(8) << left << "" << "| " << setw(15) << left << C.getEventName();
		cout << "| " << setw(10) << left << C.getEventType();
		cout << "| " << setw(10) << left << C.getLocation();
		cout << "| " << setw(11) << left << C.getDate();
		cout << "| " << setw(10) << left << C.getEventId();
		cout << "| " << setw(10) << left << C.getPrice();
		cout << "| " << setw(3) << left << C.getTotalSeats();
		cout << "| " << setw(15) << left << C.getDirector();
		cout << "| " << setw(10) << left << C.getType();
		cout << "| " << setw(3) << left << C.getAge();

	}

	void ShowEventList()
	{

		vector <Movie> vMovies = _LoadMovieDataFromFile();
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
		cout << "| " << left << setw(10) << "Movie Type";
		cout << "| " << left << setw(3) << "Age Rating";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vMovies.size() == 0)
			cout << "\t\t\t\tNo Movies Available In the System!";
		else

			for (Movie C : vMovies)
			{

				PrintMovieRecordLine(C);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

	}
};

