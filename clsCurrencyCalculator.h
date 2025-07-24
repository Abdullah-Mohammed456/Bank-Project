#pragma once
#include <iostream>
#include "clsUtilities.h"
#include "clsScreen.h"
#include "clsCurrency.h"
using namespace std;
class clsCurrecyCalculatorScreen :protected clsScreen {
private:
	static void _PrintCurrencyInfo(clsCurrency Currency) {
		cout << "\n\nCurrency Card:\n";
		Separator();
		cout << "Country Name     : " << Currency.GetCountry();
		cout << "\nCurrency Code    : " << Currency.GetCurrencyCode();
		cout << "\nCurrency Name    : " << Currency.GetCurrencyName();
		cout << "\nRate (1$)        : " << Currency.GetRate() << endl;
		Separator();
	}
public:
	static void ShowCurrencyCalculator() {
		while(true)
		{
			system("cls");
			clsScreen::_DrawScreenHeader("Currencies Calculator");
			cout << "Enter Currency Code From: ";
			string CurrencyCode1 = clsUtilities::ReadString();
			while (!clsCurrency::IsCurrencyExistCode(CurrencyCode1)) {
				cout << "\nNot Found, Please Enter Another one: ";
				CurrencyCode1 = clsUtilities::ReadString();
			}
			clsCurrency Currency1 = clsCurrency::FindCurrencyCode(CurrencyCode1);
			cout << "\nEnter Currency Code To: ";
			string CurrencyCode2 = clsUtilities::ReadString();
			while (!clsCurrency::IsCurrencyExistCode(CurrencyCode2)) {
				cout << "\nNot Found, Please Enter Another one: ";
				CurrencyCode2 = clsUtilities::ReadString();
			}
			clsCurrency Currency2 = clsCurrency::FindCurrencyCode(CurrencyCode2);
			cout << "\nEnter Amount Exchange: ";
			double Amount = clsUtilities::ReadDblNumber("Please Enter Float Number: ");
			cout << "\nCurrency From";
			_PrintCurrencyInfo(Currency1);
			double Exchange = Amount / Currency1.GetRate() * Currency2.GetRate();
			cout << Amount << " " << Currency1.GetCurrencyCode() << " = " << Exchange << " " << Currency2.GetCurrencyCode() << endl;
			cout << "\nDo You Wanna Continue? [Y/N]: ";
			char choice; cin >> choice;
			if (choice == 'n' || choice == 'N')break;
		}

	}
};