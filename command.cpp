/*
команда execute()
конкретная команда 
получатель 
отправитель 
клиент 
*/
#include <iostream>
#include <vector>
#include <string>
#include <memory>


class Command {
public:
    virtual void execute() = 0;
    virtual ~Command(){}
};

class Light {
public:
    void turnOn() {
        std::cout << "Light is on" << std::endl;
    }
    void turnOff() {
        std::cout << "Light is off" << std::endl;
    }
};

class LightOnCommand : public Command {
private:
    std::shared_ptr<Light> light;

public:
    LightOnCommand(std::shared_ptr<Light> l) : light(l) {}

    void execute() override {
        light->turnOn();
    }
};

class LightOffCommand : public Command {
private:
    std::shared_ptr<Light> light;

public:
    LightOffCommand(std::shared_ptr<Light> l) : light(l) {}

    void execute() override {
        light->turnOff();
    }
};

class RemoteControl {
private:
    std::shared_ptr<Command> onCommand;
    std::shared_ptr<Command> offCommand;

public:
    void setOnCommand(std::shared_ptr<Command> on) {
        onCommand = on;
    }
    
    void setOffCommand(std::shared_ptr<Command> off) {
        offCommand = off;
    }

    void pressOnButton() {
        if (onCommand) {
            onCommand->execute();
        }
    }

    void pressOffButton() {
        if (offCommand) {
            offCommand->execute();
        }
    }
};

int main() {
    std::shared_ptr<Light> light = std::make_shared<Light>();
    std::shared_ptr<Command> lightOn = std::make_shared<LightOnCommand>(light);
    std::shared_ptr<Command> lightOff = std::make_shared<LightOffCommand>(light);
    
    RemoteControl remote;
    remote.setOnCommand(lightOn);
    remote.setOffCommand(lightOff);

    std::cout << "Press on button:" << std::endl;
    remote.pressOnButton();

    std::cout << "Press off button:" << std::endl;
    remote.pressOffButton();

    return 0;
}