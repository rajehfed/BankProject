#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>
#include "MainBank.h"


using namespace std;

const string UserFileName = "Users.txt";

vector<string> SplitString(string S1, string Delim);
void ShowMainMenue();
void ShowUserManage();
short ReadMainMenueOption();

struct stUser {
	string userName = "Admin";
	string password = "1234";
	int permissionsRecord = -1;
	bool markForDelete = false;
};

enum enUserPermissions {
	eAll = -1, pShowClients = 1, pAddNewClients = 2,
	pDeleteClients = 4, pUpadateClients = 8, pFindClients = 16,
	pShowTransactions = 32, pManageUsers = 64
};

stUser CurrentUser{
	"Admin",
	"1234",
	-1,
	false
};

stUser ConvertUserLineToRecord(string Line, string Seperator = "#//#") {
	stUser User;
	vector<string> vUsersData = SplitString(Line, Seperator);

	if (vUsersData.size() != 3) {
		// Handle the error: corrupted line
		cout << "Error: Invalid user data format in line: " << Line << endl;
		return User;
	}

	User.userName = vUsersData[0];
	User.password = vUsersData[1];
	User.permissionsRecord = stoi(vUsersData[2]);

	return User;
}

string ConvertUserRecordToLine(stUser User, string Seperator = "#//#") {
	string stUserRecord = "";

	stUserRecord += User.userName + Seperator;
	stUserRecord += User.password + Seperator;
	stUserRecord += to_string(User.permissionsRecord);

	return stUserRecord;
}

bool UserExistsByUserName(string UserName, string FileName) {
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {
		string Line;
		while (getline(MyFile, Line)) {
			stUser User = ConvertUserLineToRecord(Line);
			if (User.userName == UserName) {
				MyFile.close();
				return true;
			}
		}
		MyFile.close();
	}
	return false;
}

int ReadPermissionsToSet() {
	char Answer = 'n';
	int Permissions = 0;

	cout << "\nDo You Want To Give this User The full access? y/n ";
	cin >> Answer;

	if (Answer == 'y' || Answer == 'Y') {
		return -1;
	}

	cout << "\nDo You Want To Give The Access To: \n";

	cout << "Show Client List? y/n? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		Permissions += enUserPermissions::pShowClients;
	};

	cout << "\nAdd New Clients? y/n?\n ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		Permissions += enUserPermissions::pAddNewClients;
	}

	cout << "\nDelete Clients? y/n?\n ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		Permissions += enUserPermissions::pDeleteClients;
	}

	cout << "\nUpdate Clients? y/n? \n";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		Permissions += enUserPermissions::pUpadateClients;
	}

	cout << "\nFind Clients? y/n? \n";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		Permissions += enUserPermissions::pFindClients;
	}

	cout << "\nTransactions Menu? y/n? \n";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		Permissions += enUserPermissions::pShowTransactions;
	}

	cout << "\nManage Users Menu? y/n? \n";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		Permissions += enUserPermissions::pManageUsers;
	}

	return Permissions;
}

stUser ReadNewUser() {
	stUser User;

	cout << "\nPlease Enter The User Name: ";
	getline(cin >> ws, User.userName);

	while (UserExistsByUserName(User.userName, UserFileName)) {
		cout << "\nUser with [" << User.userName << "] already exists, Enter another Username? ";
		getline(cin >> ws, User.userName);
	}

	cout << "\nPlease Enter The User Password: ";
	getline(cin >> ws, User.password);

	User.permissionsRecord = ReadPermissionsToSet();

	return User;
}

vector<stUser> LoadDataFromUserFile(string FileName) {
	vector<stUser> vUsers;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {
		string Line;
		while (getline(MyFile, Line)) {
			stUser User = ConvertUserLineToRecord(Line);
			if (!User.userName.empty()) {  // Only add valid users
				vUsers.push_back(User);
			}
		}
		MyFile.close();
	}
	return vUsers;
}

