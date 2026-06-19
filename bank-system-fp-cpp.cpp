#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

const string ClinetsFile = "ClientsFile.txt";
const string UsersFile = "Users.txt";

struct sUser
{
    string UserName = "";
    string Password = "";
    int Permissions = 0;
    bool FlagToDelete = false;
    bool FlagToUpdate = false;
};
sUser CurrentUser;

struct sClient
{
    string AccountNumber = "";
    string PinCode = "";
    string Name = "";
    string Phone = "";
    double AccountBalance = 0;
    bool MarkToDelete = false;
    bool MarkToUpdate = false;
};

enum enMainMenueOptions
{
    Show = 1,
    Add = 2,
    Delete = 3,
    Update = 4,
    Find = 5,
    Transaction = 6,
    Manage = 7,
    Logout = 8,
};

enum enTransactionsMenueOptions {
    Deposit = 1,
    Withdraw = 2,
    TotalBalances = 3,
    MainMenueTransactions = 4,
};

enum enManageMenueOptions {
    ListUsers = 1,
    AddUser = 2,
    DeleteUser = 3,
    UpdateUser = 4,
    FindUser = 5,
    MainMenueFromManage = 6,
};

enum enPermissions {
    eAll = -1,
    pListClients = 1,
    pAddNewClient = 2,
    pDeleteClient = 4,
    pUpdateClients = 8,
    pFindClient = 16,
    pTranactions = 32,
    pManageUsers = 64
};

void ShowMainMenu();
void ShowManageUsersMenue();
bool ShowTransactionsMenue();
void GoBackToMainMenue();
void GoBackToManageMenue();
void GoBackToTransactionsMenue();
void Login();
void StartProject();

string ReadAccountNumber() {
    string AccountNumber = "";
    cout << "Please enter your account number ? ";
    getline(cin >> ws, AccountNumber);
    return AccountNumber;
}

double ReadAmount(string message) {
    double Amount = 0;
    do
    {
        cout << message;
        cin >> Amount;
    } while (Amount < 0);
    return Amount;
}

short DetectOperation() {
    short number = 0;
    cin >> number;
    return number;
}

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord;
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "") vString.push_back(sWord);
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "") vString.push_back(S1);
    return vString;
}

vector<string> SplitString2(string S1, string Delim) {
    vector<string> vString;
    short pos = 0;
    string sWord;
    while ((pos = S1.find(Delim)) != std::string::npos) {
        sWord = S1.substr(0, pos);
        if (sWord != "")
            vString.push_back(sWord);
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "") {
        vString.push_back(S1);
    }
    return vString;
}

void GoBackToMainMenue() {
    cout << "\nPress any key to go back to Main Menue\n";
    system("pause>0");
    ShowMainMenu();
}

void GoBackToManageMenue() {
    cout << "\nPress any key to go back to Manage Menue\n";
    system("pause>0");
    ShowManageUsersMenue();
}

void GoBackToTransactionsMenue() {
    cout << "\nPress any key to go back to Transacitons Menue\n";
    system("pause>0");
    ShowTransactionsMenue();
}

void YouDontHavePermission() {
    system("cls");
    cout << "\n-------------------------------------------------\n";
    cout << "Access Denied,\n";
    cout << "You dont Have Permission To Do this,\n";
    cout << "Please Concat Your Admin.\n";
    cout << "\n-------------------------------------------------\n";
    system("pause>0");
}

string ConvertRecordToLine(sClient ClientRecord, string delimiter = "#//#") {
    string s1 = "";
    s1 += ClientRecord.AccountNumber + delimiter;
    s1 += ClientRecord.PinCode + delimiter;
    s1 += ClientRecord.Name + delimiter;
    s1 += ClientRecord.Phone + delimiter;
    s1 += to_string(ClientRecord.AccountBalance);
    return s1;
}

sClient ConvertLineToRecord(string stLine) {
    sClient ClientRecord;
    vector<string> Records = SplitString(stLine, "#//#");
    ClientRecord.AccountNumber = Records[0];
    ClientRecord.PinCode = Records[1];
    ClientRecord.Name = Records[2];
    ClientRecord.Phone = Records[3];
    ClientRecord.AccountBalance = stod(Records[4]);
    return ClientRecord;
}

