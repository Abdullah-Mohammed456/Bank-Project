#pragma once
#include <iostream>
#include "clsScreen.h"
using namespace std;
class clsTransferLogScreen :protected clsScreen {
private:
	static void _PrintClientRecordLine(clsUser::Transfer User) {
		SetColor(LightRed);
		cout << setw(8) << left << "" << "| ";
		Reset();
		cout << setw(25) << left << User.Date;
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << setw(12) << left << User.SourceAccount;
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << setw(12) << left << User.DestenitionAccount;
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << setw(12) << left << User.Amount;
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << setw(12) << left << User.SourceBalance;
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << setw(12) << left << User.DestenitionBalance;
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << setw(12) << left << User.User;
	}
public:
	static void ShowTransferLogScreen() {
		vector <clsUser::Transfer> vUsers = clsUser::GetTransferLogUsers();
		stringstream Subtitle;
		Subtitle << "Transfer [";
		Subtitle << vUsers.size();
		Subtitle << "] Transfer(s)";
		clsScreen::_DrawScreenHeader("Transfer Log Screen", Subtitle.str());
		SetColor(Yellow);
		cout << "\n\t  _______________________________________________________";
		cout << "_________________________________________\n" << endl;
		SetColor(LightRed);
		cout << setw(8) << left << "" << "| ";
		Reset();
		cout << left << setw(25) << "Date";
		SetColor(LightRed);
		cout << "| ";
		Reset();
		cout << left << setw(12) << "S.Acc";
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << left << setw(12) << "D.Acc";
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << left << setw(12) << "Amount";
		SetColor(LightRed);
		cout << "| ";
		Reset();
		cout << left << setw(12) << "S.Balance";
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << left << setw(12) << "D.Balance";
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << left << setw(12) << "User";
		SetColor(Yellow);
		cout << "\n\t  _______________________________________________________";
		cout << "_________________________________________\n" << endl;
		Reset();
		if (vUsers.size() == 0) {
			SetColor(Red);
			cout << "\t\t\t\t\tNo Log Available In the System!";
			Reset();
		}
		else

			for (clsUser::Transfer User : vUsers)
			{
				_PrintClientRecordLine(User);
				cout << endl;
			}
		SetColor(Yellow);
		cout << "\n\t  _______________________________________________________";
		cout << "_________________________________________\n" << endl;
		Reset();

	}
};