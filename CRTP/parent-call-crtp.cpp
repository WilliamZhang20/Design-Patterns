// Funny is if I didn't split draw & implement I would get a program that doesn't stop running (its recursion doesn't end)
// ALTERNATIVE: MAKE BASE DRAW PURE SO CANNOT CALL AND SO NONTERMINATION IS AVOIDED
#include <iostream>

template <typename Derived>
class Shape {
public:
	void implement() {
        std::cout << "Base CRTP interface called.\n";
		static_cast<Derived*>(this)->draw();
	}
    void draw() {
        std::cout << "base draw called\n";
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

class Animal : public Shape<Animal> {
public: // no draw :(
};

int main() {
    Shape<Circle> circle2;
	Square square;
	circle2.implement();
	square.implement();
    Animal animal;
    animal.implement(); // calls base interface + base draw
	return 0;
}