#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;
class Admin : public clsPerson
{
private:
    string _Username;
    string _Password;
    string _AdminId;


    static Admin _ConvertLinetoAdminObject(string Line, string Seperator = "#//#")
    {
        vector<string> vAdminData;
        vAdminData = clsString::Split(Line, Seperator);

        return Admin(enStatue::enAdmain, vAdminData[0], vAdminData[1], vAdminData[2],
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


    Admin(enStatue statue,string name, string email, string phone, string username, string password, string adminId) : 
        clsPerson(statue, name, email, phone )
    {
        _Username = username;
        _Password = password;
        _AdminId = adminId;

    }

    string getusername()
    {
        return _Username;
    }
    string getpassword()
    {
        return _Password;
    }


    

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
                if (admin.getusername() == username && admin.getpassword() == password)
                {
                    MyFile.close();
                    return admin;
                }

            }

            MyFile.close();

        }
        return Admin(enStatue::enAdmain, "", "", "", "", "", "");
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
                if (admin.getusername() == username)
                {
                    MyFile.close();
                    return admin;
                }

            }

            MyFile.close();

        }
        return Admin(enStatue::enAdmain, "", "", "", "", "", "");
    }


    static bool IsAdminExist(string username)
    {

        Admin admin = Admin::Find(username);

        return admin.getusername() == username;
    }
    static bool IsAdminExist(string username, string password)
    {

        Admin admin = Admin::Find(username, password);

        return admin.getusername() == username && admin.getpassword() == password;
    }
    

};


