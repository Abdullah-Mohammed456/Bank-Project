#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUtilities.h"
#include "clsBankClient.h"
using namespace std;
class clsDepositScreen:protected clsScreen {
private:
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
	static void ShowDepositScreen() {
		clsScreen::_DrawScreenHeader("Deposit Screen");
		cout << "Enter Account Number: ";
		string accountnumber = clsUtilities::ReadString();
		while (!clsBankClient::IsClientExist(accountnumber)) {
			SetColor(Red);
			cout << "Please Enter Valid Account Number: ";
			Reset();
			accountnumber = clsUtilities::ReadString();
		
		}
		clsBankClient Client = clsBankClient::Find(accountnumber);
		_PrintClientInfo(Client);
		cout << "Enter Amount You want to add: ";
		double Amount = clsUtilities::ReadDblNumber("Please Enter a Number: ");
		cout << "Are You Sure(Y/N): ";
		char choice;
		cin >> choice;
		if (choice == 'Y' || choice == 'y') {
			Client.Deposit(Amount);
			cout << "Successful Deposit:-)\n";
			Separator();
			SetColor(Green);
			cout << "Your Total Balance is: " << Client.AccountBalance << endl;
			Reset();
		}
		else {
			cout << "Your operation is cancel\n";
		}

	}
};