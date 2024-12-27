#pragma once
#include "Payment.h"

class Tadawul : public Payment {
private:
    string _cardNumber;
    string _expiryDate;
    float _creditLimit;


public:
    Tadawul(float amount,
        string cardNumber,
        string expiryDate,
        float creditLimit)
        : Payment(amount),
        _creditLimit(creditLimit), _cardNumber(cardNumber), _expiryDate(expiryDate){
    }



    bool validateCard() const {
        // Basic validation
        if (_cardNumber.length() != 8) return false;
        return true;
    }

    bool processPayment() override {
        if (!validateCard()) {
            _isSuccessful = false;
            return false;
        }

        // Check if payment amount is within credit limit
        if (_amount > _creditLimit) {
            _isSuccessful = false;
            return false;
        }

        // Generate transaction ID
        random_device rd;
        uniform_int_distribution<int> dist(1000000, 1999999);
        _transactionId = to_string(dist(rd));

        _isSuccessful = true;
        return true;
    }

    void displayPaymentDetails() const override {
        Payment::displayPaymentDetails();
        cout << "Credit Limit: $" << _creditLimit << endl;
    }
};