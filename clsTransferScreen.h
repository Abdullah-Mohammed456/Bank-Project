#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUtilities.h"
#include "clsBankClient.h"
using namespace std; 
class clsTransferScreen :protected clsScreen {
private:
	static void _AddRecord(clsBankClient Client1,clsBankClient Client2,double Amount,string Separator = "#//#") {
		auto now = time(0);
		tm local = {};
		localtime_s(&local, &now);
		string Date = "";
		Date += to_string(local.tm_mday) + "/" + to_string(local.tm_mon + 1) + "/" + to_string(local.tm_year + 1900) +
			" - " + to_string(local.tm_hour) + ":" + to_string(local.tm_min) + ":" + to_string(local.tm_sec);
		string Transfer = Date + Separator;
		Transfer += Client1.AccountNumber() + Separator;
		Transfer += Client2.AccountNumber() + Separator;
		Transfer += to_string(Amount) + Separator;
		Transfer += to_string(Client1.AccountBalance) + Separator;
		Transfer += to_string(Client2.AccountBalance) + Separator;
		Transfer += User.UserName;
		fstream MyFile;
		MyFile.open("Transfer.txt", ios::out | ios::app);
		if (MyFile.is_open()) {
			MyFile << Transfer << endl;
		}
		MyFile.close();
	}
public:
	static void ShowTransferScreen() {
		clsScreen::_DrawScreenHeader("Transfer Screen");
		
		cout << "Enter Your Account Number to Transfer From: ";
		string accountnumber = clsString::ReadString();
		while (!clsBankClient::IsClientExist(accountnumber)) {
			SetColor(Red);
			cout << "Invalid Account Number Please Choose another one: ";	
			Reset();
			accountnumber = clsString::ReadString();
		}
		clsBankClient CLient1 = clsBankClient::Find(accountnumber);
		cout << "\nClient Card\n";
		SetColor(Yellow);
		cout << "-----------------------\n";
		Reset();
		cout << "Full Name      : " << CLient1.GetFullName() << endl;
		cout << "Acc. Number    : " << CLient1.AccountNumber() << endl;
		cout << "Balance        : " << CLient1.AccountBalance << endl;
		SetColor(Yellow);
		cout << "-----------------------\n";
		Reset();
		cout << "Enter Your Account Number to Transfer To: ";
		string accountnumber2 = clsString::ReadString();
		while (!clsBankClient::IsClientExist(accountnumber2)||accountnumber2==accountnumber) {
			SetColor(Red);
			cout << "Invalid Account Number Please Choose another one: ";	
			Reset();
			accountnumber2 = clsString::ReadString();
		}
		clsBankClient CLient2 = clsBankClient::Find(accountnumber2);
		cout << "\nClient Card\n";
		SetColor(Yellow);
		cout << "-----------------------\n";
		Reset();
		cout << "Full Name      : " << CLient2.GetFullName() << endl;
		cout << "Acc. Number    : " << CLient2.AccountNumber() << endl;
		cout << "Balance        : " << CLient2.AccountBalance << endl;
		SetColor(Yellow);
		cout << "-----------------------\n";
		Reset();
		cout << "\nEnter Amount You Want to Transfer: ";
		double Amount = clsUtilities::ReadIntNumber("Enter Integer Number: ");
		while (Amount > CLient1.AccountBalance) {
			cout << "Your Amount Greater Than your Wallet Please Choose Another Value To MAX (" << CLient1.AccountBalance << "): ";
			Amount = clsUtilities::ReadIntNumber("Enter Integer Number: ");
		}
		cout << "Are You Sure? [Y/N]: ";
		char choice;
		cin >> choice;
		if (choice == 'Y' || choice == 'y') {
			cout << "\nSuccessfully Operation:-)\n";
			CLient1.WithDraw(Amount);
			CLient2.Deposit(Amount);
			cout << "\nClient Card From\n";
			SetColor(Yellow);
			cout << "-----------------------\n";
			Reset();
			cout << "Full Name      : " << CLient1.GetFullName() << endl;
			cout << "Acc. Number    : " << CLient1.AccountNumber() << endl;
			cout << "Balance        : " << CLient1.AccountBalance << endl;
			SetColor(Yellow);
			cout << "-----------------------\n";
			Reset();
			cout << "\nClient Card To\n";
			SetColor(Yellow);
			cout << "-----------------------\n";
			Reset();
			cout << "Full Name      : " << CLient2.GetFullName() << endl;
			cout << "Acc. Number    : " << CLient2.AccountNumber() << endl;
			cout << "Balance        : " << CLient2.AccountBalance << endl;
			SetColor(Yellow);
			cout << "-----------------------\n";
			Reset();
			_AddRecord(CLient1,CLient2,Amount);

		}
		else cout << "\nOperation Was Canceling . . . \n";
	}
};