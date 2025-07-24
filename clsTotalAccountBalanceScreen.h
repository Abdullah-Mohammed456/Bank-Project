#pragma once
#include <iostream>
#include "clsScreen.h"
using namespace std;
class clsTotalAccountBalanceScreen:protected clsScreen {
private:
	static void _PrintClientBalances(clsBankClient Client) {
		SetColor(LightRed);
		cout <<setw(8)<<left<<"" << "| ";
		Reset();
		cout << setw(15) << left << Client.AccountNumber();
		SetColor(LightRed);
		cout << "| ";
		Reset();
		cout << setw(20) << left << Client.GetFullName();
		SetColor(LightRed);
		cout << "| ";
		Reset();
		cout << setw(12) << left << Client.AccountBalance;
	}

public:
	static void ShowAccountBalanceScreen() {
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		string subtitle = "["+to_string(vClients.size())+"] Client(s)";
		clsScreen::_DrawScreenHeader("Balances List Screen", subtitle);
		SetColor(Yellow);
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		SetColor(LightRed);
		cout <<setw(8)<<left<<"" << "| ";
		Reset();
		cout << left << setw(15) << "Accout Number";
		SetColor(LightRed);
		cout << "| ";
		Reset();
		cout << left << setw(20) << "Client Name";
		SetColor(LightRed);
		cout << "| ";
		Reset();
		cout << left << setw(12) << "Balance";
		SetColor(Yellow);
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		Reset();
		if (vClients.size() == 0) {
			SetColor(Red);
			cout << "\t\t\t\tNo Clients Available In the System!";
			Reset();
		}
		else
			for (clsBankClient Client : vClients)
			{
				_PrintClientBalances(Client);
				cout << endl;
			}
		SetColor(Yellow);
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		Reset();
		SetColor(Green);
		int total = round(clsBankClient::GetTotalBalances());
		cout << "\t\t\t\tTotal Balances = " << total << endl;
		cout << "\t\t   Approximately " << clsUtilities::ConvertNumbersToText(total) << endl;//numbers were printed without amount 
		Reset();
	}
};