#include "Account.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <functional>
#include <algorithm>

Account::Account() : accountNumber(""), accountHolder(""), hashedPassword(""), balance(0.0) {}

Account::Account(const std::string& accNum, const std::string& holder, const std::string& password, double initialBalance)
    : accountNumber(accNum), accountHolder(holder), balance(initialBalance) {
    hashedPassword = hashPassword(password);
    if (initialBalance > 0) {
        addTransaction(Transaction(TransactionType::DEPOSIT, initialBalance, "Initial deposit"));
    }
}

std::string Account::hashPassword(const std::string& password) const {
    std::hash<std::string> hasher;
    size_t hashValue = hasher(password + accountNumber);
    std::stringstream ss;
    ss << std::hex << hashValue;
    return ss.str();
}

bool Account::authenticate(const std::string& password) const {
    return hashedPassword == hashPassword(password);
}

void Account::deposit(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Deposit amount must be positive");
    }
    balance += amount;
    addTransaction(Transaction(TransactionType::DEPOSIT, amount, "Cash deposit"));
}

bool Account::withdraw(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Withdrawal amount must be positive");
    }
    if (amount > balance) {
        return false;
    }
    balance -= amount;
    addTransaction(Transaction(TransactionType::WITHDRAWAL, amount, "Cash withdrawal"));
    return true;
}

bool Account::transfer(Account& toAccount, double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Transfer amount must be positive");
    }
    if (amount > balance) {
        return false;
    }
    
    balance -= amount;
    toAccount.balance += amount;
    
    std::string desc = "Transfer to " + toAccount.accountNumber;
    addTransaction(Transaction(TransactionType::TRANSFER_OUT, amount, desc, accountNumber, toAccount.accountNumber));
    
    desc = "Transfer from " + accountNumber;
    toAccount.addTransaction(Transaction(TransactionType::TRANSFER_IN, amount, desc, accountNumber, toAccount.accountNumber));
    
    return true;
}

void Account::addTransaction(const Transaction& transaction) {
    transactionHistory.push_back(transaction);
}

void Account::displayAccountInfo() const {
    std::cout << "\n=== Account Information ===" << std::endl;
    std::cout << "Account Number: " << accountNumber << std::endl;
    std::cout << "Account Holder: " << accountHolder << std::endl;
    std::cout << "Current Balance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
    std::cout << "Total Transactions: " << transactionHistory.size() << std::endl;
}

void Account::displayTransactionHistory() const {
    std::cout << "\n=== Transaction History ===" << std::endl;
    if (transactionHistory.empty()) {
        std::cout << "No transactions found." << std::endl;
        return;
    }
    
    for (const auto& transaction : transactionHistory) {
        transaction.display();
        std::cout << "------------------------" << std::endl;
    }
}

std::string Account::serialize() const {
    std::stringstream ss;
    ss << accountNumber << "|" << accountHolder << "|" << hashedPassword << "|" 
       << std::fixed << std::setprecision(2) << balance << "|";
    
    for (size_t i = 0; i < transactionHistory.size(); ++i) {
        ss << transactionHistory[i].serialize();
        if (i < transactionHistory.size() - 1) {
            ss << ";";
        }
    }
    
    return ss.str();
}

Account Account::deserialize(const std::string& data) {
    std::stringstream ss(data);
    std::string token;
    std::vector<std::string> tokens;
    
    while (std::getline(ss, token, '|')) {
        tokens.push_back(token);
    }
    
    if (tokens.size() < 4) {
        throw std::invalid_argument("Invalid account data format");
    }
    
    Account account;
    account.accountNumber = tokens[0];
    account.accountHolder = tokens[1];
    account.hashedPassword = tokens[2];
    account.balance = std::stod(tokens[3]);
    
    if (tokens.size() > 4 && !tokens[4].empty()) {
        std::stringstream transactionStream(tokens[4]);
        std::string transactionData;
        
        while (std::getline(transactionStream, transactionData, ';')) {
            if (!transactionData.empty()) {
                account.transactionHistory.push_back(Transaction::deserialize(transactionData));
            }
        }
    }
    
    return account;
}