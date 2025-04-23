/*
обработчик 
конкретный обработчик
клиент
*/

#include <iostream>
#include <memory>
#include <string>

enum LogLevel {
    DEBUG,
    INFO,
    ERROR
};

class Logger {
protected:
    std::shared_ptr<Logger> next;

public:
    void setNext(std::shared_ptr<Logger> nextLogger) {
        next = nextLogger;
    }

    void log(LogLevel level, const std::string& message) {
        if (canHandle(level)) {
            write(message);
        } else if (next) {
            next->log(level, message);
        }
    }
    virtual bool canHandle(LogLevel level) = 0;
    virtual void write(const std::string& message) = 0;
    virtual ~Logger() {}

};

class DebugLogger : public Logger {
public:
    bool canHandle(LogLevel level) override {
        return level == DEBUG;
    }

    void write(const std::string& message) override {
        std::cout << "DEBUG: " << message << std::endl;
    }
};

class InfoLogger : public Logger {
public:
    bool canHandle(LogLevel level) override {
        return level == INFO;
    }

    void write(const std::string& message) override {
        std::cout << "INFO: " << message << std::endl;
    }
};

class ErrorLogger : public Logger {
public:
    bool canHandle(LogLevel level) override {
        return level == ERROR;
    }

    void write(const std::string& message) override {
        std::cout << "ERROR: " << message << std::endl;
    }
};

int main() {
    std::shared_ptr<Logger> debugLogger = std::make_shared<DebugLogger>();
    std::shared_ptr<Logger> infoLogger = std::make_shared<InfoLogger>();
    std::shared_ptr<Logger> errorLogger = std::make_shared<ErrorLogger>();

    debugLogger->setNext(infoLogger);
    infoLogger->setNext(errorLogger);

    debugLogger->log(DEBUG, "This is a debug message.");
    debugLogger->log(INFO, "This is an info message.");
    debugLogger->log(ERROR, "This is an error message.");

    return 0;
}