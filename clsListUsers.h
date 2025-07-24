#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsUtilities.h"
using namespace std;
class clsListUsers :protected clsScreen {
private:
	static void _PrintClientRecordLine(clsUser User) {
		SetColor(LightRed);
		cout << setw(8) << left << "" << "| ";
		Reset();
		cout << setw(15) << left << User.UserName;
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << setw(20) << left << User.GetFullName();
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << setw(12) << left << User.Phone;
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << setw(22) << left << User.Email;
		SetColor(LightRed);
		cout << "| ";
		Reset();
		cout << setw(13) << left <<clsUtilities::EncryptedText(User.Password);
		SetColor(LightRed);
		cout << "| ";
		Reset();
		cout << setw(16) << left << User.Permission;
	}
public:
	static void ShowListUsersScreen(bool ListScreen = true) {
		vector <clsUser> vUsers = clsUser::GetListUsers();
		stringstream Subtitle;
		Subtitle << "Users [";
		Subtitle << vUsers.size();
		Subtitle << "] User(s)";
		if (ListScreen) {
			clsScreen::_DrawScreenHeader("List Users Screen", Subtitle.str());
		}
		SetColor(Yellow);
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		SetColor(LightRed);
		cout << setw(8) << left << "" << "| ";
		Reset();
		cout << left << setw(15) << "Username";
		SetColor(LightRed);
		cout << "| ";
		Reset();
		cout << left << setw(20) << "User Full Name";
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << left << setw(12) << "Phone";
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << left << setw(22) << "Email";
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << left << setw(13) << "Password";
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

			for (clsUser User : vUsers)
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