vector<sClient> LoadDataFromFile(string FileName) {
    vector<sClient> vClients;
    fstream MyFile(FileName, ios::in);
    if (MyFile.is_open())
    {
        sClient stClient;
        string line = "";
        while (getline(MyFile, line)) {
            stClient = ConvertLineToRecord(line);
            vClients.push_back(stClient);
        }
        MyFile.close();
    }
    return vClients;
}

void SaveClientsDataToFile(vector<sClient>& vClient, string FileName) {
    fstream MyFile(FileName, ios::out);
    if (MyFile.is_open())
    {
        string line = "";
        for (sClient& Client : vClient) {
            if (!Client.MarkToDelete)
            {
                line = ConvertRecordToLine(Client);
                MyFile << line << endl;
            }
        }
        MyFile.close();
    }
}

string ConvertUserToLine(sUser User) {
    string line = "";
    line += User.UserName + "#//#";
    line += User.Password + "#//#";
    line += to_string(User.Permissions);
    return line;
}

sUser ConvertLineToUser(string Line) {
    vector<string>vUser = SplitString(Line, "#//#");
    sUser User;
    User.UserName = vUser[0];
    User.Password = vUser[1];
    User.Permissions = stoi(vUser[2]);
    return User;
}

vector<sUser> LoadDataOfUsers(string UsersFile) {
    vector<sUser >vUsers;
    fstream MyFile;
    MyFile.open(UsersFile, ios::in);
    if (MyFile.is_open())
    {
        string line;
        sUser User;
        while (getline(MyFile, line)) {
            User = ConvertLineToUser(line);
            vUsers.push_back(User);
        }
        MyFile.close();
    }
    return vUsers;
}

bool SaveUserToFile(vector<sUser>& vUsers, string FileName) {
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    if (MyFile.is_open())
    {
        string line = "";
        for (sUser& i : vUsers) {
            if (i.FlagToDelete == false)
            {
                line = ConvertUserToLine(i);
                MyFile << line << "\n";
            }
        }
        MyFile.close();
    }
    return true;
}

sClient ReadClientData() {
    sClient Client;
    cout << "Enter Account Number?\n";
    getline(cin >> ws, Client.AccountNumber); cout << endl;
    cout << "Enter Pin Code?\n";
    getline(cin >> ws, Client.PinCode); cout << endl;
    cout << "Enter Name?\n";
    getline(cin >> ws, Client.Name); cout << endl;
    cout << "Enter Phone?\n";
    getline(cin >> ws, Client.Phone); cout << endl;
    cout << "Enter AccountBalane?\n";
    cin >> Client.AccountBalance;
    return Client;
}

void PrintClientRecord(sClient C) {
    cout << "| " << setw(15) << left << C.AccountNumber;
    cout << "| " << setw(10) << left << C.PinCode;
    cout << "| " << setw(40) << left << C.Name;
    cout << "| " << setw(12) << left << C.Phone;
    cout << "| " << setw(12) << left << C.AccountBalance;
    cout << endl;
}

void PrintClientCard(sClient Client) {
    cout << "\nThe following are the client details:\n";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code : " << Client.PinCode;
    cout << "\nName : " << Client.Name;
    cout << "\nPhone : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;
    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin >> ws, Client.Name);
    cout << "Enter Phone? ";
    getline(cin >> ws, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient>& vClients, sClient& Clinet) {
    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Clinet = C;
            return true;
        }
    }
    return false;
}

bool MarkClientToDelete(string AccountNumber, vector <sClient>& vClient) {
    for (sClient& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkToDelete = true;
            return true;
        }
    }
    return false;
}

bool MarkClientToUpdate(string AccountNumber, vector <sClient>& vClient) {
    for (sClient& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkToUpdate = true;
            return true;
        }
    }
    return false;
}

bool DepositAmmountToClient(string AccountNumber, vector<sClient>& vClints, double DepositeAmount) {
    for (sClient& C : vClints) {
        if (C.AccountNumber == AccountNumber)
        {
            C.AccountBalance += DepositeAmount;
            return true;
        }
    }
    return false;
}

bool WithdrawAmmountToClient(string AccountNumber, vector<sClient>& vClints, double WithdrawAmount) {
    for (sClient& C : vClints) {
        if (C.AccountNumber == AccountNumber)
        {
            C.AccountBalance -= WithdrawAmount;
            return true;
        }
    }
    return false;
}

double GetTotalBalances(vector<sClient>vClients) {
    double TotalBalances = 0;
    for (sClient& C : vClients)
        TotalBalances += C.AccountBalance;
    return TotalBalances;
}

