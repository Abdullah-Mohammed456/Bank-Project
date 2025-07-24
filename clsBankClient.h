#pragma once 
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtilities.h"
using namespace std;

class clsBankClient :public clsPerson {
private:
    enum enMode { EmptyMode, UpdateMode, AddNewMode };
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;
    static clsBankClient _ConvertLinetoClientObject(string Line, string Separator = "#//#") {
        vector<string>vClientData = clsString::Split(Line, Separator);
        if (vClientData.size() >= 7) {
            return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3],
                vClientData[4], vClientData[5], std::stof(vClientData[6]));
        }
        return _GetEmptyClientObject();
    }
    static string _ConverClientObjectToLine(clsBankClient Client, string Separator = "#//#") {
        string sClient = "";
        sClient += Client.FirstName + Separator;
        sClient += Client.LastName + Separator;
        sClient += Client.Email + Separator;
        sClient += Client.Phone + Separator;
        sClient += Client.AccountNumber() + Separator;
        sClient += Client.GetPinCode() + Separator;
        sClient += to_string(Client.GetAccountBalance());
        return sClient;
    }
    static clsBankClient _GetEmptyClientObject() {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
    static vector<clsBankClient>_LoadClientsDataFromFile() {

        vector<clsBankClient>vClients;
        fstream MyFile;
        MyFile.open("ClientsData.txt", ios::in);
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                vClients.push_back(Client);
            }
            MyFile.close();
        }
        return vClients;
    }
    static void _SaveCleintsDataToFile  (vector <clsBankClient> _vClients)
    {

        fstream MyFile;
        MyFile.open("ClientsData.txt", ios::out);

        string DataLine;

        if (MyFile.is_open())
        {
            
            for (clsBankClient& C : _vClients)
            {
                if (C._MarkedForDelete == false) {
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }

    }
    void _Update() {

        vector<clsBankClient>_vClients;
        _vClients = _LoadClientsDataFromFile();
        for (clsBankClient& C : _vClients) {
            if (C.AccountNumber() == AccountNumber()) {
                C = *this;
                break;
            }
        }
        _SaveCleintsDataToFile(_vClients);
    }
    void _AddDataLineToFile(string stDataFile) {
        fstream MyFile;
        MyFile.open("ClientsData.txt", ios::out | ios::app);
        if (MyFile.is_open()) {
            MyFile << stDataFile << endl;
            MyFile.close();
        }
    }
    void _AddNew() {
        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }

public:

    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone
        , string AccountNumber, string PinCode, float AccountBalance) :clsPerson(FirstName, LastName, Email, Phone) {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }
    string AccountNumber() {
        return _AccountNumber;
    }
    void SetPinCode(string PinCode) {
        _PinCode = PinCode;
    }
    string GetPinCode() {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;
    void SetAccountBalance(float AccountBalance) {
        _AccountBalance = AccountBalance;
    }
    float GetAccountBalance() const{
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance))float AccountBalance;
  
    bool IsEmpty()const {
        return (_Mode == enMode::EmptyMode);
    }
    static clsBankClient Find(string AccountNumber) {
        fstream MyFile;
        MyFile.open("ClientsData.txt", ios::in);
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber) {
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }
    static clsBankClient Find(string AccountNumber, string PinCode) {
        fstream MyFile;
        MyFile.open("ClientsData.txt", ios::in);
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.GetPinCode() == PinCode) {
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }
    static bool IsClientExist(string AccountNumber) {
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        return (!Client.IsEmpty());
    }


    enum enSaveResults { svFaildEmptyObject, svSucceeded, svFaildAccountExist };
    enSaveResults Save() {
        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            return enSaveResults::svFaildEmptyObject;
            break;

        }
        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;
            break;
        }
        case enMode::AddNewMode:
        {
            if (clsBankClient::IsClientExist(AccountNumber()))
            {
                return enSaveResults::svFaildAccountExist;
            }
            else
            {
                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
        }
        }
    }
    bool Delete() {
        vector<clsBankClient>_vClients=_LoadClientsDataFromFile();
        for (clsBankClient& C : _vClients) {
            if (C.AccountNumber() == AccountNumber()) {
               C._MarkedForDelete = true;
                *this = _GetEmptyClientObject();
                clsBankClient::_SaveCleintsDataToFile(_vClients);
                return true;
            }
            
        }
        return false;
    }
    static clsBankClient GetAddNewClient(string accountnumber) {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", accountnumber, "", 0);
    }
    static vector<clsBankClient>GetClientsList() {
        return clsBankClient::_LoadClientsDataFromFile();
    }
    static double GetTotalBalances() {
        vector<clsBankClient>vClients = _LoadClientsDataFromFile();
        double Total = 0;
        for (clsBankClient C : vClients) {
            Total += C.AccountBalance;
        }
        return Total;
    }
    void Deposit(double Amount) {
        _AccountBalance += Amount;
        Save();
    }
    bool WithDraw(double Amount) {
        if (Amount > _AccountBalance) {
            return false;
        }
        _AccountBalance -= Amount;
        Save();
        return true;
    }
};
    