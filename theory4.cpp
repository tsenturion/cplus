class NumericException : public std::exception {
public:
    virtual const char* what() const noexcept override = 0;
};

class IsNegativeException : public NumericException {
public:
    const char* what() const noexcept override {
        return "Negative value";
    }
};

class IsZeroException : public NumericException {
public:
    const char* what() const noexcept override {
        return "Zero value";
    }
};

void checkValue(int value) {
    if (value < 0) {
        throw IsNegativeException();
    } else if (value == 0) {
        throw IsZeroException();
    }
}

try {
    checkValue(0);
} catch (const NumericException& e) {
    std::cerr << e.what() << std::endl;
}

