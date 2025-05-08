// Second example of Dependency Inversion Principle...diverging away from shapes, areas, and volumes
// D: Dependency Inversion Principle
#include <iostream>
#include <memory>

/* 
Definition:
High-level modules should not depend on low-level modules. 
Instead, they should depend on abstraction.
Abstract classes should not depend on concrete classes.
*/

// Example Below: High-Level is Password Reminder
// Low-Level is Database...used by the high-level module
// However a naive implementation has the pw reminder instantiate a concrete connection, e.g. PostgreSQL
// Changes to PostgreSQL require changes to complex password reminder - bad
// Instead have abstract & concrete (e.g. MySQL) database connectors
// The high-level module simply calls abstract db connector which should point to concrete

// Similarly, the abstract interface for database connection is as generic as possible
// It does not have PostgreSQL or Mongo-specific functionality put into it
// Makes it easy to add any other database connector fitting needs
// As a result, changes to a specific database only require changing simple & concrete database connection class headers
// Rather than a high-level module with many other low-level modules to take care of.

class IDbConnection {
public:
    virtual void connect() = 0;
    ~IDbConnection() = default;
};

class MongoDBConnect : public IDbConnection {
public:
    void connect() final {
        std::cout << "MongoDB connection successful\n";
    }
};

class PostgreSQLConnect : public IDbConnection {
public:
    void connect() final {
        std::cout << "PostgreSQL connection successful!\n";
    }
};

class PasswordReminder {
    std::shared_ptr<IDbConnection> dbConnection;
public:
    PasswordReminder(std::shared_ptr<IDbConnection> db) : dbConnection(db) {}
    void connectWithDatabase() {
        dbConnection->connect();
    }
};

int main() {
    std::shared_ptr<IDbConnection> dbConnect = std::make_shared<PostgreSQLConnect>();
    PasswordReminder googlePw(dbConnect);
    std::cout << "Objects created\n";
    googlePw.connectWithDatabase();
}
