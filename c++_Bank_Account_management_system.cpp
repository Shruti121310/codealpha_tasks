#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// ১. লেনদেনের তথ্য রাখার জন্য ক্লাস
class Transaction {
public:
    string type;
    double amount;
    Transaction(string t, double a) : type(t), amount(a) {}
    void display() {
        cout << left << setw(15) << type << ": " << amount << " Taka" << endl;
    }
};

// ২. অ্যাকাউন্ট ক্লাস যেখানে মেইন ব্যালেন্স থাকবে
class Account {
private:
    int accountNo;
    double balance; // এটিই আপনার মেইন ব্যালেন্স
    vector<Transaction> history;

public:
    Account(int no, double initialBalance) : accountNo(no), balance(initialBalance) {}

    // ডিপোজিট করলে মেইন ব্যালেন্সে যোগ হবে
    void deposit(double amount) {
        if (amount > 0) {
            balance = balance + amount; // মেইন ব্যালেন্স আপডেট
            history.push_back(Transaction("Deposit", amount));
            cout << "\n>>> Deposited: " << amount << " Taka";
            cout << "\n>>> New Total Balance: " << balance << " Taka" << endl;
        }
    }

    // উইথড্র করলে মেইন ব্যালেন্স থেকে বিয়োগ হবে
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance = balance - amount; // মেইন ব্যালেন্স থেকে রিমুভ
            history.push_back(Transaction("Withdrawal", amount));
            cout << "\n>>> Withdrawn: " << amount << " Taka";
            cout << "\n>>> Remaining Balance: " << balance << " Taka" << endl;
            return true;
        }
        cout << "\n[!] Error: Insufficient Balance! Current: " << balance << " Taka" << endl;
        return false;
    }

    double getBalance() { return balance; }
    int getAccNo() { return accountNo; }

    void showHistory() {
        cout << "\n--- Transaction History ---" << endl;
        if (history.empty()) cout << "No history yet." << endl;
        for (auto &t : history) t.display();
    }
};

// ৩. কাস্টমার ক্লাস
class Customer {
public:
    string name;
    Account* account;
    Customer(string n, int accNo, double initialBalance) {
        name = n;
        account = new Account(accNo, initialBalance);
    }
};

vector<Customer*> customers;

Customer* findCustomer(int accNo) {
    for (auto c : customers) {
        if (c->account->getAccNo() == accNo) return c;
    }
    return nullptr;
}

void fixInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    int choice;
    cout << fixed << setprecision(2);

    while (true) {
        cout << "\n========== SHRUTI'S BANK ==========";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Fund Transfer";
        cout << "\n5. View Balance & History";
        cout << "\n6. Exit";
        cout << "\nEnter choice (1-6): ";
        
        if (!(cin >> choice)) {
            fixInput();
            continue;
        }

        if (choice == 1) {
            string name; int accNo; double initialBalance;
            cout << "Enter Name: "; cin >> name;
            cout << "Enter Acc No: "; cin >> accNo;
            cout << "Initial Deposit: "; cin >> initialBalance;
            customers.push_back(new Customer(name, accNo, initialBalance));
            cout << "\nAccount Created! Main Balance: " << initialBalance << endl;
        } 
        else if (choice == 2) {
            int accNo; double amt;
            cout << "Enter Acc No: "; cin >> accNo;
            Customer* c = findCustomer(accNo);
            if (c) {
                cout << "Enter Amount to Deposit: "; 
                if(cin >> amt) {
                    c->account->deposit(amt); // এখানে মেইন ব্যালেন্সে যোগ হচ্ছে
                } else { fixInput(); }
            } else cout << "Account not found!\n";
        }
        else if (choice == 3) {
            int accNo; double amt;
            cout << "Enter Acc No: "; cin >> accNo;
            Customer* c = findCustomer(accNo);
            if (c) {
                cout << "Enter Amount to Withdraw: "; 
                if(cin >> amt) {
                    c->account->withdraw(amt); // এখানে মেইন ব্যালেন্স থেকে বিয়োগ হচ্ছে
                } else { fixInput(); }
            } else cout << "Account not found!\n";
        }
        else if (choice == 4) {
            int fromAcc, toAcc; double amt;
            cout << "From Acc No: "; cin >> fromAcc;
            cout << "To Acc No: "; cin >> toAcc;
            Customer* sender = findCustomer(fromAcc);
            Customer* receiver = findCustomer(toAcc);

            if (sender && receiver) {
                cout << "Transfer Amount: "; cin >> amt;
                if (sender->account->withdraw(amt)) {
                    receiver->account->deposit(amt);
                    cout << "Transfer Success!\n";
                }
            } else cout << "Error in Account Numbers!\n";
        }
        else if (choice == 5) {
            int accNo;
            cout << "Enter Acc No: "; cin >> accNo;
            Customer* c = findCustomer(accNo);
            if (c) {
                cout << "\nName: " << c->name;
                cout << "\nAccount No: " << c->account->getAccNo();
                cout << "\nMAIN BALANCE: " << c->account->getBalance() << " Taka";
                c->account->showHistory();
            } else cout << "Account not found!\n";
        }
        else if (choice == 6) break;
        
        fixInput(); 
    }
    return 0;
}