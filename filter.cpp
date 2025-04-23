#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // для std::copy_if
#include <memory>    // для std::shared_ptr
#include <cctype>    // для isupper, isdigit

// 1. FilterStrategy (Интерфейс стратегии фильтрации)
class FilterStrategy {
public:
    virtual bool isValid(const std::string& str) const = 0;
    virtual ~FilterStrategy() {}
};

// 2. Конкретные стратегии фильтрации
class HasCapitalLetterStrategy : public FilterStrategy {
public:
    bool isValid(const std::string& str) const override {
        return std::any_of(str.begin(), str.end(), ::isupper);
    }
};

class HasDigitStrategy : public FilterStrategy {
public:
    bool isValid(const std::string& str) const override {
        return std::any_of(str.begin(), str.end(), ::isdigit);
    }
};

class MinLengthStrategy : public FilterStrategy {
public:
    MinLengthStrategy(size_t minLength) : minLength_(minLength) {}

    bool isValid(const std::string& str) const override {
        return str.length() > minLength_;
    }

private:
    size_t minLength_;
};

// 3. Комбинированная стратегия (используем паттерн Composite для объединения стратегий)
class CompositeFilterStrategy : public FilterStrategy {
public:
    void addStrategy(std::shared_ptr<FilterStrategy> strategy) {
        strategies_.push_back(strategy);
    }

    bool isValid(const std::string& str) const override {
        // Проверяем, что строка удовлетворяет *всем* стратегиям
        return std::all_of(strategies_.begin(), strategies_.end(),
                           [&](const auto& strategy) { return strategy->isValid(str); });
    }

private:
    std::vector<std::shared_ptr<FilterStrategy>> strategies_;
};

// 4. FilterContent (Класс для фильтрации контента)
class FilterContent {
public:
    FilterContent(std::shared_ptr<FilterStrategy> strategy) : strategy_(strategy) {}

    std::vector<std::string> filter(const std::vector<std::string>& data) const {
        std::vector<std::string> result;
        std::copy_if(data.begin(), data.end(), std::back_inserter(result),
                     [&](const auto& str) { return strategy_->isValid(str); });
        return result;
    }

private:
    std::shared_ptr<FilterStrategy> strategy_;
};

// 5. Клиентский код
int main() {
    std::vector<std::string> strings = {
        "Hello",    // Capital letter, length > 5
        "world1",   // Digit, length > 5
        "Abcde",    // Capital letter, length > 5
        "123456",   // Digit, length > 5
        "Short",    // Capital letter, length <= 5
        "NoCap",    // length > 5, no Capital letter
        "ValidStr1" // Capital letter, digit, length > 5
    };

    size_t minLength = 5;

    // Создаем стратегии
    std::shared_ptr<HasCapitalLetterStrategy> hasCapital = std::make_shared<HasCapitalLetterStrategy>();
    std::shared_ptr<HasDigitStrategy> hasDigit = std::make_shared<HasDigitStrategy>();
    std::shared_ptr<MinLengthStrategy> minLengthStrategy = std::make_shared<MinLengthStrategy>(minLength);

    // Комбинируем стратегии
    std::shared_ptr<CompositeFilterStrategy> compositeStrategy = std::make_shared<CompositeFilterStrategy>();
    compositeStrategy->addStrategy(hasCapital);
    compositeStrategy->addStrategy(hasDigit);
    compositeStrategy->addStrategy(minLengthStrategy);

    // Создаем FilterContent с комбинированной стратегией
    FilterContent filterContent(compositeStrategy);

    // Фильтруем данные
    std::vector<std::string> filteredStrings = filterContent.filter(strings);

    // Выводим отфильтрованные строки
    std::cout << "Filtered strings:" << std::endl;
    for (const auto& str : filteredStrings) {
        std::cout << str << std::endl;
    }

    return 0;
}