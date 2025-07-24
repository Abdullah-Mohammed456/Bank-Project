#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsString.h"
#include "clsUser.h"
class clsLoginRegisterScreen:protected clsScreen {
private:
	static void _PrintClientRecordLine(clsUser::LOGIN User) {
		SetColor(LightRed);
		cout << setw(8) << left << "" << "| ";
		Reset();
		cout << setw(25) << left << User.Date;
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << setw(20) << left << User.UserName;
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << setw(12) << left << User.Password;
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << setw(12) << left << User.Permissions;
	}
public:
	static void ShowLoginRegisterScreen() {
		if (!clsScreen::Permissions(clsUser::enPermissions::pLoginRegister)) {
			return;
		}
		vector <clsUser::LOGIN> vUsers = clsUser::GetListLoginUsers();
		stringstream Subtitle;
		Subtitle << "Users [";
		Subtitle << vUsers.size();
		Subtitle << "] User(s)";
		clsScreen::_DrawScreenHeader("List Users Screen", Subtitle.str());
		SetColor(Yellow);
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		SetColor(LightRed);
		cout << setw(8) << left << "" << "| ";
		Reset();
		cout << left << setw(25) << "Date";
		SetColor(LightRed);
		cout << "| ";
		Reset();
		cout << left << setw(20) << "Username";
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << left << setw(12) << "Password";
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << left << setw(12) << "Permission";
		SetColor(Yellow);
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		Reset();
		if (vUsers.size() == 0) {
			SetColor(Red);
			cout << "\t\t\t\t\tNo Users Available In the System!";
			Reset();
		}
		else

			for (clsUser::LOGIN User : vUsers)
			{
				_PrintClientRecordLine(User);
				cout << endl;
			}
		SetColor(Yellow);
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		Reset();

	}
};