#pragma once
#include <string>
#include <iostream>
#include <random>
#include <fstream>
using namespace std;

class Payment {
protected:
    float _amount;
    string _transactionId;
    bool _isSuccessful;

public:
    Payment(float amount) : _amount(amount), _isSuccessful(false) {}
    Payment(float amount, string transactionId, bool isSuccessful)
    {
        _amount = amount;
        _transactionId = transactionId;
        _isSuccessful = isSuccessful;
    }

    // Pure virtual function that must be implemented by derived classes
    virtual bool processPayment() = 0;

    // Getters
    float getAmount() const { return _amount; }

    string getTransactionId() const { return _transactionId; }

    bool isSuccessful() const { return _isSuccessful; }

    // Virtual method for payment details
    virtual void displayPaymentDetails() const {
        std::cout << "Transaction ID: " << _transactionId << std::endl;
        std::cout << "Amount: $" << _amount << std::endl;
        std::cout << "Status: " << (_isSuccessful ? "Successful" : "Failed") << std::endl;
    }
};