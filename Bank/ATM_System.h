#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "MainBank.h"

void ATMMainMenuScreen();
using namespace std;

enum enATMOptions{ eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposite = 3, eCheckBalance = 4, eLogout = 5 };

void GoBackToATMMenuScreen() {
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ATMMainMenuScreen();
}

void DepositeBalance(short Balance) {
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    if (CurrentClient.AccountBalance - Balance < 0) {
        SetConsoleColor(4);
        cout << "\nThe Amount Exceeds Your Balance, Make Another Choise." << endl;
    }
    else 
        DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, Balance * -1, vClients);

    SaveCleintsDataToFile(ClientsFileName, vClients);
}

void ShowQuickWithdrawScreen()
{
    SetConsoleColor(8);
    cout << "\n-----------------------------------\n";
    cout << "\t\tQuick Withdraw Screen";
    cout << "\n-----------------------------------\n";
    cout << "\t[1] 20 \t\t[2] 50" << endl;
    cout << "\t[3] 100 \t[4] 200" << endl;
    cout << "\t[5] 400 \t[6] 600" << endl;
    cout << "\t[7] 800 \t[8] 1000" << endl;
    cout << "\t[9] Exite" << endl;
    cout << "\n-----------------------------------\n";
    
    short Choise = 0;
    SetConsoleColor(8);
    cout << "Choose What Do You Want to do? ";
    cin >> Choise;

    switch (Choise) {
    case 1:
        system("cls");
        DepositeBalance(20);
        break;
    
    case 2:
        system("cls");
        DepositeBalance(50);
        break;

    case 3:
        system("cls");
        DepositeBalance(100);
        break;

    case 4:
        system("cls");
        DepositeBalance(200);
        break;

    case 5:
        system("cls");
        DepositeBalance(400);
        break;

    case 6:
        system("cls");
        DepositeBalance(600);
        break;

    case 7:
        system("cls");
        DepositeBalance(800);
        break;

    case 8:
        system("cls");
        DepositeBalance(1000);
        break;

    default:
        GoBackToATMMenuScreen();
        break;
    }

}
void LoginClientScreen() {
    cout << "===========================================\n";
    cout << "\t\tLogin Screen\n";
    cout << "===========================================\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    
    string AccountNumber = "";
    cout << "Please Enter The Account Number? ";
    cin >> AccountNumber;
    while (!FindClientByAccountNumber(AccountNumber, vClients, Client)){
        cout << "\nWe Cannot Find Your Account Make Sure to Enter An Existing Account Number? ";
        cin >> AccountNumber;
    } 

    string PINCode = "";
    cout << "\nPlease Enter The PIN code? ";
    cin >> PINCode;
    while ((Client.PinCode != PINCode))
    {
        cout << "\nPlease Enter The Right PIN code? ";
        cin >> PINCode;
    }

    CurrentClient = Client;
    
    ATMMainMenuScreen();
}

void PerformeATMOptions(enATMOptions ATMOptions)
{
    switch (ATMOptions)
    {
    case enATMOptions::eQuickWithdraw:
        system("cls");
        ShowQuickWithdrawScreen();
        GoBackToATMMenuScreen();
        break;

    case enATMOptions::eNormalWithdraw:
        system("cls");
        ShowWithDrawScreen();
        GoBackToATMMenuScreen();
        break;

    case enATMOptions::eDeposite:
        system("cls");
        ShowDepositScreen();
        GoBackToATMMenuScreen();
        break;

    case enATMOptions::eCheckBalance:
        system("cls");
        cout << "\nYour Balace Is " << CurrentClient.AccountBalance << "\n";
        GoBackToATMMenuScreen();
        break;

    case enATMOptions::eLogout:
        system("cls");
        break;

    default:
        break;
    }
}

void ATMMainMenuScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tATM Main Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposite.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "===========================================\n";
    SetConsoleColor(8);
    PerformeATMOptions((enATMOptions)ReadMainMenueOption());
}