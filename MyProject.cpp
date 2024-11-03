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

Customer customergen(enStatue::enCustomer, "", "", "", "");

void manageEvent()
{

	system("cls");
	cout << "\n\n\t\t\t\t========================================================\n";
	cout << "\t\t\t\t\tMange Event\n";
	cout << "\t\t\t\t========================================================\n";
	cout << "\t\t\t\t[1] Add Event.\n";
	cout << "\t\t\t\t[2] Modify Event.\n";
	cout << "\t\t\t\t[3] Delete Event.\n";
	cout << "\t\t\t\t[4] Show All Event.\n";
	cout << "\t\t\t\t[5] End Program.\n";
	cout << "\t\t\t\t========================================================\n";
	cout << "\t\t\t\tenter number from [1] to [5]? ";
	int choice ;
	try
	{
		choice = clsInputValidate::ReadIntNumber();
		if (choice < 1 || choice > 5)
			throw "error";
	}
	catch (...)
	{
		cout << "\n\t\t\t\terror, press any key to replay enter...";
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
	case 4:
		system("cls");
		Event::ShowEventList();
		manageEvent();
		break;
	default:
		break;
	}


}

void AdminSystem(string name)
{
	string password;
	string message = "";
	do
	{
		system("cls");
		cout << "\n\n\t\t\t\t========================================================\n";
		cout << "\t\t\t\t\tAdmin System\n";
		cout << "\t\t\t\t========================================================\n";
		cout << "\t\t\t\t" << message << endl;
		cout << "\t\t\t\tenter password? ";
		password = clsInputValidate::ReadString();
		message = "The password is incorrect. Please try again.";
		
	} while (!Admin::IsAdminExist(name, password));

	manageEvent();

}

void CustomerSystem(Customer customer)
{
	system("cls");
	cout << "\n\n\t\t\t\t========================================================\n";
	cout << "\t\t\t\t\tCustomer Interface.\n";
	cout << "\t\t\t\t========================================================\n";
	cout << "\t\t\t\t[1] Purchase Ticket.\n";
	cout << "\t\t\t\t[2] Cancel Booking.\n";
	cout << "\t\t\t\t[3] Show All Bookings.\n";
	cout << "\t\t\t\t[4] Show All Events.\n";
	cout << "\t\t\t\t[5] End Program.\n";
	cout << "\t\t\t\t========================================================\n";
	cout << "\t\t\t\tenter number from [1] to [5]? ";
	int choice;
	try
	{
		choice = clsInputValidate::ReadIntNumber();
		if (choice < 1 || choice > 5)
			throw "error";
	}
	catch (...)
	{
		cout << "\n\t\t\t\terror, press any key to replay enter...";
		system("pause>0");
		CustomerSystem(customer);
	}

	switch (choice)
	{
	case 1:
		system("cls");
		Booking::PurchaseTicket(customer);
		CustomerSystem(customer);
		break;
	case 2:
		system("cls");
		Booking::CancelBook(customer);
		CustomerSystem(customer);
		break;
	case 3:
		system("cls");
		Booking::ShowBookingList(customer);
		CustomerSystem(customer);
		break;
	case 4:
		system("cls");
		Booking::ShowEvents();
		CustomerSystem(customer);
		break;
	default:
		break;
	}

}

void CreateCustomer()
{
	system("cls");
	cout << "\n\n\t\t\t\t========================================================\n";
	cout << "\t\t\t\t\tCreate New User.\n";
	cout << "\t\t\t\t========================================================\n";
	cout << "\t\t\t\tenter name? ";
	string name = clsInputValidate::ReadString();
	Customer::AddCustomer(name);
	CustomerSystem(Customer::FindName(name));
}

void BookingSystem()
{
	system("cls");
	cout << "\n\n\t\t\t\t========================================================\n";
	cout << "\t\t\t\t\tBooking Ticket Event\n";
	cout << "\t\t\t\t========================================================\n";
	cout << "\t\t\t\tAre You New User? Y/N? ";
	char bl;
	cin >> bl;
	if (toupper(bl) == 'Y')
	{
		CreateCustomer();
		return;
	}

	cout << "\n\t\t\t\tenter username?  ";
	string name = clsInputValidate::ReadString();
	while (!Admin::IsAdminExist(name) && !Customer::IsCustomerNameExist(name))
	{
		cout << "\n\t\t\t\tthis Username is not exit, enter another username? ";
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
