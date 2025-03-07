#include <iostream>
#include <string>

class Lion;
class Elephant;
class Monkey;

// Visitor base class template (CRTP style)
template <typename T>
class AnimalVisitor {
public:
    virtual void visit(Lion& lion) = 0;
    virtual void visit(Elephant& elephant) = 0;
    virtual void visit(Monkey& monkey) = 0;
    virtual ~AnimalVisitor() = default;
};

// Abstract base class for animals (CRTP style)
template <typename Derived>
class Animal {
public:
    virtual ~Animal() = default;
    // Accept the visitor
    virtual void accept(AnimalVisitor& visitor) = 0;
};

class Lion : public Animal<Lion> {
public:
    void accept(AnimalVisitor& visitor) override {
        visitor.visit(*this);
    }
    void roar() const {
        std::cout << "Lion is roaring!" << std::endl;
    }
};

class Elephant : public Animal<Elephant> {
public:
    void accept(AnimalVisitor& visitor) override {
        visitor.visit(*this);
    }
    void trumpet() const {
        std::cout << "Elephant is trumpeting!" << std::endl;
    }
};

// Visitor that calculates food consumption
class FoodConsumptionVisitor : public AnimalVisitor<FoodConsumptionVisitor> {
public:
    void visit(Lion& lion) override {
        std::cout << "Lion eats 10kg of meat per day." << std::endl;
    }

    void visit(Elephant& elephant) override {
        std::cout << "Elephant eats 200kg of plants per day." << std::endl;
    }
};

// Visitor that calculates habitat size
class HabitatSizeVisitor : public AnimalVisitor<HabitatSizeVisitor> {
public:
    void visit(Lion& lion) override {
        std::cout << "Lion needs 100 square meters of habitat." << std::endl;
    }

    void visit(Elephant& elephant) override {
        std::cout << "Elephant needs 1000 square meters of habitat." << std::endl;
    }
};

int main() {
    // Create animal objects
    Lion lion;
    Elephant elephant;

    // Create visitors
    FoodConsumptionVisitor foodVisitor;
    HabitatSizeVisitor habitatVisitor;
    
    // Apply visitors to animals
    lion.accept(foodVisitor);
    elephant.accept(foodVisitor);

    std::cout << std::endl;

    lion.accept(habitatVisitor);
    elephant.accept(habitatVisitor);

    return 0;
}