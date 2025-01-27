// The Strategy Design Pattern
#include <iostream>
#include <memory>

// A flexible payment strategy containing many options
class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual std::string withdraw(double amount) = 0;
};

// This class behaves like the context - can choose any strategy
class Customer {
// private members
    std::unique_ptr<PaymentStrategy> strategy_;
public:
    explicit Customer(std::unique_ptr<PaymentStrategy> &&strategy) : strategy_(std::move(strategy)) // use rvalue ref constructor to be flexible
    {
    }
    void pay(double amount) {
        std::cout << "Paying " << amount << " dollars using " << strategy_->withdraw(amount) << "\n";
    }
};

// Various concrete strategies...
class CreditCard : public PaymentStrategy {
public:
    std::string withdraw(double amount) {
        return "credit card";
    }
};

class DebitCard : public PaymentStrategy {
public:
    std::string withdraw(double amount) {
        return "debit card";
    }
};

class Cash : public PaymentStrategy {
public:
    std::string withdraw(double amount) {
        return "cash";
    }
};

int main() {
    Customer Bob(std::make_unique<CreditCard>());
    Bob.pay(100);
    return 0;
}