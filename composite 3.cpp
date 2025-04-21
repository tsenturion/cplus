#include <iostream>
#include <string>
#include <vector>
#include <memory> // Для shared_ptr

// 1. MenuComponent (Базовый класс)
class MenuComponent {
public:
    virtual void display(int depth = 0) = 0;
    virtual ~MenuComponent() {}

protected:
    // Вспомогательный метод для отступов
    void printIndent(int depth) {
        for (int i = 0; i < depth; ++i) {
            std::cout << "  "; // Два пробела для каждого уровня вложенности
        }
    }
};

// 2. MenuItem (Листовой класс)
class MenuItem : public MenuComponent {
public:
    MenuItem(std::string name) : name_(name) {}

    void display(int depth = 0) override {
        printIndent(depth);
        std::cout << name_ << std::endl;
    }

private:
    std::string name_;
};

// 3. MenuGroup (Составной класс)
class MenuGroup : public MenuComponent {
public:
    MenuGroup(std::string name) : name_(name) {}

    void add(std::shared_ptr<MenuComponent> component) {
        children_.push_back(component);
    }

    void display(int depth = 0) override {
        printIndent(depth);
        std::cout << name_ << ":" << std::endl;
        for (const auto& child : children_) {
            child->display(depth + 1); // Рекурсивный вызов для отображения дочерних элементов с увеличением отступа
        }
    }

private:
    std::vector<std::shared_ptr<MenuComponent>> children_;
    std::string name_;
};

// 4. Клиентский код (Создание и использование меню)
int main() {
    // Создание меню "Файл"
    std::shared_ptr<MenuItem> fileOpen = std::make_shared<MenuItem>("Открыть");
    std::shared_ptr<MenuItem> fileClose = std::make_shared<MenuItem>("Закрыть");
    std::shared_ptr<MenuItem> fileCreate = std::make_shared<MenuItem>("Создать");

    std::shared_ptr<MenuGroup> fileMenu = std::make_shared<MenuGroup>("Файл");
    fileMenu->add(fileOpen);
    fileMenu->add(fileClose);
    fileMenu->add(fileCreate);

    // Создание меню "Правка"
    std::shared_ptr<MenuItem> editUndo = std::make_shared<MenuItem>("Отменить");
    std::shared_ptr<MenuItem> editRedo = std::make_shared<MenuItem>("Повторить");

    std::shared_ptr<MenuGroup> editMenu = std::make_shared<MenuGroup>("Правка");
    editMenu->add(editUndo);
    editMenu->add(editRedo);

    // Создание меню "Вид"
    std::shared_ptr<MenuItem> viewZoomIn = std::make_shared<MenuItem>("Увеличить");
    std::shared_ptr<MenuItem> viewZoomOut = std::make_shared<MenuItem>("Уменьшить");
    std::shared_ptr<MenuItem> viewScale = std::make_shared<MenuItem>("Масштабировать");

    std::shared_ptr<MenuGroup> viewMenu = std::make_shared<MenuGroup>("Вид");
    viewMenu->add(viewZoomIn);
    viewMenu->add(viewZoomOut);
    viewMenu->add(viewScale);

    // Создание главного меню
    std::shared_ptr<MenuGroup> mainMenu = std::make_shared<MenuGroup>("Главное меню");
    mainMenu->add(fileMenu);
    mainMenu->add(editMenu);
    mainMenu->add(viewMenu);

    // Отображение главного меню
    mainMenu->display();

    // Больше не нужно удалять объекты вручную!
    return 0;
}