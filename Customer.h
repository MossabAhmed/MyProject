#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputValidate.h"
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

        return Customer(enStatue::enCustomer, vCustomerData[0], vCustomerData[1], vCustomerData[2],
            vCustomerData[3]);

    }

    static string _ConverCustomerObjectToLine(Customer customer, string Seperator = "#//#")
    {

        string stCustomerRecord = "";
        stCustomerRecord += customer.GetName() + Seperator;
        stCustomerRecord += customer.GetEmail() + Seperator;
        stCustomerRecord += customer.GetPhone() + Seperator;
        stCustomerRecord += customer.getCustomerId();


        return stCustomerRecord;

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

    static void _SaveCustomerDataToFile(vector <Customer> vCustomer)
    {

        fstream MyFile;
        MyFile.open("Customer.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (Customer C : vCustomer)
            {
                DataLine = _ConverCustomerObjectToLine(C);
                MyFile << DataLine << endl;

            }

            MyFile.close();

        }

    }

public:

    Customer(enStatue statue, string name, string email, string phone, string customerId) :
        clsPerson(statue, name, email, phone)
    {
        _CustomerId = customerId;
    }

    Customer(){}

    void setCustomerId(string customerId)
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
        return Customer(enStatue::enCustomer, "", "", "", "");
    }

    static Customer FindName(string Name)
    {



        fstream MyFile;
        MyFile.open("Customer.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                Customer customer = _ConvertLinetoCustomerObject(Line);
                if (customer.GetName() == Name)
                {
                    MyFile.close();
                    return customer;
                }

            }

            MyFile.close();

        }
        return Customer(enStatue::enCustomer, "", "", "", "");
    }

    static bool IsCustomerExist(string customerId)
    {

        Customer customer = Customer::Find(customerId);

        return customer.getCustomerId() == customerId;
    }


    static bool IsCustomerNameExist(string Name)
    {

        Customer customer = Customer::FindName(Name);

        return customer.GetName() == Name;
    }

    static void AddCustomer(string& name)
    {
        Customer customer(enStatue::enCustomer, "", "", "", "");
        while (IsCustomerNameExist(name))
        {
            cout << "\nthis event already exit, enter another name: ";
            name = clsInputValidate::ReadString();
        }
        customer.SetName(name);

        cout << "\nenter your email? ";
        string word = clsInputValidate::ReadString();
        customer.SetEmail(word);

        cout << "\nenter your phone? ";
        word = clsInputValidate::ReadString();
        customer.SetPhone(word);

        random_device rd;
        uniform_int_distribution<int> dist(2000000, 2999999);
        word = to_string(dist(rd));

        while (IsCustomerExist(word))
        {
            word = to_string(dist(rd));

        }
        customer.setCustomerId(word);
        customer._AddDataLineToFile(_ConverCustomerObjectToLine(customer));
    }
    
};

