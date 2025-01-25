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
    double getTemp() {
        return temperature;
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
    double getHumidity() {
        return humidity;
    }
    void updateTemperature(double temp) override { }
    void updateHumidity(double humidity) override { 
        this->humidity = humidity;
    }
    void updateCondition(std::string condition) override {}
};

class WeatherStation { // the subject
public:
    WeatherStation(double temp = 0, double humidity=0, std::string condition = "") {
        temperature = temp;
        this->humidity = humidity;
        this->condition = condition;
    }
    void subscribe(Observer* client) {
        observers.push_back(client);
        notify_change(); // update new subscriber
    }
    void unsubscribe(Observer* client) {
        observers.remove(client); // linear time remove
        notify_change(); // update new subscriber
    }
    void changeTemp(double temp) {
        temperature = temp;
        notify_change();
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

// assumes subjects/subscribers want ALL weather data
// alternatively, I could have inherited from an abstract (Weather station) - and just had separated subjects

int main() { 
    WeatherStation station1(10, 60, "cloudy");

    TemperatureDisplay* screen = new TemperatureDisplay(); 
    station1.subscribe(screen);
    std::cout << "station temperature\n";
    std::cout << screen->getTemp() << "\n";
}