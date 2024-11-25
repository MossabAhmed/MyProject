#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream>
#include "Seat.h"
#include "Waiting.h"
#include "Event.h"
#include "iomanip"
using namespace std;
enum enPayment{ enBankCard = 1, enSadad = 2, enEdfaly = 3, enTadawul = 4, enMobicach = 5};
enum enStatueB{enActive = 1, enWaiting = 2, enCancel = 3};
class Booking
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
        stBookingRecord +=  + Seperator;
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

            cout << "\n\n\t\t\t\t========================================================\n";
            cout << "\t\t\t\tPurchase Ticket\n";
            cout << "\t\t\t\t========================================================\n";
            Event::ShowEventList();
            cout << "\t\t\t\tenter name of event? ";
            string name = clsInputValidate::ReadString();
            while (!Event::IsEventNameExist(name))
            {
                cout << "\n\t\t\t\tthis event not Exit , enter another name? ";
                name = clsInputValidate::ReadString();
            }
            Event event = Event::FindName(name);

            if (IsBookingExit(customer.getCustomerId(), name) || Waiting::IsWaitingExit(customer.getCustomerId(), name))
            {
                cout << "\n\t\t\t\tYou already book this Event...";
                return;
            }
            char bl;
            if (event.getTotalSeats() == 0)
            {
                cout << "\n\t\t\t\tsorry, there are no tickets available for purchase!"<<
                    "\n\t\t\t\twould you like to be placed on a waiting list ? Y/N? ";
                cin >> bl;
                if (toupper(bl) == 'Y')
                {
                    Waiting::AddCustomerToWaitingList(customer.getCustomerId(), name);
                    cout << "\n\t\t\t\twe have placed you on waiting list!";
                    return;
                }
                else
                {
                    return;
                }

            }

            Booking booking("", "", "", "", 0.0, ' ', 0, enPayment::enBankCard, enStatueB::enActive);

            cout << "\n\t\t\t\tenter row of seat? ";
            char ch;
            cin >> ch;
            cout << "\n\t\t\t\tenter culom of seat? ";
            int cu = clsInputValidate::ReadIntNumber();
            while (IsBookingSeatExit(name, ch, cu))
            {
                cout << "\n\t\t\t\tthis Seat is reserved, enter row? ";
                cin >> ch;
                cout << "\n\t\t\t\tenter culom of seat? ";
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
            
            cout << "\n\t\t\t choice Payment method? [1] BankCard, [2] Sadad, [3] Edfaly, [4] Tadawul, [5] Mobicash? ";
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
            int h = event.getTotalSeats();
            h--;
            event.setTotalSeats(h);
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
            cout << "\n\t\t\t\t Booking Done!";
            

        }


        static void ShowBookingList(Customer customer)
        {
            vector <Booking> vBook = _LoadBookingDataFromFile();
            cout << "\t\t\t\t==========================================\n";
            cout << "\t\t\t\t\tBooking List for " << customer.GetName() << endl;
            cout << "\t\t\t\t==========================================\n";
            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
            cout << "_________________________________________\n" << endl;

            cout << setw(8) << left << "" << "| " << left << setw(15) << "ID";
            cout << "| " << left << setw(20) << "Date";
            cout << "| " << left << setw(12) << "Event Name";
            cout << "| " << left << setw(11) << "Seat Number";
            cout << "| " << left << setw(15) << "Payment Method";
            cout << "| " << left << setw(12) << "Price";
            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
            cout << "_________________________________________\n" << endl;

            int n = 0;

            for (Booking& C : vBook)
            {
                if (C.getCustomerId() == customer.getCustomerId() && Event::IsEventNameExist(C.getEventName()))
                {
                    n++;
                    PrintBookRecordLine(C);
                    cout << endl;
                }
            }
            if (n == 0)
            {
                cout << "\n\t\t\t\tNo book to show!";
            }

            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
            cout << "_________________________________________\n" << endl;
            Waiting::ShowWaitingList(customer.getCustomerId());
            
        }

        static void delBooking(Booking book)
        {
            vector <Booking> vBooking = _LoadBookingDataFromFile();
            for (Booking& C : vBooking)
            {
                if (C.getBookingId() == book.getBookingId())
                {
                    C._Statue = enStatueB::enCancel;
                    _SaveBookingDataToFile(vBooking);
                    return;
                }
            }
        }

        static void AddBook(Booking book, Waiting wait)
        {
            book.setBookingDate(wait.getWaitingDate());
            book.setCustomerId(wait.getCustomerId());
            book._AddDataLineToFile(_ConverBookingObjectToLine(book));
        }

        static void CancelBook(Customer customer)
        {
            cout << "\n\n\t\t\t\t========================================================\n";
            cout << "\t\t\t\t\tCancel Book.\n";
            cout << "\t\t\t\t========================================================\n";
            ShowBookingList(customer);
            cout << "\t\t\t\tenter name of event? ";
            string name = clsInputValidate::ReadString();
            while (!Event::IsEventNameExist(name))
            {
                cout << "\n\t\t\t\tthis event not Exit , enter another name? ";
                name = clsInputValidate::ReadString();
            }
            if (!IsBookingExit(customer.getCustomerId(), name) && !Waiting::IsWaitingExit(customer.getCustomerId(), name))
            {
                cout << "\n\t\t\t\tYou have not book...";
                system("pause>0");
                return;
            }
            Booking book = Find(customer.getCustomerId(), name);
            Waiting wait = Waiting::Findwait(customer.getCustomerId(), name);
            if (book.getEventName() == name)
            {
                delBooking(book);
                wait = Waiting::Findname(name);
                if (wait.getEventName() == name)
                {
                    AddBook(book, wait);
                    Waiting::RemoveCustomerFromWaitingList(wait);
                }
            }
            else
            {
                Waiting::RemoveCustomerFromWaitingList(wait);
            }
            cout << "\n\t\t\t\tRemove Successfuly!";
            
        }

     
        static void PrintBookRecordLine(Booking book)
        {

            cout << setw(8) << left << "" << "| " << setw(15) << left << book.getBookingId();
            cout << "| " << setw(20) << left << book.getBookingDate();
            cout << "| " << setw(12) << left << book.getEventName();
            cout << "| " << setw(11) << left << book.getRow() + to_string(book.getCulomn());
            cout << "| " << setw(15) << left << book.getPayment();
            cout << "| " << setw(12) << left << book.getTotalPrice();

        }


        static void ShowEvents()
        {
            Event::ShowEventList();
            
        }
};

