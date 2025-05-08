// I: Interface Segregation Principle
#include <iostream>
#include <type_traits>
#include <vector>
#include <string>

// A shape interface that does 2D area can't do 3D volume
// Thus, a Square shouldn't be a "sibling" of a "Cuboid" or "Sphere"
// So instead have a different interface for 3D shapes only

// For shapes that don't support area it falls up
class ShapeInterface { 
public:
    virtual double area() = 0;
    ~ShapeInterface() = default;
};

// To regulate commonality amongst all shapes, 2D and 3D - with a single calculate function
// The "Manager class" in a way of both 2D and 3D shapes for convenience...
class ManageShapeInterface {
public:
    // May either be 2D area or 3D surface area
    virtual double calculate() = 0;
    ~ManageShapeInterface() = default;
};

class ThreeDimensionalShapeInterface : public ShapeInterface {
public:
    ~ThreeDimensionalShapeInterface() = default;
    virtual double volume() = 0;
};

// But we can still have a dual area/volume, since a 3D 
class Cuboid : public ThreeDimensionalShapeInterface, public ManageShapeInterface {
    double length;
    double width;
    double height;
public:
    Cuboid(double l2, double w2, double h2) : length(l2), width(w2), height(h2) {}
    double area() {
        return 2 * (length * width + length * height + width * height);
    }
    double volume() {
        return length * width * height;
    }
    double calculate() final { return this->area(); }
};

// Shape classes holds only geometric data (e.g. sides, radii)
class Square : public ShapeInterface, public ManageShapeInterface {
	double length_;
public:
	Square(double length) : length_(length) {}
	double getLength() const { return length_; }
    double area() final { return length_ * length_; }
    double calculate() final { return this->area(); }
};

class Circle : public ShapeInterface, public ManageShapeInterface {
	double radius_;
public:
	Circle(double radius) : radius_(radius) {}
	double getRadius() const { return radius_; }
    double area() final { return 3.14 * radius_ * radius_; }
    double calculate() final { return this->area(); }
};

// Class to calculate sum of all shape areas (separated responsibilities)
class AreaCalculator {
private:
	std::vector<ShapeInterface*> shapes_;
public:
    AreaCalculator() = default;
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
private:
	std::vector<ThreeDimensionalShapeInterface*> shapes_;
public:
    VolumeCalculator() = default;
    VolumeCalculator(std::vector<ThreeDimensionalShapeInterface*> shapes) : shapes_(shapes) {}
    double sum() const {
        double res = 0;
        for(int i=0; i<shapes_.size(); i++) {
            if(std::is_abstract_v<decltype(*shapes_[i])>) {
                throw "Invalid shape\n";
            }
            // a header with only this class can remain stable
            res += shapes_[i]->volume(); // very simple
		}
        return res;
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
    shapes.push_back(new Cuboid(1, 6, 8));
	AreaCalculator areas(shapes);
	CalculatorOutputter output(areas);
	double area = areas.sum();
	std::cout << area << "\n";
    std::cout << output.outputHTML() << "\n";
    std::cout << output.outputJSON() << "\n";
    
	std::vector<ThreeDimensionalShapeInterface*> second;
    second.push_back(new Cuboid(5, 6, 8));
    VolumeCalculator vols(second);
    std::cout << "Volume: " << vols.sum() << "\n";
	return 0;
}
