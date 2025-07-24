#pragma once
#include <iostream>
#include "clsUtilities.h"
#include "clsScreen.h"
#include "clsCurrency.h"
using namespace std;
class clsUpdateCurrecyScreen :protected clsScreen {
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
	static void ShowUpdateCurrency() {
		clsScreen::_DrawScreenHeader("Update Currency Screen");
		cout << "Enter Currency Code: ";
		string CurrencyCode = clsUtilities::ReadString();
		while (!clsCurrency::IsCurrencyExistCode(CurrencyCode)) {

			cout << "\nInvalid Currency Code, Please Try again: ";
			CurrencyCode = clsUtilities::ReadString();
		}
		clsCurrency Currency = clsCurrency::FindCurrencyCode(CurrencyCode);
		cout << "\nEnter Rate You Want: ";
		double Rate = clsUtilities::ReadDblNumber("Please Enter Float Number: ");
		cout << "\nAre You Sure? [Y/N]: ";
		char choice; cin >> choice;
		if (choice == 'Y' || choice == 'y') {
			Currency.SaveUpdatedRate(Rate);
			cout << "\nRate Updated Successfully:-)";
			_PrintCurrencyInfo(Currency);
		}
		else {
			cout << "\nOperation was Canceling . . . \n";
		}
	}
};