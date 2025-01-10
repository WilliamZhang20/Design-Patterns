// Have to match up round hole with square peg via an adapter
#include <iostream>
#include <cmath>

class RoundPeg {
public:
    RoundPeg(int radius) : radius_{radius} {}
    ~RoundPeg() {}
    int getRadius() const {
        return radius_;
    }
private:
    int radius_;
};

class SquarePeg {
public:
    SquarePeg(int width) : width_{width} {}
    int getWidth() {
        return width_;
    }
private:
    int width_;
};

class RoundHole {
private:
    int radius_;
public:
    RoundHole(int radius) : radius_{radius} { }
    int getRadius() const {
        return radius_;
    }
    bool fits(RoundPeg* peg) { // only a round peg can fit into a round hole!
        return this->getRadius() >= peg->getRadius();
    }
};

class SquarePegAdapter : public RoundPeg {
private:
    SquarePeg* peg_;
public:
    // constructor is special - roundPeg has no default constructor
    // so but you need to call a roundPeg constructor to create SquarePegAdapter
    // that means  
    SquarePegAdapter(SquarePeg* peg) : RoundPeg(peg->getWidth()), peg_(peg) {}
    
    int getRadius() {
        // output is round peg that could fit in the square input
        return peg_->getWidth() * sqrt(2) / 2;
    }
};

int main() {
    RoundHole* hole = new RoundHole(5);
    RoundPeg* rpeg = new RoundPeg(5);
    std::cout << (hole->fits(rpeg) ? "fits" : "doesn't fit") << std::endl;
    
    SquarePeg* small_sqpeg = new SquarePeg(5);
    SquarePeg* large_sqpeg = new SquarePeg(10);

    // below line doesn't compile....
    // std::cout << (hole->fits(small_sqpeg) ? "fits" : "doesn't fit") << std::endl;
    
    SquarePegAdapter* small_sqpeg_adapter = new SquarePegAdapter(small_sqpeg);
    SquarePegAdapter* large_sqpeg_adapter = new SquarePegAdapter(large_sqpeg);

    std::cout << (hole->fits(small_sqpeg_adapter) ? "fits" : "doesn't fit") << std::endl;
    
    std::cout << (hole->fits(large_sqpeg_adapter) ? "fits" : "doesn't fit") << std::endl;
    
    return 0;
}