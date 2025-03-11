// Command Design Pattern
#include <iostream>
#include <string>
#include <vector>

class Waiter {
    public:
        void addOrderItem(std::string item) {
            order.push_back(item);
        }
    private:
        std::string delivery;
        std::vector<std::string> order;
};

class FoodOrder {
    public:
        virtual void execute() = 0;
    protected:
        Waiter server; // assigned waiter
};

class OnlineOrder : public FoodOrder {
    public:
        void execute() override {

        }
};

class DineInOrder : public FoodOrder {
    public:
        void execute() override {

        }
};

class Chef {

};

int main() {
    return 0;
}
