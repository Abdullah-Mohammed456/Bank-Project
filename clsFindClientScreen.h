#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsUtilities.h"
using namespace std;
class clsFindClientScreen:protected clsScreen{
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
	static void ShowFindClient() {
		if (!clsScreen::Permissions(clsUser::enPermissions::pFindClient))
		{
			return;
		}
		clsScreen::_DrawScreenHeader("Find Client Screen");
		cout << "Please Enter Account Number: ";
		string accountnumber = clsUtilities::ReadString();
		while (!clsBankClient::IsClientExist(accountnumber)) {
			cout << "Invalid Account Number, Please try again: ";
			accountnumber = clsUtilities::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(accountnumber);
		if (Client.IsEmpty()) {
			cout << "\nClient Not Found\n";	
		}
		else {
			cout << "\nClient Found :-)\n";
		}
		_PrintClientInfo(Client);
	}
};