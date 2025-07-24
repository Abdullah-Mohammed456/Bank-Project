#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
using namespace std;
class clsUpdateClientScreen :clsScreen {
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
		float accountbalance;
		cin >> accountbalance;
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
	static void ShowUpdateClient() {
		if (!clsScreen::Permissions(clsUser::enPermissions::pUpdateClients))
		{
			return;
		}
		clsScreen::_DrawScreenHeader("Update Client Screen");
		cout << "Enter Your Account Number: ";
		string _accountnumber = clsUtilities::ReadString();
		while (!clsBankClient::IsClientExist(_accountnumber)) {

			cout << "Invalid Account Number, Please Try again: ";
			_accountnumber = clsUtilities::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(_accountnumber);
		_PrintClientInfo(Client);
		cout << "\n\nUpdate Client Info:";
		cout << "\n____________________\n";
		_ReadClientInfo(Client);
		clsBankClient::enSaveResults SaveResult = Client.Save();
		switch (SaveResult) {
		case clsBankClient::enSaveResults::svSucceeded: {
			cout << "\nAccount Updated Successfully :-)\n";
			_PrintClientInfo(Client);
			break;
		}
		case clsBankClient::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError account was not saved because it's Empty";
			break;
		}
		}
	}

};