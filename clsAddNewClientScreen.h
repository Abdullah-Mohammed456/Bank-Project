#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsPerson.h"
#include "clsScreen.h"
using namespace std;
class clsAddNewClientScreen:protected clsScreen {
private:
	static void _ReadClientInfo(clsBankClient& Client) {
		cout << "Enter First Name: ";
		Client.FirstName = clsUtilities::ReadString();
		cout << "Enter Last Name: ";
		Client.LastName = clsUtilities::ReadString();
		cout << "Enter Email: ";
		Client.Email = clsUtilities::ReadString();
		cout << "Enter Phone: ";
		Client.Phone = clsUtilities::ReadString();
		cout << "Enter Pin Code: ";
		Client.SetPinCode(clsUtilities::ReadString());
		cout << "Enter Account Balance: ";
		float accountbalance=clsUtilities::ReadDblNumber("Please Enter a Number: ");
		
		Client.SetAccountBalance(accountbalance);
	}
	static void _PrintClientInfo(clsBankClient Client) {
		cout << "\nClient Card:\n";
		Separator();
		cout << "FirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.GetFullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.GetPinCode();
		cout << "\nBalance     : " << Client.GetAccountBalance() << endl;
		Separator();
	}
public:
	static void ShowAddNewClient() {
		if (!clsScreen::Permissions(clsUser::enPermissions::pAddNewClient))
		{
			return;
		}
		clsScreen::_DrawScreenHeader("Add New Client Screen");
		cout << "Enter Account Number: ";
		string accountnumber = clsUtilities::ReadString();
		while (clsBankClient::IsClientExist(accountnumber))
		{
			cout << "Invalid Account Number, Please Try Again: ";
			accountnumber = clsUtilities::ReadString();
		}
		clsBankClient NewClient = clsBankClient::GetAddNewClient(accountnumber);
		_ReadClientInfo(NewClient);
		clsBankClient::enSaveResults Result = NewClient.Save();
		switch (Result)
		{
		case clsBankClient::svFaildEmptyObject:
			cout << "The Client is Empty\n";
			break;
		case clsBankClient::svSucceeded:
			cout << "Account has been Created successfully:-)\n";
			_PrintClientInfo(NewClient);
			break;
		case clsBankClient::svFaildAccountExist:
			cout << "Sorry Account Already Exist You can not add another same\n";
			break;
		default:
			break;
		}
	}
	
};