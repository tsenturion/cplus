#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // transform

// 1. MenuComponent (Базовый класс для элементов меню)
class MenuComponent {
public:
    virtual void display() = 0;
    virtual ~MenuComponent() {}
};

// 2. MenuItem (Конкретный пункт меню)
class MenuItem : public MenuComponent {
public:
    MenuItem(std::string name) : name_(name) {}

    void display() override {
        std::cout << "  " << name_ << std::endl;
    }

private:
    std::string name_;
};

// 3. MenuGroup (Группа меню)
class MenuGroup : public MenuComponent {
public:
    MenuGroup(std::string name) : name_(name) {}

    void add(MenuComponent* component) {
        children_.push_back(component);
    }

    void display() override {
        std::cout << name_ << ":" << std::endl;
        // Не используем цикл, а вызываем display() для каждого элемента вручную (подходит для небольшого фиксированного количества элементов)
        if(children_.size() > 0)
          children_[0]->display();
        if(children_.size() > 1)
          children_[1]->display();
        if(children_.size() > 2)
          children_[2]->display();
        if(children_.size() > 3)
          children_[3]->display();
        if(children_.size() > 4)
          children_[4]->display();

    }

private:
    std::vector<MenuComponent*> children_;
    std::string name_;
};

// 4. Клиентский код
int main() {
    // Создание элементов меню "Файл"
    MenuItem* fileOpen = new MenuItem("Открыть");
    MenuItem* fileClose = new MenuItem("Закрыть");
    MenuItem* fileCreate = new MenuItem("Создать");

    // Создание группы меню "Файл"
    MenuGroup* fileMenu = new MenuGroup("Файл");
    fileMenu->add(fileOpen);
    fileMenu->add(fileClose);
    fileMenu->add(fileCreate);

    // Создание элементов меню "Правка"
    MenuItem* editUndo = new MenuItem("Отменить");
    MenuItem* editRedo = new MenuItem("Повторить");

    // Создание группы меню "Правка"
    MenuGroup* editMenu = new MenuGroup("Правка");
    editMenu->add(editUndo);
    editMenu->add(editRedo);

    // Создание элементов меню "Вид"
    MenuItem* viewZoomIn = new MenuItem("Увеличить");
    MenuItem* viewZoomOut = new MenuItem("Уменьшить");
    MenuItem* viewScale = new MenuItem("Масштабировать");

    // Создание группы меню "Вид"
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

    // Очистка памяти (важно!)
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