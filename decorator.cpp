// decorator design pattern
// applied to data source management system
#include <iostream>
#include <string>
#include <algorithm>

using string = std::string;

class DataSource {
public:
    virtual void writeData(string data) = 0;
    virtual string readData() = 0;
};

// Concrete Component with variations
class FileSource : public DataSource {
    string name;
    string data;
public:
    FileSource(string str) {
        this->name = str;
    }
    void writeData(string str) {
        // std::cout << "writing regular\n";
        data = str;
    }
    string readData() {
        return data;
    }
};

// Base implementation of the Decorator Class: follows interface as component but specifically for wrapping
class DataSourceDecorator : public DataSource {
public:
    DataSourceDecorator(DataSource* source) : wrapee_(source) {}

    // delegates work to wrapped component
    void writeData(string data) {
        wrapee_->writeData(data);
    }

    string readData() {
        return wrapee_->readData();
    }
protected:
    DataSource* wrapee_; // to be a component 
};

// Sloppy encryption - by simple reversal
class EncryptionDecorator : public DataSourceDecorator {
public:
    EncryptionDecorator(DataSource* src) : DataSourceDecorator(src) {}
    void writeData(string data) {
        reverse(data.begin(), data.end());
        // std::cout << "writing for encryptor\n";
        wrapee_->writeData(data);
    }
    string readData() {
        string ret = wrapee_->readData();
        reverse(ret.begin(), ret.end());
        return ret;
    }
};

// sloppy compression of RLE
class CompressionDecorator : public DataSourceDecorator {
public:
    CompressionDecorator(DataSource* src) : DataSourceDecorator(src) {}

    void writeData(string data) {
        // std::cout << "writing for compressor\n";
        std::string encoded = "";
        int count = 1;
        for (size_t i = 1; i <= data.size(); ++i) {
            if (i < data.size() && data[i] == data[i - 1]) {
                ++count;
            } else {
                encoded += data[i - 1];
                if (count > 1) encoded += std::to_string(count); // Append count if greater than 1
                count = 1;
            }
        }
        wrapee_->writeData(encoded);
    }
    string readData() {
        string encoded = wrapee_->readData();
        std::string decoded = "";
        for (size_t i = 0; i < encoded.size(); ++i) {
            char ch = encoded[i];
            std::string countStr = "";
            while (i + 1 < encoded.size() && std::isdigit(encoded[i + 1])) {
                countStr += encoded[++i]; // Collect digits for count
            }
            int count = countStr.empty() ? 1 : std::stoi(countStr);
            decoded.append(count, ch); // Append character 'count' times
        }
        return decoded;
    }
};  

/*
Example of a security demanding class - managing salaries
*/
class SalaryManager {
    DataSource* source_;
public:
    SalaryManager(DataSource* src) : source_(src) {}

    void configure(bool encrypt, bool compress) {
        if(encrypt) {
            source_ = new EncryptionDecorator(source_);
        }

        if(compress) {
            source_ = new CompressionDecorator(source_);
        }
    }

    string load() {
        return source_->readData();
    }

    void save(string dt) {
        source_->writeData(dt);
    }
};

int main() {
    FileSource* fileSource = new FileSource("salary_data.txt");

    // Create the SalaryManager and configure it
    SalaryManager salaryManager(fileSource);

    // Saving without encryption or compression
    salaryManager.save("50000");
    std::cout << "Salary without encryption or compression: " 
              << salaryManager.load() << std::endl;

    // Now configure with encryption and compression
    salaryManager.configure(true, true); // Enable both encryption and compression

    // Saving with encryption and compression
    salaryManager.save("50000");
    std::cout << "Salary with encryption and compression: " 
              << salaryManager.load() << std::endl;

    // Clean up
    delete fileSource;
}