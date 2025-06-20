#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Customer {
public:
    int customerID;
    string name;
    string contact;

    Customer(int id, string n, string c) {
        customerID = id;
        name = n;
        contact = c;
    }

    void displayInfo() {
        cout << "Customer ID: " << customerID << "\nName: " << name << "\nContact: " << contact << endl;
    }
};

class Account {
public:
    int accountNumber;
    double balance;
    int customerID;
    vector<string> transactionHistory;

    Account(int accNo, int custID) {
        accountNumber = accNo;
        customerID = custID;
        balance = 0.0;
    }

    void deposit(double amount) {
        balance += amount;
        transactionHistory.push_back("Deposited: $" + to_string(amount));
        cout << "Deposit successful!\n";
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            transactionHistory.push_back("Withdrawn: $" + to_string(amount));
            cout << "Withdrawal successful!\n";
        }
        else {
            cout << "Insufficient balance!\n";
        }
    }

    void transfer(Account& receiver, double amount) {
        if (amount <= balance) {
            balance -= amount;
            receiver.balance += amount;
            transactionHistory.push_back("Transferred: $" + to_string(amount) + " to Account " + to_string(receiver.accountNumber));
            receiver.transactionHistory.push_back("Received: $" + to_string(amount) + " from Account " + to_string(accountNumber));
            cout << "Transfer successful!\n";
        }
        else {
            cout << "Insufficient balance!\n";
        }
    }

    void displayBalance() {
        cout << "Current Balance: $" << balance << endl;
    }

    void showTransactions() {
        cout << "Transaction History for Account " << accountNumber << ":\n";
        for (string entry : transactionHistory) {
            cout << "- " << entry << endl;
        }
    }
};
vector<Customer> customers;
vector<Account> accounts;
Customer* findCustomerByID(int id) {
    for (auto& cust : customers) {
        if (cust.customerID == id)
            return &cust;
    }
    return nullptr;
}

Account* findAccountByNumber(int accNo) {
    for (auto& acc : accounts) {
        if (acc.accountNumber == accNo)
            return &acc;
    }
    return nullptr;
}
void createCustomer() {
    int id;
    string name, contact;
    cout << "Enter Customer ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Contact: ";
    getline(cin, contact);

    if (findCustomerByID(id) != nullptr) {
        cout << "Customer ID already exists.\n";
        return;
    }

    customers.push_back(Customer(id, name, contact));
    cout << "Customer created successfully.\n";
}
void createAccount() {
    int accNo, custID;
    cout << "Enter Account Number: ";
    cin >> accNo;
    cout << "Enter Customer ID: ";
    cin >> custID;

    if (findCustomerByID(custID) == nullptr) {
        cout << "Customer not found.\n";
        return;
    }

    if (findAccountByNumber(accNo) != nullptr) {
        cout << "Account already exists.\n";
        return;
    }

    accounts.push_back(Account(accNo, custID));
    cout << "Account created successfully.\n";
}
void showMenu() {
    cout << "\n----- Banking System Menu -----\n";
    cout << "1. Create Customer\n";
    cout << "2. Create Account\n";
    cout << "3. Deposit\n";
    cout << "4. Withdraw\n";
    cout << "5. Transfer Funds\n";
    cout << "6. Show Transaction History\n";
    cout << "7. Show Account Balance\n";
    cout << "8. Exit\n";
    cout << "-------------------------------\n";
}

int main() {
    int choice;

    do {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            createCustomer();
        }
        else if (choice == 2) {
            createAccount();
        }
        else if (choice == 3) {
            int accNo;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Amount to Deposit: ";
            cin >> amount;

            Account* acc = findAccountByNumber(accNo);
            if (acc != nullptr) {
                acc->deposit(amount);
            }
            else {
                cout << "Account not found!\n";
            }
        }
        else if (choice == 4) {
            int accNo;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Amount to Withdraw: ";
            cin >> amount;

            Account* acc = findAccountByNumber(accNo);
            if (acc != nullptr) {
                acc->withdraw(amount);
            }
            else {
                cout << "Account not found!\n";
            }
        }
        else if (choice == 5) {
            int fromAcc, toAcc;
            double amount;
            cout << "Enter Sender Account Number: ";
            cin >> fromAcc;
            cout << "Enter Receiver Account Number: ";
            cin >> toAcc;
            cout << "Enter Amount to Transfer: ";
            cin >> amount;

            Account* sender = findAccountByNumber(fromAcc);
            Account* receiver = findAccountByNumber(toAcc);

            if (sender && receiver) {
                sender->transfer(*receiver, amount);
            }
            else {
                cout << "One or both accounts not found!\n";
            }
        }
        else if (choice == 6) {
            int accNo;
            cout << "Enter Account Number: ";
            cin >> accNo;

            Account* acc = findAccountByNumber(accNo);
            if (acc != nullptr) {
                acc->showTransactions();
            }
            else {
                cout << "Account not found!\n";
            }
        }
        else if (choice == 7) {
            int accNo;
            cout << "Enter Account Number: ";
            cin >> accNo;

            Account* acc = findAccountByNumber(accNo);
            if (acc != nullptr) {
                acc->displayBalance();
            }
            else {
                cout << "Account not found!\n";
            }
        }
        else if (choice == 8) {
            cout << "Exiting program.\n";
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 8);

    return 0;
}
