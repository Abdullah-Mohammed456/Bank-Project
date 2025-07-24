#pragma once
#include <iostream>
#include "Global.h"
#include "SetConsoleColors.h"
#include "clsScreen.h"
#include "clsListClientsScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsMenuScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyScreen.h"
#include "clsUser.h"
class clsMainScreen :protected clsScreen {
private:
	enum enMainMenueOptions {
		eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
		eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
		eManageUsers = 7,eLoginRegister=8,eCurrency=9, eExit = 10
	};
	static void _GoBackToMainMenue() {
		SetColor(Red);
		cout << "\t\tPress on any key to return to Main Screen . . .\n\n";
		Reset();
		system("pause");
		clsMainScreen::ShowMainMenu();
	}
	static void _ListClients()
	{
		//cout << "List Clients Will be Here...\n"
		
		clsListClientsScreen::ShowClientsList();
	}
	static void _AddNewClient(){
		//cout << "Add New Client Will be Here...\n";
		
		clsAddNewClientScreen::ShowAddNewClient();
	}
	static void _DeleteClient(){
		//cout << "Delete Client Will be Here...\n";
		
		clsDeleteClient::ShowDeleteClient();
	}
	static void _UpdateClient(){
		//cout << "Update Client Will be Here...\n";
		
		clsUpdateClientScreen::ShowUpdateClient();
	}
	static void _FindClient(){
		//cout << "Find Client Will be Here...\n";
		
		clsFindClientScreen::ShowFindClient();
	}
	static void _ShowTransactionsMenue(){
		//cout << "Show Transactions Menu Will be Here...\n";
		
		clsTransactionsMenuScreen::ShowTransactionsScreen();
	}
	static void _ManageUsers(){
		//cout << "Manage Users Will be Here...\n";
		
		clsMangeUsersScreen::ShowMangeUserScreen();
	}
	static void _LoginRegister(){
		
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
	}
	static void _Currecny(){
		
		clsCurrecnyScreen::ShowCurrencyScreen();
	}
	static void _Logout()
	{
		User=clsUser::GetEmptyUser();
	}
public :
	static void ShowMainMenu() {
		system("cls");
		clsScreen::_DrawScreenHeader("Main Screen");
		int Choice = clsUtilities::clsSelectOptions({ "List Clients","Add New Client","Delete Client","Update Client","Find Client"
		, "Transactions ","Manage Users","Login Register","Currency Exchange", "Logout"}, "Main Menu");
		switch (Choice)
		{
		case enMainMenueOptions::eAddNewClient:
		{
			system("cls");
			_AddNewClient();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eDeleteClient: 
		{
			system("cls");
			_DeleteClient();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eExit:
		{
				system("cls");
				_Logout();
			break;
		}
		case enMainMenueOptions::eFindClient:
		{
			system("cls");
			_FindClient();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eListClients:
		{
			system("cls");
			_ListClients();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eManageUsers:
		{
			system("cls");
			_ManageUsers();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eShowTransactionsMenue:
		{
			system("cls");
			_ShowTransactionsMenue();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eUpdateClient:
		{
			system("cls");
			_UpdateClient();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eLoginRegister: {
			system("cls");
			_LoginRegister();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eCurrency: {
			system("cls");
			_Currecny();
			_GoBackToMainMenue();
			break;
		}
		default:
			break;
		}
	}
}; 