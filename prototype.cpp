/*
интерфейс clone()
конкретный прототип
клиентский код

clone()

поверхностное копирование
глубокое копирование
*/

#include <iostream>
#include <string>
#include <memory>

// Базовый интерфейс
class Shape {
public: 
	virtual void draw() const = 0;
    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual ~Shape() = default;
};

// Конкретный прототип круг
class Circle : public Shape {
private:
    int radius;

public:
    Circle(int r) : radius(r) {}

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this);
    }

    void draw() const override {
        std::cout << "Рисуем круг с радиусом " << radius << std::endl;
    }
};

// конкретный прототик прямоугольник
class Rectangle : public Shape {
private:
    int width, height;

public:
    Rectangle(int w, int h) : width(w), height(h) {}

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Rectangle>(*this);
    }

    void draw() const override {
        std::cout << "Рисуем прямоугольник с шириной " << width << " и высотой " << height << std::endl;
    }
};


void cloneAndDraw(const Shape& original) {
    std::unique_ptr<Shape> clone = original.clone();
    clone->draw();
}

int main() {
    Circle circle(5);
    Rectangle rectangle(10, 20);

    circle.draw();
    rectangle.draw();

    cloneAndDraw(circle);
    cloneAndDraw(rectangle);

    return 0;
}