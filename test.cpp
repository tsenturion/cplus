#include <iostream>
#include <string>
#include <algorithm>  
#include <cctype>   

// Абстракция
class Text {
public:
    Text(const std::string& content) : content_(content) {}
    virtual ~Text() = default;

    virtual std::string get_content() const = 0; // Чисто виртуальная функция

protected:
    std::string content_;
};

class SimpleText : public Text {
public:
    SimpleText(const std::string& content) : Text(content) {}

    std::string get_content() const override {
        return content_;
    }
};

class TitleText : public Text {
public:
    TitleText(const std::string& content, int font_size = 16) : Text(content), font_size_(font_size) {}

    std::string get_content() const override {
        return content_;
    }

    int get_font_size() const {
        return font_size_;
    }

private:
    int font_size_;
};

// Реализация
class ITextRenderer {
public:
    virtual ~ITextRenderer() = default;
    virtual std::string render(const Text& text) const = 0;
};

class UppercaseRenderer : public ITextRenderer {
public:
    std::string render(const Text& text) const override {
        std::string content = text.get_content();
        std::transform(content.begin(), content.end(), content.begin(), ::toupper); // std::toupper для char
        return content;
    }
};

class LowercaseRenderer : public ITextRenderer {
public:
    std::string render(const Text& text) const override {
        std::string content = text.get_content();
        std::transform(content.begin(), content.end(), content.begin(), ::tolower); // std::tolower для char
        return content;
    }
};

// Пример использования
int main() {
    SimpleText simple_text("Hello, world!");
    TitleText title_text("My Awesome Title", 24);

    UppercaseRenderer uppercase_renderer;
    LowercaseRenderer lowercase_renderer;

    // Рендеринг простого текста
    std::string uppercase_simple_text = uppercase_renderer.render(simple_text);
    std::string lowercase_simple_text = lowercase_renderer.render(simple_text);

    std::cout << "Simple text (uppercase): " << uppercase_simple_text << std::endl;
    std::cout << "Simple text (lowercase): " << lowercase_simple_text << std::endl;

    // Рендеринг текста заголовка
    std::string uppercase_title_text = uppercase_renderer.render(title_text);
    std::string lowercase_title_text = lowercase_renderer.render(title_text);

    std::cout << "Title text (uppercase): " << uppercase_title_text << std::endl;
    std::cout << "Title text (lowercase): " << lowercase_title_text << std::endl;


    // Демонстрация добавления нового рендерера
    class HtmlRenderer : public ITextRenderer {
    public:
        std::string render(const Text& text) const override {
            return "<h1>" + text.get_content() + "</h1>"; // Упрощенный пример
        }
    };

    HtmlRenderer html_renderer;
    std::string html_simple_text = html_renderer.render(simple_text);
    std::cout << "Simple text (HTML): " << html_simple_text << std::endl;


    return 0;
}


