#pragma once

#include <iostream>
#include <string>
using namespace std;

enum enStatue { enAdmain = 1, enCustomer };

class clsPerson
{
private:
    enStatue _Statue;
    string _Name;
    string _Email;
    string _Phone;

public:

    clsPerson(enStatue statue ,string Name, string Email, string Phone)
    {
        _Statue = statue;
        _Name = Name;
        _Email = Email;
        _Phone = Phone;
    }

    clsPerson(){}

    void SetName(string Name)
    {
        _Name = Name;
    }

    string GetName()
    {
        return _Name;
    }
    __declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;

    void SetEmail(string Email)
    {
        _Email = Email;
    }

    string GetEmail()
    {
        return _Email;
    }
    __declspec(property(get = GetEmail, put = SetEmail)) string Email;

    void SetPhone(string Phone)
    {
        _Phone = Phone;
    }

    string GetPhone()
    {
        return _Phone;
    }
    __declspec(property(get = GetPhone, put = SetPhone)) string Phone;

    

};

