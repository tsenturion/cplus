/*
IShape Draw()
LegacyCircle без Draw(), есть OldDrawCircle()
CircleAdapter
клиентский код
*/

#include <iostream>
using namespace std;

class IShape {
public:
	virtual void Draw() const = 0;
	virtual ~IShape() {}
};

class LegacyCircle {
public:
	void OldDrawCircle() const {    
        cout << "Legacy Circle Drawing!" << endl;
    }
};

class CircleAdapter : public IShape {
private:
    LegacyCircle* legacyCircle_;

public:
    CircleAdapter(LegacyCircle* legacyCircle) : legacyCircle_(legacyCircle) {}
    void Draw() const override {
        cout << "Circle Drawing!" << endl;
        legacyCircle_->OldDrawCircle();
    }
};

void ClientCode(const IShape* shape) {
    shape->Draw();
}

int main() {
    LegacyCircle* legacy = new LegacyCircle();
    IShape* shape = new CircleAdapter(legacy);
    ClientCode(shape);
    delete shape;
    delete legacy;
    return 0;
}