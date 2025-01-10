#include <mutex>
#include <thread>
#include <iostream>
#include <chrono>
#include <string>

class Singleton 
{
private:
    static Singleton* pinstance_;
    static std::mutex mutex_;
protected:
    Singleton(const std::string value) : value_(value) {}
    ~Singleton() {}
    std::string value_;

public:
    Singleton(Singleton &other) = delete; // block cloning
    void operator=(const Singleton& other) = delete; // block assignment

    static Singleton *getInstance(const std::string& value); // requires thread handing to avoid copying

    void functionalLogic() 
    {
        // ....
    }

    std::string value() const {
        return value_; // oh that's why we have underscore - for the function name...
    }
};

Singleton* Singleton::pinstance_ = nullptr;
std::mutex Singleton::mutex_;

Singleton *Singleton::getInstance(const std::string& value) {
    std::lock_guard<std::mutex> lock(mutex_); // prevents race conditions
    if(pinstance_ == nullptr) {
        pinstance_ = new Singleton(value);
    }
    return pinstance_;
}

void threadFoo() {
    // initialize one instance
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::getInstance("foo");
    std::cout << singleton->value() << "\n";
}


void threadBar() {
    // initialize another instance
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::getInstance("foo");
    std::cout << singleton->value() << "\n";
}

int main() {
    std::cout << "If you see different values, something went wrong\n";
    std::thread t1(threadFoo);
    std::thread t2(threadFoo);
    t1.join();
    t2.join();
    return 0;
}