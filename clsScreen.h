#pragma once
#include <iostream>
#include "SetConsoleColors.h"
#include "Separator.h"
#include "clsUser.h"
#include <ctime>
using namespace std;
class clsScreen{
protected:
	static void Time_And_User() {
		time_t now = time(0);
		tm local = {};
		localtime_s(&local, &now);
		cout << "\t\t\t\tUser: " << User.UserName;
		cout << "\n\t\t\t\tDate: " << local.tm_mday << "/" << local.tm_mon + 1 << "/" << local.tm_year + 1900 << "\n\n";

	}
	static void _DrawScreenHeader(string text,string subtitle="") {
		cout << "\t\t\t\t";
		Separator();
		SetColor(LightCyan);
		cout << "\t\t\t\t\t\t\t" << text << endl;
		Reset();
		if (subtitle != "") {
			SetColor(LightCyan);
			cout << "\t\t\t\t\t\t\t" << subtitle << endl;
			Reset();
		}
		cout << "\t\t\t\t";
		Separator();
		Time_And_User();

	}
	static bool Permissions(clsUser::enPermissions Permissions)
	{
		if (!User.EnterOrNot(Permissions))
		{
			cout << "\t\t\t\t";
			Separator();
			SetColor(Red);
			cout << "\t\t\t\t\tAccess Denied Contact With Your Admin\n";
			Reset();
			cout << "\t\t\t\t";
			Separator();

			return false;
		}
		return true;
		
	}
};