// observer design pattern
#include <iostream>
#include <string>
#include <list>

class Observer { // for weather specifically
public:
    virtual ~Observer() {};
    virtual void updateTemperature(double) = 0;
    virtual void updateHumidity(double) = 0;
    virtual void updateCondition(std::string) = 0;
};

class TemperatureDisplay : public Observer {
    double temperature;
public:
    TemperatureDisplay() {
        temperature = 0;
    }
    void updateTemperature(double temp) override {
        temperature = temp;
    }
    void updateHumidity(double humidity) override { }
    void updateCondition(std::string condition) override {}
};

class HumidityDisplay : public Observer {
    double humidity;
public:
    HumidityDisplay() {
        humidity = 0;
    }
    void updateTemperature(double temp) override { }
    void updateHumidity(double humidity) override { 
        this->humidity = humidity;
    }
    void updateCondition(std::string condition) override {}
};

class WeatherStation { // the subject
public:
    void subscribe(Observer* client) {
        observers.push_back(client);
    }
    void unsubscribe(Observer* client) {
        observers.remove(client); // linear time remove
    }
    void notify_change() {
        std::list<Observer*>::iterator iterator = observers.begin();
        while (iterator != observers.end()) {
            (*iterator)->updateTemperature(temperature);
            (*iterator)->updateHumidity(humidity);
            (*iterator)->updateCondition(condition);
            ++iterator;
        }
    }
private:
    std::list<Observer*> observers;
    double temperature;
    double humidity;
    std::string condition;
};