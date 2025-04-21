/*
MenuComponent dispalay
MenuItem
MenuGroup

меню:
    -файл
        -открыть
        -сохранить
        -создать
    -правка
        -повторить
        -отменить
    -вид
        -масштабировать
            -увеличить
            -уменьшить
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class MenuComponent {
public:
	virtual void display(int indent = 0) const = 0;
    virtual ~MenuComponent() = default;
};

class MenuItem : public MenuComponent {
private:
    string name;
public:
    MenuItem(const string& name) : name(name) {}

    void display(int indent = 0) const override {
        cout << string(indent, ' ') << "- " << name << endl;
    }  
};

class MenuGroup : public MenuComponent {
private:
    string name;
    vector<shared_ptr<MenuComponent>> items;
public:
    MenuGroup(const string& name) : name(name) {}

    void add(shared_ptr<MenuComponent> item) {
        items.push_back(item);
    }

    void display(int indent = 0) const override {
        cout << string(indent, ' ') << "+" << name << endl;
        for (const auto& item : items) {
            item->display(indent + 2);
        }
    }
};

int main() {
    auto rootMenu = make_shared<MenuGroup>("Главное меню");
    auto fileMenu = make_shared<MenuGroup>("Файлы");
    fileMenu->add(make_shared<MenuItem>("Открыть"));
    fileMenu->add(make_shared<MenuItem>("Сохранить"));
    fileMenu->add(make_shared<MenuItem>("Создать"));

    auto editMenu = make_shared<MenuGroup>("Правка");
    editMenu->add(make_shared<MenuItem>("Повторить"));
    editMenu->add(make_shared<MenuItem>("Отменить"));

    auto viewMenu = make_shared<MenuGroup>("Вид");
    auto scaleMenu = make_shared<MenuGroup>("Масштабировать");
    scaleMenu->add(make_shared<MenuItem>("Увеличить"));
    scaleMenu->add(make_shared<MenuItem>("Уменьшить"));
    viewMenu->add(scaleMenu);
    rootMenu->add(fileMenu);
    rootMenu->add(editMenu);
    rootMenu->add(viewMenu);

    rootMenu->display();

    return 0;
}