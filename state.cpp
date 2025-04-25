/*
контекст 
состояние 
конкретные состояния 
*/

#include <iostream>
#include <memory>

class TrafficLightState {
public:
    virtual void handleRequest() = 0;
    virtual ~TrafficLightState() {}
};

class TrafficLight {
private:
    std::shared_ptr<TrafficLightState> state;

public:
    void setState(std::shared_ptr<TrafficLightState> state) {
        this->state = state;
    }

    void request() {
        state->handleRequest();
    }
};

class RedState : public TrafficLightState {
public:
    void handleRequest() override {
        std::cout << "Red light: Stop!" << std::endl;
    }
};

class YellowState : public TrafficLightState {
public:
    void handleRequest() override {
        std::cout << "Yellow light: Prepare to stop!" << std::endl;
    }
};

class GreenState : public TrafficLightState {
public:
    void handleRequest() override {
        std::cout << "Green light: Go!" << std::endl;
    }
};

int main() {
    TrafficLight trafficLight;
    std::shared_ptr<TrafficLightState> redState = std::make_shared<RedState>();
    std::shared_ptr<TrafficLightState> yellowState = std::make_shared<YellowState>();
    std::shared_ptr<TrafficLightState> greenState = std::make_shared<GreenState>();

    trafficLight.setState(redState);
    trafficLight.request();

    trafficLight.setState(yellowState);
    trafficLight.request();

    trafficLight.setState(greenState);
    trafficLight.request();

    return 0;
}