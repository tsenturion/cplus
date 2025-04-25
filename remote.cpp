#include <iostream>
#include <string>
#include <vector>

// Receiver (Knows how to perform the operations)
class ElectronicDevice {
public:
    virtual void turnOnLight() = 0;
    virtual void turnOffLight() = 0;
    virtual void turnOnAC() = 0;
    virtual void turnOffAC() = 0;
    virtual void openDoor() = 0;
    virtual void closeDoor() = 0;
    virtual std::string getDescription() const = 0;
    virtual ~ElectronicDevice() {} // Important: Virtual Destructor
};

class SmartHomeSystem : public ElectronicDevice {
public:
    SmartHomeSystem(std::string name) : name(name) {}

    void turnOnLight() override {
        std::cout << name << ": Turning on the lights." << std::endl;
        lightOn = true;
    }

    void turnOffLight() override {
        std::cout << name << ": Turning off the lights." << std::endl;
        lightOn = false;
    }

    void turnOnAC() override {
        std::cout << name << ": Turning on the AC." << std::endl;
        acOn = true;
    }

    void turnOffAC() override {
        std::cout << name << ": Turning off the AC." << std::endl;
        acOn = false;
    }

    void openDoor() override {
        std::cout << name << ": Opening the door." << std::endl;
        doorOpen = true;
    }

    void closeDoor() override {
        std::cout << name << ": Closing the door." << std::endl;
        doorOpen = false;
    }

    std::string getDescription() const override {
        return name;
    }

private:
    std::string name;
    bool lightOn = false;
    bool acOn = false;
    bool doorOpen = false;

};


// Command (Interface for executing an operation)
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() {}
};


// Concrete Commands (Bind an action to a specific receiver)
class TurnOnLightCommand : public Command {
public:
    TurnOnLightCommand(ElectronicDevice* device) : device(device) {}
    void execute() override { device->turnOnLight(); }
    void undo() override { device->turnOffLight(); }
private:
    ElectronicDevice* device;
};


class TurnOffLightCommand : public Command {
public:
    TurnOffLightCommand(ElectronicDevice* device) : device(device) {}
    void execute() override { device->turnOffLight(); }
    void undo() override { device->turnOnLight(); }
private:
    ElectronicDevice* device;
};


class TurnOnACCommand : public Command {
public:
    TurnOnACCommand(ElectronicDevice* device) : device(device) {}
    void execute() override { device->turnOnAC(); }
    void undo() override { device->turnOffAC(); }
private:
    ElectronicDevice* device;
};


class TurnOffACCommand : public Command {
public:
    TurnOffACCommand(ElectronicDevice* device) : device(device) {}
    void execute() override { device->turnOffAC(); }
    void undo() override { device->turnOnAC(); }
private:
    ElectronicDevice* device;
};


class OpenDoorCommand : public Command {
public:
    OpenDoorCommand(ElectronicDevice* device) : device(device) {}
    void execute() override { device->openDoor(); }
    void undo() override { device->closeDoor(); }
private:
    ElectronicDevice* device;
};


class CloseDoorCommand : public Command {
public:
    CloseDoorCommand(ElectronicDevice* device) : device(device) {}
    void execute() override { device->closeDoor(); }
    void undo() override { device->openDoor(); }
private:
    ElectronicDevice* device;
};



// Invoker (Asks the command to carry out the request)
class RemoteControl {
public:
    void setCommand(Command* command) {
        this->command = command;
    }

    void pressButton() {
        if (command != nullptr) {
            command->execute();
            history.push_back(command); // Add command to history for undo
        }
        else {
            std::cout << "No command set!" << std::endl;
        }
    }

    void undo() {
        if (!history.empty()) {
            Command* lastCommand = history.back();
            lastCommand->undo();
            history.pop_back();
        }
        else {
            std::cout << "Nothing to undo!" << std::endl;
        }
    }


private:
    Command* command = nullptr;
    std::vector<Command*> history; // Store commands for undo functionality
};



int main() {
    // Create the Receiver
    SmartHomeSystem* livingRoom = new SmartHomeSystem("Living Room");

    // Create Concrete Commands
    TurnOnLightCommand* turnOnLight = new TurnOnLightCommand(livingRoom);
    TurnOffLightCommand* turnOffLight = new TurnOffLightCommand(livingRoom);
    TurnOnACCommand* turnOnAC = new TurnOnACCommand(livingRoom);
    TurnOffACCommand* turnOffAC = new TurnOffACCommand(livingRoom);
    OpenDoorCommand* openDoor = new OpenDoorCommand(livingRoom);
    CloseDoorCommand* closeDoor = new CloseDoorCommand(livingRoom);


    // Create the Invoker
    RemoteControl remote;

    // Example Usage
    remote.setCommand(turnOnLight);
    remote.pressButton(); // Turns on the light

    remote.setCommand(turnOnAC);
    remote.pressButton(); // Turns on the AC

    remote.setCommand(openDoor);
    remote.pressButton(); // Opens the door

    remote.undo(); // Closes the door
    remote.undo(); // Turns off AC
    remote.undo(); // Turns off Light

    remote.undo(); // Nothing to undo

    // Clean up memory (very important!)
    delete turnOnLight;
    delete turnOffLight;
    delete turnOnAC;
    delete turnOffAC;
    delete openDoor;
    delete closeDoor;
    delete livingRoom; // Delete the receiver *last* if other commands depend on it!

    return 0;
}