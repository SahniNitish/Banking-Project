#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include "Transaction.h"

class Account {
private:
    std::string accountNumber;
    std::string accountHolder;
    std::string hashedPassword;
    double balance;
    std::vector<Transaction> transactionHistory;
    
    std::string hashPassword(const std::string& password) const;
    
public:
    Account();
    Account(const std::string& accNum, const std::string& holder, const std::string& password, double initialBalance = 0.0);
    
    bool authenticate(const std::string& password) const;
    void deposit(double amount);
    bool withdraw(double amount);
    bool transfer(Account& toAccount, double amount);
    
    std::string getAccountNumber() const { return accountNumber; }
    std::string getAccountHolder() const { return accountHolder; }
    double getBalance() const { return balance; }
    std::vector<Transaction> getTransactionHistory() const { return transactionHistory; }
    
    void addTransaction(const Transaction& transaction);
    void displayAccountInfo() const;
    void displayTransactionHistory() const;
    
    std::string serialize() const;
    static Account deserialize(const std::string& data);
};

#endif