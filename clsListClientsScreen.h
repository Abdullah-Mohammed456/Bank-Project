#pragma once
#include <iostream>
#include <sstream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "SetConsoleColors.h"
using namespace std;
class clsListClientsScreen:protected clsScreen {
private:
	static void _PrintClientRecordLine(clsBankClient Client) {
		SetColor(LightRed);
		cout <<setw(8)<<left<<""<< "| ";
		Reset();
		cout << setw(15) << left << Client.AccountNumber();
		SetColor(LightRed);
		cout <<""<< "| ";
		Reset();
		cout << setw(20) << left << Client.GetFullName();
		SetColor(LightRed);
		cout <<""<< "| ";
		Reset();
		cout << setw(12) << left << Client.Phone;
		SetColor(LightRed);
		cout <<""<< "| ";
		Reset();
		cout << setw(20) << left << Client.Email;
		SetColor(LightRed);
		cout << "| ";
		Reset();
		cout << setw(10) << left << Client.PinCode;
		SetColor(LightRed);
		cout << "| ";
		Reset();
		cout << setw(12) << left << Client.AccountBalance;
	}
public:
	
	static void ShowClientsList(bool ListScreen = true) {
		if (!(clsScreen::Permissions(clsUser::enPermissions::pListClients)))
		{
			return;
		}
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		stringstream Subtitle;
		Subtitle << "Clients [";
		Subtitle << vClients.size();
		Subtitle << "] Client(s)";
		if (ListScreen) {
			clsScreen::_DrawScreenHeader("List Clients Screen", Subtitle.str());
		}
		SetColor(Yellow);
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		SetColor(LightRed);
		cout << setw(8) << left << "" << "| ";
		Reset();
		cout << left << setw(15) << "Accout Number";
		SetColor(LightRed);
		cout <<"| ";
		Reset();
		cout << left << setw(20) << "Client Name";
		SetColor(LightRed);
		cout<<""<< "| ";
		Reset();
		cout << left << setw(12) << "Phone";
		SetColor(LightRed);
		cout<<""<< "| ";
		Reset();
		cout << left << setw(20) << "Email";
		SetColor(LightRed);
		cout<<""<< "| ";
		Reset();
		cout << left << setw(10) << "Pin Code";
		SetColor(LightRed);
		cout<<""<< "| ";
		Reset();		
		cout << left << setw(12) << "Balance";
		SetColor(Yellow);
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		Reset();
		if (vClients.size() == 0) {
			SetColor(Red);
			cout << "\t\t\t\t\tNo Clients Available In the System!";
			Reset();
		}
		else

			for (clsBankClient Client : vClients)
			{

				_PrintClientRecordLine(Client);
				cout << endl;
			}
		SetColor(Yellow);
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		Reset();
	}

};