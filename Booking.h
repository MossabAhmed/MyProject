#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream>
#include "Seat.h"
#include "Waiting.h"
#include "Event.h"
#include "clsDate.h"
using namespace std;
enum enPayment{ enBankCard = 1, enSadad = 2, enEdfaly = 3, enTadawul = 4, enMobicach = 5};
enum enStatueB{enActive = 1, enWaiting = 2, enCancel = 3};
class Booking : public Event, Seat
{
	string _BookingId;
	string _BookingDate;
    string _CustomerId;
    string _NameEvent;
    float _TotalPrice;
    enPayment _Payment;
    enStatueB _Statue;

    static Booking _ConvertLinetoBookingObject(string Line, string Seperator = "#//#")
    {
        vector<string> vBookingData;
        vBookingData = clsString::Split(Line, Seperator);
        if (vBookingData.empty())
        {
            return Booking("", "", "", "", 0.0, ' ', 0, enPayment::enBankCard, enStatueB::enActive);
        }
        return Booking(vBookingData[0], vBookingData[1], vBookingData[2],
            vBookingData[3], stod(vBookingData[4]), vBookingData[5][0], stoi(vBookingData[6]),
            vBookingData[7] == "BankCard" ? enPayment::enBankCard : (vBookingData[7] == "Sadad" ? enPayment::enSadad : (vBookingData[7] == "Edfaly" ? enPayment::enEdfaly :
           (vBookingData[7] == "Tadawul" ? enPayment::enTadawul : enPayment::enMobicach))),
            vBookingData[8] == "Active" ? enStatueB::enActive : enStatueB::enWaiting);

    }

    static string _ConverBookingObjectToLine(Booking booking, string Seperator = "#//#")
    {

        string stBookingRecord = "";
        stBookingRecord += booking.getBookingId() + Seperator;
        stBookingRecord += booking.getBookingDate() + Seperator;
        stBookingRecord += booking.getCustomerId() + Seperator;
        stBookingRecord += booking.getEventName() + Seperator;
        stBookingRecord += to_string(booking.getTotalPrice()) + Seperator;
        stBookingRecord += booking.getRow() + Seperator;
        stBookingRecord += to_string(booking.getCulomn()) + Seperator;
        stBookingRecord += booking.getPayment() + Seperator;
        stBookingRecord += booking.getStatue();

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
                if (C._Statue != enStatueB::enCancel)
                DataLine = _ConverBookingObjectToLine(C);
                MyFile << DataLine << endl;

            }