sUser ReadANewUser() {
    sUser User;
    cout << "\nEnter Username? ";
    getline(cin >> ws, User.UserName);
    cout << "\nEnter Password? ";
    getline(cin >> ws, User.Password);
    return User;
}

void PrintUserDetailes(sUser i) {
    cout << "\n------------------------------------------------------\n";
    cout << "\n| " << setw(14) << left << i.UserName << "| " << setw(10) << left << i.Password << "| " << setw(14) << left << i.Permissions;
}

void PrintUserCard(sUser User) {
    cout << "\nThe following are the User Details:\n";
    cout << "\n---------------------------------------";
    cout << setw(12) << left << "\nUserName" << ":" << User.UserName;
    cout << setw(12) << left << "\nPassword" << ":" << User.Password;
    cout << setw(12) << left << "\nPermissions" << ":" << User.Permissions;
}

bool FindUserByUserName(sUser& User, vector<sUser>& vUsers) {
    for (sUser& v : vUsers)
    {
        if (v.UserName == User.UserName)
        {
            User = v;
            return true;
        }
    }
    return false;
}

bool MarkUserToDelete(sUser User, vector <sUser>& vUsers) {
    for (sUser& V : vUsers)
    {
        if (V.UserName == User.UserName)
        {
            V.FlagToDelete = true;
            return true;
        }
    }
    return false;
}

bool MarkUserToUpdate(sUser User, vector<sUser> vUsers) {
    for (sUser& U : vUsers)
    {
        if (U.UserName == User.UserName)
        {
            U.FlagToUpdate = true;
            return true;
        }
    }
    return false;
}

void GetAccessForUser(sUser& User) {
    int Permissions = 0;
    char answer = 'n';

    cout << "\nDo you want to give full access? y/n? ";
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
        User.Permissions = -1;
    }
    else {
        cout << "\nDo you want to give access to : \n";

        cout << "\nShow Client List? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            Permissions += 1;

        cout << "\nAdd New Client? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            Permissions += 2;

        cout << "\nDelete Client? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            Permissions += 4;

        cout << "\nUpdate Client? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            Permissions += 8;

        cout << "\nFind Client? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            Permissions += 16;

        cout << "\nTransactions? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            Permissions += 32;

        cout << "\nManage Users? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
            Permissions += 64;

        User.Permissions = Permissions;
    }
}

void ChangeUserDetails(sUser& User) {
    cout << "\nEnter Password? ";
    getline(cin >> ws, User.Password);
    GetAccessForUser(User);
}

bool CheckAccses(enPermissions Permission) {
    if (CurrentUser.Permissions == enPermissions::eAll)
        return true;

    if ((CurrentUser.Permissions & Permission) == Permission)
        return true;

    return false;
}

bool CheckIfUserNameAndPassowrdAreCorrect(string UserName, string Password) {
    vector<sUser> vUsers;
    fstream MyFile(UsersFile, ios::in);
    if (MyFile.is_open())
    {
        sUser stUser;
        string line = "";
        while (getline(MyFile, line)) {
            stUser = ConvertLineToUser(line);
            vUsers.push_back(stUser);
        }
        MyFile.close();
    }

    for (sUser& i : vUsers)
    {
        if (UserName == i.UserName && Password == i.Password)
        {
            CurrentUser = i;
            return true;
        }
    }
    return false;
}

void AddClients() {
    char Answer = 'n';
    do {
        string AccountNumber = ReadAccountNumber();
        vector<sClient> vClients = LoadDataFromFile(ClinetsFile);
        sClient Client;
        while (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
            cout << "Client with [" << AccountNumber << "] already exists Enter another Account Number ? ";
            getline(cin >> ws, AccountNumber);
        }
        Client = ChangeClientRecord(AccountNumber);
        vClients.push_back(Client);
        cout << "Client Added Successfully, do you want to add more clients? Y/N ? ";
        cin >> Answer;
        cout << endl;
        SaveClientsDataToFile(vClients, ClinetsFile);
    } while (Answer == 'y' || Answer == 'Y');
}

void PrintAllClientsData(vector<sClient> vClients) {
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (sClient& C : vClients) {
        PrintClientRecord(C);
    }
}

void ShowClientList() {
    system("cls");
    vector<sClient> vClient = LoadDataFromFile(ClinetsFile);
    PrintAllClientsData(vClient);
}

