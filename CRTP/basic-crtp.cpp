// CRTP (Basic)
// Comprehensive: https://stackoverflow.com/questions/4173254/what-is-the-curiously-recurring-template-pattern-crtp 

#include <iostream>
/*
CRTP avoids overhead by resolving method calls at compile time. 
CRTP can be used to implement various design patterns, such as 
- mixins
- policy-based design.
*/

template <typename Derived>
class Shape {
public:
	void draw() {
		static_cast<Derived*>(this)->draw();
	}
};

class Circle : public Shape<Circle> {
public:
	void draw() {
		std::cout << "Draw circle\n";
	}
};

class Square : public Shape<Square> {
public:
    void draw() {
        std::cout << "Drawing a Square" << std::endl;
    }
};

int main() {
	Shape<Circle> circle; // draws circle
	Square square;
	circle.draw();
	square.draw();
	
	Circle circle2;
	circle2.draw();
	return 0;
}