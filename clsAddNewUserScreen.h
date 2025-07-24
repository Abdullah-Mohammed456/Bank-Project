#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUtilities.h"
#include "clsUser.h"
using namespace std;
class clsAddNewUserScreen :protected clsScreen {
public:
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
	static void _ReadUserInfo(clsUser& User, bool Register = false) {
		cout << "Enter First Name: ";
		User.FirstName = clsUtilities::ReadString();
		cout << "Enter Last Name: ";
		User.LastName = clsUtilities::ReadString();
		cout << "Enter Email: ";
		User.Email = clsUtilities::ReadString();
		cout << "Enter Phone: ";
		User.Phone = clsUtilities::ReadString();
		if (Register == false) {
			cout << "Enter Password: ";
			User.SetPassword(clsUtilities::ReadString());
		}
		User.Permission = _ReadPermisssions();
	}
	static int _ReadPermisssions() {
		int per = 0;
		if (clsUtilities::YesOrNo("Do you want all permissions (Y/N): "))
		{
			return -1;
		}
		vector<string>vPermissions = { "List Client","Add New Client","Delete Client","Update Client","Find Client","Transactions","Mange Users","Login Register","Currencies Exchange" };
		for (int i = 0; i < vPermissions.size(); i++) {
			if (clsUtilities::YesOrNo("Do you want " + vPermissions[i] + " permission (Y / N) : ")) {
				per += pow(2, i);
			}
		}
		if (per == 511)return -1;
		return per;
	}
	static void ShowAddNewUser() {
		clsScreen::_DrawScreenHeader("Add New User Screen");
		cout << "Enter Username: ";
		string username = clsUtilities::ReadString();
		while (clsUser::IsUserExist(username))
		{
			SetColor(Red);
			cout << "The UserName Already Exist, Please Choose another one: ";
			Reset();
			username = clsUtilities::ReadString();
		}
		clsUser User = clsUser::GetAddNewUser(username);
		_ReadUserInfo(User);
		clsUser::enSaveResult result = User.Save();
		switch (result)
		{
		case clsUser::svFaild:
		{
			cout << "Failed to Add New User\n";
			break;
		}
		case clsUser::svSuccess:
		{

			cout << "Account Created successfully:-)\n";
			clsAddNewUserScreen::_PrintUserInfo(User);
			break;
		}
		case clsUser::svFaildExist:
		{
			cout << "Account Does Exist\n";
			break;
		}
		}
	}
};