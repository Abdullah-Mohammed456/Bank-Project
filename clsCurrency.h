#pragma once
#include <iostream>
#include <vector>
#include "clsScreen.h"
#include "clsUtilities.h"
#include "clsString.h"
#include <fstream>
using namespace std;
class clsCurrency {
private:
	enum enMode { enEmptyMode, enUpdateMode };
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	double _Rate;

	static string _ConvertObjectToLine(clsCurrency Currency, string Separator = "#//#") {
		string File = "";
		File += Currency._Country + Separator;
		File += Currency._CurrencyCode + Separator;
		File += Currency._CurrencyName + Separator;
		File += to_string(Currency._Rate);
		return File;
	}
	static clsCurrency _ConvertLineToObject(string Line, string Separator = "#//#") {
		vector<string>vCurrencies = clsString::Split(Line, Separator);
		return clsCurrency(enMode::enUpdateMode, vCurrencies[0], vCurrencies[1], vCurrencies[2], stod(vCurrencies[3]));
	}
	static clsCurrency _GetEmptyObject() {
		return clsCurrency(enMode::enEmptyMode, "", "", "", 0.0);
	}
	static vector<clsCurrency> _LoadObjectFromFile() {
		vector<clsCurrency>vCurrencies;
		string Line;
		fstream MyFile;
		MyFile.open("Currency.txt", ios::in);
		if (MyFile.is_open()) {
			while (getline(MyFile, Line)) {
				clsCurrency Currency = clsCurrency::_ConvertLineToObject(Line);
				vCurrencies.push_back(Currency);
			}
			MyFile.close();
		}
		return vCurrencies;
	}
	void _Update() {
		vector<clsCurrency>vCurrencies = _LoadObjectFromFile();
		for (auto& C : vCurrencies) {
			if (C._CurrencyCode == GetCurrencyCode()) {
				C = *this;
				break;
			}
		}
		
		fstream MyFile;
		MyFile.open("Currency.txt", ios::out); // overwrite
		if (MyFile.is_open()) {
			for (clsCurrency& C : vCurrencies) {
				MyFile << _ConvertObjectToLine(C) << endl;
			}
			MyFile.close();
		}
	}
public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, double Rate) {
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}
	bool IsEmpty() {
		return _Mode == enMode::enEmptyMode;
	}
	string GetCountry() {
		return _Country;
	}
	string GetCurrencyCode() {

		return _CurrencyCode;
	}
	string GetCurrencyName() {

		return _CurrencyName;
	}
	void SaveUpdatedRate(double NewRate) {
		_Rate = NewRate;
		_Update();
	}
	double GetRate() {
		return _Rate;
	}
	static clsCurrency FindCurrencyCode(string CurrencyCode) {
		CurrencyCode = clsString::UpperAllString(CurrencyCode);
		vector<clsCurrency>vCurrencies = _LoadObjectFromFile();
		for (clsCurrency C : vCurrencies) {
			if (C._CurrencyCode == CurrencyCode) {
				return C;
			}
		}
		return _GetEmptyObject();
	}
	static clsCurrency FindCountryName(string CountryName) {
		CountryName = clsString::UpperFirstLetterOfEachWord(CountryName);
		vector<clsCurrency>vCurrencies = _LoadObjectFromFile();
		for (clsCurrency C : vCurrencies) {
			if (C._Country == CountryName) {
				return C;
			}
		}
		return _GetEmptyObject();
	}
	static vector<clsCurrency> GetCurrenciesList() {
		return _LoadObjectFromFile();
	}
	static bool IsCurrencyExistCode(string CurrencyCode) {
		clsCurrency Currency = clsCurrency::FindCurrencyCode(CurrencyCode);
		return (!Currency.IsEmpty());
	}
	static bool IsCurrencyExistName(string CountryName) {
		clsCurrency Currency = clsCurrency::FindCountryName(CountryName);
		return (!Currency.IsEmpty());
	}
};