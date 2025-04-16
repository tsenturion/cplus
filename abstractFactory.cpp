/*
абстрактная фабрика
конкретная фабрика
абстрактные продукты
конкретные продукты
клиентский код

*/

/*
абстрактные продукты - Button, Checkbox
конкретные продукты - WindowsButton, WindowsCheckbox, LinuxButton, LinuxCheckbox
абстрактная фабрика
конкретны фабрики - WindowsFactory, LinuxFactory
клиентский код
*/
#include <iostream>
#include <memory>
#include <string>

// Базовые интерфейсы кнопки и флажка
class Button
{
public:
    virtual ~Button() {}
    virtual void paint() const = 0;
};

class Checkbox {
public:
    virtual ~Checkbox() {}
    virtual void paint() const = 0;
};

//конкретные продукты
class WindowsButton : public Button {
public:
    void paint() const override {
        std::cout << "Painting Windows Button" << std::endl;
    }
};

class WindowsCheckbox : public Checkbox {
public:
    void paint() const override {
        std::cout << "Painting Windows Checkbox" << std::endl;
    }
};

class LinuxButton : public Button {
public:
    void paint() const override {
        std::cout << "Painting Linux Button" << std::endl;
    }
};

class LinuxCheckbox : public Checkbox {
public:
    void paint() const override {
        std::cout << "Painting Linux Checkbox" << std::endl;
    }
};

// абстрактная фабрика
class GUIFactory {
public:
    virtual ~GUIFactory() {}
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() = 0;
};

// конкретные фабрики
class WindowsFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<WindowsButton>();
    }

    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<WindowsCheckbox>();
    }
};

class LinuxFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<LinuxButton>();
    }

    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<LinuxCheckbox>();
    }
};

// клиентский код
void renderUI(std::unique_ptr<GUIFactory> factory) {
    auto button = factory->createButton();
    auto checkbox = factory->createCheckbox();

    button->paint();
    checkbox->paint();
}

int main() {
    std::cout << "Windows UI:" << std::endl;
    renderUI(std::make_unique<WindowsFactory>());
    std::cout << std::endl;
    std::cout << "Linux UI:" << std::endl;
    renderUI(std::make_unique<LinuxFactory>());

    return 0;
}