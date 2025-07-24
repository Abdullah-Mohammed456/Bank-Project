#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtilities.h"
using namespace std;
class clsUser :public clsPerson {
private:
	enum enMode { enEmptyMode, enUpdateMode, enAddNewMode };
	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkedForDelete = false;
	static clsUser _ConvertLineToUser(string Line, string Separator = "#//#") {
		vector<string>vUsers = clsString::Split(Line, Separator);
		if (vUsers.size() < 7)return GetEmptyUser();
		return clsUser(enMode::enUpdateMode, vUsers[0], vUsers[1], vUsers[2], vUsers[3], vUsers[4],clsUtilities::DecryptedText(vUsers[5]), stoi(vUsers[6]));
	}
	struct LOGIN;
	static LOGIN _ConvertLineToUserLogin(string Line, string Separator = "#//#") {
		vector<string>vUsers = clsString::Split(Line, Separator);
		LOGIN Login;
		Login.Date = vUsers[0];
		Login.UserName = vUsers[1];
		Login.Password = clsUtilities::DecryptedText(vUsers[2]);
		Login.Permissions = vUsers[3];
		return Login;
	}
	struct Transfer;
	static Transfer _ConvertLineToUserTransfer(string Line, string Separator = "#//#") {
		vector<string>vUsers = clsString::Split(Line, Separator);
		Transfer transfer;
		transfer.Date = vUsers[0];
		transfer.SourceAccount = vUsers[1];
		transfer.DestenitionAccount = vUsers[2];
		transfer.Amount = stod(vUsers[3]);
		transfer.SourceBalance = stod(vUsers[4]);
		transfer.DestenitionBalance = stod(vUsers[5]);
		transfer.User = vUsers[6];
		return transfer;
	}
	string _ConvertUserToLine(string Separator = "#//#") {
		string file = "";
		file += FirstName + Separator;
		file += LastName + Separator;
		file += Email + Separator;
		file += Phone + Separator;
		file += UserName + Separator;
		file += clsUtilities::EncryptedText(Password) + Separator;
		file += to_string(Permission) + Separator;
		return file;
	}
	static vector<clsUser>_LoadUsers() {
		vector<clsUser>vUsers;
		fstream MyFile;
		string Line;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open()) {
			while (getline(MyFile, Line)) {
				clsUser User = clsUser::_ConvertLineToUser(Line);
				vUsers.push_back(User);
			}
			MyFile.close();
		}
		return vUsers;
	}
	static vector<LOGIN>_LoadLoginUsers() {
		vector<LOGIN>vUsers;
		fstream MyFile;
		string Line;
		MyFile.open("Login.txt", ios::in);
		if (MyFile.is_open()) {
			while (getline(MyFile, Line)) {
				LOGIN User = clsUser::_ConvertLineToUserLogin(Line);
				vUsers.push_back(User);
			}
			MyFile.close();
		}
		return vUsers;
	}
	static vector<Transfer>_LoadTransferLogUsers() {
		vector<Transfer>vUsers;
		fstream MyFile;
		string Line;
		MyFile.open("Transfer.txt", ios::in);
		if (MyFile.is_open()) {
			while (getline(MyFile, Line)) {
				Transfer User = clsUser::_ConvertLineToUserTransfer(Line);
				vUsers.push_back(User);
			}
			MyFile.close();
		}
		return vUsers;
	}
	static void _SaveUsersToFile(vector<clsUser>vUsers) {
		string File;
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);
		if (MyFile.is_open()) {
			for (auto& U : vUsers) {
				if (U._MarkedForDelete == false) {
					File = U._ConvertUserToLine();
					MyFile << File << endl;
				}
			}
			MyFile.close();
		}

	}

	void _Update() {
		vector < clsUser>vUsers = _LoadUsers();
		for (auto& U : vUsers) {
			if (U.UserName == UserName) {
				U = *this;
				break;
			}
		}
		_SaveUsersToFile(vUsers);
	}
	void AddNewTofile(string File) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);
		if (MyFile.is_open()) {
			MyFile << File << endl;
			MyFile.close();
		}
	}
	void _AddNew() {
		AddNewTofile(this->_ConvertUserToLine());
	}
	
