/*
издатель
наблюдатель
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

class IObserver {
public:
    virtual void update(float temperature) = 0;
    virtual ~IObserver() = default;
};

class ISubject {
public:
    virtual void addObserver(std::shared_ptr<IObserver> observer) = 0;
    virtual void removeObserver(std::shared_ptr<IObserver> observer) = 0;
    virtual void notifyObservers() = 0;
    virtual ~ISubject() = default;
};

class WeatherStation : public ISubject {
private:
    std::vector<std::shared_ptr<IObserver>> observers;
    float temperature;

public:
    void setTemperature(float temp) {
        temperature = temp;
        notifyObservers();
    }

    void addObserver(std::shared_ptr<IObserver> observer) override {
        observers.push_back(observer);
    }

    void removeObserver(std::shared_ptr<IObserver> observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    };
    
    void notifyObservers() override {
        for (const auto& observer : observers) {
            observer->update(temperature);
        }
    }
};

class Display : public IObserver {
private:
    std::string name;

public:
    Display(const std::string& name) : name(name) {}

    void update(float temperature) override {
        std::cout << name << ": The temperature is now " << temperature << " degrees Celsius." << std::endl;
    }
};

class Logger : public IObserver {
public:
    void update(float temperature) override {
        std::cout << "Logger: The temperature is now " << temperature << " degrees Celsius." << std::endl;
    }
};

int main() {
    WeatherStation weatherStation;

    auto display1 = std::make_shared<Display>("Display 1");
    auto display2 = std::make_shared<Display>("Display 2");
    auto logger = std::make_shared<Logger>();

    weatherStation.addObserver(display1);
    weatherStation.addObserver(display2);
    weatherStation.addObserver(logger);

    weatherStation.setTemperature(25.5f);

    return 0;
}