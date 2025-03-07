#include <iostream>

// Abstract Base Class defining the template method
class Beverage {
public:
    // Common method for boiling water (same for all beverages)
    void boilWater() {
        std::cout << "Boiling water\n";
    }

    // Common method for pouring into a cup (same for all beverages)
    void pourInCup() {
        std::cout << "Pouring into cup\n";
    }

    virtual void prepare() = 0;

    virtual void addCondiments() = 0;

    virtual ~Beverage() {}
};

class Tea : public Beverage {
public:
    void prepare() override {
        boilWater();
        std::cout << "Steeping the tea\n";
    }

    void addCondiments() override {
        std::cout << "Adding lemon\n";
    }
};

class Coffee : public Beverage {
public:
    void prepare() override {
        boilWater();
        std::cout << "Dripping coffee through filter\n";
    }

    void addCondiments() override {
        std::cout << "Adding sugar and milk\n";
    }
};

class CocaCola : public Beverage {
public:
    void prepare() override {
        std::cout << "Pouring CocaCola from bottle\n";
    }

    void addCondiments() override {
        std::cout << "Adding ice to the coca cola\n";
    }
};

// This method is VERY GENERAL - works on any type!
void prepareDrink(Beverage* drink) {
    drink->prepare();
    drink->addCondiments(); // cause EVERYONE needs the SAME condiments!
    drink->pourInCup();
}

int main() {
    Tea tea;
    Coffee coffee;
    CocaCola cocaCola;

    std::cout << "Preparing Tea:\n";
    prepareDrink(&tea);
    std::cout << "\n";

    std::cout << "Preparing Coffee:\n";
    prepareDrink(&coffee);
    std::cout << "\n";

    std::cout << "Preparing CocaCola:\n";
    prepareDrink(&cocaCola);
    std::cout << "\n";

    return 0;
}
