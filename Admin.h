#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include "Event.h"
#include "Movie.h"
using namespace std;
class Admin : public clsPerson
{
private:
    string _AdminId;
    Event* admin;

    static Admin _ConvertLinetoAdminObject(string Line, string Seperator = "#//#")
    {
        vector<string> vAdminData;
        vAdminData = clsString::Split(Line, Seperator);

        return Admin(vAdminData[0], vAdminData[1], vAdminData[2],
            vAdminData[3], vAdminData[4], vAdminData[5]);

    }


    static  vector <Admin> _LoadAdminDataFromFile()
    {

        vector <Admin> vAdmin;

        fstream MyFile;
        MyFile.open("Admin.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                Admin admin = _ConvertLinetoAdminObject(Line);

                vAdmin.push_back(admin);
            }

            MyFile.close();

        }

        return vAdmin;

    }





public:

    Admin(string name, string username, string password, string phone, string email, string adminId) :
        clsPerson(name, username, password, phone, email)
    {
        _AdminId = adminId;
    }

    Admin(Event* event)
    {
        this->admin = event;
    }

    Admin() {}

    static Admin Find(string username, string password)
    {
        fstream MyFile;
        MyFile.open("Admin.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                Admin admin = _ConvertLinetoAdminObject(Line);
                if (admin.getUsername() == username && admin.getPassword() == password)
                {
                    MyFile.close();
                    return admin;
                }

            }

            MyFile.close();

        }
        return Admin("", "", "", "", "", "");
    }
    static Admin Find(string username)
    {



        fstream MyFile;
        MyFile.open("Admin.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                Admin admin = _ConvertLinetoAdminObject(Line);
                if (admin.getUsername() == username)
                {
                    MyFile.close();
                    return admin;
                }

            }

            MyFile.close();

        }
        return Admin("", "", "", "", "", "");
    }


    static bool IsAdminExist(string username)
    {

        Admin admin = Admin::Find(username);

        return admin.getUsername() == username;
    }
    static bool IsAdminExist(string username, string password)
    {

        Admin admin = Admin::Find(username, password);

        return admin.getUsername() == username && admin.getPassword() == password;
    }


};