void DeleteClient() {
    vector<sClient> vClients = LoadDataFromFile(ClinetsFile);
    sClient Client;
    cout << "\n-------------------------------------\n";
    cout << "\tDelete Client Screen\t\n";
    cout << "\n-------------------------------------\n";
    string AccountNumber = ReadAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        MarkClientToDelete(AccountNumber, vClients);
        SaveClientsDataToFile(vClients, ClinetsFile);
        cout << "Client Delete Successfully\n";
    }
    else
    {
        cout << "Client with Account Number(" << AccountNumber << ") is Not Found!\n";
    }
}

void UpdateClient() {
    cout << "\n-------------------------------------\n";
    cout << "\Update Client Info Screen\t\n";
    cout << "\n-------------------------------------\n";
    char Answer = 'n';
    string AccountNumber = ReadAccountNumber();
    vector<sClient> vClients = LoadDataFromFile(ClinetsFile);
    sClient Client;
    if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClients) {
                if (C.AccountNumber == AccountNumber) {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveClientsDataToFile(vClients, ClinetsFile);
            cout << "\n\nClient Update Successfully ";
        }
    }
    else {
        cout << "Client with Account Number(" << AccountNumber << ") is Not Found!\n";
    }
}

void FindClient() {
    cout << "\n-------------------------------------\n";
    cout << "\Find Client Info Screen\t\n";
    cout << "\n-------------------------------------\n";
    string AccountNumber = ReadAccountNumber();
    vector<sClient> vClients = LoadDataFromFile(ClinetsFile);
    sClient Client;
    if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
        PrintClientCard(Client);
    }
    else {
        cout << "Client with Account Number(" << AccountNumber << ") is Not Found!\n";
    }
}

bool ShowDepositScreen() {
    cout << "\n-------------------------------------\n";
    cout << "\tDeposit Screen\t\n";
    cout << "\n-------------------------------------\n";
    vector <sClient>vClients = LoadDataFromFile(ClinetsFile);
    sClient Client;
    string AccountNumber = ReadAccountNumber();
    char Answer = 'Y';
    while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {
        cout << "\n CLient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadAccountNumber();
    }
    PrintClientCard(Client);
    double DepositeAmount = ReadAmount("\nPlease enter your deposite amount? ");
    cout << "\nAre You sure you want perform this transaction? y/n  ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
        DepositAmmountToClient(AccountNumber, vClients, DepositeAmount);
        cout << "\nThe amount has been successfully deposited into the account.\n";
        SaveClientsDataToFile(vClients, ClinetsFile);
        return true;
    }
    else { return false; }
}

bool ShowWithDrawScreen() {
    cout << "\n-------------------------------------\n";
    cout << "\Withdraw Screen\t\n";
    cout << "\n-------------------------------------\n";
    vector <sClient>vClients = LoadDataFromFile(ClinetsFile);
    sClient Client;
    string AccountNumber = ReadAccountNumber();
    char Answer = 'Y';
    while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {
        cout << "\n CLient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadAccountNumber();
    }
    PrintClientCard(Client);
    double WithdrawAmount = ReadAmount("\nPlease enter your Withdraw amount? ");
    while (WithdrawAmount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        WithdrawAmount = ReadAmount("\nPlease enter your Withdraw amount? ");
    }
    cout << "\nAre You sure you want perform this transaction? y/n  ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
        WithdrawAmmountToClient(AccountNumber, vClients, WithdrawAmount);
        cout << "\nThe amount has been successfully Withdraw from the account.\n";
        SaveClientsDataToFile(vClients, ClinetsFile);
        return true;
    }
    else { return false; }
}

void ShowTotalBalanceScreen() {
    vector<sClient>vClients = LoadDataFromFile(ClinetsFile);
    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).\n";
    cout << "\n_____________________________________________________";
    cout << "__________________________________________________________________\n\n";
    cout << " | " << left << setw(20) << "Account Number";
    cout << " | " << left << setw(45) << "Client Name";
    cout << " | " << left << setw(45) << "Balance";
    cout << "\n_____________________________________________________";
    cout << "__________________________________________________________________\n\n\n";
    for (sClient& C : vClients)
    {
        cout << " | " << left << setw(20) << C.AccountNumber;
        cout << " | " << left << setw(45) << C.Name;
        cout << " | " << left << setw(45) << C.AccountBalance << endl;
    }
    cout << endl << "The Total Balances is : " << GetTotalBalances(vClients);
}

