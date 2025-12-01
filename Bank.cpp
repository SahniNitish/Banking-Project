#include "Bank.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <iomanip>

Bank::Bank(const std::string& filename) : dataFile(filename) {
    loadData();
}

bool Bank::createAccount(const std::string& accountHolder, const std::string& password, double initialDeposit) {
    if (accountHolder.empty() || password.empty()) {
        return false;
    }
    
    if (password.length() < 4) {
        std::cout << "Password must be at least 4 characters long." << std::endl;
        return false;
    }
    
    if (initialDeposit < 0) {
        std::cout << "Initial deposit cannot be negative." << std::endl;
        return false;
    }
    
    std::string accountNumber = generateAccountNumber();
    Account newAccount(accountNumber, accountHolder, password, initialDeposit);
    
    accounts.push_back(newAccount);
    accountIndex[accountNumber] = accounts.size() - 1;
    
    saveData();
    
    std::cout << "\nAccount created successfully!" << std::endl;
    std::cout << "Account Number: " << accountNumber << std::endl;
    std::cout << "Account Holder: " << accountHolder << std::endl;
    std::cout << "Initial Balance: $" << std::fixed << std::setprecision(2) << initialDeposit << std::endl;
    
    return true;
}

Account* Bank::login(const std::string& accountNumber, const std::string& password) {
    auto it = accountIndex.find(accountNumber);
    if (it == accountIndex.end()) {
        return nullptr;
    }
    
    Account& account = accounts[it->second];
    if (account.authenticate(password)) {
        return &account;
    }
    
    return nullptr;
}

Account* Bank::findAccount(const std::string& accountNumber) {
    auto it = accountIndex.find(accountNumber);
    if (it != accountIndex.end()) {
        return &accounts[it->second];
    }
    return nullptr;
}

std::string Bank::generateAccountNumber() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(10000000, 99999999);
    
    std::string accountNumber;
    do {
        accountNumber = std::to_string(dis(gen));
    } while (accountIndex.find(accountNumber) != accountIndex.end());
    
    return accountNumber;
}

bool Bank::saveData() {
    std::ofstream file(dataFile);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to save data to file." << std::endl;
        return false;
    }
    
    for (const auto& account : accounts) {
        file << account.serialize() << std::endl;
    }
    
    file.close();
    return true;
}

bool Bank::loadData() {
    std::ifstream file(dataFile);
    if (!file.is_open()) {
        return true;
    }
    
    accounts.clear();
    accountIndex.clear();
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            try {
                Account account = Account::deserialize(line);
                accounts.push_back(account);
                accountIndex[account.getAccountNumber()] = accounts.size() - 1;
            } catch (const std::exception& e) {
                std::cerr << "Error loading account data: " << e.what() << std::endl;
            }
        }
    }
    
    file.close();
    return true;
}

void Bank::displayAllAccounts() const {
    if (accounts.empty()) {
        std::cout << "No accounts found." << std::endl;
        return;
    }
    
    std::cout << "\n=== All Bank Accounts ===" << std::endl;
    std::cout << std::setw(12) << "Account #" << std::setw(20) << "Account Holder" 
              << std::setw(15) << "Balance" << std::endl;
    std::cout << std::string(47, '-') << std::endl;
    
    for (const auto& account : accounts) {
        std::cout << std::setw(12) << account.getAccountNumber()
                  << std::setw(20) << account.getAccountHolder()
                  << std::setw(14) << "$" << std::fixed << std::setprecision(2) 
                  << account.getBalance() << std::endl;
    }
}