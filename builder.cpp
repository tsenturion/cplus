/*
builder
сам объект (продукт) 
интерфейс строителя
конкретный строитель
директор
    */ 
/*
Pizza
    размер (маленькая, большая, средняя)
    сыр
    пеперони
    ананасы
    соус
*/

#include <iostream>
#include <string>

// класс продукта
class Pizza {
private:
    std::string size;
    bool cheese = false;
    bool pepperoni = false;
    bool pineapple = false;
    std::string sauce = "tomato";

public:
    void setSize(const std::string& s) { size = s; }
    void addCheese(bool c) { cheese = c; }
    void addPepperoni(bool p) { pepperoni = p; }
    void addPineapple(bool p) { pineapple = p; }
    void setSauce(const std::string& s) { sauce = s; }

    void show() const {
        std::cout << "Pizza with " << size << " size and " << sauce << " sauce\n";
        if (cheese) { std::cout << "Cheese "; }
        if (pepperoni) { std::cout << "Pepperoni "; }
        if (pineapple) { std::cout << "Pineapple "; }
    }
};

// строитель
class PizzaBuilder {
private:
    Pizza pizza;

public:
    PizzaBuilder& setSize(const std::string& size) {
        pizza.setSize(size);
        return *this;
    }

    PizzaBuilder& addCheese() {
        pizza.addCheese(true);
        return *this;
    }

    PizzaBuilder& addPepperoni() {
        pizza.addPepperoni(true);
        return *this;
    }

    PizzaBuilder& addPineapple() {
        pizza.addPineapple(true);
        return *this;
    }

    PizzaBuilder& setSauce(const std::string& sauce) {
        pizza.setSauce(sauce);
        return *this;
    }

    Pizza build() {
        return pizza;
    }
};

// клиентский код
int main() {
    PizzaBuilder builder;
    Pizza pizza = builder.setSize("large")
                    .addCheese()
                    .addPepperoni()
                    .setSauce("tomato")
                    .build();

    pizza.show();
    return 0;
}