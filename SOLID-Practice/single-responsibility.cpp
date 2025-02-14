// S: Single responsibility principle
#include <iostream>
#include <vector>
#include <string>

class Shape { 
public:
    virtual ~Shape() = 0;
};

// Shape classes holds only geometric data (e.g. sides, radii)
class Square : public Shape {
	double length_;
public:
	Square(double length) : length_(length) {}
	double getLength() const { return length_; }
};

class Circle : public Shape {
	double radius_;
public:
	Circle(double radius) : radius_(radius) {}
	double getRadius() const { return radius_; }
};

// Class to calculate sum of all shape areas (separated responsibilities)
class AreaCalculator {
	std::vector<Shape*> shapes_;
public:
	AreaCalculator(std::vector<Shape*> shapes) : shapes_(shapes) {}
	double sum() const { // ALTERNATIVE: implement visitor!!!!
		for(int i=0; i<shapes_.size(); i++) {
				// if shape is square call square
				// if shape is circle call circle ...etc.
		}
	}
};

class CalculatorOutputter {
	AreaCalculator calc_;
public:
	CalculatorOutputter(AreaCalculator areas) : calc_(areas) {}
	std::string outputJSON() {
		std::cout << "JSON logic\n";
	}
	std::string outputHTML() {
		std::cout << "HTML logic\n";
	}
};

int main() {
	std::vector<Shape*> shapes;
	shapes.push_back(new Circle(3.0));
	shapes.push_back(new Square(5.0));
	AreaCalculator areas(shapes);
	CalculatorOutputter output(areas);
	double area = areas.sum();
	output.outputJSON();
	output.outputHTML();
	return 0;
}