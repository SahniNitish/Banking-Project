# Banking Simulation System

## Project Overview
A console-based banking simulation system implemented in C++ that provides secure account management, financial transactions, and data persistence.

**Created by:** Nitish Sahni

## Features

### Core Functionalities
- **Account Management**
  - Create new user accounts with secure password storage
  - Login/logout functionality with password hashing
  - Account information display

- **Financial Transactions**
  - Deposit funds into accounts
  - Withdraw funds with balance validation
  - Transfer money between accounts
  - Complete transaction history tracking

- **Security Features**
  - Password hashing for secure authentication
  - Input validation and error handling
  - Secure data storage

- **Data Persistence**
  - File-based storage for accounts and transactions
  - Automatic data loading and saving
  - Data integrity protection

## Project Structure
```
C++Project/
├── Account.h          # Account class declaration
├── Account.cpp        # Account class implementation
├── Transaction.h      # Transaction class declaration
├── Transaction.cpp    # Transaction class implementation
├── Bank.h             # Bank management class declaration
├── Bank.cpp           # Bank management class implementation
├── BankingSystem.h    # Main system interface declaration
├── BankingSystem.cpp  # Main system interface implementation
├── main.cpp           # Application entry point
├── Makefile           # Build configuration
└── README.md          # Project documentation
```

## Compilation and Execution

### Using Makefile (Recommended)
```bash
# Build the project
make

# Build and run
make run

# Build with debug symbols
make debug

# Clean build files
make clean

# Show help
make help
```

### Manual Compilation
```bash
g++ -std=c++17 -Wall -Wextra -pedantic -O2 *.cpp -o banking_system
./banking_system
```

## Usage Guide

### Main Menu
1. **Create Account** - Register a new bank account
2. **Login** - Access existing account
3. **Exit** - Close the application

### Banking Menu (After Login)
1. **View Account Information** - Display account details and balance
2. **Deposit Money** - Add funds to your account
3. **Withdraw Money** - Remove funds from your account
4. **Transfer Money** - Send funds to another account
5. **View Transaction History** - See all past transactions
6. **Logout** - Return to main menu

## Technical Implementation

### Classes
- **Account**: Manages individual bank accounts with secure authentication
- **Transaction**: Handles transaction records and history
- **Bank**: Manages multiple accounts and data persistence
- **BankingSystem**: Provides user interface and system coordination

### Security Features
- Password hashing using C++ standard hash functions
- Input validation for all user inputs
- Balance verification for withdrawals and transfers
- Secure data serialization

### Data Storage
- Account data stored in `bank_data.txt`
- Automatic backup and recovery
- Transaction history preserved across sessions

## Requirements
- C++17 compatible compiler (GCC 7+ recommended)
- Standard C++ libraries
- POSIX-compatible system (Linux/macOS) or Windows with appropriate compiler

## Example Usage
1. Run the application: `make run`
2. Create a new account with your name and password
3. Note down the generated account number
4. Login using your account number and password
5. Perform banking operations as needed
6. Logout when finished

## Error Handling
- Invalid input validation
- Insufficient funds protection
- File I/O error handling
- Password security enforcement

## Future Enhancements
- SQLite database integration
- Enhanced encryption
- Multi-currency support
- Account statements generation
- Administrative features

## License
This project is created for educational purposes as part of a C++ programming course.# Banking-Project
