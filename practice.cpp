#include <iostream>
#include <unordered_map>
#include <string>
#include <memory> // Для unique_ptr

// 1. NonCopyableUnorderedMap (Предотвращение копирования и перемещения)
template <typename K, typename V>
class NonCopyableUnorderedMap : public std::unordered_map<K, V> {
public:
    NonCopyableUnorderedMap() = default;
    NonCopyableUnorderedMap(const NonCopyableUnorderedMap&) = delete;
    NonCopyableUnorderedMap& operator=(const NonCopyableUnorderedMap&) = delete;
    NonCopyableUnorderedMap(NonCopyableUnorderedMap&&) = delete;
    NonCopyableUnorderedMap& operator=(NonCopyableUnorderedMap&&) = delete;
};


// 2. Singleton (Одиночка)
class ConfigurationManager {
private:
    static std::unique_ptr<ConfigurationManager> instance; // Использование unique_ptr для управления памятью
    NonCopyableUnorderedMap<std::string, std::string> configMap; // Использование NonCopyableUnorderedMap

    ConfigurationManager() {} // Private constructor

public:
    ConfigurationManager(const ConfigurationManager&) = delete; // Удаление конструктора копирования
    ConfigurationManager& operator=(const ConfigurationManager&) = delete; // Удаление оператора присваивания копированием

    static ConfigurationManager& getInstance() {
        if (!instance) {
            instance = std::unique_ptr<ConfigurationManager>(new ConfigurationManager());
        }
        return *instance;
    }

    // 3. addConfig (Добавление конфигурации)
    void addConfig(const std::string& key, const std::string& value) {
        configMap[key] = value;
    }

    std::string getConfig(const std::string& key) const {
        auto it = configMap.find(key);
        if (it != configMap.end()) {
            return it->second;
        } else {
            return ""; // Или можно бросить исключение, если ключ не найден
        }
    }

    void printAllConfigs() const {
        std::cout << "Configurations:" << std::endl;
        for (const auto& pair : configMap) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }
};

// Инициализация статического члена (важно!)
std::unique_ptr<ConfigurationManager> ConfigurationManager::instance = nullptr;


int main() {
    // Получение экземпляра ConfigurationManager
    ConfigurationManager& configManager = ConfigurationManager::getInstance();

    // Добавление конфигураций
    configManager.addConfig("database_url", "localhost:5432");
    configManager.addConfig("log_level", "INFO");
    configManager.addConfig("theme", "dark");

    // Получение конфигураций
    std::string dbUrl = configManager.getConfig("database_url");
    std::string logLevel = configManager.getConfig("log_level");

    std::cout << "Database URL: " << dbUrl << std::endl;
    std::cout << "Log Level: " << logLevel << std::endl;

    // Попытка скопировать ConfigurationManager приведет к ошибке компиляции,
    // поскольку конструктор копирования и оператор присваивания удалены.

    configManager.printAllConfigs();

    return 0;
}