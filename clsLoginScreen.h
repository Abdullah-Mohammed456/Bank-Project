#pragma once
#include "Global.h"
#include <iostream>
#include "clsScreen.h"
#include <conio.h>
#include "clsUtilities.h"
#include "clsMainScreen.h"
#include "clsAddNewUserScreen.h"
class clsLoginScreen :protected clsScreen {
private:
	static string SetPassword() {
		string s = "";
		char c;
		while (true) {
			c = _getch();
			if (c == '\r')break;
			else if (c == ' ')continue;
			else if (c == 8) {
				if (!s.empty())
				{
					s.pop_back();
					cout << "\b \b";
				}
				continue;
			}
			else {
				cout << '*';
				s.push_back(c);
			}
		}
		if (s.size() < 8 || s.size() > 16) {
			SetColor(Red);
			cout << "\nPlease Choose Password Between [8-16] Characters: ";
			Reset();
			return SetPassword();
		}
		return s;
	}
	static void _AddRecord(string Separator = "#//#") {
		auto now = time(0);
		tm local = {};
		localtime_s(&local, &now);
		string Date = "";
		Date += to_string(local.tm_mday) + "/" + to_string(local.tm_mon + 1) + "/" + to_string(local.tm_year + 1900) +
			" - " + to_string(local.tm_hour) + ":" + to_string(local.tm_min) + ":" + to_string(local.tm_sec);
		string Login = Date + Separator;
		Login += User.UserName + Separator;
		Login += User.Password + Separator;
		Login += to_string(User.Permission);
		User.Date = Date;
		fstream MyFile;
		MyFile.open("Login.txt", ios::out | ios::app);
		if (MyFile.is_open()) {
			MyFile << Login << endl;
		}
		MyFile.close();
	}
	static void _Login() {
		cout << "Enter Your Username: ";
		string username = clsUtilities::ReadString();
		cout << "Enter Your Password: ";
		string password = SetPassword();
		User = clsUser::Find(username, password);
		short Tries = 3;
		while ((User.UserName != username || User.Password != password) && Tries >= 1) {
			User = clsUser::GetEmptyUser();
			SetColor(Red);
			cout << "\nEnter Valid Username or Password\n";
			Reset();
			cout << "You Have " << Tries - 1 << " Tries To Login\n\n";
			Tries--;
			if (Tries == 0)break;
			cout << "Enter Your Username: ";
			username = clsUtilities::ReadString();
			cout << "Enter Your Password: ";
			password = SetPassword();
			User = clsUser::Find(username, password);
		}
		if (Tries == 0) {
			cout << "\nYou Are Locked After 3 Tries To Login\n";
			User.FaildLogin = true;
			return;
		}
		_AddRecord();
		clsMainScreen::ShowMainMenu();
	}
	static void _Register() {
		cout << "Enter Your Username: ";
		string username = clsUtilities::ReadString();
		while (clsUser::IsUserExist(username)) {
			SetColor(Red);
			cout << "\nUsername is Already Taken, Please Choose Another one: ";
			Reset();
			username = clsUtilities::ReadString();
		}
		cout << "Enter Your Password: ";
		string password = SetPassword();
		cout << "\n\n";
		clsUser NEWUSER=clsUser::AddNewUser(username, password);
		clsAddNewUserScreen::_ReadUserInfo(NEWUSER,true);
		clsUser::enSaveResult Result = NEWUSER.Save();
		switch (Result)
		{
		case clsUser::svSuccess:
			SetColor(Green);
			cout << "\n\nSuccessfully Created:-)\n";
			Reset();
			break;
		case clsUser::svFaild:
			SetColor(Red);
			cout << "\n\Failed Created:-(\n";
			Reset();
			break;
		case clsUser::svFaildExist:
			SetColor(Red);
			cout << "\n\Account is Already Exist:-(\n";
			Reset();
			break;
		default:
			break;
		}
		cout << "\nClick on Any KeyCap To Login\n";
		system("pause");
	}
public:

	static void ShowLoginScreen() {
		system("cls");
		clsScreen::_DrawScreenHeader("Login Screen");
		_Login();
	}
	static void ShowRegisterscreen() {
		system("cls");
		clsScreen::_DrawScreenHeader("Register Screen");
		_Register();
	}
	static void App() {
		clsScreen::_DrawScreenHeader("Welcome Back");
		int choice = clsUtilities::clsSelectOptions({ "Register","Login","Logout" }, "Login Menu");
		switch (choice) {
		case 1: {
			ShowRegisterscreen();
		}
		case 2: {
			ShowLoginScreen();
			break;
		}
		case 3:
		{
			break;
		}
		}
	}
};