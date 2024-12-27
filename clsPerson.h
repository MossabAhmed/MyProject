#pragma once
#include <iostream>
#include <string>
using namespace std;
class clsPerson
{
    string _Name;
    string _Username;
    string _Password;
    string _Phone;
    string _Email;

public:

    clsPerson(string name, string username, string password, string phone, string email)
    {
        _Name = name;
        _Username = username;
        _Password = password;
        _Phone = phone;
        _Email = email;
    }

    clsPerson() {}

    void setName(string name)
    {
        _Name = name;
    }

    string getName()
    {
        return _Name;
    }

    void setUsername(string name)
    {
        _Username = name;
    }

    string getUsername()
    {
        return _Username;
    }

    void setPassword(string name)
    {
        _Password = name;
    }

    string getPassword()
    {
        return _Password;
    }

    void setPhone(string name)
    {
        _Phone = name;
    }

    string getPhone()
    {
        return _Phone;
    }

    void setEmail(string name)
    {
        _Email = name;
    }

    string getEmail()
    {
        return _Email;
    }


};

