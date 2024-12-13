#pragma once
#include "Payment.h"

class BankCard : public Payment {
protected:
    string _cardNumber;
    string _cardHolderName;
    string _expiryDate;
    string _cvv;

public:
    BankCard(float amount,
        string cardNumber,
        string cardHolderName,
        string expiryDate,
        string cvv)
        : Payment(amount),
        _cardNumber(cardNumber),
        _cardHolderName(cardHolderName),
        _expiryDate(expiryDate),
        _cvv(cvv) {
    }

    bool validateCard() const {
        // Basic validation
        if (_cardNumber.length() != 8) return false;
        if (_cvv.length() != 3) return false;
        if (_cardHolderName.empty()) return false;

        return true;
    }

    bool processPayment() override {
        if (!validateCard()) {
            _isSuccessful = false;
            return false;
        }

        // Generate random transaction ID
        random_device rd;
        uniform_int_distribution<int> dist(2000000, 2999999);
        _transactionId = to_string(dist(rd));

        // Simulate payment processing
        _isSuccessful = true;
        return true;
    }

    void displayPaymentDetails() const override {
        Payment::displayPaymentDetails();
        cout << "Card Number: ****" << _cardNumber.substr(_cardNumber.length() - 4) << endl;
        cout << "Card Holder: " << _cardHolderName << endl;
    }
};