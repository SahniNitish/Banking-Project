#ifndef BANK_H
#define BANK_H

#include <vector>
#include <string>
#include <unordered_map>
#include "Account.h"

class Bank {
private:
    std::vector<Account> accounts;
    std::unordered_map<std::string, size_t> accountIndex;
    std::string dataFile;
    
public:
    Bank(const std::string& filename = "bank_data.txt");
    
    bool createAccount(const std::string& accountHolder, const std::string& password, double initialDeposit = 0.0);
    Account* login(const std::string& accountNumber, const std::string& password);
    Account* findAccount(const std::string& accountNumber);
    
    bool saveData();
    bool loadData();
    
    void displayAllAccounts() const;
    std::string generateAccountNumber();
    
    size_t getAccountCount() const { return accounts.size(); }
};

#endif