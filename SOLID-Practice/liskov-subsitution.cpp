// L: Liskov Subsitution Principle
#include <iostream>
#include <type_traits>
#include <vector>
#include <string>

/*
Definition: 
Let q(x) be a property provable about objects of x of type T. 
Then q(y) should be provable for objects y of type S where S is a subtype of T.
*/

// Here, we make an improvement to the "application"
// We add a volume calculator for some shapes, inheriting from area calc
// It must behave the same as its parent to be SOLID
// So that other classes that use parent can use same interface with child

// For shapes that don't support area it falls up
class ShapeInterface { 
public:
    virtual double area() = 0;
    ~ShapeInterface();
};

// Shape classes holds only geometric data (e.g. sides, radii)
class Square : public ShapeInterface {
	double length_;
public:
	Square(double length) : length_(length) {}
	double getLength() const { return length_; }
    double area() final { return length_ * length_; }
};

class Circle : public ShapeInterface {
	double radius_;
public:
	Circle(double radius) : radius_(radius) {}
	double getRadius() const { return radius_; }
    double area() final { return 3.14 * radius_ * radius_; }
};

// Class to calculate sum of all shape areas (separated responsibilities)
class AreaCalculator {
protected:
	std::vector<ShapeInterface*> shapes_;
public:
	AreaCalculator(std::vector<ShapeInterface*> shapes) : shapes_(shapes) {}
	double sum() const {
        double res = 0;
		for(int i=0; i<shapes_.size(); i++) {
            if(std::is_abstract_v<decltype(*shapes_[i])>) {
                throw "Invalid shape\n";
            }
            // a header with only this class can remain stable
            res += shapes_[i]->area(); // very simple
		}
        return res;
	}
};

// Class to call volume methods...
class VolumeCalculator : public AreaCalculator {
    double sum() const {
        // In order to be compatible with CalculatorOutputter...
        // ... it must return a single sum value and not an array of volumes!
        return 0;
    }
};

// Class to format output of sum of all shape areas
class CalculatorOutputter {
	AreaCalculator calc_;
public:
	CalculatorOutputter(AreaCalculator areas) : calc_(areas) {}
	std::string outputJSON() {
		std::cout << "JSON logic\n";
        return "{" + std::to_string(calc_.sum()) + "}";
	}
	std::string outputHTML() {
		std::cout << "HTML logic\n";
        return "<output>" + std::to_string(calc_.sum()) + "</output>\n";
	}
};

int main() {
	std::vector<ShapeInterface*> shapes;
	shapes.push_back(new Circle(3.0));
	shapes.push_back(new Square(5.0));
	AreaCalculator areas(shapes);
	CalculatorOutputter output(areas);
	double area = areas.sum();
	std::cout << area << "\n";
    std::cout << output.outputHTML() << "\n";
    std::cout << output.outputJSON() << "\n";
	return 0;
}
