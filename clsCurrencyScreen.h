#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUtilities.h"
#include "clsUser.h"
#include "clsListCurrenciesScreen.h"
#include "clsUpdateCurrencyScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsCurrencyCalculator.h"
using namespace std;
class clsCurrecnyScreen :clsScreen {
private:
	enum enCurrency{eListCurrencies=1,eFindCurreny,eUpdateRate,eCurrencyCalc,eMainMenu};
	static void _GoBackToCurrecyScreen() {
		SetColor(Red);
		cout << "\t\tEnter on any KeyCap To return . . .\n";
		Reset();
		system("pause");
		system("cls");
		ShowCurrencyScreen();
	}
	static void _ListCurrencies() {
		//cout << "List Currencies Screen Will Be Here . . .\n";
		clsListCurrenciesScreen::ShowCurrenciesScreen();
	}
	static void _FindCurrency() {
		//cout << "Find Currency Screen Will Be Here . . .\n";
		clsFindCurrecyScreen::ShowFindCurrency();
	}
	static void _UpdateRate() {
		//cout << "Update Rate Screen Will Be Here . . .\n";
		clsUpdateCurrecyScreen::ShowUpdateCurrency();
	}
	static void _CurrencyClac() {
		//cout << "Currency Claculator Screen Will Be Here . . .\n";
		clsCurrecyCalculatorScreen::ShowCurrencyCalculator();
	}
public:
	static void ShowCurrencyScreen() {
		if (!clsScreen::Permissions(clsUser::enPermissions::pCurrencies)) {
			return;
		}
		clsScreen::_DrawScreenHeader("Currencies Screen");
		int choice = clsUtilities::clsSelectOptions({ "List Currencies","Find Currency","Update Currency","Currency Calculator","Main Menu" }, "Currencies Menu");
		switch (choice) {
		case enCurrency::eCurrencyCalc: {
			system("cls");
			_CurrencyClac();
			_GoBackToCurrecyScreen();
			break;
		}
		case enCurrency::eFindCurreny: {
			system("cls");
			_FindCurrency();
			_GoBackToCurrecyScreen();
			break;
		}
		case enCurrency::eListCurrencies: {
			system("cls");
			_ListCurrencies();
			_GoBackToCurrecyScreen();
			break;
		}
		case enCurrency::eMainMenu: {
			system("cls");
			break;
		}
		case enCurrency::eUpdateRate: {
			system("cls");
			_UpdateRate();
			_GoBackToCurrecyScreen();
			break;
		}
		}
	}

};