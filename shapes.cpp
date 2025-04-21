#include <iostream>
#include <vector>

// 1. LegacyCircle (без Draw())
class LegacyCircle {
public:
    LegacyCircle(int x, int y, int radius) : x_(x), y_(y), radius_(radius) {}

    void OldDrawCircle() {
        std::cout << "LegacyCircle: OldDrawCircle at (" << x_ << ", " << y_
                  << ") with radius " << radius_ << std::endl;
    }

private:
    int x_;
    int y_;
    int radius_;
};

// 2. IShapeDraw (Интерфейс для рисования фигур)
class IShapeDraw {
public:
    virtual void Draw() = 0;
    virtual ~IShapeDraw() {}
};

// 3. CircleAdapter (Адаптер для LegacyCircle)
class CircleAdapter : public IShapeDraw {
public:
    CircleAdapter(LegacyCircle* circle) : circle_(circle) {}

    void Draw() override {
        // Используем OldDrawCircle() для рисования
        circle_->OldDrawCircle();
    }

private:
    LegacyCircle* circle_;
};

// 4. Composite (Композиция - класс для хранения и управления фигурами)
class Composite : public IShapeDraw {
public:
    void Add(IShapeDraw* shape) {
        children_.push_back(shape);
    }

    void Remove(IShapeDraw* shape) {
        for (size_t i = 0; i < children_.size(); ++i) {
            if (children_[i] == shape) {
                children_.erase(children_.begin() + i);
                return;
            }
        }
    }

    void Draw() override {
        std::cout << "Composite: Drawing all children..." << std::endl;
        for (IShapeDraw* shape : children_) {
            shape->Draw();
        }
        std::cout << "Composite: Finished drawing all children." << std::endl;
    }

private:
    std::vector<IShapeDraw*> children_;
};


// 5. Клиентский код
int main() {
    // Создание LegacyCircle
    LegacyCircle* legacyCircle1 = new LegacyCircle(10, 20, 5);
    LegacyCircle* legacyCircle2 = new LegacyCircle(30, 40, 8);

    // Создание адаптеров для LegacyCircle
    IShapeDraw* circleAdapter1 = new CircleAdapter(legacyCircle1);
    IShapeDraw* circleAdapter2 = new CircleAdapter(legacyCircle2);

    // Создание Composite
    Composite* composite = new Composite();

    // Добавление фигур в Composite
    composite->Add(circleAdapter1);
    composite->Add(circleAdapter2);

    // Рисование Composite
    composite->Draw();

    // Удаление объектов (важно для предотвращения утечек памяти)
    delete composite;
    delete circleAdapter1;
    delete circleAdapter2;
    delete legacyCircle1; // Также удаляем LegacyCircle, так как Adapter им владеет

    return 0;
}