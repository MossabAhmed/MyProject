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


    Admin(string name, string email, string phone, string username, string password, string adminId) : 
        clsPerson(name, email, phone )
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
                if (admin.getusername() == username)
                {
                    MyFile.close();
                    return admin;
                }

            }

            MyFile.close();

        }
        return Admin("", "", "", "", "", "");
    }


    static bool IsClientExist(string customerId)
    {

        Admin customer = Admin::Find(customerId);

        return customer.getusername() == customerId;
    }
    static bool IsClientExist(string customerId, string password)
    {

        Admin customer = Admin::Find(customerId, password);

        return customer.getusername() == customerId && customer.getpassword() == password;
    }
    void CreatAccount()
    {
        Admin admin("", "", "", "", "", "");
        string customerId;
        getline(cin >> ws, customerId);
        while (IsClientExist(customerId))
        {
            cout << "sorry, is exit, enter another id.";
            getline(cin >> ws, customerId);

        }
        admin.SetName(customerId);
        getline(cin >> ws, customerId);
        admin.SetEmail(customerId);


    }

};


