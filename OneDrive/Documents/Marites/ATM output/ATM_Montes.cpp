#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Account {
private:
    int id;
    string name;
    string pin;
    double balance;

public:
    Account(int id, string name, string pin, double balance) 
        : id(id), name(name), pin(pin), balance(balance) {}

    string getName() const { return name; }
    string getPin() const { return pin; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Successfully deposited $" << amount << endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds! Current balance: $" << balance << endl;
            return false;
        } else if (amount <= 0) {
            cout << "Invalid amount." << endl;
            return false;
        }
        balance -= amount;
        cout << "Successfully withdrew $" << amount << endl;
        return true;
    }

    void changePin(string newPin) {
        pin = newPin;
        cout << "PIN updated successfully!" << endl;
    }

    string toString() const {
        return to_string(id) + " " + name + " " + pin + " " + to_string(balance);
    }
};

class ATM {
private:
    vector<Account> accounts;
    int currentUserIndex = -1;

    void loadAccounts() {
        ifstream file("accounts.txt");
        int id; string name, pin; double balance;
        while (file >> id >> name >> pin >> balance) {
            accounts.emplace_back(id, name, pin, balance);
        }
        file.close();
    }

    void saveAccounts() {
        ofstream file("accounts.txt");
        for (const auto& acc : accounts) {
            file << acc.toString() << endl;
        }
        file.close();
    }

public:
    ATM() { loadAccounts(); }

    bool login() {
        string inputName, inputPin;
        cout << "--- Welcome to the ATM ---\nEnter Account Name: ";
        cin >> inputName;
        cout << "Enter PIN: ";
        cin >> inputPin;

        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].getName() == inputName && accounts[i].getPin() == inputPin) {
                currentUserIndex = i;
                cout << "Login successful! Welcome, " << inputName << ".\n";
                return true;
            }
        }
        cout << "Invalid Name or PIN.\n";
        return false;
    }

    void showMenu() {
        int choice;
        Account& user = accounts[currentUserIndex];
        
        do {
            cout << "\n1. Check Balance\n2. Deposit\n3. Withdraw\n4. Change PIN\n5. Logout\nChoice: ";
            cin >> choice;

            switch (choice) {
                case 1: cout << "Balance: $" << user.getBalance() << endl; break;
                case 2: {
                    double amt; cout << "Amount: "; cin >> amt;
                    user.deposit(amt);
                    saveAccounts();
                    break;
                }
                case 3: {
                    double amt; cout << "Amount: "; cin >> amt;
                    if(user.withdraw(amt)) saveAccounts();
                    break;
                }
                case 4: {
                    string newPin; cout << "New PIN: "; cin >> newPin;
                    user.changePin(newPin);
                    saveAccounts();
                    break;
                }
            }
        } while (choice != 5);
    }
};

int main() {
    ATM myAtm;
    if (myAtm.login()) {
        myAtm.showMenu();
    }
    return 0;
}