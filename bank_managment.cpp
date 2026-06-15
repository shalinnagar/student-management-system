/*
 * ================================================
 *       BANK MANAGEMENT APPLICATION
 *       C++ | OOP + File Handling
 * ================================================
 */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// ============================================================
// CLASS: BankAccount
// ============================================================
class BankAccount {
private:
    int accountNumber;
    string customerName;
    double balance;

public:
    // Constructor
    BankAccount() {
        accountNumber = 0;
        customerName = "";
        balance = 0.0;
    }

    BankAccount(int accNo, string name, double bal) {
        accountNumber = accNo;
        customerName = name;
        balance = bal;
    }

    // ---- Getters ----
    int getAccountNumber() { return accountNumber; }
    string getCustomerName() { return customerName; }
    double getBalance() { return balance; }

    // ---- Setters ----
    void setAccountNumber(int accNo) { accountNumber = accNo; }
    void setCustomerName(string name) { customerName = name; }
    void setBalance(double bal) { balance = bal; }

    // ---- Core Banking Operations ----

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "\n[ERROR] Invalid deposit amount!\n";
            return;
        }
        balance += amount;
        cout << "\n[SUCCESS] Rs. " << fixed << setprecision(2) << amount
             << " deposited successfully!\n";
        cout << "New Balance: Rs. " << balance << "\n";
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "\n[ERROR] Invalid withdrawal amount!\n";
            return false;
        }
        if (amount > balance) {
            cout << "\n[ERROR] Insufficient balance! Available: Rs. "
                 << fixed << setprecision(2) << balance << "\n";
            return false;
        }
        balance -= amount;
        cout << "\n[SUCCESS] Rs. " << fixed << setprecision(2) << amount
             << " withdrawn successfully!\n";
        cout << "Remaining Balance: Rs. " << balance << "\n";
        return true;
    }

    void checkBalance() {
        cout << "\n-----------------------------\n";
        cout << "  Account No : " << accountNumber << "\n";
        cout << "  Name       : " << customerName << "\n";
        cout << "  Balance    : Rs. " << fixed << setprecision(2) << balance << "\n";
        cout << "-----------------------------\n";
    }

    void displayAccount() {
        cout << left << setw(12) << accountNumber
             << setw(20) << customerName
             << "Rs. " << fixed << setprecision(2) << balance << "\n";
    }
};

// ============================================================
// CLASS: Bank (File Handling + Menu)
// ============================================================
class Bank {
private:
    string filename;

    // Save single account to file (append mode)
    void saveToFile(BankAccount &acc) {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << acc.getAccountNumber() << "\n"
                 << acc.getCustomerName() << "\n"
                 << acc.getBalance() << "\n";
            file.close();
        } else {
            cout << "[ERROR] Could not open file for saving!\n";
        }
    }

    // Rewrite entire file from array
    void rewriteFile(BankAccount accounts[], int count) {
        ofstream file(filename, ios::trunc);
        if (file.is_open()) {
            for (int i = 0; i < count; i++) {
                file << accounts[i].getAccountNumber() << "\n"
                     << accounts[i].getCustomerName() << "\n"
                     << accounts[i].getBalance() << "\n";
            }
            file.close();
        }
    }

    // Load all accounts from file
    int loadFromFile(BankAccount accounts[], int maxSize) {
        ifstream file(filename);
        int count = 0;
        if (file.is_open()) {
            int accNo;
            string name;
            double bal;
            while (file >> accNo && count < maxSize) {
                file.ignore();
                getline(file, name);
                file >> bal;
                file.ignore();
                accounts[count].setAccountNumber(accNo);
                accounts[count].setCustomerName(name);
                accounts[count].setBalance(bal);
                count++;
            }
            file.close();
        }
        return count;
    }

