#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include "Separator.h"
using namespace std;
class clsDate {
public:
    int days, months, years;
    enum MONTHS { Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec };
    clsDate(int d, int m, int y) :days(d), months(m), years(y) {}
    clsDate() {
        auto now = time(0);
        tm* local;
        //local = localtime_s(&now);
        days = local->tm_mday;
        months = local->tm_mon + 1;
        years = local->tm_year + 1900;
    }
    static int Months(clsDate M) {
        if (M.months == MONTHS::Jan || M.months == MONTHS::Mar || M.months == MONTHS::May || M.months == MONTHS::Jul || M.months == MONTHS::Aug || M.months == MONTHS::Oct || M.months == MONTHS::Dec) {
            return 31;
        }
        else if (M.months == MONTHS::Feb && ((M.years % 4 == 0) && (M.years % 100 != 0) || (M.years % 400 == 0))) {
            return 29;
        }
        else if (M.months == MONTHS::Feb) {
            return 28;
        }
        else return 30;
    }
    static bool valid(clsDate V) {
        int test = Months(V);
        if ((V.days == 1 || V.days == 3 || V.days == 5 || V.days == 7 || V.days == 8 || V.days == 10 || V.days == 12) && test == 31) {
            return true;
        }
        else if ((V.days == 4 || V.days == 6 || V.days == 9 || V.days == 11) && test == 30) {
            return true;
        }
        else if ((V.months == MONTHS::Feb && ((V.years % 4 == 0) && (V.years % 100 != 0) || (V.years % 400 == 0))) && test == 29) {
            return true;
        }
        else if (V.months == 2 && ((V.years % 4 != 0) && (V.years % 100 == 0) || (V.years % 400 != 0)) && test == 28) {
            return true;
        }
        else return false;
    }
};
class clsUtilities :public clsDate {
public:
    static bool IsNumberBetween(int input, int from, int to) {
        if (input >= from && input <= to) {
            return true;
        }
        return false;
    }
    static bool IsNumberBetween(double input, double from, double to) { //overloading function with double
        if (input >= from && input <= to) {
            return true;
        }
        return false;
    }
    static bool IsValidDate(clsDate date) {
        if (valid(date)) {
            return true;
        }
        return false;

    }
    static bool IsDateBetween(clsDate date, clsDate from, clsDate to) {
        if (date.days >= from.days && date.days <= to.days && date.months >= from.months && date.months <= to.months && date.years >= from.years && date.years <= to.years) {
            return true;
        }
        return false;
    }
    static int ReadIntNumber(string output) {
        int x;
        while (true) {
            cin >> x;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000,'\n');
                cout << output;
            }
            else break;
        }
        return x;
    }
    static int ReadIntNumberBetween(int from, int to, string output) {
        int x;
        while (true) {
            cin >> x;
            if (x >= from && x <= to) {
                break;
            }
            else if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                SetColor(Red);
                cout << "Please Enter Integer Number: ";
                Reset();
            }
            else { 
                cin.clear();
                cin.ignore(1000, '\n');
                cout << output;
            }
        }
        return x;
    }
    static double ReadDblNumber(string output) {
        double x;
        while (true) {
            cin >> x;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                SetColor(Red);
                cout << output;
                Reset();
            }
            else break;
        }
        return x;
    }

    static double ReadDblNumberBetween(double from, double to, string output) {
        double x;
        while (true) {
            cin >> x;
            if (x >= from && x <= to) {
                break;
            }
            else if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "invalid number try again:\n";
            }
            else {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << output;
            }
        }
        return x;
    }
    static string ReadString() {
        string s;
        getline(cin >> ws, s);
        return s;
    }
    static string ConvertNumbersToText(long long Number) {
        string oneToNineteen[] = {
            "", "One", "Two", "Three", "Four", "Five", "Six", "Seven",
            "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen",
            "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"
        };
        string tens[] = {
            "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
        };
        if (Number == 0)return "Zero";
        if (Number >= 1000000000)
            return ConvertNumbersToText(Number / 1000000000) + " Billion" +
            (Number % 1000000000 ? " " + ConvertNumbersToText(Number % 1000000000) : "");

        if (Number >= 1000000)
            return ConvertNumbersToText(Number / 1000000) + " Million" +
            (Number % 1000000 ? " " + ConvertNumbersToText(Number % 1000000) : "");

        if (Number >= 1000)
            return ConvertNumbersToText(Number / 1000) + " Thousand" +
            (Number % 1000 ? " " + ConvertNumbersToText(Number % 1000) : "");

        if (Number >= 100)
            return oneToNineteen[Number / 100] + " Hundred" +
            (Number % 100 ? " " + ConvertNumbersToText(Number % 100) : "");

        if (Number >= 20)
            return tens[Number / 10] +
            (Number % 10 ? " " + oneToNineteen[Number % 10] : "");

        return oneToNineteen[Number];
    }

    static int clsSelectOptions(vector<string>options,string header,bool canExit = true) {
        int index = 1;
        cout << "\t\t\t\t\t\t===============================\n\t\t\t\t\t\t\t"<<header<<"\n\t\t\t\t\t\t===============================\n";
        for (auto option : options) {
            SetColor(Red);
            cout << setw(48) << left << "" << "[";
            SetColor(LightCyan);
            cout << index;
            SetColor(Red);
            cout << "] ";
            Reset();
            cout<< option << '\n';
            index++;
        }
        cout << "\t\t\t\t";
        Separator();
        size_t maxOptions= canExit == true ? options.size() : options.size()-1;
        SetColor(Green);
        cout << setw(48) << left << ""<< "Select Option From [1-" << maxOptions << "]: ";
        Reset();
        int choice = ReadIntNumberBetween(1, maxOptions, "Invalid Number Please Choice Number between [1-" +to_string(maxOptions)+ "]: ");
        return choice;
    }
    static bool YesOrNo(string text) {
        cout << text;
        string input;
        cin >> input;
        if (!input.empty() && (tolower(input[0]) == 'y')) {
            return true;
        }
        else return false;
    }
    static string EncryptedText(string Text, short Encryption = 2) {

        for (int i = 0; i < Text.size(); i++) {

            Text[i] = char((int)Text[i] + Encryption);
        }

        return Text;
    }
    static string DecryptedText(string Text, short Encryption = 2) {

        for (int i = 0; i < Text.size(); i++) {

            Text[i] = char((int)Text[i] - Encryption);
        }

        return Text;
    }
};