#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUtilities.h"
using namespace std;
class clsFindUserScreen:protected clsScreen {
private:
	static void _PrintUserInfo(clsUser User) {
		cout << "\nUser Card:\n";
		Separator();
		cout << "FirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.GetFullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUsername    : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermission  : " << User.Permission << endl;
		Separator();
	}
public:
	static void ShowFindUser() {
		clsScreen::_DrawScreenHeader("Find User Screen");
		cout << "Enter Username: ";
		string username = clsUtilities::ReadString();
		while (!clsUser::IsUserExist(username)) {
			cout << "Username Not Exist, Please Try again: ";
			username = clsUtilities::ReadString();
		}
		clsUser User = clsUser::Find(username);
		cout << "\nUser Found:-)\n";
		_PrintUserInfo(User);
	}
};