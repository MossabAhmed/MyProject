#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream>
#include "iomanip"
#include "Event.h"
#include "GlobalCustomer.h"
#include "GlobalEvent.h"
#include "Movie.h"
#include "Concert.h"
#include "Play.h"


using namespace std;
class Booking
{
    string _BookingId;
    string _BookingDate;
    string _CustomerId;
    string _NameEvent;
    float _TotalPrice;
    bool checkbook = false;

    static Booking _ConvertLinetoBookingObject(string Line, string Seperator = "#//#")
    {
        vector<string> vBookingData;
        vBookingData = clsString::Split(Line, Seperator);
        if (vBookingData.empty())
        {
            return Booking("", "", "", "", 0.0);
        }
        return Booking(vBookingData[0], vBookingData[1], vBookingData[2],
            vBookingData[3], stod(vBookingData[4]));

    }

    static string _ConverBookingObjectToLine(Booking booking, string Seperator = "#//#")
    {

        string stBookingRecord = "";
        stBookingRecord += booking.getBookingId() + Seperator;
        stBookingRecord += booking.getBookingDate() + Seperator;
        stBookingRecord += booking.getCustomerId() + Seperator;
        stBookingRecord += booking.getEventName() + Seperator;
        stBookingRecord += to_string(booking.getTotalPrice()) + Seperator;

        return stBookingRecord;

    }

    static  vector <Booking> _LoadBookingDataFromFile()
    {

        vector <Booking> vBooking;

        fstream MyFile;
        MyFile.open("Booking.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                Booking booking = _ConvertLinetoBookingObject(Line);

                vBooking.push_back(booking);
            }

            MyFile.close();

        }

