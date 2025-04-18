/*

Config
set - устанавливает значение по ключу
get - возвращает значение по ключу
*/

#include <iostream>
#include <string>
#include <unordered_map>

class Config {
private:
    Config() {
        std::cout << "Config created" << std::endl;
    }

    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
    std::unordered_map<std::string, std::string> settings;

public:
    static Config& getInstance() {
        static Config instance;
        return instance;
    }

    void set(const std::string& key, const std::string& value) {
        settings[key] = value;
    }
    
    std::string get(const std::string& key) {
        if (settings.find(key) != settings.end()) {
            return settings[key];
        } else {
            return "NOT_FOUND";
        }
    }       
};

void testFuncion() {
    Config::getInstance().set("level", "2");
    std::cout << Config::getInstance().get("level") << std::endl;
}

int main() {
    Config::getInstance().set("language", "c++");
    Config::getInstance().set("mode", "debug");

    std::cout << "language: " << Config::getInstance().get("language") << std::endl;
    std::cout << "mode: " << Config::getInstance().get("mode") << std::endl;
    std::cout << "version: " << Config::getInstance().get("version") << std::endl;

    testFuncion();
}