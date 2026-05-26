#include <iostream>
#include <string>
using namespace std;

#define MAX_ACCOUNTS 100


int accountNumber[MAX_ACCOUNTS];
string accountName[MAX_ACCOUNTS];
string accountType[MAX_ACCOUNTS];
string accountPin[MAX_ACCOUNTS];
double accountBalance[MAX_ACCOUNTS];
bool accountActive[MAX_ACCOUNTS];
int totalAccounts = 0;
int nextAccountNumber = 1001;


string ADMIN_PIN = "admin123";


void printLine()
{
    cout<<endl;
}


int findAccount(int accNo)
{
    for (int i = 0; i < totalAccounts; i++)
    {
        if (accountNumber[i] == accNo)
        {
            return i;
        }
    }
    return -1;
}


void createAccount()
{
    if (totalAccounts >= MAX_ACCOUNTS)
    {
        cout << "Sorry, bank is full!" << endl;
        return;
    }

    string name, pin, confirm, type;
    double opening;
    int choice;

    cout << endl;
    printLine();
    cout << "      OPEN NEW ACCOUNT" << endl;
    printLine();

    cout << "Enter your full name : ";
    cin.ignore();
    getline(cin, name);

    cout << "Account type?" << endl;
    cout << "  1. Savings" << endl;
    cout << "  2. Checking" << endl;
    cout << "Your choice : ";
    cin >> choice;

    if (choice == 1)
    {
        type = "Savings";
    }
    else
    {
        type = "Current";
    }

    cout << "Set a 4-digit PIN : ";
    cin >> pin;
    cout << "Confirm your PIN  : ";
    cin >> confirm;

    if (pin != confirm)
    {
        cout << "PINs do not match! Try again." << endl;
        return;
    }

    cout << "Opening deposit amount : Rs. ";
    cin >> opening;

    if (opening < 500)
    {
        cout << "Minimum opening deposit is Rs. 500" << endl;
        return;
    }

    // Save the account
    int i = totalAccounts;
    accountNumber[i] = nextAccountNumber;
    accountName[i] = name;
    accountType[i] = type;
    accountPin[i] = pin;
    accountBalance[i] = opening;
    accountActive[i] = true;

    cout << endl;
    cout << "Account created successfully!" << endl;
    cout << "Your Account Number is : " << nextAccountNumber << endl;

    totalAccounts++;
    nextAccountNumber++;
}


void depositMoney(int index)
{
    double amount;
    cout << "Enter amount to deposit : Rs. ";
    cin >> amount;

    if (amount <= 0)
    {
        cout << "Invalid amount!" << endl;
        return;
    }

    accountBalance[index] += amount;
    cout << "Rs. " << amount << " deposited successfully." << endl;
    cout << "New Balance : Rs. " << accountBalance[index] << endl;
}


void withdrawMoney(int index)
{
    double amount;
    cout << "Enter amount to withdraw : Rs. ";
    cin >> amount;

    if (amount <= 0)
    {
        cout << "Invalid amount!" << endl;
        return;
    }

    if (amount > accountBalance[index])
    {
        cout << "Not enough balance!" << endl;
        return;
    }

    accountBalance[index] -= amount;
    cout << "Rs. " << amount << " withdrawn successfully." << endl;
    cout << "New Balance : Rs. " << accountBalance[index] << endl;
}


void transferMoney(int fromIndex)
{
    int toAccNo;
    double amount;

    cout << "Enter destination account number : ";
    cin >> toAccNo;

    int toIndex = findAccount(toAccNo);

    if (toIndex == -1)
    {
        cout << "Destination account not found!" << endl;
        return;
    }

    if (!accountActive[toIndex])
    {
        cout << "Destination account is closed!" << endl;
        return;
    }

    if (toIndex == fromIndex)
    {
        cout << "Cannot transfer to your own account!" << endl;
        return;
    }

    cout << "Enter amount to transfer : Rs. ";
    cin >> amount;

    if (amount <= 0)
    {
        cout << "Invalid amount!" << endl;
        return;
    }

    if (amount > accountBalance[fromIndex])
    {
        cout << "Not enough balance!" << endl;
        return;
    }

    accountBalance[fromIndex] -= amount;
    accountBalance[toIndex] += amount;

    cout << "Rs. " << amount << " transferred to "
         << accountName[toIndex] << " successfully." << endl;
    cout << "Your new balance : Rs. " << accountBalance[fromIndex] << endl;
}
void showDetails(int index)
{
    printLine();
    cout << "       ACCOUNT DETAILS" << endl;
    printLine();
    cout << "Account Number : " << accountNumber[index] << endl;
    cout << "Account Holder : " << accountName[index] << endl;
    cout << "Account Type   : " << accountType[index] << endl;
    cout << "Balance        : Rs. " << accountBalance[index] << endl;
    cout << "Status         : " << (accountActive[index] ? "Active" : "Closed") << endl;
    printLine();
}


void changePin(int index)
{
    string oldPin, newPin, confirm;

    cout << "Enter current PIN : ";
    cin >> oldPin;

    if (oldPin != accountPin[index])
    {
        cout << "Wrong PIN!" << endl;
        return;
    }

    cout << "Enter new PIN     : ";
    cin >> newPin;
    cout << "Confirm new PIN   : ";
    cin >> confirm;

    if (newPin != confirm)
    {
        cout << "PINs do not match!" << endl;
        return;
    }

    accountPin[index] = newPin;
    cout << "PIN changed successfully!" << endl;
}

