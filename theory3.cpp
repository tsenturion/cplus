#include <iostream>
#include <exception>
#include <string>

class MyCustimException : public std::exception {
private:
    std::string message;

public:
    MyCustimException(const std::string& msg) : message(msg) {}

    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

void riskyFunc(int value) {
    if (value < 0) {
        throw MyCustimException("Negative value is not allowed" + std::to_string(value));
    }
    std::cout << "Value: " << value << std::endl;
}

int main() {
    try
    {
        riskyFunc(-1);
    }
    catch(const MyCustimException& e)
    {
        std::cerr << "Exception caught: " << e.what() << '\n';
    }
    return 0;
}