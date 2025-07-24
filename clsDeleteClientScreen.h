#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
using namespace std;
class clsDeleteClient:protected clsScreen {
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
	static void ShowDeleteClient() {
		if (!clsScreen::Permissions(clsUser::enPermissions::pDeleteClient))
		{
			return;
		}
		clsScreen::_DrawScreenHeader("Delete Client Screen");
		clsListClientsScreen::ShowClientsList(false);
		cout << "Enter Your Account you want to delete it: ";
		string accountnumber = clsUtilities::ReadString();
		while (!clsBankClient::IsClientExist(accountnumber)) {
			cout << "Sorry Your Account Number not valid, Try Again: ";
			accountnumber = clsUtilities::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(accountnumber);
		_PrintClientInfo(Client);
		cout << "Are You Sure For That? To Delete it (Y/N): ";
		char cDelete; cin >> cDelete;
		if (cDelete == 'Y' || cDelete == 'y') {
			if (Client.Delete()) {
				cout << "Account has been deleted successfully:-)\n";
				_PrintClientInfo(Client);
			}
			else {
				cout << "Error, Sorry the Client has not been deleted\n";
			}
		}

	}
};