// ── Account menu after login ──
void accountMenu(int index)
{
    int choice;

    do
    {
        cout << endl;
        printLine();
        cout << "  Welcome, " << accountName[index] << endl;
        cout << "  Balance : Rs. " << accountBalance[index] << endl;
        printLine();
        cout << "  1. Deposit" << endl;
        cout << "  2. Withdraw" << endl;
        cout << "  3. Transfer" << endl;
        cout << "  4. View Account Details" << endl;
        cout << "  5. Change PIN" << endl;
        cout << "  0. Logout" << endl;
        printLine();
        cout << "  Your choice : ";
        cin >> choice;

        if (choice == 1)
        {
            depositMoney(index);
        }
        else if (choice == 2)
        {
            withdrawMoney(index);
        }
        else if (choice == 3)
        {
            transferMoney(index);
        }
        else if (choice == 4)
        {
            showDetails(index);
        }
        else if (choice == 5)
        {
            changePin(index);
        }
        else if (choice == 0)
        {
            cout << "Logged out. Goodbye!" << endl;
        }
        else
        {
            cout << "Invalid choice! Try again." << endl;
        }

    } while (choice != 0);
}

// ── Login ──
void login()
{
    int accNo;
    string pin;

    cout << "Enter account number : ";
    cin >> accNo;
    cout << "Enter PIN            : ";
    cin >> pin;

    int index = findAccount(accNo);

    if (index == -1)
    {
        cout << "Account not found!" << endl;
        return;
    }

    if (!accountActive[index])
    {
        cout << "This account is closed!" << endl;
        return;
    }

    if (pin != accountPin[index])
    {
        cout << "Wrong PIN!" << endl;
        return;
    }

    accountMenu(index);
}

// ── Admin: list all accounts ──
void listAllAccounts()
{
    if (totalAccounts == 0)
    {
        cout << "No accounts yet!" << endl;
        return;
    }

    printLine();
    cout << "  No.  Name                Type       Balance     Status" << endl;
    printLine();

    for (int i = 0; i < totalAccounts; i++)
    {
        cout << "  " << accountNumber[i]
             << "  " << accountName[i]
             << "  " << accountType[i]
             << "  Rs." << accountBalance[i]
             << "  " << (accountActive[i] ? "Active" : "Closed")
             << endl;
    }
    printLine();
}

// ── Admin: search one account ──
void searchAccount()
{
    int accNo;
    cout << "Enter account number to search : ";
    cin >> accNo;

    int index = findAccount(accNo);
    if (index == -1)
    {
        cout << "Account not found!" << endl;
        return;
    }

    showDetails(index);
}

// ── Admin: close an account ──
void closeAccount()
{
    int accNo;
    cout << "Enter account number to close : ";
    cin >> accNo;

    int index = findAccount(accNo);
    if (index == -1)
    {
        cout << "Account not found!" << endl;
        return;
    }

    accountActive[index] = false;
    cout << "Account " << accNo << " has been closed." << endl;
}

// ── Admin: show bank summary ──
void bankSummary()
{
    int activeCount = 0;
    double totalMoney = 0;

    for (int i = 0; i < totalAccounts; i++)
    {
        if (accountActive[i])
        {
            activeCount++;
            totalMoney += accountBalance[i];
        }
    }

    printLine();
    cout << "       BANK SUMMARY" << endl;
    printLine();
    cout << "Total accounts  : " << totalAccounts << endl;
    cout << "Active accounts : " << activeCount << endl;
    cout << "Total money     : Rs. " << totalMoney << endl;
    printLine();
}

// ── Admin menu ──
void adminMenu()
{
    string pin;
    cout << "Enter admin PIN : ";
    cin >> pin;

    if (pin != ADMIN_PIN)
    {
        cout << "Wrong admin PIN! Access denied." << endl;
        return;
    }

    int choice;

    do
    {
        cout << endl;
        printLine();
        cout << "         ADMIN PANEL" << endl;
        printLine();
        cout << "  1. List all accounts" << endl;
        cout << "  2. Search an account" << endl;
        cout << "  3. Close an account" << endl;
        cout << "  4. Bank summary" << endl;
        cout << "  0. Back to main menu" << endl;
        printLine();
        cout << "  Your choice : ";
        cin >> choice;

        if (choice == 1)
        {
            listAllAccounts();
        }
        else if (choice == 2)
        {
            searchAccount();
        }
        else if (choice == 3)
        {
            closeAccount();
        }
        else if (choice == 4)
        {
            bankSummary();
        }
        else if (choice == 0)
        {
            cout << "Returning to main menu..." << endl;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 0);
}

// ── Main function ──
int main()
{
    int choice;

    do
    {
        cout << endl;
        printLine();
        cout << "    WELCOME TO MY BANK SYSTEM" << endl;
        printLine();
        cout << "  1. Create New Account" << endl;
        cout << "  2. Login" << endl;
        cout << "  3. Admin Panel" << endl;
        cout << "  0. Exit" << endl;
        printLine();
        cout << "  Your choice : ";
        cin >> choice;

        if (choice == 1)
        {
            createAccount();
        }
        else if (choice == 2)
        {
            login();
        }
        else if (choice == 3)
        {
            adminMenu();
        }
        else if (choice == 0)
        {
            cout << "Thank you! Goodbye!" << endl;
        }
        else
        {
            cout << "Invalid choice! Try again." << endl;
        }

    } while (choice != 0);

    return 0;
}
