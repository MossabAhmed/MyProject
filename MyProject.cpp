#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include <random>
#include "Customer.h"
#include "Admin.h"
#include "Booking.h"
#include "clsInputValidate.h"
#include "Event.h"
using namespace std;

void manageEvent()
{

	system("cls");
	cout << "========================================================\n";
	cout << "Login\n";
	cout << "========================================================\n";
	cout << "[1] Add Event.\n";
	cout << "[2] Modify Event.\n";
	cout << "[3] Delete Event.\n";
	cout << "[4] End Program.\n";
	cout << "========================================================\n";
	cout << "enter number from [1] to [4]? ";
	int choice ;
	try
	{
		choice = clsInputValidate::ReadIntNumber();
		if (choice < 1 || choice > 4)
			throw "error";
	}
	catch (...)
	{
		cout << "\nerror, press any key to replay enter...";
		system("pause>0");
		manageEvent();
	}

	switch (choice)
	{
	case 1:
		system("cls");
		Event::AddEvent();
		manageEvent();
		break;
	case 2:
		system("cls");
		Event::ModifyEvent();
		manageEvent();
		break;
	case 3:
		system("cls");
		Event::DeleteEvent();
		manageEvent();
		break;
	default:
		break;
	}


}

void AdminSystem(string name)
{
	string password;
	do
	{
		system("cls");
		cout << "========================================================\n";
		cout << "Admin System\n";
		cout << "========================================================\n";
		cout << "enter password? ";
		password = clsInputValidate::ReadString();
		
	} while (!Admin::IsAdminExist(name, password));

	manageEvent();

}

void CustomerSystem(Customer customer)
{

}

void CreateCustomer()
{

}

void BookingSystem()
{
	system("cls");
	cout << "========================================================\n";
	cout << "Booking Ticket Event\n";
	cout << "========================================================\n";
	cout << "Are You New User? ";
	bool bl;
	cin >> bl;
	if (bl)
	{
		CreateCustomer();
		return;
	}

	cout << "\nenter username?  ";
	string name = clsInputValidate::ReadString();
	while (!Admin::IsAdminExist(name) && !Customer::IsCustomerExist(name))
	{
		cout << "\nthis Username is not exit, enter another username? ";
        name = clsInputValidate::ReadString();

	}
	Admin admin = Admin::Find(name);

	Customer customer = Customer::FindName(name);

	if (admin.getusername() == name)
	{
		AdminSystem(name);
		return;
	}
	CustomerSystem(customer);

}

int main()
{
	BookingSystem();
	system("pause>0");
}
