#include <iostream>
#include <string>
#include <vector>

using namespace std;

// --- Account Class ---
class Account {
private:
    string accountHolder;
    int pin;
    double balance;

public:
    // Constructor
    Account(string name, int p, double initialBalance) {
        accountHolder = name;
        pin = p;
        balance = initialBalance;
    }

    // Encapsulation: Getter for balance
    double getBalance() const {
        return balance;
    }

    // Verify PIN
    bool verifyPin(int inputPin) const {
        return pin == inputPin;
    }

    // Update PIN
    void changePin(int newPin) {
        pin = newPin;
    }

    // Deposit Logic
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Successfully deposited $" << amount << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    // Withdrawal Logic with Balance Check
    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Error: Insufficient funds. Current balance: $" << balance << endl;
            return false;
        } else if (amount <= 0) {
            cout << "Error: Invalid withdrawal amount." << endl;
            return false;
        } else {
            balance -= amount;
            cout << "Successfully withdrew $" << amount << endl;
            return true;
        }
    }
};

// --- ATM Controller Class ---
class ATM {
public:
    void showMenu(Account &userAccount) {
        int choice;
        do {
            cout << "\n--- ATM Main Menu ---" << endl;
            cout << "1. Check Balance" << endl;
            cout << "2. Deposit Money" << endl;
            cout << "3. Withdraw Money" << endl;
            cout << "4. Change PIN" << endl;
            cout << "5. Exit" << endl;
            cout << "Select an option: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Current Balance: $" << userAccount.getBalance() << endl;
                    break;
                case 2: {
                    double dAmount;
                    cout << "Enter deposit amount: ";
                    cin >> dAmount;
                    userAccount.deposit(dAmount);
                    break;
                }
                case 3: {
                    double wAmount;
                    cout << "Enter withdrawal amount: ";
                    cin >> wAmount;
                    userAccount.withdraw(wAmount);
                    break;
                }
                case 4: {
                    int oldPin, newPin;
                    cout << "Enter current PIN: ";
                    cin >> oldPin;
                    if (userAccount.verifyPin(oldPin)) {
                        cout << "Enter new 4-digit PIN: ";
                        cin >> newPin;
                        userAccount.changePin(newPin);
                        cout << "PIN changed successfully." << endl;
                    } else {
                        cout << "Incorrect PIN." << endl;
                    }
                    break;
                }
                case 5:
                    cout << "Thank you for using our ATM. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid option. Please try again." << endl;
            }
        } while (choice != 5);
    }
};

// --- Main Program ---
int main() {
    // Initialize a sample account
    Account myAccount("Marites", 1234, 1000.00);
    ATM myAtm;

    int enteredPin;
    cout << "Welcome, Marites!" << endl;
    cout << "Please enter your 4-digit PIN: ";
    cin >> enteredPin;

    if (myAccount.verifyPin(enteredPin)) {
        myAtm.showMenu(myAccount);
    } else {
        cout << "Invalid PIN. Access Terminated." << endl;
    }

    return 0;
}