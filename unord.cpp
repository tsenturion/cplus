#include <iostream>
#include <unordered_map>
#include <string>

template <typename K, typename V>
class NonCopyableUnorderedMap : public std::unordered_map<K, V> {
public:
    NonCopyableUnorderedMap() = default;
    NonCopyableUnorderedMap(const NonCopyableUnorderedMap&) = delete; // Delete copy constructor
    NonCopyableUnorderedMap& operator=(const NonCopyableUnorderedMap&) = delete; // Delete copy assignment operator
    NonCopyableUnorderedMap(NonCopyableUnorderedMap&&) = delete; // Delete move constructor
    NonCopyableUnorderedMap& operator=(NonCopyableUnorderedMap&&) = delete; // Delete move assignment operator
};

int main() {
    NonCopyableUnorderedMap<std::string, int> myMap;

    myMap["apple"] = 1;
    myMap["banana"] = 2;
    myMap["cherry"] = 3;

    std::cout << "Map contents:" << std::endl;
    for (const auto& pair : myMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // The following lines will cause compile-time errors:
    // NonCopyableUnorderedMap<std::string, int> myMap2 = myMap;  // Copy constructor is deleted
    // myMap2 = myMap; // Copy assignment is deleted

    // NonCopyableUnorderedMap<std::string, int> myMap3 = std::move(myMap); //Move constructor is deleted

    return 0;
}