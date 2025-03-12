// Command Design Pattern
#include <iostream>
#include <string>
#include <queue>
// Resource: https://student.cs.uwaterloo.ca/~cs446/1171/Arch_Design_Activity/Command.pdf

class Chef;

class Order {
    public:
        virtual void execute() = 0;
    protected:
        Chef menu;
        std::string item;
};

class OrderFood : public Order {
    public:
        void execute() override {
            menu.cook();
        }
};

class OrderDrink : public Order {
    public:
        void execute() override {
            menu.pourDrink();
        }
};

// Invokes Commands / Orders
class Waiter {
    public:
        void takeOrder(Order* order) {
            orders.push(order);
        }
        void placeOrders() {
            while(!orders.empty()) {
                Order* curr = orders.front();
                orders.pop();
                curr->execute();
            }
        }
    private:
        std::queue<Order*> orders;
};

// Receives commands/orders
class Chef {
public:
    void cook() {
        std::cout << "Cooking food";
    }
    void pourDrink() {
        std::cout << "pouring drink";
    }
};

int main() {
    Waiter service;
    return 0;
}
