/*
абстрация 
уточненная абстракция 
реализация
конкретные реализации
*/
#include<iostream>
#include<memory>
using namespace std;

class IRenderer {
public:
    virtual void renderCircle(float x, float y, float radius) = 0;
    virtual void renderSquare(float x, float y, float size) = 0;
    virtual ~IRenderer() {}
};

class VectorRenderer : public IRenderer {
public:
    void renderCircle(float x, float y, float radius) override {
        cout << "Drawing a circle of radius " << radius << " in (" << x << ", " << y << ")" << endl;
    }
    void renderSquare(float x, float y, float size) override {
        cout << "Drawing a square of size " << size << " in (" << x << ", " << y << ")" << endl;
    }
};

class RasterRenderer : public IRenderer {
public:
    void renderCircle(float x, float y, float radius) override {
        cout << "Rasterizing a circle of radius " << radius << " in (" << x << ", " << y << ")" << endl;
    }
    void renderSquare(float x, float y, float size) override {
        cout << "Rasterizing a square of size " << size << " in (" << x << ", " << y << ")" << endl;
    }
};

class Shape {
protected:
    IRenderer* renderer;
public:
    Shape(IRenderer* rend) : renderer(rend) {}
    virtual ~Shape() = default;
    virtual void draw() = 0;
};

class Circle : public Shape {
private:
    float x, y, radius;
public:
    Circle(IRenderer* rend, float x_, float y_, float r)
        : Shape(rend), x(x_), y(y_), radius(r) {}
    void draw() override {
        renderer->renderCircle(x, y, radius);
    }
};

class Square : public Shape {
private:
    float x, y, size;
public:
    Square(IRenderer* rend, float x_, float y_, float s)
        : Shape(rend), x(x_), y(y_), size(s) {}
    void draw() override {
        renderer->renderSquare(x, y, size);
    }
};

int main() {
    VectorRenderer vectorRenderer;
    RasterRenderer rasterRenderer;

    Circle circle1(&vectorRenderer, 10, 10, 5);
    Circle circle2(&rasterRenderer, 20, 20, 7);
    Square square1(&vectorRenderer, 30, 30, 4);

    circle1.draw();
    circle2.draw();
    square1.draw();

    return 0;
}