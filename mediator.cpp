// mediator design pattern
#include <iostream>
#include <set>
#include <string>

using string = std::string;

class Entity {
public:
    virtual void sendMessage(const string& msg) = 0;
    virtual void receiveMessage(const string& msg) = 0;
};

class Mediator {
public:
    virtual void notify(string msg, Entity* sender) = 0; // has to have sender, regardless of scenario - don't want loopback
};

class AirTrafficControl : public Mediator { // more like a radio tower
public:
    void connect(Entity* entity) {
        entities.insert(entity);
    }
    void disconnect(Entity* entity) {
        entities.erase(entity);
    }
    void notify(string msg, Entity* sender) override {
        for (auto& entity : entities) {
            if (entity != sender) {
                entity->receiveMessage(msg);
            }
        }
    }
private:
    std::set<Entity*> entities; // unordered!!! - faster access under BST
};

class Aircraft : public Entity {
    string name;
    AirTrafficControl* atc;
public:
    Aircraft(const std::string& name, AirTrafficControl* atc) : name(name), atc(atc) {
        atc->connect(this);
    }

    void sendMessage(const std::string& message) override {
        std::cout << name << " (Plane) sends message: " << message << std::endl;
        atc->notify(name + ": " + message, this);
    }

    void receiveMessage(const std::string& message) override {
        std::cout << name << " (Plane) received message: " << message << std::endl;
    }
};

class GroundCrew : public Entity { 
    string name;
    AirTrafficControl* atc;
public:
    GroundCrew(const std::string& name, AirTrafficControl* atc) : name(name), atc(atc) {
        atc->connect(this);
    }

    void sendMessage(const std::string& message) override {
        std::cout << name << " (GroundCrew) sends message: " << message << std::endl;
        atc->notify(name + ": " + message, this);
    }

    void receiveMessage(const std::string& message) override {
        std::cout << name << " (GroundCrew) received message: " << message << std::endl;
    }
};

int main() {
    AirTrafficControl atc;

    Aircraft flight1("AA 123", &atc);
    Aircraft flight2("UA 678", &atc);
    GroundCrew firetruck("Fire Crew 1", &atc);

    firetruck.sendMessage("In position to salute UA 678");
    flight1.sendMessage("Requesting permission to land");
    return 0;
}