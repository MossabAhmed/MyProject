#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream>
using namespace std;
class Waiting
{
	string _WaitingId;
    string _WaitingDate;
    string _Customer_Id;
    string _EventName;
    static Waiting _ConvertLinetoWaitingObject(string Line, string Seperator = "#//#")
    {
        vector<string> vWaitingData;
        vWaitingData = clsString::Split(Line, Seperator);

        return Waiting( vWaitingData[0], vWaitingData[1], vWaitingData[2],
            vWaitingData[3]);

    }

    static string _ConverWaitingObjectToLine(Waiting waiting, string Seperator = "#//#")
    {

        string stWaitingRecord = "";
        stWaitingRecord += waiting.getWaitingId() + Seperator;
        stWaitingRecord += waiting.getWaitingDate() + Seperator;
        stWaitingRecord += waiting.getCustomerId() + Seperator;
        stWaitingRecord += waiting.getEventName();


        return stWaitingRecord;

    }
    static  vector <Waiting> _LoadWaitingDataFromFile()
    {

        vector <Waiting> vWaiting;

        fstream MyFile;
        MyFile.open("Waiting.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                Waiting waiting = _ConvertLinetoWaitingObject(Line);

                vWaiting.push_back(waiting);
            }

            MyFile.close();

        }

        return vWaiting;

    }




    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Waiting.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static void _SaveWaitingDataToFile(vector <Waiting> vWaiting)
    {

        fstream MyFile;
        MyFile.open("Waiting.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (Waiting C : vWaiting)
            {
                DataLine = _ConverWaitingObjectToLine(C);
                MyFile << DataLine << endl;

            }

            MyFile.close();

        }

    }
public:
    Waiting(string waitingId, string waitingDate, string _customer_Id, string eventName)
    {
        _WaitingId = waitingId;
        _WaitingDate = waitingDate;
        _Customer_Id = _customer_Id;
        _EventName = eventName;
    }

    Waiting(){}

    void setWaitingId(string waitingId)
    {
        _WaitingId = waitingId;
    }

    void setWaitingDate(string waitingDate)
    {
        _WaitingDate = waitingDate;
    }

    void setCustomerId(string customerId)
    {
        _Customer_Id = customerId;
    }

    void setEventName(string eventName)
    {
        _EventName = eventName;
    }

    string getWaitingId()
    {
        return _WaitingId;
    }

    string getWaitingDate()
    {
        _WaitingDate;
    }

    string getCustomerId()
    {
        return _Customer_Id;
    }

    string getEventName()
    {
        return _EventName;
    }

    static Waiting Find(string id, string name)
    {



        fstream MyFile;
        MyFile.open("Waiting.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                Waiting waiting = _ConvertLinetoWaitingObject(Line);
                if (waiting.getCustomerId() == id && waiting.getEventName() == name)
                {
                    MyFile.close();
                    return waiting;
                }

            }

            MyFile.close();

        }
        return Waiting( "", "", "", "" );
    }

    static bool IsWaitingExit(string id, string name)
    {
        Waiting waiting = Find(id, name);
        return waiting.getCustomerId() == id && waiting.getEventName() == name;
    }

    static void AddCustomerToWaitingList(string id, string name)
    {

    }
    
};

