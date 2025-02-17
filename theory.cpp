#include <iostream>
#include <stdexcept>

void MyFunc(int c) {
    if (c == 0) {
        throw std::runtime_error("Division by zero");
    }
    std::cout << "Result: " << 10 / c << std::endl;
}

int main() {
    try {
        MyFunc(0);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}