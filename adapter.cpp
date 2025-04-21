/*
объекта
класса

целевой интерфейс 
адаптируемый класс
адаптер
*/

#include <iostream>
#include <string>
using namespace std;

class Target {
public:
    virtual ~Target() = default;
    virtual void Request() const {
        cout << "Target: The default target's behavior." << endl;
    }
};

class Adaptee {
public:
    void SpecificRequest() const {
        cout << "Adaptee: The special behavior of the adaptee." << endl;
    }
};

class Adapter : public Target {
private:
    Adaptee* adaptee_;

public:
    Adapter(Adaptee* adaptee) : adaptee_(adaptee) {}

    void Request() const override {
        cout << "Adapter: (TRANSLATED) Special behavior of the adaptee." << endl;
        adaptee_->SpecificRequest();
    }
};

void ClientCode(const Target* target) {
    target->Request();
}

int main() {
    cout << "Client: I can work just fine with the Target objects:" << endl;
    Target* target = new Target;
    ClientCode(target);

    cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:" << endl;
    Adaptee* adaptee = new Adaptee;
    Target* adapter = new Adapter(adaptee);
    ClientCode(adapter);

    delete target;
    delete adaptee;
    delete adapter;
    return 0;
}