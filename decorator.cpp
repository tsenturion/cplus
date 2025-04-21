/*
компонент
конкретный компонент
декоратор
конкретный декоратор
*/

#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Beverage {
public:
    virtual string getDescription() const = 0;
    virtual double cost() const = 0;
    virtual ~Beverage() {}
};

class Cofee : public Beverage {
public:
    string getDescription() const override {
        return "Кофе";
    }

    double cost() const override {
        return 10.0;
    }
};

class BeverageDecorator : public Beverage {
protected:
    shared_ptr<Beverage> beverage;

public:
    BeverageDecorator(shared_ptr<Beverage> beverage) : beverage(beverage) {}
};

class Milk : public BeverageDecorator {
public:
    Milk(shared_ptr<Beverage> beverage) : BeverageDecorator(beverage) {}

    string getDescription() const override {
        return beverage->getDescription() + ", молоко";
    }

    double cost() const override {
        return beverage->cost() + 2.0;
    }
};

class Sugar : public BeverageDecorator {
public:
    Sugar(shared_ptr<Beverage> beverage) : BeverageDecorator(beverage) {}

    string getDescription() const override {
        return beverage->getDescription() + ", сахар";
    }

    double cost() const override {
        return beverage->cost() + 1.0;
    }
};
int main() {
    shared_ptr<Beverage> drink = make_shared<Cofee>();
    drink = make_shared<Milk>(drink);
    drink = make_shared<Sugar>(drink);
    cout << drink->getDescription() << endl;
    cout << drink->cost() << endl;
    return 0;
}