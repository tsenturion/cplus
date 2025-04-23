/*
контекст
интерфейс
конкрентнве стратегии
*/

class SortStrategy {
public:
    virtual void sort(std::vector<int>& data) = 0;   
}
class AscendingSord : public SortStrategy{
public:
    void sort(std::vector<int>& data) override {
        std::sort(data.begin(), data.end());
    }
};

class DescendingSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::sort(data.rbegin(), data.rend());
    }
};

class Sorter {
private: 
    std::unique_ptr<SortStrategy> strategy;
public:
    void setSorted(std::unique_ptr<SortStrategy> newStrategy) {
        this->strategy = std::move(newStrategy);
    }
    void sortData(std::vector<int>& data) {
        if (strategy) {
            strategy->sort(data);
        } else {
            std::cerr << "No sorting strategy set." << std::endl;
        }
    }
};


    }