#ifndef BANKING_SYSTEM_H
#define BANKING_SYSTEM_H

#include "Bank.h"

class BankingSystem {
private:
    Bank bank;
    Account* currentUser;
    bool isRunning;
    
    void displayMainMenu();
    void displayUserMenu();
    void handleCreateAccount();
    void handleLogin();
    void handleDeposit();
    void handleWithdraw();
    void handleTransfer();
    void handleAccountInfo();
    void handleTransactionHistory();
    void handleLogout();
    
    double getValidAmount();
    std::string getValidInput(const std::string& prompt);
    void clearScreen();
    void pause();
    
public:
    BankingSystem();
    void run();
};

#endif