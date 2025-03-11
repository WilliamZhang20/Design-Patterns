#include <iostream>
#include <string>
// Resource: https://stackoverflow.com/questions/7876168/using-the-visitor-pattern-with-template-derived-classes

class BaseVisitor {
    public:
        virtual ~BaseVisitor() {};
};

// Visitor base template class
template <typename T>
class AnimalVisitor {
public:
    virtual void visit(T&) = 0;
};

// Abstract base class for animals
template <typename Animal>
class BaseAnimal {
public:
    // This accept function upcasts to the base animal so it can work with any animal type
    template <typename T>
    void accept(T& visitor) {
        visitor.visit(static_cast<Animal&>(*this)); // upcast then visit!
    }
};

class Lion : public BaseAnimal<Lion> {
public:
    void roar() const {
        std::cout << "Lion is roaring!" << std::endl;
    }
};

class Elephant : public BaseAnimal<Elephant> {
public:
    void trumpet() const {
        std::cout << "Elephant is trumpeting!" << std::endl;
    }
};

// Visitor that calculates food consumption
// Multiple inheritance used to define visitor interfaces for all visited objects
class FoodConsumptionVisitor : public BaseVisitor,
                               public AnimalVisitor<Lion>,
                               public AnimalVisitor<Elephant> {
public:
    void visit(Lion& lion) override {
        std::cout << "Lion eats 10kg of meat per day." << std::endl;
    }

    void visit(Elephant& elephant) override {
        std::cout << "Elephant eats 200kg of plants per day." << std::endl;
    }
};

// Visitor that calculates habitat size
// Possible alternatives to multiple inheritance include composition of interfaces & type traits 
class HabitatSizeVisitor : public BaseVisitor,
                           public AnimalVisitor<Lion>,
                           public AnimalVisitor<Elephant>  {
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