void ShowUsersList() {
    vector<sUser>vUsers = LoadDataOfUsers(UsersFile);
    cout << "\t\tUsers List(" << vUsers.size() << ") User(s).\n";
    cout << "\n------------------------------------------------------\n";
    cout << "| " << setw(14) << left << "User Name" << "| " << setw(10) << left << "Password" << "| " << setw(14) << left << "Permissions";

    for (sUser& i : vUsers) {
        PrintUserDetailes(i);
    }
}

void ShowAddNewUser() {
    system("cls");
    cout << "\n-------------------------------------------------\n";
    cout << "\t\tAdd New User Screen\t\t";
    cout << "\n-------------------------------------------------\n";
    cout << "\nAdding New User:\n";
    char Answer = 'n';
    do {
        sUser User = ReadANewUser();
        vector <sUser> vUsers = LoadDataOfUsers(UsersFile);
        while (FindUserByUserName(User, vUsers)) {
            cout << "User with [" << User.UserName << "] already exists Enter another Account Number ? ";
            User = ReadANewUser();
        }
        GetAccessForUser(User);
        vUsers.push_back(User);
        SaveUserToFile(vUsers, UsersFile);

        cout << "\nDo You Want to Add a new User ? y/n ";
        cin >> Answer;
    } while (Answer == 'y' || Answer == 'Y');
}

bool ShowUpdateUser() {
    system("cls");
    cout << "\n-------------------------------------------------\n";
    cout << "\t\Update User Screen\t\t";
    cout << "\n-------------------------------------------------\n";
    char Answer = 'n';

    string UserName = "";
    cout << "Please enter UserName? ";
    getline(cin >> ws, UserName);
    sUser User;
    User.UserName = UserName;
    vector <sUser> vUsers = LoadDataOfUsers(UsersFile);

    if (FindUserByUserName(User, vUsers)) {
        PrintUserCard(User);

        cout << "\nAre you sure you want to Update this User? y/n ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            for (sUser& U : vUsers) {
                if (U.UserName == User.UserName) {
                    ChangeUserDetails(U);
                    break;
                }
            }
            SaveUserToFile(vUsers, UsersFile);
            return true;
        }
    }
    else
    {
        cout << "\nUser with UserName (" << User.UserName << ") is Not Found!\n ";
        return false;
    }
    return false;
}

bool ShowDeleteUser() {
    system("cls");
    cout << "\n-------------------------------------------------\n";
    cout << "\t\tDelete User Screen\t\t";
    cout << "\n-------------------------------------------------\n";
    char Answer = 'n';

    string UserName = "";
    cout << "Please enter UserName? ";
    getline(cin >> ws, UserName);
    sUser User;
    User.UserName = UserName;
    vector <sUser> vUsers = LoadDataOfUsers(UsersFile);
    if (User.UserName == "Admin")
    {
        cout << "\nYou Can not Delete Admins of Users";
        return false;
    }
    if (FindUserByUserName(User, vUsers)) {
        PrintUserCard(User);
        cout << "\nAre you sure you want delete this User? y/n ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            MarkUserToDelete(User, vUsers);
            SaveUserToFile(vUsers, UsersFile);
            return true;
        }
    }
    else
    {
        cout << "\nUser with UserName (" << User.UserName << ") is Not Found!\n ";
        return false;
    }
    return false;
}

void ShowFindClient() {
    system("cls");
    cout << "\n-------------------------------------------------\n";
    cout << "\t\Find User Screen\t\t";
    cout << "\n-------------------------------------------------\n";

    cout << "Please enter UserName? ";
    sUser User;
    getline(cin >> ws, User.UserName);
    vector <sUser> vUsers = LoadDataOfUsers(UsersFile);

    if (FindUserByUserName(User, vUsers))
        PrintUserCard(User);
    else
        cout << "\nUser with UserName (" << User.UserName << ") is Not Found!\n ";
}

void ReadOperationTransaction(enTransactionsMenueOptions Operation) {
    switch (Operation) {
    case enTransactionsMenueOptions::Deposit:
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenue();
        break;
    case enTransactionsMenueOptions::Withdraw:
        system("cls");
        ShowWithDrawScreen();
        GoBackToTransactionsMenue();
        break;
    case enTransactionsMenueOptions::TotalBalances:
        system("cls");
        ShowTotalBalanceScreen();
        GoBackToTransactionsMenue();
        break;
    case enTransactionsMenueOptions::MainMenueTransactions:
        system("cls");
        ShowMainMenu();
        break;
    }
}

