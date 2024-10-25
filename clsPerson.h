#pragma once

#include <iostream>
#include <string>
using namespace std;
class clsPerson
{
private:

    string _Name;
    string _Email;
    string _Phone;

public:

    clsPerson(string Name, string Email, string Phone)
    {

        _Name = Name;
        _Email = Email;
        _Phone = Phone;
    }

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

