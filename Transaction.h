#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

enum class TransactionType {
    DEPOSIT,
    WITHDRAWAL,
    TRANSFER_OUT,
    TRANSFER_IN
};

class Transaction {
private:
    std::string transactionId;
    TransactionType type;
    double amount;
    std::time_t timestamp;
    std::string description;
    std::string fromAccount;
    std::string toAccount;
    
public:
    Transaction();
    Transaction(TransactionType t, double amt, const std::string& desc, 
                const std::string& from = "", const std::string& to = "");
    
    std::string getTransactionId() const { return transactionId; }
    TransactionType getType() const { return type; }
    double getAmount() const { return amount; }
    std::time_t getTimestamp() const { return timestamp; }
    std::string getDescription() const { return description; }
    std::string getFromAccount() const { return fromAccount; }
    std::string getToAccount() const { return toAccount; }
    
    std::string typeToString() const;
    std::string timestampToString() const;
    void display() const;
    
    std::string serialize() const;
    static Transaction deserialize(const std::string& data);
    
private:
    std::string generateId();
};

#endif