public:

	struct LOGIN {
		string Date;
		string UserName;
		string Password;
		string Permissions;
	};

	struct Transfer {
		string Date;
		string SourceAccount;
		string DestenitionAccount;
		double Amount;
		double SourceBalance;
		double DestenitionBalance;
		string User;
	};


	bool FaildLogin = false;
	string Date;
	enum enPermissions {
		eAll = -1, eHaveNoPermissions = 0, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64
		, pLoginRegister = 128, pCurrencies = 256
	};
	
	bool IsEmpty() const{
		return (_Mode == enMode::enEmptyMode);
	}
	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permission) :
		clsPerson(FirstName, LastName, Email,Phone) {
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permission;
	}
	void SetUserName(const string& UserName) {
		_UserName = UserName;
	}
	string GetUserName()const {
		return _UserName;
	}
	__declspec(property(get = GetUserName, put = SetUserName))string UserName;
	void SetPassword(const string& Password) {
		_Password = Password;
	}
	string GetPassword()const {
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword))string Password;
	void SetPermission(const int& Permission) {
		_Permissions=Permission;
	}
	int GetPermission() {
		return _Permissions;
	}
	__declspec(property(get = GetPermission, put = SetPermission)) int
	Permission;
	
	static bool IsUserExist(string Username) {
		clsUser User=clsUser::Find(Username);
		return (!User.IsEmpty());
	}
	static clsUser Find( string UserName) {
		vector<clsUser>vUsers = clsUser::_LoadUsers();
		for (auto U : vUsers) {
			if (U.UserName == UserName) {
				return U;
			}
		}
		return GetEmptyUser();
	}
	static clsUser Find(const string& UserName,const string& Password) {
		vector<clsUser>vUsers = clsUser::_LoadUsers();
		for (auto U : vUsers) {
			if (U.UserName == UserName&&U.Password==Password) {
				return U;
			}
		}
		return GetEmptyUser();
	}
	enum enSaveResult { svSuccess,svFaild,svFaildExist };
	enSaveResult Save() {
		switch (_Mode)
		{
		case clsUser::enEmptyMode:
		{
			return svFaild;
			break;
		}
		case clsUser::enUpdateMode:
		{
			_Update();
			return svSuccess;
			break;
		}
		case clsUser::enAddNewMode:
		{
			if (clsUser::IsUserExist(UserName)) {
				return svFaildExist;
			}
			else {
				_AddNew();
				_Mode = enMode::enUpdateMode;
				return svSuccess;
			}
		}
		default:
			break;
		}
		
	}
	static clsUser GetAddNewUser(string UserName) {
		return clsUser(enMode::enAddNewMode, "", "", "", "", UserName, "", 0);
	}
	static vector<clsUser>GetListUsers() {
		return _LoadUsers();
	}
	static vector<LOGIN>GetListLoginUsers() {
		return _LoadLoginUsers();
	}
	static vector<Transfer>GetTransferLogUsers() {
		return _LoadTransferLogUsers();
	}
	bool DeleteUser() {
		vector<clsUser>vUsers = _LoadUsers();
		for (auto& U : vUsers) {
			if (U.UserName == _UserName) {
				U._MarkedForDelete = true;
				*this = GetEmptyUser();
				_SaveUsersToFile(vUsers);
				return true;
			}
		}
		return false;
	}
	static clsUser GetEmptyUser() {
		return clsUser(enMode::enEmptyMode, "", "", "", "", "", "", 0);
	}
	bool EnterOrNot(enPermissions Permissions)
	{
		if (this->Permission==enPermissions::eHaveNoPermissions)return false;
		if (this->Permission == enPermissions::eAll)
		{
			return true;
		}
		if ((this->Permission& Permissions)== Permissions)return true;
		else
		{
			return false;
		}
	}
	static clsUser AddNewUser(string username, string Passwrod) {
		return clsUser(enMode::enAddNewMode, "", "", "", "", username, Passwrod, 0);
	}
};