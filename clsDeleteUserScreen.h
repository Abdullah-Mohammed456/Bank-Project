#pragma once
#include <iostream>
#include "clsScreen.h"
using namespace std;
class clsDeleteUserScreen:protected clsScreen {
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
	static void ShowDeleteUser() {
		clsScreen::_DrawScreenHeader("Delete User Screen");
		clsListUsers::ShowListUsersScreen(false);
		cout << "Enter Your User you want to delete it: ";
		string username = clsUtilities::ReadString();
		while (!clsUser::IsUserExist(username)) {
			cout << "Sorry Your username not valid, Try Again: ";
			username = clsUtilities::ReadString();
		}
		clsUser User = clsUser::Find(username);
		_PrintUserInfo(User);
		cout << "Are You Sure For That? To Delete it (Y/N): ";
		char cDelete; cin >> cDelete;
		if (cDelete == 'Y' || cDelete == 'y') {
			if (User.DeleteUser()) {
				cout << "user has been deleted successfully:-)\n";
				_PrintUserInfo(User);
			}
			else {
				cout << "Error, Sorry the User has not been deleted\n";
			}
		}

	}
};