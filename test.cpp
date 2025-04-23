/*
список строк
    заглавные символы
    одну цифру
    имеют длину больше N = 5

FilterStrategy
FilterContext
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <memory>

class FilterStrategy {
public:
    virtual bool apply(const std::string& str) = 0;
    virtual ~FilterStrategy() {}
};

class UppercaseOnly : public FilterStrategy {
public:
    bool apply(const std::string& str) override {
        return !str.empty() && std::all_of(str.begin(), str.end(), [](char c) {
            return std::isupper(static_cast<unsigned char>(c));
        });
    }
};

class ContainsDigit : public FilterStrategy {
public:
    bool apply(const std::string& str) override {
        return std::any_of(str.begin(), str.end(), [](char c) {
            return std::isdigit(static_cast<unsigned char>(c));
        });
    }
};

class LengthGreaterThan : public FilterStrategy {
public:
    bool apply(const std::string& str) override {
        return str.length() > 5;
    }
};

class FilterContext {
private:
    std::unique_ptr<FilterStrategy> strategy;

public:
    void setStrategy(std::unique_ptr<FilterStrategy> newStrategy) {
        strategy = std::move(newStrategy);
    }

    std::vector<std::string> filter(const std::vector<std::string>& input) {
        std::vector<std::string> result;
        if (!strategy) return result;

        for (const auto& str : input) {
            if (strategy->apply(str)) {
                result.push_back(str);
            }
        }
        return result;
    }
};

int main() {
    std::vector<std::string> inputStrings = {"HELLO", "WORLD", "ABC123", "DEF456", "GHIJK"};

    FilterContext context;
    context.setStrategy(std::make_unique<UppercaseOnly>());
    auto result1 = context.filter(inputStrings);
    std::cout << "Filter 1: ";
    for (const auto& str : result1) std::cout << str << " ";
    std::cout << std::endl;

    context.setStrategy(std::make_unique<ContainsDigit>());
    auto result2 = context.filter(inputStrings);
    std::cout << "Filter 2: ";
    for (const auto& str : result2) std::cout << str << " ";
    std::cout << std::endl;

    context.setStrategy(std::make_unique<LengthGreaterThan>());
    auto result3 = context.filter(inputStrings);
    std::cout << "Filter 3: ";
    for (const auto& str : result3) std::cout << str << " ";
    std::cout << std::endl;

    return 0;
}