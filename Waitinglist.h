#pragma once
#include <iostream>
#include <fstream>
#include "clsString.h"
#include <vector>
#include <string>
#include <random>
#include "clsInputValidate.h"
using namespace std;
class Waitinglist
{
	string _WaitId;
	string _Jointime;
	string _CustomerId;
	string _Eventname;
    bool checkdel = false;

    static Waitinglist _ConvertLinetoBookingObject(string Line, string Seperator = "#//#")
    {
        vector<string> vBookingData;
        vBookingData = clsString::Split(Line, Seperator);
        if (vBookingData.empty())
        {
            return Waitinglist("", "", "", "");
        }
        return Waitinglist(vBookingData[0], vBookingData[1], vBookingData[2],
            vBookingData[3]);

    }

    static string _ConverBookingObjectToLine(Waitinglist booking, string Seperator = "#//#")
    {

        string stBookingRecord = "";
        stBookingRecord += booking._WaitId + Seperator;
        stBookingRecord += booking._Jointime + Seperator;
        stBookingRecord += booking._CustomerId + Seperator;
        stBookingRecord += booking._Eventname;

        return stBookingRecord;

    }

    static  vector <Waitinglist> _LoadBookingDataFromFile()
    {

        vector <Waitinglist> vBooking;

        fstream MyFile;
        MyFile.open("Waitinglist.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                Waitinglist booking = _ConvertLinetoBookingObject(Line);

                vBooking.push_back(booking);
            }

            MyFile.close();

        }

        return vBooking;

    }

    void _AddDataLineToFile(string  stDataLine)
    {

        fstream MyFile;
        MyFile.open("Waitinglist.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static void _SaveBookingDataToFile(vector <Waitinglist> vBooking)
    {

        fstream MyFile;
        MyFile.open("Waitinglist.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (Waitinglist C : vBooking)
            {
                if (!C.checkdel)
                {
                    DataLine = _ConverBookingObjectToLine(C);
                    MyFile << DataLine << endl;
                }

            }

            MyFile.close();

        }

    }

    public:
        Waitinglist(string id, string join, string custrome, string name)
        {
            _WaitId = id;
            _Jointime = join;
            _CustomerId = custrome;
            _Eventname = name;
        }

        Waitinglist(){}

        string getId() { return _WaitId; }

        string getcustomer() { return _CustomerId; }

        string getEventname() { return _Eventname; }

        string getJoin() { return _Jointime; }


        static Waitinglist Find(string id, string name)
        {



            fstream MyFile;
            MyFile.open("Waitinglist.txt", ios::in);//read Mode

            if (MyFile.is_open())
            {
                string Line;
                while (getline(MyFile, Line))
                {
                    Waitinglist booking = _ConvertLinetoBookingObject(Line);
                    if (booking._CustomerId == id && booking._Eventname == name)
                    {
                        MyFile.close();
                        return booking;
                    }

                }

                MyFile.close();

            }
            return Waitinglist("", "", "", "");
        }

        static bool IsBookingExit(string id, string name)
        {
            Waitinglist booking = Find(id, name);
            return (booking._CustomerId == id && booking._Eventname == name);
        }

        static Waitinglist Findname(string name)
        {



            fstream MyFile;
            MyFile.open("Waitinglist.txt", ios::in);//read Mode

            if (MyFile.is_open())
            {
                string Line;
                while (getline(MyFile, Line))
                {
                    Waitinglist booking = _ConvertLinetoBookingObject(Line);
                    if (booking._Eventname == name)
                    {
                        MyFile.close();
                        return booking;
                    }

                }

                MyFile.close();

            }
            return Waitinglist("", "", "", "");
        }

        static bool IsBookingnameExit(string name)
        {
            Waitinglist booking = Findname(name);
            return (booking._Eventname == name);
        }

        static Waitinglist Find(string id)
        {



            fstream MyFile;
            MyFile.open("Waitinglist.txt", ios::in);//read Mode

            if (MyFile.is_open())
            {
                string Line;
                while (getline(MyFile, Line))
                {
                    Waitinglist booking = _ConvertLinetoBookingObject(Line);
                    if (booking._WaitId == id)
                    {
                        MyFile.close();
                        return booking;
                    }

                }

                MyFile.close();

            }
            return Waitinglist("", "", "", "");
        }

        static bool IsBookingExit(string id)
        {
            Waitinglist booking = Find(id);
            return (booking._WaitId == id);
        }

        static bool AddCustomer(string id, string name)
        {
            Waitinglist wait;
            random_device rd;
            uniform_int_distribution<int> dist(3000000, 3999999);
            string num = to_string(dist(rd));

            while (IsBookingExit(name))
            {
                name = to_string(dist(rd));
            }
            wait._WaitId = num;
            wait._Jointime = clsInputValidate::Datetime();
            wait._CustomerId = id;
            wait._Eventname = name;
            wait._AddDataLineToFile(_ConverBookingObjectToLine(wait));

            cout << "\n\t\t\t\tyou have been added to the waiting list!";
            return true;
        }

        static bool RemoveCustomer(Waitinglist wait)
        {
            vector <Waitinglist> vWait = _LoadBookingDataFromFile();
            for (Waitinglist& C : vWait)
            {
                if (C.getId() == wait.getId())
                {
                    C.checkdel = true;
                    _SaveBookingDataToFile(vWait);
                    return true;
                }
            }

        }

};

