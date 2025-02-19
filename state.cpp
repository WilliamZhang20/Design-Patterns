// State Design Pattern
#include <iostream>
#include <string>
#include <cmath>
#include <cassert>
#include <vector>
#include <utility>

/*
Sequence: insert coins, then select an item...then determine if enough cash, etc.*/

class VendingMachine;

class State {
	protected:
		VendingMachine* machine;
		int selection;
	public:
        State(VendingMachine* machine_) : machine(machine_) {}
		virtual ~State() {}
		virtual void dispenseItem() = 0;
		virtual void selectItem() = 0;
		virtual void insertCoins() = 0;
		virtual void returnMoney() = 0;
};

class VendingMachine {	
	State* state_;
	double balance_;
	std::vector<std::pair<std::string, int>> items_;
public:
	void dropItem(double idx) {
			if(balance_ < items_[idx].second) {
				throw "not enough balance";
			} else {
				balance_ -= items_[idx].second;
			}
	}
	void addBalance() {
		double coin;
		std::cin >> coin;
		coin = std::floor(coin * 100) / 100; // truncate to the penny
		assert(coin > 0); // no way to take away money publicly
		balance_ += coin;
	}
	VendingMachine(State* state, std::vector<std::pair<std::string, int>> items) : state_(nullptr), items_(items) {
		this->changeState(state);
	}
	~VendingMachine() {
		delete state_;
	}
	void changeState(State* state) {
		std::cout << "Transition to " << typeid(*state).name() << ".\n"; 
		if(this->state_ != nullptr) {
			delete this->state_;
		}
		this->state_ = state;
	}
	int checkItem(std::string val) {
		for(int i=0; i<items_.size(); i++) {
			if(val == items_[i].first) {
				if(balance_ < items_[i].second) {
					return -1;
				} else {
					return i;
				}
			}
		}
        return -1;
	}
	double getBalance() const {
		return balance_;
	}
	std::string getItems() const {
		std::string ret = "";
		for(int i=0; i<items_.size(); i++) {
			ret += items_[i].first;
		}
		return ret;
	}
	void emptyCash() {
		if(balance_ < 0) {
			std::cout << "no money\n";
		}
		std::cout << "Here's " << balance_ << "back\n";
		balance_ = 0;
	}
};

class Idle : public State {
public:
    Idle(VendingMachine* machine_) : State(machine_) {}
	void insertCoins() override;
	void selectItem() override {
		std::cout << "Insert cash first\n";
	}
	void dispenseItem() override {
		std::cout << "Insert cash first\n";
	}
	void returnMoney() override {
		std::cout << "Insert cash first\n";
	}
};

class ProcessMoney : public State {
public:
    ProcessMoney(VendingMachine* machine_) : State(machine_) {}
    void insertCoins() override { // the gate to open coins is open
        machine->addBalance();
    }
    void selectItem() override;
    void dispenseItem() override {
        std::cout << "Choose an item";
    }
    void returnMoney() override {
        machine->emptyCash();
        machine->changeState(new Idle(machine));
    }
};

class ItemSelection : public State {
public:
    ItemSelection(VendingMachine* machine_) : State(machine_) {}
    void insertCoins() override { 
        machine->addBalance();
        machine->changeState(new ProcessMoney(machine));
    }
    void selectItem() override { // can always keep selecting items...
        std::string item;
        std::cout << "Choose from: " << machine->getItems() << "\n";
        std::cin >> item;
        selection = machine->checkItem(item);
        if(selection == -1) {
            std::cout << "Not enough cash: insert coins or choose another\n";
            return;
        }
    }
    void dispenseItem() override;
    void returnMoney() override {
        machine->emptyCash();
        machine->changeState(new Idle(machine));
    }
};

class ItemDispensed : public State {
public:
    ItemDispensed(VendingMachine* machine_) : State(machine_) {}
    void insertCoins() override { 
        machine->addBalance();
        machine->changeState(new ProcessMoney(machine));
    }
    void selectItem() override {
        std::string item;
        std::cout << "Choose from: " << machine->getItems() << "\n";
        std::cin >> item;
        selection = machine->checkItem(item);
        if(selection == -1) {
            std::cout << "Not enough cash: insert coins or choose another\n";
            return;
        }
        machine->changeState(new ItemSelection(machine));
    }
    void dispenseItem() override {
        std::cout << "Insert coins or select an item again\n";
    }
    void returnMoney() override {
        machine->emptyCash();
        machine->changeState(new Idle(machine));
    }
};

void ItemSelection::dispenseItem()  {
    if(selection == -1) {
        std::cout << "Please select a correct item\n";
        return;
    }
    machine->dropItem(selection);
    machine->changeState(new ItemDispensed(machine));
}

void ProcessMoney::selectItem() {
    std::string item;
    std::cout << "Choose from: " << machine->getItems() << "\n";
    std::cin >> item;
    selection = machine->checkItem(item);
    if(selection == -1) {
        std::cout << "Not enough cash: insert coins or choose another\n";
        return;
    }
    machine->changeState(new ItemSelection(machine));
}

void Idle::insertCoins() {
    machine->addBalance();
    machine->changeState(new ProcessMoney(machine));
}

int main() {
	return 0;
}