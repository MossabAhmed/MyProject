#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
class Waiting
{
	string _WaitingId;
    string _WaitingDate;
    string _Customer_Id;
    string _EventName;
    bool checkdel = false;
    static Waiting _ConvertLinetoWaitingObject(string Line, string Seperator = "#//#")
    {
        vector<string> vWaitingData;
        vWaitingData = clsString::Split(Line, Seperator);
        if (vWaitingData.empty())
        {
            return Waiting("", "", "", "");
        }
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
                if (C.checkdel == false)
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
        return _WaitingDate;
    }

    string getCustomerId()
    {
        return _Customer_Id;
    }

    string getEventName()
    {
        return _EventName;
    }

    static Waiting Findwait(string id, string name)
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
        Waiting waiting = Findwait(id, name);
        return waiting.getCustomerId() == id && waiting.getEventName() == name;
    }

    static Waiting Findname(string name)
    {



        fstream MyFile;
        MyFile.open("Waiting.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                Waiting waiting = _ConvertLinetoWaitingObject(Line);
                if (waiting.getEventName() == name)
                {
                    MyFile.close();
                    return waiting;
                }

            }

            MyFile.close();

        }
        return Waiting("", "", "", "");
    }

    static bool IsWaitingnameExit(string name)
    {
        Waiting waiting = Findname(name);
        return waiting.getEventName() == name;
    }

    static Waiting FindId(string id)
    {



        fstream MyFile;
        MyFile.open("Waiting.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                Waiting waiting = _ConvertLinetoWaitingObject(Line);
                if (waiting.getWaitingId() == id)
                {
                    MyFile.close();
                    return waiting;
                }

            }

            MyFile.close();

        }
        return Waiting("", "", "", "");
    }

    static bool IsWaitingIdExit(string id)
    {
        Waiting waiting = FindId(id);
        return waiting.getWaitingId() == id;
    }


    static void AddCustomerToWaitingList(string id, string name)
    {
        Waiting waiting = Findname(name);
        string word;

        if (waiting.getEventName() != name)
        {
            random_device rd;
            uniform_int_distribution<int> dist(4000000, 4999999);
            word = to_string(dist(rd));

            while (IsWaitingIdExit(word))
            {
                word = to_string(dist(rd));
            }
            waiting.setWaitingId(word);
        }
        waiting.setWaitingDate(clsInputValidate::Datetime());
        waiting.setCustomerId(id);
        waiting.setEventName(name);
        waiting._AddDataLineToFile(_ConverWaitingObjectToLine(waiting));
        
    }

    static void RemoveCustomerFromWaitingList(Waiting wait)
    {
        vector <Waiting> vWait = _LoadWaitingDataFromFile();
        for (Waiting& C : vWait)
        {
            if (wait.getCustomerId() == C.getCustomerId() && wait.getEventName() == C.getEventName())
            {
                C.checkdel = true;
                _SaveWaitingDataToFile(vWait);
                return;
            }
        }

    }

    static void PrintWaitRecordLine(Waiting wait)
    {

        cout << setw(8) << left << "" << "| " << setw(15) << left << wait.getWaitingId();
        cout << "| " << setw(20) << left << wait.getWaitingDate();
        cout << "| " << setw(12) << left << wait.getEventName();
    }

        public:


            static void ShowWaitingList(string id)
            {
                vector <Waiting> vWait = _LoadWaitingDataFromFile();
                cout << "\t==========================================\n";
                cout << "\tWaiting List Screen" << endl;
                cout << "\t==========================================\n";
                cout << setw(8) << left << "" << "\n\t_______________________________________________________";
                cout << "_________________________________________\n" << endl;

                cout << setw(8) << left << "" << "| " << left << setw(15) << "Waiting ID";
                cout << "| " << left << setw(20) << "Join Date";
                cout << "| " << left << setw(12) << "Event Name";
                cout << setw(8) << left << "" << "\n\t_______________________________________________________";
                cout << "_________________________________________\n" << endl;

                int n = 0;

                for (Waiting& C : vWait)
                {
                    if (C.getCustomerId() == id)
                    {
                        n++;
                        PrintWaitRecordLine(C);
                        cout << endl;
                    }
                }
                if (n == 0)
                {
                    cout << "\n\t\t\tNo Data to show!";
                }

                cout << setw(8) << left << "" << "\n\t_______________________________________________________";
                cout << "_________________________________________\n" << endl;

            }

    
};

