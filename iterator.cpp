#include <iostream>
#include <vector>
#include <string>

template <typename T, typename U>
class DataIterator {
public:
    typedef typename std::vector<T>::iterator iter_type;
    DataIterator(U *data, iter_type pos = iter_type()) : m_data(data), m_it(pos) {}
    std::vector<T>& operator*() const {
        if(m_it >= m_data->begin() && m_it < m_data->end()) {
            return *m_it;
        }
    }
    iter_type& operator++() {
        m_it++;
        return m_it;
    }
    iter_type& first() {
        m_it = m_data->begin();
        return m_it;
    }
    bool isDone() {
        return (m_it == m_data->end());
    }

private:
    U *m_data;
    iter_type m_it; // iterator index
};

template <typename T>
class Database {
    friend class DataIterator<T, Database>;
public:
    void addRow(std::vector<T> row) {
        pData.push_back(row);
    }
    DataIterator<T, Database>* createIterator() {
        return new DataIterator<T, Database>(this);
    }
    DataIterator<T, Database> begin() {
        return DataIterator<T, Database>(this, pData.begin());
    }
    DataIterator<T, Database> end() {
        return DataIterator<T, Database>(this, pData.end());
    }
private:
    std::vector<std::vector<T>> pData;
};

class Student {
public:
    Student(int age = -1, double gpa = -1, std::string name = "", std::string home = "") : m_age(age), m_gpa(gpa), m_name(name), m_home(home) {}
    int getAge() const { return m_age; }
    double getGpa() const { return m_gpa; }
    std::string getName() const { return m_name; }
    std::string getHome() const { return m_home; }
private:
    int m_age;
    double m_gpa;
    std::string m_name;
    std::string m_home;
};

int main() {
	Database<Student> school;
    // Adding some data to the database
    school.addRow({Student(18, 3.5, "Alice", "New York"), Student(19, 3.8, "Bob", "Los Angeles")});
    school.addRow({Student(20, 3.9, "Charlie", "Chicago"), Student(21, 3.6, "David", "San Francisco")});

    DataIterator<Student, Database<Student>> *it = school.createIterator();
    for (it->first(); !it->isDone(); ++(*it)) {
        // Dereferencing and using the iterator to print the data
        auto row = *it;
        for (const auto& student : row) {
            std::cout << "Name: " << student.getName() << ", Age: " << student.getAge() 
                      << ", GPA: " << student.getGpa() << ", Home: " << student.getHome() << std::endl;
        }
    }
    delete it;
    return 0;
}
