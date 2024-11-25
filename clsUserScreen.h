#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include "Admin.h"
#include "Customer.h"
#include "GlobalCustomer.h"
#include "CustomerInterface.h"
#include "AdminInterface.h"

using namespace std;
class clsUserScreen : public clsScreen
{
	static void CreateCustomerScreen()
	{

		system("cls");
		string title = "Create New Customer";
		_DrawScreenHeader(title);
		cout << "\t\t\t\tenter username? ";
		string name = clsInputValidate::ReadString();
		Customer::AddCustomer(name);
		globCustomer = Customer::FindUserName(name);
		CustomerInterface::showtypeEvent();
	}
public:
	static void UserInerface()
	{
		system("cls");
		string title = "Booking System";
		_DrawScreenHeader(title);
		cout << "\t\t\t\tAre You New User? Y/N? ";
		string message = "";
		char bl;
		cin >> bl;
		if (toupper(bl) == 'Y')
		{
			CreateCustomerScreen();
			return;
		}
		string name, pass;
		do
		{
			cout << "\n\t\t\t\t" << message;

			cout << "\n\t\t\t\tenter username?  ";
			name = clsInputValidate::ReadString();

			cout << "\n\t\t\t\tenter password?  ";
			pass = clsInputValidate::ReadPassword();
			message = "this username is not exist or password is incorrect!";

		} while (!Admin::IsAdminExist(name, pass) && !Customer::IsCustomerExist(name, pass));

		Admin admin = Admin::Find(name);

		globCustomer = Customer::FindUserName(name);

		if (admin.getUsername() == name)
		{
			AdminInterface::showtypeEvent();
			return;
		}
		CustomerInterface::showtypeEvent();
	}
};

