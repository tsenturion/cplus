#include <iostream>
#include <string>
#include <memory> // Для shared_ptr

// 1. ComplaintLevel (Уровень жалобы)
enum class ComplaintLevel {
    LOW,
    MEDIUM,
    HIGH
};

// 2. ComplaintHandler (Базовый класс обработчика)
class ComplaintHandler {
public:
    virtual ~ComplaintHandler() {}
    virtual void setNext(std::shared_ptr<ComplaintHandler> nextHandler) {
        next_ = nextHandler;
    }

    void handle(ComplaintLevel level, const std::string& message) {
        if (canHandle(level)) {
            respond(message);
        } else if (next_) {
            next_->handle(level, message);
        } else {
            std::cout << "Complaint cannot be handled." << std::endl;
        }
    }

protected:
    virtual bool canHandle(ComplaintLevel level) = 0;
    virtual void respond(const std::string& message) = 0;

private:
    std::shared_ptr<ComplaintHandler> next_;
};

// 3. Конкретные обработчики
class CallCenterAgent : public ComplaintHandler {
protected:
    bool canHandle(ComplaintLevel level) override {
        return level == ComplaintLevel::LOW;
    }

    void respond(const std::string& message) override {
        std::cout << "Call Center Agent handling complaint: " << message << std::endl;
        std::cout << "Providing basic assistance." << std::endl;
    }
};

class Manager : public ComplaintHandler {
protected:
    bool canHandle(ComplaintLevel level) override {
        return level == ComplaintLevel::MEDIUM;
    }

    void respond(const std::string& message) override {
        std::cout << "Manager handling complaint: " << message << std::endl;
        std::cout << "Offering additional support and solutions." << std::endl;
    }
};

class Director : public ComplaintHandler {
protected:
    bool canHandle(ComplaintLevel level) override {
        return level == ComplaintLevel::HIGH;
    }

    void respond(const std::string& message) override {
        std::cout << "Director handling complaint: " << message << std::endl;
        std::cout << "Taking significant action to resolve the issue." << std::endl;
    }
};

// 4. Клиентский код
int main() {
    // Создание цепочки обработчиков
    std::shared_ptr<CallCenterAgent> agent = std::make_shared<CallCenterAgent>();
    std::shared_ptr<Manager> manager = std::make_shared<Manager>();
    std::shared_ptr<Director> director = std::make_shared<Director>();

    agent->setNext(manager);
    manager->setNext(director);

    // Обработка жалоб разного уровня
    std::cout << "Submitting LOW level complaint:" << std::endl;
    agent->handle(ComplaintLevel::LOW, "Unable to reset password.");

    std::cout << "\nSubmitting MEDIUM level complaint:" << std::endl;
    agent->handle(ComplaintLevel::MEDIUM, "Incorrect billing statement.");

    std::cout << "\nSubmitting HIGH level complaint:" << std::endl;
    agent->handle(ComplaintLevel::HIGH, "Severe service outage and data loss.");

    std::cout << "\nSubmitting UNHANDLED level complaint:" << std::endl;
    agent->handle((ComplaintLevel)5, "Unrecognized Complaint Level"); // Неизвестный уровень жалобы

    return 0;
}