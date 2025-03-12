// Command Design Pattern
#include <iostream>
#include <string>
#include <queue>
// Resource: https://student.cs.uwaterloo.ca/~cs446/1171/Arch_Design_Activity/Command.pdf

// Receives commands/orders
class Chef {
    public:
        void cook() {
            std::cout << "Cooking food!\n";
        }
        void pourDrink() {
            std::cout << "Preparing drink!\n";
        }
};

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

int main() {
    Waiter service;

    // Create OrderFood and OrderDrink objects - they are directly connected to the chef's "menu"
    Order* order1 = new OrderFood();
    Order* order2 = new OrderDrink();

    // Waiter takes the orders
    service.takeOrder(order1);
    service.takeOrder(order2);

    // Waiter places the orders
    service.placeOrders();
    delete order1;
    delete order2;
    return 0;
}