public:
    Bank(string fname = "accounts.txt") {
        filename = fname;
    }

    // ---- Create New Account ----
    void createAccount() {
        BankAccount accounts[100];
        int count = loadFromFile(accounts, 100);

        int accNo;
        string name;
        double initialDeposit;

        cout << "\n========== CREATE ACCOUNT ==========\n";
        cout << "Enter Account Number : ";
        cin >> accNo;

        // Check if account already exists
        for (int i = 0; i < count; i++) {
            if (accounts[i].getAccountNumber() == accNo) {
                cout << "[ERROR] Account number already exists!\n";
                return;
            }
        }

        cin.ignore();
        cout << "Enter Customer Name  : ";
        getline(cin, name);
        cout << "Enter Initial Deposit: Rs. ";
        cin >> initialDeposit;

        if (initialDeposit < 0) {
            cout << "[ERROR] Initial deposit cannot be negative!\n";
            return;
        }

        BankAccount newAcc(accNo, name, initialDeposit);
        saveToFile(newAcc);

        cout << "\n[SUCCESS] Account created successfully!\n";
        cout << "Account No: " << accNo << " | Name: " << name << "\n";
    }

    // ---- Deposit Money ----
    void depositMoney() {
        BankAccount accounts[100];
        int count = loadFromFile(accounts, 100);

        int accNo;
        double amount;

        cout << "\n========== DEPOSIT ==========\n";
        cout << "Enter Account Number : ";
        cin >> accNo;

        for (int i = 0; i < count; i++) {
            if (accounts[i].getAccountNumber() == accNo) {
                cout << "Enter Deposit Amount : Rs. ";
                cin >> amount;
                accounts[i].deposit(amount);
                rewriteFile(accounts, count);
                return;
            }
        }
        cout << "[ERROR] Account not found!\n";
    }

    // ---- Withdraw Money ----
    void withdrawMoney() {
        BankAccount accounts[100];
        int count = loadFromFile(accounts, 100);

        int accNo;
        double amount;

        cout << "\n========== WITHDRAWAL ==========\n";
        cout << "Enter Account Number : ";
        cin >> accNo;

        for (int i = 0; i < count; i++) {
            if (accounts[i].getAccountNumber() == accNo) {
                cout << "Enter Withdrawal Amount: Rs. ";
                cin >> amount;
                if (accounts[i].withdraw(amount)) {
                    rewriteFile(accounts, count);
                }
                return;
            }
        }
        cout << "[ERROR] Account not found!\n";
    }

    // ---- Check Balance ----
    void checkBalance() {
        BankAccount accounts[100];
        int count = loadFromFile(accounts, 100);

        int accNo;
        cout << "\n========== BALANCE CHECK ==========\n";
        cout << "Enter Account Number : ";
        cin >> accNo;

        for (int i = 0; i < count; i++) {
            if (accounts[i].getAccountNumber() == accNo) {
                accounts[i].checkBalance();
                return;
            }
        }
        cout << "[ERROR] Account not found!\n";
    }

    // ---- Display All Accounts ----
    void displayAllAccounts() {
        BankAccount accounts[100];
        int count = loadFromFile(accounts, 100);

        cout << "\n========== ALL ACCOUNTS ==========\n";
        if (count == 0) {
            cout << "No accounts found!\n";
            return;
        }
        cout << left << setw(12) << "Acc. No"
             << setw(20) << "Name"
             << "Balance\n";
        cout << string(45, '-') << "\n";
        for (int i = 0; i < count; i++) {
            accounts[i].displayAccount();
        }
        cout << string(45, '-') << "\n";
        cout << "Total Accounts: " << count << "\n";
    }
};

// ============================================================
// MAIN MENU
// ============================================================
int main() {
    Bank bank("accounts.txt");
    int choice;

    cout << "\n";
    cout << "  ╔══════════════════════════════════╗\n";
    cout << "  ║   WELCOME TO C++ BANK SYSTEM     ║\n";
    cout << "  ╚══════════════════════════════════╝\n";

    do {
        cout << "\n========== MAIN MENU ==========\n";
        cout << " 1. Create New Account\n";
        cout << " 2. Deposit Money\n";
        cout << " 3. Withdraw Money\n";
        cout << " 4. Check Balance\n";
        cout << " 5. Display All Accounts\n";
        cout << " 0. Exit\n";
        cout << "================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bank.createAccount();       break;
            case 2: bank.depositMoney();        break;
            case 3: bank.withdrawMoney();       break;
            case 4: bank.checkBalance();        break;
            case 5: bank.displayAllAccounts();  break;
            case 0:
                cout << "\nThank you for using C++ Bank System. Goodbye!\n\n";
                break;
            default:
                cout << "\n[ERROR] Invalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}