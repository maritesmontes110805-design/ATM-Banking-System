#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Class representing a Bank Account
class Account {
private:
    int id;
    string name;
    string pin;
    double balance;

public:
    Account(int id, string name, string pin, double balance) 
        : id(id), name(name), pin(pin), balance(balance) {}

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    string getPin() const { return pin; }
    double getBalance() const { return balance; }

    // Setters / Operations
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Successfully deposited $" << amount << endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Error: Insufficient funds. Current balance: $" << balance << endl;
            return false;
        } else if (amount <= 0) {
            cout << "Error: Invalid amount." << endl;
            return false;
        } else {
            balance -= amount;
            cout << "Successfully withdrew $" << amount << endl;
            return true;
        }
    }

    void setPin(string newPin) {
        pin = newPin;
        cout << "PIN updated successfully." << endl;
    }
};

// --- Helper Functions ---

// Saves the current state of all 10 accounts back to the file
void updateDatabase(const vector<Account>& accounts) {
    ofstream outFile("accounts.txt");
    if (outFile.is_open()) {
        for (const auto& acc : accounts) {
            outFile << acc.getId() << " " << acc.getName() << " " 
                    << acc.getPin() << " " << fixed << setprecision(2) 
                    << acc.getBalance() << endl;
        }
        outFile.close();
    }
}

int main() {
    vector<Account> accounts;
    ifstream inFile("accounts.txt");

    // Load the 10 accounts from the file
    int id; string name, pin; double bal;
    while (inFile >> id >> name >> pin >> bal) {
        accounts.push_back(Account(id, name, pin, bal));
    }
    inFile.close();

    if (accounts.empty()) {
        cout << "Error: Could not load account data. Please check accounts.txt." << endl;
        return 1;
    }

    // Login System
    string inputName, inputPin;
    Account* currentUser = nullptr;

    cout << "==============================" << endl;
    cout << "   WELCOME TO THE TITAN ATM   " << endl;
    cout << "==============================" << endl;
    
    cout << "Enter Account Name: "; cin >> inputName;
    cout << "Enter PIN: "; cin >> inputPin;

    for (auto& acc : accounts) {
        if (acc.getName() == inputName && acc.getPin() == inputPin) {
            currentUser = &acc;
            break;
        }
    }

    if (currentUser == nullptr) {
        cout << "Login Failed: Invalid credentials." << endl;
        return 0;
    }

    // Transaction Menu
    int choice;
    do {
        cout << "\n--- Hello, " << currentUser->getName() << "! ---" << endl;
        cout << "1. Check Balance" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Change PIN" << endl;
        cout << "5. Exit" << endl;
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Your Balance: $" << fixed << setprecision(2) << currentUser->getBalance() << endl;
                break;
            case 2: {
                double dAmt;
                cout << "Enter deposit amount: "; cin >> dAmt;
                currentUser->deposit(dAmt);
                updateDatabase(accounts);
                break;
            }
            case 3: {
                double wAmt;
                cout << "Enter withdrawal amount: "; cin >> wAmt;
                if (currentUser->withdraw(wAmt)) {
                    updateDatabase(accounts);
                }
                break;
            }
            case 4: {
                string newPin;
                cout << "Enter new 4-digit PIN: "; cin >> newPin;
                currentUser->setPin(newPin);
                updateDatabase(accounts);
                break;
            }
            case 5:
                cout << "Thank you for using our ATM. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 5);

    return 0;
}