#pragma once
#include <iostream>
#include "clsScreen.h"
using namespace std;
class clsUpdateUserScreen :protected clsScreen {
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
	static void _ReadUserInfo(clsUser& User) {
		cout << "Enter First Name: ";
		User.FirstName = clsUtilities::ReadString();
		cout << "Enter Last Name: ";
		User.LastName = clsUtilities::ReadString();
		cout << "Enter Email: ";
		User.Email = clsUtilities::ReadString();
		cout << "Enter Phone: ";
		User.Phone = clsUtilities::ReadString();
		cout << "Enter Password: ";
		User.SetPassword(clsUtilities::ReadString());
		User.SetPermission(_ReadPermisssions());
	}
	static int _ReadPermisssions() {
		int per = 0;
		if (clsUtilities::YesOrNo("Do you want all permissions (Y/N): "))
		{
			return clsUser::enPermissions::eAll;
		}
		vector<string>vPermissions = { "List Client","Add New Client","Delete Client","Update Client","Find Client","Transactions","Mange Users" };
		for (int i = 0; i < vPermissions.size(); i++) {
			if (clsUtilities::YesOrNo("Do you want " + vPermissions[i] + " permission (Y / N) : ")) {
				per += pow(2, i);
			}
		}
		if (per == 511) return -1; 
		return per;
	}
public:
	static void ShowUpdateUser() {
		clsScreen::_DrawScreenHeader("Update User Screen");
		cout << "Enter Your Username: ";
		string Username = clsUtilities::ReadString();
		while (!clsUser::IsUserExist(Username)) {

			cout << "Invalid Username, Please Try again: ";
			Username = clsUtilities::ReadString();
		}
		clsUser User = clsUser::Find(Username);
		_PrintUserInfo(User);
		cout << "\n\nUpdate User Info:";
		cout << "\n____________________\n";
		_ReadUserInfo(User);
		clsUser::enSaveResult SaveResult = User.Save();
		switch (SaveResult) {
		case clsUser::enSaveResult::svSuccess:{
			cout << "\nUser Updated Successfully :-)\n";
			_PrintUserInfo(User);
			break;
		}
		case clsUser::enSaveResult::svFaildExist:
		{
			cout << "\nError User was not saved because it's Empty";
			break;
		}
		}
	}
};