            MyFile.close();

        }

    }

    public:
        Booking(string bookingId, string bookingDate, string customerId, string name, float price, char row, int culomn, enPayment payment, enStatueB statue) :
            Seat(row, culomn)
        {
            _BookingId = bookingId;
            _BookingDate = bookingDate;
            _CustomerId = customerId;
            _NameEvent = name;
            _TotalPrice = price;
            _Payment = payment;
            _Statue = statue;
        }

        Booking(){}

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
        void setPayment(enPayment statue)
        {
            _Payment = statue;
        }
        string getPayment()
        {
            return (_Payment == enPayment::enBankCard ? "BankCard" : (_Payment == enPayment::enSadad ? "Sadad" : 
                (_Payment == enPayment::enEdfaly ? "Edfaly" :
                (_Payment == enPayment::enTadawul ? "Tadawul" : "MobiCash"))));
        }

        void setStatue(enStatueB statue)
        {
            _Statue = statue;
        }

        string getStatue()
        {
            return (_Statue == enStatueB::enActive ? "Active" : (_Statue == enStatueB::enWaiting ? "Waiting" : "Cancel"));
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
            return Booking("", "", "", "", 0.0, ' ', 0, enPayment::enBankCard, enStatueB::enActive);
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
            return Booking("", "", "", "", 0.0, ' ', 0, enPayment::enBankCard, enStatueB::enActive);
        }

        static bool IsBookingIdExit(string id)
        {
            Booking booking = FindId(id);
            return (booking.getBookingId() == id);
        }

        static Booking FindSeat(string name, char ch, int cu)
        {
            fstream MyFile;
            MyFile.open("Booking.txt", ios::in);//read Mode

            if (MyFile.is_open())
            {
                string Line;
                while (getline(MyFile, Line))
                {
                    Booking booking = _ConvertLinetoBookingObject(Line);
                    if (booking.getEventName() == name && booking.getRow() == ch && booking.getCulomn() == cu)
                    {
                        MyFile.close();
                        return booking;
                    }

                }

                MyFile.close();

            }
            return Booking("", "", "", "", 0.0, ' ', 0, enPayment::enBankCard, enStatueB::enActive);
        }

        static bool IsBookingSeatExit(string name, char ch, int cu)
        {
            Booking booking = FindSeat(name, ch, cu);
            return (booking.getEventName() == name && booking.getRow() == ch && booking.getCulomn() == cu);
        }

        static void PurchaseTicket(Customer customer)
        {
            cout << "========================================================\n";
            cout << "Purchase Ticket\n";
            cout << "========================================================\n";
            cout << "enter name of event? ";
            string name = clsInputValidate::ReadString();
            while (!Event::IsEventNameExist(name))
            {
                cout << "\nthis event not Exit , enter another name? ";
                name = clsInputValidate::ReadString();
            }
            Event event = Event::FindName(name);

            if (IsBookingExit(customer.getCustomerId(), name) || Waiting::IsWaitingExit(customer.getCustomerId(), name))
            {
                cout << "\nYou already book this Event...";
                system("pause>0");
                return;
            }
           
            bool bl;
            if (event.getTotalTickets() == 0)
            {
                cout << "\nsorry, there are no tickets available for purchase!"<<
                    "\nwould you like to be placed on a waiting list ? ";
                cin >> bl;
                if (bl)
                {
                    Waiting::AddCustomerToWaitingList(customer.getCustomerId(), name);
                    return;
                }
                else
                {
                    return;
                }

            }

            Booking booking("", "", "", "", 0.0, ' ', 0, enPayment::enBankCard, enStatueB::enActive);

            cout << "\nenter row of seat? ";
            char ch;
            cin >> ch;
            cout << "\nenter culom of seat? ";
            int cu = clsInputValidate::ReadIntNumber();
            while (IsBookingSeatExit(name, ch, cu))
            {
                cout << "\nthis Seat is reserved, enter row? ";
                cin >> ch;
                cout << "\nenter culom of seat? ";
                cu = clsInputValidate::ReadIntNumber();
            }

            booking.setRow(ch);
            booking.setCulomn(cu);

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
            float price;
            switch (toupper(booking.getRow()))
            {
            case 'A':
                price = event.getPrice() + (event.getPrice() / 100) * 20;
                break;
            default:
                price = event.getPrice();
                break;
            }

            booking.setTotalPrice(price);
            
            cout << "\n choice Payment method? [1] BankCard, [2] Sadad, [3] Edfaly, [4] Tadawul, [5] Mobicash? ";
            int choice = clsInputValidate::ReadIntNumber();
            switch (choice)
            {
            case enBankCard:
                booking.setPayment(enBankCard);
                break;
            case enSadad:
                booking.setPayment(enSadad);
                break;
            case enEdfaly:
                booking.setPayment(enEdfaly);
                break;
            case enTadawul:
                booking.setPayment(enTadawul);
                break;
            case enMobicach:
                booking.setPayment(enMobicach);
                break;
            default:
                return;
            }
            booking.setCustomerId(customer.getCustomerId());
            booking.setEventName(event.getName());
            booking._AddDataLineToFile(_ConverBookingObjectToLine(booking));
            int h = event.getTotalTickets();
            h--;
            event.setTotalTickets(h);
            vector <Event> vEvent = event._LoadEventDataFromFile();
            for (Event& C : vEvent)
            {
                if (C.getName() == event.getName())
                {
                    C = event;
                    event._SaveEventsDataToFile(vEvent);
                    break;
                }
            }
            cout << "\n Booking Done!";
            cout << "\n press any key to continuo...";
            system("pause>0");

        }

        static void CancelBook(Customer customer)
        {

        }

};

