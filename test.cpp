/**
Message getText()
SimpleMessage()
MessageDecorator shared_ptr
LoggerDecorator 'LOG: '
EncryptDecorator '*'
 */
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Message {
public:
    virtual string getText() const = 0;
    virtual ~Message() {}
};

class SimpleMessage : public Message {
public:
    string getText() const override {
        return "Привет мир!";
    }
};

class MessageDecorator : public Message {
protected:
    shared_ptr<Message> message;

public:
    MessageDecorator(shared_ptr<Message> message) : message(message) {}
};

class LoggerDecorator : public MessageDecorator {   
public:
    LoggerDecorator(shared_ptr<Message> message) : MessageDecorator(message) {}

    string getText() const override {
        return "LOG: " + message->getText();
    }
};

class EncryptDecorator : public MessageDecorator {
public:
    EncryptDecorator(shared_ptr<Message> message) : MessageDecorator(message) {}

    string getText() const override {
        string original = message->getText();
        for (char& c : original) {
            if (isalpha(c)) {
                c = '*';
            }
        }
        return original;
    }
};

int main() {
    shared_ptr<Message> msg = make_shared<SimpleMessage>();
    cout << "простое сообщение: " << msg->getText() << endl;
    msg = make_shared<LoggerDecorator>(msg);
    cout << "сообщение с логированием: " << msg->getText() << endl;

    msg = make_shared<EncryptDecorator>(msg);
    cout << "зашифрованное сообщение: " << msg->getText() << endl;
    return 0;
}