        return vBooking;

    }

    void _AddDataLineToFile(string  stDataLine)
    {

        fstream MyFile;
        MyFile.open("Booking.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static void _SaveBookingDataToFile(vector <Booking> vBooking)
    {

        fstream MyFile;
        MyFile.open("Booking.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (Booking C : vBooking)
            {
                if (!C.getCheckBook())
                {
                    DataLine = _ConverBookingObjectToLine(C);
                    MyFile << DataLine << endl;
                }

            }

            MyFile.close();

        }

    }

public:
    Booking(string bookingId, string bookingDate, string customerId, string name, float price)
    {
        _BookingId = bookingId;
        _BookingDate = bookingDate;
        _CustomerId = customerId;
        _NameEvent = name;
        _TotalPrice = price;
    }

    Booking() {}



    void setBookingId(string bookingId)
    {
        _BookingId = bookingId;
    }

    void setBookingDate(string bookingDate)
    {
        _BookingDate = bookingDate;
    }

    void setCustomerId(string customerId)
    {
        _CustomerId = customerId;
    }
    void setEventName(string name)
    {
        _NameEvent = name;
    }

    void setTotalPrice(float total)
    {
        _TotalPrice = total;
    }

    string getBookingId()
    {
        return _BookingId;
    }

    string getBookingDate()
    {
        return _BookingDate;
    }

    string getCustomerId()
    {
        return _CustomerId;
    }

    string getEventName()
    {
        return _NameEvent;
    }

    float getTotalPrice()
    {
        return _TotalPrice;
    }
    void setCheckBook()
    {
        checkbook = true;
    }

    bool getCheckBook()
    {
        return checkbook;
    }

    static Booking Find(string id, string name)
    {



        fstream MyFile;
        MyFile.open("Booking.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                Booking booking = _ConvertLinetoBookingObject(Line);
                if (booking.getCustomerId() == id && booking.getEventName() == name)
                {
                    MyFile.close();
                    return booking;
                }

            }

            MyFile.close();

        }
        return Booking("", "", "", "", 0.0);
    }

    static bool IsBookingExit(string id, string name)
    {
        Booking booking = Find(id, name);
        return (booking.getCustomerId() == id && booking.getEventName() == name);
    }

    static Booking FindId(string id)
    {



        fstream MyFile;
        MyFile.open("Booking.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                Booking booking = _ConvertLinetoBookingObject(Line);
                if (booking.getBookingId() == id)
                {
                    MyFile.close();
                    return booking;
                }

            }

            MyFile.close();

        }
        return Booking("", "", "", "", 0.0);
    }

    static bool IsBookingIdExit(string id)
    {
        Booking booking = FindId(id);
        return (booking.getBookingId() == id);
    }

    static void moviepurchase()
    {

        string name;
        Movie movie;
        Booking booking;
        cout << "\t\t\t\tenter name of event? ";
        name = clsInputValidate::ReadString();
        while (!movie.IsEventNameExist(name))
        {
            cout << "\n\t\t\t\tthis event not Exist , enter another name? ";
            name = clsInputValidate::ReadString();
        }

        movie = movie.FindEventName(name);
        if (IsBookingExit(globCustomer.getCustomerId(), name))
        {
            cout << "\n\t\t\t\tYou already book this Event...";
            return;
        }

        if (movie.getTotalSeats() == 0)
        {
            cout << "\n\t\t\t\tsorry, there are no tickets available for purchase!";
            return;
        }

        random_device rd;
        uniform_int_distribution<int> dist(3000000, 3999999);
        name = to_string(dist(rd));

        while (IsBookingIdExit(name))
        {
            name = to_string(dist(rd));
        }
        booking.setBookingId(name);

        name = clsInputValidate::Datetime();
        booking.setBookingDate(name);


        booking.setTotalPrice(movie.getPrice());

        booking.setCustomerId(globCustomer.getCustomerId());
        booking.setEventName(movie.getEventName());
        booking._AddDataLineToFile(_ConverBookingObjectToLine(booking));
        movie.setTotalSeats(movie.getTotalSeats() - 1);
        vector <Movie> vMovie = movie._LoadMovieDataFromFile();
        for (Movie& C : vMovie)
        {
            if (C.getEventName() == movie.getEventName())
            {
                C = movie;
                break;
            }

        }
        movie._SaveMoviesDataToFile(vMovie);

    }
    static void Concertpurchase()
    {
        string name;
        Concert movie;
        Booking booking;
        cout << "\t\t\t\tenter name of event? ";
        name = clsInputValidate::ReadString();
        while (!movie.IsEventNameExist(name))
        {
            cout << "\n\t\t\t\tthis event not Exist , enter another name? ";
            name = clsInputValidate::ReadString();
        }

        movie = movie.FindEventName(name);
        if (IsBookingExit(globCustomer.getCustomerId(), name))
        {
            cout << "\n\t\t\t\tYou already book this Event...";
            return;
        }

        if (movie.getTotalSeats() == 0)
        {
            cout << "\n\t\t\t\tsorry, there are no tickets available for purchase!";
            return;
        }

        random_device rd;
        uniform_int_distribution<int> dist(3000000, 3999999);
        name = to_string(dist(rd));

        while (IsBookingIdExit(name))
        {
            name = to_string(dist(rd));
        }
        booking.setBookingId(name);

        name = clsInputValidate::Datetime();
        booking.setBookingDate(name);


        booking.setTotalPrice(movie.getPrice());

        booking.setCustomerId(globCustomer.getCustomerId());
        booking.setEventName(movie.getEventName());
        booking._AddDataLineToFile(_ConverBookingObjectToLine(booking));
        movie.setTotalSeats(movie.getTotalSeats() - 1);
        vector <Concert> vMovie = movie._LoadConcertDataFromFile();
        for (Concert& C : vMovie)
        {
            if (C.getEventName() == movie.getEventName())
            {
                C = movie;
                break;
            }

        }
        movie._SaveConcertDataToFile(vMovie);
    }
    static void Playpurchase()
    {
        string name;
        Play movie;
        Booking booking;
        cout << "\t\t\t\tenter name of event? ";
        name = clsInputValidate::ReadString();
        while (!movie.IsEventNameExist(name))
        {
            cout << "\n\t\t\t\tthis event not Exist , enter another name? ";
            name = clsInputValidate::ReadString();
        }

        movie = movie.FindEventName(name);
        if (IsBookingExit(globCustomer.getCustomerId(), name))
        {
            cout << "\n\t\t\t\tYou already book this Event...";
            return;
        }

        if (movie.getTotalSeats() == 0)
        {
            cout << "\n\t\t\t\tsorry, there are no tickets available for purchase!";
            return;
        }

        random_device rd;
        uniform_int_distribution<int> dist(3000000, 3999999);
        name = to_string(dist(rd));

        while (IsBookingIdExit(name))
        {
            name = to_string(dist(rd));
        }
        booking.setBookingId(name);

        name = clsInputValidate::Datetime();
        booking.setBookingDate(name);


        booking.setTotalPrice(movie.getPrice());

        booking.setCustomerId(globCustomer.getCustomerId());
        booking.setEventName(movie.getEventName());
        booking._AddDataLineToFile(_ConverBookingObjectToLine(booking));
        movie.setTotalSeats(movie.getTotalSeats() - 1);
        vector <Play> vMovie = movie._LoadConcertDataFromFile();
        for (Play& C : vMovie)
        {
            if (C.getEventName() == movie.getEventName())
            {
                C = movie;
                break;
            }

        }
        movie._SaveConcertDataToFile(vMovie);
    }



    static void PrintBookRecordLine(Booking book)
    {

        cout << setw(8) << left << "" << "| " << setw(15) << left << book.getBookingId();
        cout << "| " << setw(20) << left << book.getBookingDate();
        cout << "| " << setw(12) << left << book.getEventName();
        cout << "| " << setw(12) << left << book.getTotalPrice();

    }

    static bool ShowBookingList()
    {
        vector <Booking> vBook = _LoadBookingDataFromFile();
        cout << "\t\t\t\t==========================================\n";
        cout << "\t\t\t\t\tBooking List for " << globCustomer.getName() << endl;
        cout << "\t\t\t\t==========================================\n";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "ID";
        cout << "| " << left << setw(20) << "Date";
        cout << "| " << left << setw(12) << "Event Name";
        cout << "| " << left << setw(12) << "Price";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        int n = 0;

        for (Booking& C : vBook)
        {
            if (C.getCustomerId() == globCustomer.getCustomerId())
            {
                n++;
                PrintBookRecordLine(C);
                cout << endl;
            }
        }
        if (n == 0)
        {
            cout << "\n\t\t\t\tNo book to show!";
            return false;
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        return true;

    }

    static void delBooking(Booking book)
    {
        vector <Booking> vBooking = _LoadBookingDataFromFile();
        for (Booking& C : vBooking)
        {
            if (C.getBookingId() == book.getBookingId())
            {
                C.setCheckBook();
                _SaveBookingDataToFile(vBooking);
                return;
            }
        }
    }

    static void CancelMovie()
    {
        string name;
        Booking booking;
        Movie movie;

        cout << "\t\t\t\tenter name of event? ";
        name = clsInputValidate::ReadString();
        while (!IsBookingExit(globCustomer.getCustomerId(), name))
        {
            cout << "\n\t\t\t\tthis event not Exist or no book , enter another name? ";
            name = clsInputValidate::ReadString();
        }
        Booking book = Find(globCustomer.getCustomerId(), name);
        delBooking(book);
        movie.setTotalSeats(movie.getTotalSeats() + 1);
        vector <Movie> vMovie = movie._LoadMovieDataFromFile();
        for (Movie& C : vMovie)
        {
            if (C.getEventName() == movie.getEventName())
            {
                C = movie;
                break;
            }

        }
        movie._SaveMoviesDataToFile(vMovie);
    }
    static void CancelConcert()
    {
        string name;
        Booking booking;
        Concert movie;

        cout << "\t\t\t\tenter name of event? ";
        name = clsInputValidate::ReadString();
        while (!IsBookingExit(globCustomer.getCustomerId(), name))
        {
            cout << "\n\t\t\t\tthis event not Exist or no book , enter another name? ";
            name = clsInputValidate::ReadString();
        }
        Booking book = Find(globCustomer.getCustomerId(), name);
        delBooking(book);
        movie.setTotalSeats(movie.getTotalSeats() + 1);
        vector <Concert> vMovie = movie._LoadConcertDataFromFile();
        for (Concert& C : vMovie)
        {
            if (C.getEventName() == movie.getEventName())
            {
                C = movie;
                break;
            }

        }
        movie._SaveConcertDataToFile(vMovie);
    }
    static void CancelPlay()
    {
        string name;
        Booking booking;
        Play movie;

        cout << "\t\t\t\tenter name of event? ";
        name = clsInputValidate::ReadString();
        while (!IsBookingExit(globCustomer.getCustomerId(), name))
        {
            cout << "\n\t\t\t\tthis event not Exist or no book, enter another name? ";
            name = clsInputValidate::ReadString();
        }
        Booking book = Find(globCustomer.getCustomerId(), name);
        delBooking(book);
        movie.setTotalSeats(movie.getTotalSeats() + 1);
        vector <Play> vMovie = movie._LoadConcertDataFromFile();
        for (Play& C : vMovie)
        {
            if (C.getEventName() == movie.getEventName())
            {
                C = movie;
                break;
            }

        }
        movie._SaveConcertDataToFile(vMovie);
    }




};