void PrintUserRecordLine(stUser User) {
	cout << "| " << setw(15) << left << User.userName;
	cout << "| " << setw(40) << left << User.password;
	cout << "| " << setw(12) << left << User.permissionsRecord;
}
void ShowAllUsersScreen()
{
	vector <stUser> vUsers = LoadDataFromUserFile(UserFileName);

	cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ") User(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << left << setw(10) << "Password";
	cout << "| " << left << setw(40) << "Permissions";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	if (vUsers.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else

		for (stUser U : vUsers)
		{

			PrintUserRecordLine(U);
			cout << endl;
		}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

}

void PrintUserRecord(stUser User) {
	cout << "| " << setw(15) << left << User.userName;
	cout << "| " << setw(40) << left << User.password;
	cout << "| " << setw(12) << left << User.permissionsRecord;
};
void UserCard(stUser User) {
	cout << "\nThe following are the User details:\n";
	cout << "-----------------------------------";
	cout << "\nUser Name    : " << User.userName;
	cout << "\nPassword     : " << User.password;
	cout << "\nPermissions  : " << User.permissionsRecord;
	cout << "\n-----------------------------------\n";
}
bool FindUserByUserName(string UserName, vector<stUser> vUsers, stUser& User) {

	for (stUser& U : vUsers) {
		if (U.userName == UserName) {
			User = U;
			return true;
		}
	}

	return false;
}
bool IsPasswordMatch(string Password, vector<stUser> vUsers, stUser& User) {
	for (stUser& U : vUsers) {
		if (U.password == Password) {
			User = U;
			return true;
		}
	}

	return false;
}
stUser ChangeUserRecord(string UserName) {
	stUser User;
	User.userName = UserName;

	cout << "\nEnter The User Password: ";
	getline(cin >> ws, User.password);

	User.permissionsRecord = ReadPermissionsToSet();

	return User;
}
bool MarkUserForDelete(string UserName, vector<stUser>& vUsers) {
	for (stUser& U : vUsers) {
		if (U.userName == UserName) {
			U.markForDelete = true;
			return true;
		}
	}
	return false;
}

vector<stUser> SaveUsersDataToFile(string FileName, vector<stUser> vUsers) {
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string DataLine;

	if (MyFile.is_open()) {

		for (stUser& U : vUsers) {
			if (!U.markForDelete) {
				DataLine = ConvertUserRecordToLine(U);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}

	return vUsers;
};

void AddUserDataLineToFile(string FileName, string stDataLine) {
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open()) {
		MyFile << stDataLine << endl;
		MyFile.close();
	}
}
void AddNewUser() {
	stUser User;
	User = ReadNewUser();
	AddUserDataLineToFile(UserFileName, ConvertUserRecordToLine(User));
}
void AddNewUsers() {
	char AddMore = 'Y';
	do
	{
		cout << "\nAdding New User:\n\n";
		AddNewUser();
		cout << "Do You Want To Add More Users? y/n? ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

bool DeleteUserByUserName(string UserName, vector<stUser>& vUsers) {
	stUser User;
	char Answer = 'n';

	if (FindUserByUserName(UserName, vUsers, User)) {
		UserCard(User);

		cout << "\nAre You Sure That You want To Delete This User? y/n? ";
		cin >> Answer;
		if (tolower(Answer) == 'y') {
			MarkUserForDelete(UserName, vUsers);
			SaveUsersDataToFile(UserFileName, vUsers);
			vUsers = LoadDataFromUserFile(UserFileName);
			return true;
		}
	}
	else {
		cout << "\nUser With User Name {" << UserName << "} is Not Found" << endl;
	}

	return false;
}
bool UpdateUserByUserName(string UserName, vector<stUser>& vUsers) {
	stUser User;
	char Update = 'n';

	if (FindUserByUserName(UserName, vUsers, User)) {
		UserCard(User);
		cout << "\nAre You Sure You Want To Update This User? y/n? ";
		cin >> Update;

		if (toupper(Update) == 'Y') {

			for (stUser& U : vUsers) {
				if (U.userName == UserName) {
					U = ChangeUserRecord(UserName);
					break;
				}
			}
			SaveUsersDataToFile(UserFileName, vUsers);
			cout << "\nUser Updated Successfully.";
			return true;
		}
	}
	else {
		cout << "\nUser With User Name {" << UserName << "} is Not Found" << endl;
		return false;
	}
}

string ReadUserName()
{
	string UserName = "";

	cout << "\nPlease enter User Name? ";
	cin >> UserName;
	return UserName;

}
string ReadUserPassword() {
	string Password = "";

	cout << "\nPlease enter User Password? ";
	cin >> Password;
	return Password;
}

void ShowDeleteUserScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDelete User Screen";
	cout << "\n-----------------------------------\n";

	vector <stUser> vUsers = LoadDataFromUserFile(UserFileName);
	string UserName = ReadUserName();
	if (UserName == "Admin" || UserName == "admin")
		cout << "\nYou Cannot Delete this number User!!" << endl;
	else
		DeleteUserByUserName(UserName, vUsers);


}
void ShowUpdateUserScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate User Info Screen";
	cout << "\n-----------------------------------\n";

	vector <stUser> vUsers = LoadDataFromUserFile(UserFileName);
	string UserName = ReadUserName();
	UpdateUserByUserName(UserName, vUsers);
}
void ShowAddUsersScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tAdd New Users Screen";
	cout << "\n-----------------------------------\n";

	AddNewUsers();
}
void ShowFindUsersScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tFind User Screen";
	cout << "\n-----------------------------------\n";

	vector <stUser> vUsers = LoadDataFromUserFile(UserFileName);
	stUser User;
	string UserName = ReadUserName();
	if (FindUserByUserName(UserName, vUsers, User))
		UserCard(User);
	else
		cout << "\nUsert with User Name[" << UserName << "] is not found!";
}
void GoBackToManageUserMenu() {
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowUserManage();
}

