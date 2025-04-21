#include <iostream>
#include <string>

// 1. Implementation (Реализация) - ITextRenderer
class ITextRenderer {
public:
    virtual std::string render(const std::string& text) = 0;
    virtual ~ITextRenderer() {}
};

// 2. Concrete Implementations (Конкретные реализации)
class UppercaseRenderer : public ITextRenderer {
public:
    std::string render(const std::string& text) override {
        std::string result = text;
        for (char& c : result) {
            c = toupper(c);
        }
        return result;
    }
};

class LowercaseRenderer : public ITextRenderer {
public:
    std::string render(const std::string& text) override {
        std::string result = text;
        for (char& c : result) {
            c = tolower(c);
        }
        return result;
    }
};

// 3. Abstraction (Абстракция) - Text
class Text {
protected:
    ITextRenderer* renderer;

public:
    Text(ITextRenderer* renderer) : renderer(renderer) {}

    virtual std::string format(const std::string& text) {
        return renderer->render(text);
    }

    virtual ~Text() {
        delete renderer;
    }
};

// 4. Refined Abstractions (Уточненные абстракции)
class SimpleText : public Text {
public:
    SimpleText(ITextRenderer* renderer) : Text(renderer) {}

    std::string format(const std::string& text) override {
        return Text::format(text); // Просто использует базовую реализацию format
    }
};

class TitleText : public Text {
public:
    TitleText(ITextRenderer* renderer) : Text(renderer) {}

    std::string format(const std::string& text) override {
        std::string formattedText = Text::format(text);
        // Дополнительное форматирование для заголовков (например, добавление разделителей)
        return "== " + formattedText + " ==";
    }
};

// 5. Client Code (Клиентский код)
int main() {
    // Создание конкретных реализаций (рендереров)
    ITextRenderer* upperRenderer = new UppercaseRenderer();
    ITextRenderer* lowerRenderer = new LowercaseRenderer();

    // Создание уточненных абстракций (текстов)
    Text* simpleUpperText = new SimpleText(upperRenderer);
    Text* titleLowerText = new TitleText(lowerRenderer);

    // Использование
    std::string myText = "Hello, World!";
    std::cout << "Simple Upper Text: " << simpleUpperText->format(myText) << std::endl;
    std::cout << "Title Lower Text: " << titleLowerText->format(myText) << std::endl;

    // Очистка памяти
    delete simpleUpperText;
    delete titleLowerText;

    return 0;
}