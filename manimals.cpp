#include <iostream>

#include <string>

#include <vector>

// Абстрактный класс животного (Animal)
class Animal {
	public: virtual std::string getName() const = 0;
	virtual std::string getType() const = 0; // Травоядное или плотоядное
	virtual std::string getContinent() const = 0; // Африка или Австралия
	virtual void makeSound() const = 0;
	virtual~Animal() {}
};
// Конкретные классы животных
// Африка
class Lion: public Animal {
	public: std::string getName() const override {
		return "Лев";
	}
	std::string getType() const override {
		return "Плотоядное";
	}
	std::string getContinent() const override {
		return "Африка";
	}
	void makeSound() const override {
		std::cout << "Рычит!" << std::endl;
	}
};
class Zebra: public Animal {
	public: std::string getName() const override {
		return "Зебра";
	}
	std::string getType() const override {
		return "Травоядное";
	}
	std::string getContinent() const override {
		return "Африка";
	}
	void makeSound() const override {
		std::cout << "Ржет!" << std::endl;
	}
};
// Австралия
class Kangaroo: public Animal {
	public: std::string getName() const override {
		return "Кенгуру";
	}
	std::string getType() const override {
		return "Травоядное";
	}
	std::string getContinent() const override {
		return "Австралия";
	}
	void makeSound() const override {
		std::cout << "Бормочет!" << std::endl;
	}
};
class Dingo: public Animal {
	public: std::string getName() const override {
		return "Динго";
	}
	std::string getType() const override {
		return "Плотоядное";
	}
	std::string getContinent() const override {
		return "Австралия";
	}
	void makeSound() const override {
		std::cout << "Воет!" << std::endl;
	}
};
// Абстрактная фабрика
class ContinentFactory {
	public: virtual Animal * createHerbivore() const = 0;
	virtual Animal * createCarnivore() const = 0;
	virtual~ContinentFactory() {}
};
// Конкретные фабрики
class AfricaFactory: public ContinentFactory {
	public: Animal * createHerbivore() const override {
		return new Zebra();
	}
	Animal * createCarnivore() const override {
		return new Lion();
	}
};
class AustraliaFactory: public ContinentFactory {
	public: Animal * createHerbivore() const override {
		return new Kangaroo();
	}
	Animal * createCarnivore() const override {
		return new Dingo();
	}
};
// Клиентский код
void ClientCode(const ContinentFactory & factory) {
	Animal * herbivore = factory.createHerbivore();
	Animal * carnivore = factory.createCarnivore();
	std::cout << "Травоядное: " << herbivore - > getName() << " (" << herbivore - > getContinent() << ")" << std::endl;
	std::cout << "Плотоядное: " << carnivore - > getName() << " (" << carnivore - > getContinent() << ")" << std::endl;
	delete herbivore;
	delete carnivore;
}
int main() {
	std::cout << "Африка:" << std::endl;
	AfricaFactory * africa = new AfricaFactory();
	ClientCode( * africa);
	delete africa;
	std::cout << std::endl;
	std::cout << "Австралия:" << std::endl;
	AustraliaFactory * australia = new AustraliaFactory();
	ClientCode( * australia);
	delete australia;
	return 0;
}