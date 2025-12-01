#include "BankingSystem.h"
#include <iostream>

int main() {
    try {
        BankingSystem bankingSystem;
        bankingSystem.run();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}