/*
травоядное 
плотоядное

африка
    травоядное зебра
    плотоядное лев
австралия
    травоядное кенгуру
    плотоядное динго
*/
#include <iostream>
#include <memory>

// Базовые интерфейсы животных
class Herbivore {
public:
    virtual ~Herbivore() = default;
    virtual void info() const = 0;
};

class Carnivore {
public:
    virtual ~Carnivore() = default;
    virtual void info() const = 0;
};

// Конкретные продукты животных
class Zebra : public Herbivore {
public:
    void info() const override {
        std::cout << "I am a Zebra!" << std::endl;
    }
};

class Lion : public Carnivore {
public:
    void info() const override {
        std::cout << "I am a Lion!" << std::endl;
    }
};

class Kangaroo : public Herbivore {
public:
    void info() const override {
        std::cout << "I am a Kangaroo!" << std::endl;
    }
};

class Dingo : public Carnivore {
public:
    void info() const override {
        std::cout << "I am a Dingo!" << std::endl;
    }
};

// Абстрактная фабрика
class ContinentFactory {
public:
    virtual ~ContinentFactory() = default;
    virtual std::unique_ptr<Herbivore> createHerbivore() const = 0;
    virtual std::unique_ptr<Carnivore> createCarnivore() const = 0;
};

// Конкретные фабрики
class AfricaFactory : public ContinentFactory {
public:
    std::unique_ptr<Herbivore> createHerbivore() const override {
        return std::make_unique<Zebra>();
    }

    std::unique_ptr<Carnivore> createCarnivore() const override {
        return std::make_unique<Lion>();
    }
};

class AustraliaFactory : public ContinentFactory {
public:
    std::unique_ptr<Herbivore> createHerbivore() const override {
        return std::make_unique<Kangaroo>();
    }

    std::unique_ptr<Carnivore> createCarnivore() const override {
        return std::make_unique<Dingo>();
    }  
};

// Клиентский код
void describeAnimals(const ContinentFactory& factory, const std::string& continentName) {
    std::cout << continentName << ":" << std::endl;
    auto herbivore = factory.createHerbivore();
    auto carnivore = factory.createCarnivore();
    herbivore->info();
    carnivore->info();
    std::cout << std::endl;
}

int main() {
    AfricaFactory africaFactory;
    AustraliaFactory australiaFactory;

    describeAnimals(africaFactory, "Africa");
    describeAnimals(australiaFactory, "Australia");

    return 0;
}
