#pragma once
#include <iostream>
#include "clsUtilities.h"
#include "clsScreen.h"
#include "SetConsoleColors.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalAccountBalanceScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
using namespace std;
class clsTransactionsMenuScreen:protected clsScreen {
private:
	enum enTransactions{eDeposit=1,eWithdraw,eTotalBalances,eTransfer,eTransferLog,eMainMenu};
	static void _GoBackToTransactionsMenu() {
		SetColor(Red);
		cout << setw(36) << left << "" << "Press on any KeyCap to return . . .\n";
		Reset();
		system("pause");
		ShowTransactionsScreen();
	}
	static void _ShowDepositScreen() {
		//cout << "Deposit Screen will be here . . .\n";
		clsDepositScreen::ShowDepositScreen();
	}
	static void _ShowWithdrawScreen() {
		//cout << "Withdraw Screen will be here . . .\n";
		clsWithDrawScreen::ShowWithdrawScreen();
	}
	static void _ShowTotalBalancesScreen() {
		clsTransactionsMenuScreen::_ShowTotalBalancesScreen();
	}
	static void _ShowTransferScreen() {
		clsTransferScreen::ShowTransferScreen();
	}
	static void _ShowTransferLogScreen() {
		clsTransferLogScreen::ShowTransferLogScreen();
	}
public:
	static void ShowTransactionsScreen() {
		if (!clsScreen::Permissions(clsUser::pTransactions))
		{
			return;
		}
		system("cls");
		clsScreen::_DrawScreenHeader("Transactions Menu Screen");
		int choice = clsUtilities::clsSelectOptions({ "Deposit","Withdraw","Total Balances","Transfer","Transfer Log","Main Menu"}, "Transactions Menu");
		switch (choice) {
		case enTransactions::eDeposit: {
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenu();
			break;
		}
		case enTransactions::eMainMenu: {
			system("cls");
			break;
		}
		case enTransactions::eTotalBalances: {
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenu();
			break;
		}
		case enTransactions::eWithdraw: {
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenu();
			break;
		}
		case enTransactions::eTransfer: {
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenu();
			break;
		}
		case enTransactions::eTransferLog: {
			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionsMenu();
			break;
		}
		}

	}
};