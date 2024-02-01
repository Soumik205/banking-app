#include <bits/stdc++.h>
using namespace std;

class BankAccount
{
private:
    int type;
    string name;
    int number;
    string creationDate;
    double balance;

public:
    BankAccount(int t, string n, int num, string date, double bal) : type(t), name(n), number(num), creationDate(date), balance(bal) {}

    // displays account information
    void displayAccount() const
    {
        if (type == 1) cout << "Account Type: Current Account";
        else if (type == 2) cout << "Account Type: Savings Account";
        else if (type == 3) cout << "Account Type: Salary Account";
        cout << "\nName: " << name << "\nAccount Number: " << number << "\nCreation Date: " << creationDate << "\nBalance: $" << balance << endl << endl;
    }

    // returns the account number
    int getAccountNumber() const
    {
        return number;
    }

    // returns the account type
    int getType () const 
    {
        return type;
    }

    // used to change user name of any account
    void changeName(string newName) 
    {
        name = newName;
        cout << "Changed account holder name to " << name << "!" << endl << endl;
    }

    // checks if the current balance is less than the minimum balance for that type of account or not
    static bool isLegal (int type, double amount) 
    {
        if (type == 1 && amount < 200) return false;
        else if (type == 2 && amount < 100) return false;
        else return true;
    }

    // perfroms the deposit operation
    void deposit(double amount) 
    {
        balance += amount;
        cout << "Deposited $" << amount << " into account " << number << ". New balance: $" << balance << endl << endl;
    }

    // performs the money withdrawal operation
    bool withdraw(double amount, int type)
    {
        if (balance >= amount)
        {
            double temp = balance - amount;
            if (isLegal(type, temp)) 
            {
                balance -= amount;
                cout << "Withdrawn $" << amount << " from account " << number << ". New balance: $" << balance << endl << endl;
                return true;
            }
            else {
                cout << "Please maintain the minimum balance. Insufficient funds in account " << number << ". Unable to withdraw." << endl << endl;
                return false;
            }
        }
        else
        {
            cout << "Insufficient funds in account " << number << ". Unable to withdraw." << endl << endl;
            return false;
        }
    }

    
};

class Bank
{
private:
    vector <BankAccount> accounts;

public:
    void createAccount (int type, const string &name, int number, const string &date, double balance)
    {
        if (BankAccount::isLegal(type, balance)) 
        {
            accounts.emplace_back(type, name, number, date, balance);
            cout << "Hello, " << name << ". Your account is created successfully!" << endl << endl;
        }
        else 
        {
            cout << "The minimum balance criteria for this type of account is not fulfilled. Please increase the balance." << endl << endl;
        }
        
    }

    // used to display all the accounts currently in the bank
    void displayAllAccounts() const
    {
        cout << "All Accounts: " << endl;
        for (const auto &account : accounts)
        {
            account.displayAccount();
        }
    }

    // Updates the name of any user account
    void updateAccount (int accountNumber)
    {
        cout << "We only allow you to change your name." << endl << endl;
        for (auto &account : accounts)
        {
            if (account.getAccountNumber() == accountNumber)
            {
                string newName;
                cout << "Enter new name of account holder " << accountNumber << ": ";
                getchar();
                getline(cin, newName);
                account.changeName(newName);
                cout << "Account updated successfully!" << endl << endl;
                return;
            }
        }
        cout << "Account not found!" << endl << endl;
    }

    // used to delete the account of any user
    void deleteAccount(int accountNumber) 
    {
        auto it = remove_if(accounts.begin(), accounts.end(), [accountNumber](const BankAccount& account) 
        {
            return account.getAccountNumber() == accountNumber;
        });

        if (it != accounts.end()) 
        {
            accounts.erase(it, accounts.end());
            cout << "Account deleted successfully!" << endl << endl;
        } 
        else 
        {
            cout << "Account not found!" << endl << endl;
        }
    }

    // used to perform deposit operation
    void depositAmount (int accountNumber, double amount)
    {
        for (auto &account : accounts)
        {
            if (account.getAccountNumber() == accountNumber)
            {
                account.deposit(amount);
                return;
            }
        }
        cout << "Account not found!" << endl << endl;
    }

