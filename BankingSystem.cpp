#include "BankingSystem.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <stdexcept>

BankingSystem::BankingSystem() : currentUser(nullptr), isRunning(true) {}

void BankingSystem::run() {
    std::cout << "=== Welcome to Banking Simulation System ===" << std::endl;
    std::cout << "Created by: Nitish Sahni" << std::endl;
    std::cout << "===========================================" << std::endl;
    
    while (isRunning) {
        if (currentUser == nullptr) {
            displayMainMenu();
        } else {
            displayUserMenu();
        }
    }
    
    std::cout << "Thank you for using Banking Simulation System!" << std::endl;
}

void BankingSystem::displayMainMenu() {
    std::cout << "\n=== Main Menu ===" << std::endl;
    std::cout << "1. Create Account" << std::endl;
    std::cout << "2. Login" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Enter your choice: ";
    
    int choice;
    if (!(std::cin >> choice)) {
        std::cout << "Invalid input. Please enter a number." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    switch (choice) {
        case 1:
            handleCreateAccount();
            break;
        case 2:
            handleLogin();
            break;
        case 3:
            isRunning = false;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
    }
}

void BankingSystem::displayUserMenu() {
    std::cout << "\n=== Banking Menu ===" << std::endl;
    std::cout << "Welcome, " << currentUser->getAccountHolder() << "!" << std::endl;
    std::cout << "1. View Account Information" << std::endl;
    std::cout << "2. Deposit Money" << std::endl;
    std::cout << "3. Withdraw Money" << std::endl;
    std::cout << "4. Transfer Money" << std::endl;
    std::cout << "5. View Transaction History" << std::endl;
    std::cout << "6. Logout" << std::endl;
    std::cout << "Enter your choice: ";
    
    int choice;
    if (!(std::cin >> choice)) {
        std::cout << "Invalid input. Please enter a number." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    switch (choice) {
        case 1:
            handleAccountInfo();
            break;
        case 2:
            handleDeposit();
            break;
        case 3:
            handleWithdraw();
            break;
        case 4:
            handleTransfer();
            break;
        case 5:
            handleTransactionHistory();
            break;
        case 6:
            handleLogout();
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
    }
}

void BankingSystem::handleCreateAccount() {
    std::cout << "\n=== Create New Account ===" << std::endl;
    
    std::string accountHolder = getValidInput("Enter account holder name: ");
    std::string password = getValidInput("Enter password (min 4 characters): ");
    
    std::cout << "Enter initial deposit amount (or 0 for no deposit): $";
    double initialDeposit = getValidAmount();
    
    if (bank.createAccount(accountHolder, password, initialDeposit)) {
        std::cout << "Please remember your account number for future logins." << std::endl;
        pause();
    } else {
        std::cout << "Failed to create account. Please try again." << std::endl;
        pause();
    }
}

void BankingSystem::handleLogin() {
    std::cout << "\n=== Login ===" << std::endl;
    
    std::string accountNumber = getValidInput("Enter account number: ");
    std::string password = getValidInput("Enter password: ");
    
    currentUser = bank.login(accountNumber, password);
    
    if (currentUser) {
        std::cout << "Login successful! Welcome back, " << currentUser->getAccountHolder() << "!" << std::endl;
        pause();
    } else {
        std::cout << "Invalid account number or password. Please try again." << std::endl;
        pause();
    }
}

void BankingSystem::handleDeposit() {
    std::cout << "\n=== Deposit Money ===" << std::endl;
    std::cout << "Current Balance: $" << std::fixed << std::setprecision(2) << currentUser->getBalance() << std::endl;
    
    std::cout << "Enter deposit amount: $";
    double amount = getValidAmount();
    
    try {
        currentUser->deposit(amount);
        bank.saveData();
        std::cout << "Deposit successful!" << std::endl;
        std::cout << "New Balance: $" << std::fixed << std::setprecision(2) << currentUser->getBalance() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    pause();
}

void BankingSystem::handleWithdraw() {
    std::cout << "\n=== Withdraw Money ===" << std::endl;
    std::cout << "Current Balance: $" << std::fixed << std::setprecision(2) << currentUser->getBalance() << std::endl;
    
    std::cout << "Enter withdrawal amount: $";
    double amount = getValidAmount();
    
    try {
        if (currentUser->withdraw(amount)) {
            bank.saveData();
            std::cout << "Withdrawal successful!" << std::endl;
            std::cout << "New Balance: $" << std::fixed << std::setprecision(2) << currentUser->getBalance() << std::endl;
        } else {
            std::cout << "Insufficient funds for this withdrawal." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    pause();
}

void BankingSystem::handleTransfer() {
    std::cout << "\n=== Transfer Money ===" << std::endl;
    std::cout << "Current Balance: $" << std::fixed << std::setprecision(2) << currentUser->getBalance() << std::endl;
    
    std::string toAccountNumber = getValidInput("Enter recipient account number: ");
    
    Account* toAccount = bank.findAccount(toAccountNumber);
    if (!toAccount) {
        std::cout << "Recipient account not found." << std::endl;
        pause();
        return;
    }
    
    if (toAccount->getAccountNumber() == currentUser->getAccountNumber()) {
        std::cout << "Cannot transfer to the same account." << std::endl;
        pause();
        return;
    }
    
    std::cout << "Recipient: " << toAccount->getAccountHolder() << std::endl;
    std::cout << "Enter transfer amount: $";
    double amount = getValidAmount();
    
    try {
        if (currentUser->transfer(*toAccount, amount)) {
            bank.saveData();
            std::cout << "Transfer successful!" << std::endl;
            std::cout << "New Balance: $" << std::fixed << std::setprecision(2) << currentUser->getBalance() << std::endl;
        } else {
            std::cout << "Insufficient funds for this transfer." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    pause();
}

void BankingSystem::handleAccountInfo() {
    currentUser->displayAccountInfo();
    pause();
}

void BankingSystem::handleTransactionHistory() {
    currentUser->displayTransactionHistory();
    pause();
}

void BankingSystem::handleLogout() {
    std::cout << "Logging out... Goodbye, " << currentUser->getAccountHolder() << "!" << std::endl;
    currentUser = nullptr;
    pause();
}

double BankingSystem::getValidAmount() {
    double amount;
    while (!(std::cin >> amount) || amount < 0) {
        std::cout << "Please enter a valid positive amount: $";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return amount;
}

std::string BankingSystem::getValidInput(const std::string& prompt) {
    std::string input;
    do {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (input.empty()) {
            std::cout << "Input cannot be empty. Please try again." << std::endl;
        }
    } while (input.empty());
    return input;
}

void BankingSystem::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void BankingSystem::pause() {
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}