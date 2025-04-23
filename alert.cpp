#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // std::for_each

// 1. Observer Interface (Наблюдатель)
class TemperatureObserver {
public:
    virtual void update(double temperature) = 0;
    virtual ~TemperatureObserver() {}
};

// 2. Concrete Observers (Конкретные наблюдатели)
class HeatAlert : public TemperatureObserver {
private:
    double threshold;
public:
    HeatAlert(double threshold) : threshold(threshold) {}
    void update(double temperature) override {
        if (temperature > threshold) {
            std::cout << "Heat Alert: Temperature is " << temperature << " (threshold: " << threshold << ")" << std::endl;
        }
    }
};

class ColdAlert : public TemperatureObserver {
private:
    double threshold;
public:
    ColdAlert(double threshold) : threshold(threshold) {}
    void update(double temperature) override {
        if (temperature < threshold) {
            std::cout << "Cold Alert: Temperature is " << temperature << " (threshold: " << threshold << ")" << std::endl;
        }
    }
};

// 3. Subject (Субъект)
class TemperatureSensor {
private:
    std::vector<TemperatureObserver*> observers;
    double temperature;

public:
    void attach(TemperatureObserver* observer) {
        observers.push_back(observer);
    }

    void detach(TemperatureObserver* observer) {
        for (size_t i = 0; i < observers.size(); ++i) {
            if (observers[i] == observer) {
                observers.erase(observers.begin() + i);
                return;
            }
        }
    }

    void setTemperature(double temperature) {
        this->temperature = temperature;
        notifyObservers();
    }

private:
    void notifyObservers() {
        std::for_each(observers.begin(), observers.end(),
                      [this](TemperatureObserver* observer) { observer->update(this->temperature); });
    }
};

// 4. Клиентский код
int main() {
    // Создаем TemperatureSensor (Субъект)
    TemperatureSensor sensor;

    // Создаем HeatAlert и ColdAlert (Наблюдатели)
    HeatAlert heatAlert(10.0);
    ColdAlert coldAlert(0.0);

    // Регистрируем наблюдателей на сенсоре
    sensor.attach(&heatAlert);
    sensor.attach(&coldAlert);

    // Изменяем температуру
    sensor.setTemperature(15.0); // Вывод: Heat Alert: Temperature is 15 (threshold: 10)
    sensor.setTemperature(-5.0); // Вывод: Cold Alert: Temperature is -5 (threshold: 0)
    sensor.setTemperature(5.0);  // Нет вывода

     // Отписываем heatAlert, больше heatAlert не будет получать уведомления
     sensor.detach(&heatAlert);
     sensor.setTemperature(15.0); // Нет вывода
     sensor.setTemperature(-5.0); // Вывод: Cold Alert: Temperature is -5 (threshold: 0)

    // Освобождаем память (Важно!)
    sensor.detach(&heatAlert);
    sensor.detach(&coldAlert);
    delete &heatAlert; // Удаляем объекты, созданные в main
    delete &coldAlert; //  !!! ОБЯЗАТЕЛЬНО !!!

    return 0;
}