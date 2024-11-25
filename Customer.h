#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include <vector>
#include <random>
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
            vCustomerData[3], vCustomerData[4], vCustomerData[5]);

    }

    static string _ConverCustomerObjectToLine(Customer customer, string Seperator = "#//#")
    {

        string stCustomerRecord = "";
        stCustomerRecord += customer.getName() + Seperator;
        stCustomerRecord += customer.getUsername() + Seperator;
        stCustomerRecord += customer.getPassword() + Seperator;
        stCustomerRecord += customer.getPhone() + Seperator;
        stCustomerRecord += customer.getEmail() + Seperator;
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

    Customer(string name, string username, string password, string phone, string email, string customerId) :
        clsPerson(name, username, password, phone, email)
    {
        _CustomerId = customerId;
    }

    Customer() {}

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
        return Customer("", "", "", "", "", "");
    }

    static bool IsCustomerIdExist(string customerId)
    {

        Customer customer = Customer::Find(customerId);

        return customer.getCustomerId() == customerId;
    }

    static Customer FindUserName(string Name)
    {



        fstream MyFile;
        MyFile.open("Customer.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                Customer customer = _ConvertLinetoCustomerObject(Line);
                if (customer.getUsername() == Name)
                {
                    MyFile.close();
                    return customer;
                }

            }

            MyFile.close();

        }
        return Customer("", "", "", "", "", "");
    }

    static bool IsCustomerUserNameExist(string Name)
    {

        Customer customer = Customer::FindUserName(Name);

        return customer.getUsername() == Name;
    }

    static Customer FindCustomer(string name, string password)
    {

        fstream MyFile;
        MyFile.open("Customer.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                Customer customer = _ConvertLinetoCustomerObject(Line);
                if (customer.getUsername() == name && customer.getPassword() == password)
                {
                    MyFile.close();
                    return customer;
                }

            }

            MyFile.close();

        }
        return Customer("", "", "", "", "", "");
    }

    static bool IsCustomerExist(string name, string password)
    {

        Customer customer = Customer::FindCustomer(name, password);

        return customer.getUsername() == name && customer.getPassword() == password;
    }

    static void AddCustomer(string& name)
    {
        Customer customer;
        while (IsCustomerUserNameExist(name))
        {
            cout << "\n\t\t\t\tthis username already exit, enter another name: ";
            name = clsInputValidate::ReadName();
        }
        customer.setUsername(name);

        cout << "\n\t\t\t\tenter your name? ";
        string word = clsInputValidate::ReadString();
        customer.setName(word);

        cout << "\n\t\t\t\tenter password? ";
        word = clsInputValidate::ReadPassword();
        customer.setPassword(word);

        cout << "\n\t\t\t\tenter your phone? ";
        word = clsInputValidate::ReadString();
        customer.setPhone(word);

        cout << "\n\t\t\t\tenter your email? ";
        word = clsInputValidate::ReadEmail();
        customer.setEmail(word);

        random_device rd;
        uniform_int_distribution<int> dist(2000000, 2999999);
        word = to_string(dist(rd));

        while (IsCustomerIdExist(word))
        {
            word = to_string(dist(rd));

        }
        customer.setCustomerId(word);
        customer._AddDataLineToFile(_ConverCustomerObjectToLine(customer));
    }



};


