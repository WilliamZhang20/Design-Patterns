#include <iostream>

// base operations of all concrete products
class Product {
public:
    virtual ~Product() {}
    virtual std::string Operation() const = 0; // made abstract
};

// concrete products to implement variations of the product
class ConcreteProduct1 : public Product {
public:
    std::string Operation() const override {
        return "{Result of concrete product 1}";
    }
};

class ConcreteProduct2 : public Product {
public:
    std::string Operation() const override {
        return "{Result of concrete product 2}";
    }
};

// creator factory returns object of the product, delegates different creators
class Creator { // also abstract...in correspondence with the product
public:
    virtual ~Creator() {}
    virtual Product* FactoryMethod() const = 0;

    std::string SomeOperation() const {
        Product* product = this->FactoryMethod();
        // use the product
        std::string result = "Creator: the creator's code has just worked with " + product->Operation();
        delete product;
        return result;
    }
};

class ConcreteCreator1 : public Creator {
public:
    Product* FactoryMethod() const override { // returns an abstracted general product, ensures independence between creator & product
        return new ConcreteProduct1();
    }
};


class ConcreteCreator2 : public Creator {
public:
    Product* FactoryMethod() const override {
        return new ConcreteProduct2();
    }
};

void clientRequest(const Creator& creator) {
    std::cout << "I would like to receive a product. It can be made in any way, but has to fulfill my requirements\n";
    std::cout << creator.SomeOperation() << std::endl;
}

int main() {
    std::cout << "App: Launched with the ConcreteCreator1.\n";
    Creator* creator = new ConcreteCreator1();
    clientRequest(*creator);
    std::cout << std::endl;
    std::cout << "App: Launched with the ConcreteCreator2.\n";
    Creator* creator2 = new ConcreteCreator2();
    clientRequest(*creator2);

    delete creator;
    delete creator2;
    return 0;
}