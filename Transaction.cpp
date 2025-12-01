#include "Transaction.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <random>

Transaction::Transaction() : type(TransactionType::DEPOSIT), amount(0.0), timestamp(std::time(nullptr)) {
    transactionId = generateId();
}

Transaction::Transaction(TransactionType t, double amt, const std::string& desc, 
                        const std::string& from, const std::string& to)
    : type(t), amount(amt), description(desc), fromAccount(from), toAccount(to) {
    timestamp = std::time(nullptr);
    transactionId = generateId();
}

std::string Transaction::generateId() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(100000, 999999);
    
    return "TXN" + std::to_string(dis(gen));
}

std::string Transaction::typeToString() const {
    switch (type) {
        case TransactionType::DEPOSIT:
            return "DEPOSIT";
        case TransactionType::WITHDRAWAL:
            return "WITHDRAWAL";
        case TransactionType::TRANSFER_OUT:
            return "TRANSFER OUT";
        case TransactionType::TRANSFER_IN:
            return "TRANSFER IN";
        default:
            return "UNKNOWN";
    }
}

std::string Transaction::timestampToString() const {
    char buffer[100];
    std::tm* timeinfo = std::localtime(&timestamp);
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return std::string(buffer);
}

void Transaction::display() const {
    std::cout << "Transaction ID: " << transactionId << std::endl;
    std::cout << "Type: " << typeToString() << std::endl;
    std::cout << "Amount: $" << std::fixed << std::setprecision(2) << amount << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Date/Time: " << timestampToString() << std::endl;
    
    if (!fromAccount.empty()) {
        std::cout << "From Account: " << fromAccount << std::endl;
    }
    if (!toAccount.empty()) {
        std::cout << "To Account: " << toAccount << std::endl;
    }
}

std::string Transaction::serialize() const {
    std::stringstream ss;
    ss << transactionId << "," << static_cast<int>(type) << "," 
       << std::fixed << std::setprecision(2) << amount << "," 
       << timestamp << "," << description << "," 
       << fromAccount << "," << toAccount;
    return ss.str();
}

Transaction Transaction::deserialize(const std::string& data) {
    std::stringstream ss(data);
    std::string token;
    std::vector<std::string> tokens;
    
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    
    if (tokens.size() < 7) {
        throw std::invalid_argument("Invalid transaction data format");
    }
    
    Transaction transaction;
    transaction.transactionId = tokens[0];
    transaction.type = static_cast<TransactionType>(std::stoi(tokens[1]));
    transaction.amount = std::stod(tokens[2]);
    transaction.timestamp = std::stoll(tokens[3]);
    transaction.description = tokens[4];
    transaction.fromAccount = tokens[5];
    transaction.toAccount = tokens[6];
    
    return transaction;
}