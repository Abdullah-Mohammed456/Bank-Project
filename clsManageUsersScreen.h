#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUtilities.h"
#include "clsUser.h"
#include "clsListUsers.h"
#include "clsAddNewUserScreen.h"
#include "clsFindUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsDeleteUserScreen.h"
using namespace std;
class clsMangeUsersScreen: protected clsScreen {
private:
	enum enMangeScreen{eListUsers=1,eAddNewUser,eDeleteUser,eUpdateUser,eFindUser,eMainMenu};
static void _GoBackToMangeUsersScreen() {
		SetColor(Red);
		cout << "\t\t\tEnter on anykey to Return . . .\n";
			Reset();
			system("Pause");
			ShowMangeUserScreen();
	}
static void _ShowListUsers(){
	//cout << "List Users Screen Will be Here . . .\n";
	clsListUsers::ShowListUsersScreen();
}
static void _ShowAddNewUser(){
	//cout << "Add New User Will be Here . . . \n";
	clsAddNewUserScreen::ShowAddNewUser();
}
static void _ShowDeleteUser(){
	//cout << "Delete User Screen Will be Here . . .\n ";
	clsDeleteUserScreen::ShowDeleteUser();
}
static void _ShowUpdateUser(){
	//cout << "Update User Screen Will be Here . . . \n";
	clsUpdateUserScreen::ShowUpdateUser();
}
static void _ShowFindUser(){
	//cout << "Find User Screen Will be Here . . .\n";
	clsFindUserScreen::ShowFindUser();
}
public:
	static void ShowMangeUserScreen(){
		system("cls");
		if (!clsScreen::Permissions(clsUser::pManageUsers))
		{
			return;
		} 
		clsScreen::_DrawScreenHeader("Mange Users Screen");
		int choice = clsUtilities::clsSelectOptions({ "List Users","Add New User","Delete User","Update User","Find User","Main Menu" }, "Mange Users Menu");
		switch (choice) {
		case enMangeScreen::eAddNewUser: {
			system("cls");
			_ShowAddNewUser();
			_GoBackToMangeUsersScreen();
			break;

		}
		case enMangeScreen::eDeleteUser: {
			system("cls");
			_ShowDeleteUser();
			_GoBackToMangeUsersScreen();
			break;
		}
		case enMangeScreen::eFindUser: {
			system("cls");
			_ShowFindUser();
			_GoBackToMangeUsersScreen();
			break;
		}
		case enMangeScreen::eListUsers: {
			system("cls");
			_ShowListUsers();
			_GoBackToMangeUsersScreen();
			break;
		}
		case enMangeScreen::eUpdateUser: {
			system("cls");
			_ShowUpdateUser();
			_GoBackToMangeUsersScreen();
			break;
		}
		case enMangeScreen::eMainMenu: {
			system("cls");
		}
		}
	}
};