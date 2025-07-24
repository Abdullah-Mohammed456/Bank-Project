#pragma once
#include <iostream>
#include "clsUtilities.h"
#include "clsScreen.h"
#include "clsCurrency.h"
using namespace std;
class clsFindCurrecyScreen :protected clsScreen {
private:
	static void _PrintCurrencyInfo(clsCurrency Currency) {
		cout << "\n\nCurrency Card:\n";
		Separator();
		cout << "Country Name     : " << Currency.GetCountry();
		cout << "\nCurrency Code    : " << Currency.GetCurrencyCode();
		cout << "\nCurrency Name    : " << Currency.GetCurrencyName();
		cout << "\nRate (1$)        : " << Currency.GetRate()<< endl;
		Separator();
	}

public:
	static void ShowFindCurrency() {
		clsScreen::_DrawScreenHeader("Find Currecny Screen");
		cout << "Choose Find By Currency Code [1] OR Country Name [2]: ";
		int choice = clsUtilities::ReadIntNumberBetween(1, 2, "Please Enter integer Number: ");
		if (choice == 1) {
			cout << "\nEnter Currency Code: ";
			string CurrencyCode = clsUtilities::ReadString();
			CurrencyCode = clsString::UpperAllString(CurrencyCode);
			while (!clsCurrency::IsCurrencyExistCode(CurrencyCode)) {
				cout << "Currency Code Not Exist, Please Try again: ";
				CurrencyCode = clsUtilities::ReadString();
				CurrencyCode = clsString::UpperAllString(CurrencyCode);
			}
			clsCurrency Currency = clsCurrency::FindCurrencyCode(CurrencyCode);
			cout << "\n\nCurrency Found:-)\n";
			_PrintCurrencyInfo(Currency);
		}
		else {
			cout << "\nEnter Country Name: ";
			string CountryName = clsUtilities::ReadString();
			CountryName = clsString::UpperFirstLetterOfEachWord(CountryName);
			while (!clsCurrency::IsCurrencyExistName(CountryName))
			{
				cout << "Currency Name Not Exist, Please Try again: ";
				CountryName = clsUtilities::ReadString();
				CountryName = clsString::UpperFirstLetterOfEachWord(CountryName);

			}
			clsCurrency Currency = clsCurrency::FindCountryName(CountryName);
			cout << "\n\nCurrency Found:-)\n";
			_PrintCurrencyInfo(Currency);
		}
	}
};