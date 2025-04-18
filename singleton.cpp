/*
скрыть конструктор
создать статический getInstance()
единственный экземпляр класса

приватный конструктор 
приватная статичная переменная
публичный статичный метод

-
-srp
-тестирование

ленивая инициализация
жадная инициализация

управление памятью
временем жизни объекта
порядком инициализации глобальных переменных
*/
#include<iostream>
#include<string>

class Logger {
private:
	Logger() {
        std::cout << "логгер создан\n";
    }
	Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
public:
	static Logger* getInstance() {
        static Logger inctance;
        return &inctance;
    }

    void log(const std::string& msg) {
        std::cout << "вывод в логгер: " << msg << "\n";
    }
};

void doSomething() {
    Logger::getInstance()->log("что-то");
}

int main() {
    Logger::getInstance()->log("что-то еще");
    doSomething();
    Logger::getInstance()->log("end");
    return 0;
}