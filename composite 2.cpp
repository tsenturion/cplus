#include <iostream>
#include <string>
#include <vector>

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

    void add(MenuComponent* component) {
        children_.push_back(component);
    }

    void display(int depth = 0) override {
        printIndent(depth);
        std::cout << name_ << ":" << std::endl;
        for (MenuComponent* child : children_) {
            child->display(depth + 1); // Рекурсивный вызов для отображения дочерних элементов с увеличением отступа
        }
    }

private:
    std::vector<MenuComponent*> children_;
    std::string name_;
};

// 4. Клиентский код (Создание и использование меню)
int main() {
    // Создание меню "Файл"
    MenuItem* fileOpen = new MenuItem("Открыть");
    MenuItem* fileClose = new MenuItem("Закрыть");
    MenuItem* fileCreate = new MenuItem("Создать");

    MenuGroup* fileMenu = new MenuGroup("Файл");
    fileMenu->add(fileOpen);
    fileMenu->add(fileClose);
    fileMenu->add(fileCreate);

    // Создание меню "Правка"
    MenuItem* editUndo = new MenuItem("Отменить");
    MenuItem* editRedo = new MenuItem("Повторить");

    MenuGroup* editMenu = new MenuGroup("Правка");
    editMenu->add(editUndo);
    editMenu->add(editRedo);

    // Создание меню "Вид"
    MenuItem* viewZoomIn = new MenuItem("Увеличить");
    MenuItem* viewZoomOut = new MenuItem("Уменьшить");
    MenuItem* viewScale = new MenuItem("Масштабировать");

    MenuGroup* viewMenu = new MenuGroup("Вид");
    viewMenu->add(viewZoomIn);
    viewMenu->add(viewZoomOut);
    viewMenu->add(viewScale);

    // Создание главного меню
    MenuGroup* mainMenu = new MenuGroup("Главное меню");
    mainMenu->add(fileMenu);
    mainMenu->add(editMenu);
    mainMenu->add(viewMenu);

    // Отображение главного меню
    mainMenu->display();

    // Освобождение памяти (Важно!)
    delete fileOpen;
    delete fileClose;
    delete fileCreate;
    delete fileMenu;
    delete editUndo;
    delete editRedo;
    delete editMenu;
    delete viewZoomIn;
    delete viewZoomOut;
    delete viewScale;
    delete viewMenu;
    delete mainMenu;

    return 0;
}