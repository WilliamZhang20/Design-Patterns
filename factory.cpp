#include <iostream>

// base operations of all concrete products
class Notification {
public:
    virtual ~Notification() {}
    virtual std::string send() const = 0; // made abstract
};

// concrete products to implement variations of the product
class EmailNotification : public Notification {
public:
    std::string send() const override {
        return "Sending Email";
    }
};

class SMSNotification : public Notification {
public:
    std::string send() const override {
        return "Sending SMS";
    }
};

// creator factory returns object of the product, delegates different creators
class NotificationFactory { // also abstract...in correspondence with the product
public:
    virtual ~NotificationFactory() {}
    virtual Notification* FactoryMethod() const = 0;

    std::string Send() const {
        Notification* msg = this->FactoryMethod();
        // use the product
        std::string result = "Creator: the creator's code has just worked with " + msg->send();
        delete msg;
        return result;
    }
};

class Email_Sender : public NotificationFactory {
public:
    Notification* FactoryMethod() const override { // returns an abstracted general product, ensures independence between creator & product
        return new EmailNotification();
    }
};


class SMS_Sender : public NotificationFactory {
public:
    Notification* FactoryMethod() const override {
        return new SMSNotification();
    }
};

void clientRequest(const NotificationFactory& creator) {
    std::cout << "I would like to receive a product. It can be made in any way, but has to fulfill my requirements\n";
    std::cout << creator.Send() << std::endl;
    std::cout << "Received from the creator: " << creator.FactoryMethod()->send() << "\n"; // received the product
}

int main() {
    std::cout << "App: Launched with the ConcreteCreator1.\n";
    NotificationFactory* creator = new Email_Sender();
    clientRequest(*creator);
    std::cout << std::endl;
    std::cout << "App: Launched with the ConcreteCreator2.\n";
    NotificationFactory* creator2 = new SMS_Sender();
    clientRequest(*creator2);

    delete creator;
    delete creator2;
    return 0;
}