#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
using namespace std;

class Customer : public clsPerson
{
	string _CustomerId;


    static Customer _ConvertLinetoCustomerObject(string Line, string Seperator = "#//#")
    {
        vector<string> vCustomerData;
        vCustomerData = clsString::Split(Line, Seperator);

        return Customer(vCustomerData[0], vCustomerData[1], vCustomerData[2],
            vCustomerData[3]);

    }
    static  vector <Customer> _LoadCustomerDataFromFile()
    {

        vector <Customer> vCustomer;

        fstream MyFile;
        MyFile.open("Customer.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                Customer customer = _ConvertLinetoCustomerObject(Line);

                vCustomer.push_back(customer);
            }

            MyFile.close();

        }

        return vCustomer;

    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Customer.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

public:

    Customer(string name, string email, string phone, string customerId) :
        clsPerson(name, email, phone)
    {
        _CustomerId = customerId;
    }

    string getCustomerId()
    {
        return _CustomerId;
    }


   

    static Customer Find(string customerId)
    {



        fstream MyFile;
        MyFile.open("Customer.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                Customer customer = _ConvertLinetoCustomerObject(Line);
                if (customer.getCustomerId() == customerId)
                {
                    MyFile.close();
                    return customer;
                }

            }

            MyFile.close();

        }
        return Customer("", "", "", "");
    }


    static Customer Find(string customerId)
    {



        fstream MyFile;
        MyFile.open("Customer.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                Customer customer = _ConvertLinetoCustomerObject(Line);
                if (customer.getCustomerId() == customerId)
                {
                    MyFile.close();
                    return customer;
                }

            }

            MyFile.close();

        }
        return Customer("", "", "", "");
    }

    static bool IsClientExist(string customerId)
    {

        Customer customer = Customer::Find(customerId);

        return customer.getCustomerId() == customerId;
    }

    void CreatAccount()
    {
        string customerId;
        getline(cin >> ws, customerId);
        while (IsClientExist(customerId))
        {
            cout << "sorry, is exit, enter another id.";
            getline(cin >> ws, customerId);

        }

    }
};