enum enManageUser { eShowUsersList = 1, eAddNewUsers = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMene = 6 };
void PerformeManageUser(enManageUser ManageUser) {
	switch (ManageUser)
	{
	case eShowUsersList:
		system("cls");
		ShowAllUsersScreen();
		GoBackToManageUserMenu();
		break;

	case eAddNewUsers:
		system("cls");
		ShowAddUsersScreen();
		GoBackToManageUserMenu();
		break;

	case eDeleteUser:
		system("cls");
		ShowDeleteUserScreen();
		GoBackToManageUserMenu();
		break;

	case eUpdateUser:
		system("cls");
		ShowUpdateUserScreen();
		GoBackToManageUserMenu();
		break;

	case eFindUser:
		system("cls");
		ShowFindUsersScreen();
		GoBackToManageUserMenu();
		break;

	case eMainMene:
		system("cls");
		ShowMainMenue();
		break;
	}
}
void ShowUserManage() {
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tManage Users Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Show Users List.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User Info.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menu.\n";
	cout << "===========================================\n";
	PerformeManageUser((enManageUser)ReadMainMenueOption());
}

void Login() {
	string UserName = "";
	string Password = "";
	stUser User;
	vector<stUser> vUsers = LoadDataFromUserFile(UserFileName);

	cout << "Please Enter The User Name... ";
	cin >> UserName;

	cout << "Please Enter Password... ";
	cin >> Password;

	while (!FindUserByUserName(UserName, vUsers, User) || !IsPasswordMatch(Password, vUsers, User))
	{
		cout << "\nUser Name / Password Are Wrong Please Try Again? " << endl;
		cout << "Please Enter The User Name... ";
		cin >> UserName;

		cout << "Please Enter Password... ";
		cin >> Password;
	} 

	if (FindUserByUserName(UserName, vUsers, User) && IsPasswordMatch(Password, vUsers, User)) {
		CurrentUser = User;
		ShowMainMenue();
	}
}
void LoginScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tLogin Screen";
	cout << "\n-----------------------------------\n";
	Login();
}