bool ShowTransactionsMenue() {
    system("cls");
    cout << "\n=================================================\n";
    cout << "\t\tTransactions Menue Screen\t\t";
    cout << "\n=================================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "\n=================================================\n";
    cout << "Choose what do you want to do? [1 to 4]? ";

    ReadOperationTransaction((enTransactionsMenueOptions)DetectOperation());
    return true;
}

void ChooseOperationToManage(enManageMenueOptions Operation) {
    switch (Operation) {
    case enManageMenueOptions::ListUsers:
        system("cls");
        ShowUsersList();
        GoBackToManageMenue();
        break;
    case enManageMenueOptions::AddUser:
        system("cls");
        ShowAddNewUser();
        GoBackToManageMenue();
        break;
    case enManageMenueOptions::DeleteUser:
        system("cls");
        ShowDeleteUser();
        GoBackToManageMenue();
        break;
    case enManageMenueOptions::UpdateUser:
        system("cls");
        ShowUpdateUser();
        GoBackToManageMenue();
        break;
    case enManageMenueOptions::FindUser:
        system("cls");
        ShowFindClient();
        GoBackToManageMenue();
        break;
    case enManageMenueOptions::MainMenueFromManage:
        system("cls");
        ShowMainMenu();
        break;
    default:
        system("cls");
        ShowUsersList();
        GoBackToManageMenue();
        break;
    }
}

void ShowManageUsersMenue() {
    system("cls");
    cout << "\n=================================================\n";
    cout << "\t\tManage Users Menue Screen\t\t";
    cout << "\n=================================================\n";

    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menue.\n";
    cout << "=================================================\n";
    cout << "Choose what do you want to do ? [1 to 6]:   ";
    ChooseOperationToManage((enManageMenueOptions)DetectOperation());
}

void BeginOperations(enMainMenueOptions Operation) {
    switch (Operation) {
    case enMainMenueOptions::Show:
        system("cls");
        if (CheckAccses(enPermissions::pListClients))
            ShowClientList();
        else
            YouDontHavePermission();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::Add:
        system("cls");
        if (CheckAccses(enPermissions::pAddNewClient))
            AddClients();
        else
            YouDontHavePermission();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::Delete:
        system("cls");
        if (CheckAccses(enPermissions::pDeleteClient))
            DeleteClient();
        else
            YouDontHavePermission();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::Update:
        system("cls");
        if (CheckAccses(enPermissions::pUpdateClients))
            UpdateClient();
        else
            YouDontHavePermission();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::Find:
        system("cls");
        if (CheckAccses(enPermissions::pFindClient))
            FindClient();
        else
            YouDontHavePermission();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::Transaction:
        system("cls");
        if (CheckAccses(enPermissions::pTranactions))
            ShowTransactionsMenue();
        else
            YouDontHavePermission();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::Manage:
        system("cls");
        if (CheckAccses(enPermissions::pManageUsers))
            ShowManageUsersMenue();
        else
            YouDontHavePermission();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::Logout:
        system("cls");
        Login();
        break;
    default:
        system("cls");
        ShowClientList();
        GoBackToMainMenue();
        break;
    }
}

void ShowMainMenu() {
    system("cls");
    cout << "\n=================================================\n";
    cout << "\t\tMain Menue Screen\t\t";
    cout << "\n=================================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "=================================================\n";
    cout << "Choose what do you want to do ? [1 to 8]:   ";
    BeginOperations((enMainMenueOptions)DetectOperation());
}

void StartProject() {
    ShowMainMenu();
}

void Login() {
    system("cls");
    cout << "\n-------------------------------------------------\n";
    cout << "\t\tLogin Screen\t\t";
    cout << "\n-------------------------------------------------\n";
    string UserName, Password;
    cout << "\nEnter UserName? "; getline(cin >> ws, UserName);
    cout << "\nEnter Password? "; getline(cin >> ws, Password);

    while (CheckIfUserNameAndPassowrdAreCorrect(UserName, Password) == false) {
        system("cls");
        cout << "\n-------------------------------------------------\n";
        cout << "\t\tLogin Screen\t\t";
        cout << "\n-------------------------------------------------\n";
        cout << "Invalid UserName or Paswwrod";
        cout << "\nEnter UserName? "; getline(cin >> ws, UserName);
        cout << "\nEnter Password? "; getline(cin >> ws, Password);
    };
    StartProject();
}

int main() {
    Login();
}