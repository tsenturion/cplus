/*
абстрактный класс
подклассы
основной класс

продукт 
конкретные продукты
создатель creatProduct()
конкретные создатели
клиентский код


*/
// if (type == 'console') logger = new ConsoleLogger();
// else if (type == 'file') logger = new FileLogger();

//интерфейс продукта
class Product
{
private:
    virtual void use() = 0;
    virtual ~Product() {}
};

//конкретные реализации 
class ConcreteProductA : public Product {
public:
    void use() override { std::cout << "Using ConcreteProductA" << std::endl; }
};

class ConcreteProductB : public Product {
public:
    void use() override { std::cout << "Using ConcreteProductB" << std::endl; }
};

//абстрактный класс создателя
class Creator
{
public:
    virtual std::unique_ptr<Product> createProduct() const = 0;

    void someOperation() const {
        auto product = createProduct();
        product->use();
    }

    virtual ~Creator() {}
};
    
//конкретные реализации создателя
class CreatorA : public Creator {
public:
    std::unique_ptr<Product> createProduct() const override {
        return std::make_unique<ConcreteProductA>();
    }
};

class CreatorB : public Creator {
public:
    std::unique_ptr<Product> createProduct() const override {
        return std::make_unique<ConcreteProductB>();
    }
};

