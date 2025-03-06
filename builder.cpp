// Builder Design Pattern 
// Uniqueness: constructs part by part rather than all at once
// Contrast: factory just abstracts the delgation of construction to different subtypes 
// Adheres to Single Responsibility Principle
#include <iostream>
#include <string>
#include <memory>

class Car { // if child classes such as "FordCar" or "ToyotaCar" exist they could add more internal variables
	 std::string make;
	 std::string model;
	 std::string engine;
	 std::string transmission;
	 int drive;
public:
	 Car() {
        make = ""; model = ""; engine = ""; transmission = ""; drive = 0;
	 }
	 virtual std::string getInfo() { 
        return make + " " + model + ":\nEngine: " + engine + "\nTransmission: " + transmission + "\nWheel Drive: " + std::to_string(drive) + "\n"; 
	 }
	 void setMake(std::string make) { this->make = make; }
	 void setModel(std::string model) { this->model = model; }
	 void setTransmission(std::string transmission) { this->transmission = transmission; }
	 void setDrive(int drive) { this->drive = drive; }
	 std::string getMake() { return make; }
	 std::string getModel() { return model; }
	 std::string getTransmission() { return transmission; }
	 int getDrive() { return drive; }
};

class CarBuilder {
public:
    virtual void setMake(std::string) = 0;
    virtual void setModel(std::string) = 0;
    virtual void setTransmission(std::string) = 0;
    virtual void setDrive(int) = 0;
    virtual std::shared_ptr<Car> getCar() = 0;
};

class ToyotaBuilder : public CarBuilder {
private:
		std::shared_ptr<Car> toyotaCar; // toyota Car
public:
    ToyotaBuilder() { toyotaCar = std::make_unique<Car>(); }
    void setMake(std::string make) override {
        toyotaCar->setMake(make);
    }
    void setModel(std::string model) override {
        toyotaCar->setModel(model);
    }
    void setTransmission(std::string transmission) override {
        toyotaCar->setTransmission(transmission);
    }
    void setDrive(int drive) override {
        toyotaCar->setDrive(drive);
    }
    std::shared_ptr<Car> getCar() override {
        return toyotaCar;
    }
};

class FordBuilder : public CarBuilder {
private:
		std::shared_ptr<Car> fordCar;
public:
		FordBuilder() { fordCar = std::make_unique<Car>(); }
		void setMake(std::string make) override {
        fordCar->setMake(make);
    }
    void setModel(std::string model) override {
        fordCar->setModel(model);
    }
    void setTransmission(std::string transmission) override {
        fordCar->setTransmission(transmission);
    }
    void setDrive(int drive) override {
        fordCar->setDrive(drive);
    }
    std::shared_ptr<Car> getCar() override {
        return fordCar;
    }
};

class FordDirector {
private:
		CarBuilder* builder;
public:
    FordDirector(CarBuilder* builder) : builder(builder) {}
    void buildMustang() {
        builder->setMake("Ford");
        builder->setModel("Mustang");
        builder->setTransmission("Manual");
        builder->setDrive(6); // RWD (Rear-Wheel Drive)
    }
    void buildBronco() {
        builder->setMake("Ford");
        builder->setModel("Bronco");
        builder->setTransmission("Automatic");
        builder->setDrive(4); // 4WD (Four-Wheel Drive)
    }
    void buildF150() {
        builder->setMake("Ford");
        builder->setModel("F150");
        builder->setTransmission("Automatic");
        builder->setDrive(4); // 4WD (Four-Wheel Drive)
    }
};

class ToyotaDirector {
private:
		CarBuilder* builder;
public:
		ToyotaDirector(CarBuilder* builder) : builder(builder) {}
    void buildCamry() {
        builder->setMake("Toyota");
        builder->setModel("Camry");
        builder->setTransmission("Automatic");
        builder->setDrive(2); // FWD (Front-Wheel Drive)
    }
    void buildCorolla() {
        builder->setMake("Toyota");
        builder->setModel("Corolla");
        builder->setTransmission("Manual");
        builder->setDrive(2); // FWD (Front-Wheel Drive)
    }
    void buildRav4() {
        builder->setMake("Toyota");
        builder->setModel("Rav4");
        builder->setTransmission("Automatic");
        builder->setDrive(4); // AWD (All-Wheel Drive)
    }
};

int main() {
    FordBuilder fordBuilder;
    ToyotaBuilder toyotaBuilder;
    FordDirector fordDirector(&fordBuilder);
    ToyotaDirector toyotaDirector(&toyotaBuilder);
    fordDirector.buildMustang();
    std::shared_ptr<Car> mustang = fordBuilder.getCar();
    std::cout << "Built a " << mustang->getInfo();
    return 0;
}
