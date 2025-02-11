// Visitor Design Pattern
#include <iostream>
#include <memory>

// Forward Declare
class Visitor;
class Shape;
class Rectangle;
class Circle;
class Triangle;

// When to use:
/*
- Needs common operation on a group or structure of complex objects (e.g. a tree)
- Clean up business logic (refocus a class on data rather than jobs)
*/

class Visitor { // abstract visitor
	public:
		virtual void visitCircle(const Circle* circle) const = 0;
		virtual void visitRectangle(const Rectangle* rectangle) const = 0;
		virtual void visitTriangle(const Triangle* triangle) const = 0;
};

class Shape {
	public:
		virtual ~Shape() = default;
		virtual void accept(const Visitor& visitor) = 0;
};

class Circle : public Shape {
	public:
		Circle(double radius) : radius_(radius) {}
		void accept(const Visitor& visitor) {
			visitor.visitCircle(this);
		}
		double getRadius() const { return radius_; }
	private:
		double radius_;
};

class Rectangle : public Shape {
	public:
		Rectangle(double length, double width) : length_(length), width_(width) {}
		void accept(const Visitor& visitor) {
			visitor.visitRectangle(this);
		}
		double getLength() const { return length_; }
		double getWidth() const { return width_; }
	private:
		double length_;
		double width_;
};

class Triangle : public Shape {
	public:
		Triangle(double height, double width) : height_(height), width_(width) {}
		void accept(const Visitor& visitor) {
			visitor.visitTriangle(this);
		}
		double getHeight() const { return height_; }
		double getWidth() const { return width_; }
	private:
		double height_;
		double width_;
};

class CalculateArea : public Visitor { // single responsibility class!!!
	public:
    CalculateArea() {}
		void visitCircle(const Circle* circle) const override {
			std::cout << "Area of a circle is " << 3.14 * circle->getRadius() << "\n";
		}
		void visitRectangle(const Rectangle* rectangle) const override {
			std::cout << "Area of rectangle is " << rectangle->getLength() * rectangle->getWidth() << "\n";
		}
		void visitTriangle(const Triangle* triangle) const override {
			std::cout << "Area of triangle is " << triangle->getHeight() * 0.5 * triangle->getWidth() << "\n";
		}
};

int main() {
	Circle circle1(5.6);
	Rectangle square(8, 8);
	std::unique_ptr<Visitor> findArea = std::make_unique<CalculateArea>(); // safe memory handling
	circle1.accept(*findArea);
	square.accept(*findArea);
	return 0;
}