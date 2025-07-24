#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
using namespace std;
class clsListCurrenciesScreen :protected clsScreen {
private:
	static void _PrintClientRecordLine(clsCurrency Currency) {
	SetColor(LightRed);
	cout << setw(8) << left << "" << "| ";
	Reset();
	cout << setw(30) << left << Currency.GetCountry();
	SetColor(LightRed);
	cout << "" << "| ";
	Reset();
	cout << setw(15) << left << Currency.GetCurrencyCode();
	SetColor(LightRed);
	cout << "" << "| ";
	Reset();
	cout << setw(30) << left << Currency.GetCurrencyName();
	SetColor(LightRed);
	cout << "" << "| ";
	Reset();
	cout << setw(15) << left << to_string(Currency.GetRate());
}
public:
	static void ShowCurrenciesScreen() {
		vector<clsCurrency>vCurrencies = clsCurrency::GetCurrenciesList();
		stringstream Subtitle;
		Subtitle << "Currencies[";
		Subtitle << vCurrencies.size();
		Subtitle << "] Currency";
		clsScreen::_DrawScreenHeader("List Currencies Screen", Subtitle.str());
		SetColor(Yellow);
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		SetColor(LightRed);
		cout << setw(8) << left << "" << "| ";
		Reset();
		cout << left << setw(30) << "Country Name";
		SetColor(LightRed);
		cout << "| ";
		Reset();
		cout << left << setw(15) << "Currency Code";
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << left << setw(30) << "Currency Name";
		SetColor(LightRed);
		cout << "" << "| ";
		Reset();
		cout << left << setw(15) << "Rate (1$)";
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		Reset();
		if (vCurrencies.size() == 0) {
			SetColor(Red);
			cout << "\t\t\t\t\tNo Currencies Available In the System!";
			Reset();
		}
		else

			for (clsCurrency Currency : vCurrencies)
			{

				_PrintClientRecordLine(Currency);
				cout << endl;
			}
		SetColor(Yellow);
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		Reset();
	}
};