    // used to perform the withdrawal operation 
    void withdrawAmount(int accountNumber, double amount)
    {
        for (auto &account : accounts)
        {
            if (account.getAccountNumber() == accountNumber)
            {
                int type = account.getType();
                if (account.withdraw(amount, type))
                {
                    return;
                }
                else
                {
                    cout << "Withdrawal unsuccessful." << endl << endl;
                    return;
                }
            }
        }
        cout << "Account not found!" << endl << endl;
    }

    // used to perform the search opeartion based on account number
    void searchAccount(int accountNumber) const
    {
        for (const auto &account : accounts)
        {
            if (account.getAccountNumber() == accountNumber)
            {
                account.displayAccount();
                return;
            }
        }
        cout << "Oops! Account not found!" << endl << endl;
    }
};


int main()
{
    Bank bank;
    int choice;

    while (true)
    {
        cout << "\n\nBanking Application" << endl;
        cout << "1. Create a new account" << endl;
        cout << "2. Display all accounts" << endl;
        cout << "3. Update an account" << endl;
        cout << "4. Delete an account" << endl;
        cout << "5. Deposit an amount into your account" << endl;
        cout << "6. Withdraw an amount from your account" << endl;
        cout << "7. Search for an account" << endl;
        cout << "8. Exit" << endl;
        cout << "Please enter your choice (1-8): ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                int type;
                string name;
                int accountNumber;
                string creationDate;
                double initialBalance;

                cout << "\nWelcome to the account creation portal" << endl;
                cout << "--------------------------------------\n" << endl;
                
                cout << "Please choose one of the below available account types:" << endl;
                cout << "1. Current Account (Minimum Balance required 200$)" << endl;
                cout << "2. Savings Account (Minimum Balance required 100$)" << endl;
                cout << "3. Salary Account (Minimum Balance required 0$)" << endl << endl;

                cout << "Please enter account type (1-3): ";
                cin >> type;
                cout << "Please enter user name: ";
                getchar();
                getline(cin, name);
                cout << "Please enter an unique account number: ";
                cin >> accountNumber;
                cout << "Please enter creation date (DD/MM/YYYY): ";
                cin >> creationDate;
                cout << "Please enter initial balance: $";
                cin >> initialBalance;

                bank.createAccount(type, name, accountNumber, creationDate, initialBalance);
                break;
            }
            case 2:
            {
                cout << "\nHere are all the accounts in this bank: " << endl;
                cout << "-----------------------------------------\n" << endl;
                bank.displayAllAccounts();
                break;
            }
            case 3:
            {
                cout << "\nWelcome to the account update portal" << endl;
                cout << "------------------------------------\n" << endl;

                int accountNumber;
                cout << "Please enter account number to update: ";
                cin >> accountNumber;
                bank.updateAccount(accountNumber);
                break;
            }
            case 4:
            {
                cout << "\nWant to delete your account? You're in the right place!" << endl;
                cout << "-------------------------------------------------------\n" << endl;

                int accountNumber;
                cout << "Please enter account number to delete: ";
                cin >> accountNumber;
                bank.deleteAccount(accountNumber);
                break;
            }
            case 5:
            {
                cout << "\nWelcome to the cash deposit portal" << endl;
                cout << "----------------------------------\n" << endl;

                int accountNumber;
                double amount;
                cout << "Please enter account number to deposit into: ";
                cin >> accountNumber;
                cout << "Please enter amount to deposit: $";
                cin >> amount;
                bank.depositAmount(accountNumber, amount);
                break;
            }
            case 6:
            {
                cout << "\nWelcome to the cash withdrawal portal" << endl;
                cout << "-------------------------------------\n" << endl;

                int accountNumber;
                double amount;
                int type;
                cout << "Please enter account number to withdraw from: ";
                cin >> accountNumber;
                cout << "Please enter amount to withdraw: $";
                cin >> amount;
                bank.withdrawAmount(accountNumber, amount);
                break;
            }
            case 7:
            {
                cout << "\nWelcome to the search account portal" << endl;
                cout << "------------------------------------\n" << endl;

                int accountNumber;
                cout << "Please enter account number to search: ";
                cin >> accountNumber;
                bank.searchAccount(accountNumber);
                break;
            }
            case 8:
                cout << "\nHope you liked our service! Closing Window...!\n";
                return 0;
            default:
                cout << "\nInvalid choice. Please enter a number between 1 and 8.\n";
        }
    }
    return 0;
}