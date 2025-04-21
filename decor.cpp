#include <iostream>
#include <string>
#include <memory>

// 1. Message (Базовый компонент)
class Message {
public:
    virtual std::string getText() = 0;
    virtual ~Message() {}
};

// 2. SimpleMessage (Конкретный компонент)
class SimpleMessage : public Message {
public:
    SimpleMessage(std::string text) : text_(text) {}

    std::string getText() override {
        return text_;
    }

private:
    std::string text_;
};

// 3. MessageDecorator (Базовый декоратор)
class MessageDecorator : public Message {
public:
    MessageDecorator(std::shared_ptr<Message> message) : message_(message) {}

    std::string getText() override {
        return message_->getText(); // Делегируем получение текста базовому сообщению
    }

protected:
    std::shared_ptr<Message> message_; // Используем shared_ptr
};

// 4. LetterDecorator (Конкретный декоратор - добавление LOG:)
class LetterDecorator : public MessageDecorator {
public:
    LetterDecorator(std::shared_ptr<Message> message) : MessageDecorator(message) {}

    std::string getText() override {
        return "LOG: " + message_->getText();
    }
};

// 5. EncryptDecorator (Конкретный декоратор - шифрование *)
class EncryptDecorator : public MessageDecorator {
private:
    std::string encrypt(const std::string& text) {
        std::string encryptedText = "";
        for (char c : text) {
            encryptedText += "*";
        }
        return encryptedText;
    }

public:
    EncryptDecorator(std::shared_ptr<Message> message) : MessageDecorator(message) {}

    std::string getText() override {
        return encrypt(message_->getText());
    }
};

// 6. Клиентский код
int main() {
    // Исходное сообщение
    std::shared_ptr<Message> simpleMessage = std::make_shared<SimpleMessage>("Hello, world!");

    // Декорирование сообщения
    std::shared_ptr<Message> letterMessage = std::make_shared<LetterDecorator>(simpleMessage);
    std::shared_ptr<Message> encryptedLetterMessage = std::make_shared<EncryptDecorator>(letterMessage);

    // Вывод сообщений
    std::cout << "Simple Message: " << simpleMessage->getText() << std::endl;
    std::cout << "Letter Message: " << letterMessage->getText() << std::endl;
    std::cout << "Encrypted Letter Message: " << encryptedLetterMessage->getText() << std::endl;

    // Больше не нужно удалять объекты вручную, shared_ptr сделает это за нас

    return 0;
}