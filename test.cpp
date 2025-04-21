/*
абстракция - Text: SimpleText, TitleText
реализация - ITextRenderer (render): UppercaseRenderer, LowercaseRenderer

*/
#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
using namespace std;

class ITextRenderer {
public:
	virtual void render(const string& text) = 0;
    virtual ~ITextRenderer() = default;
};

class UppercaseRenderer : public ITextRenderer {
public:
	void render(const string& text) override {
        string upper = text;
        transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
        cout << "Рендерим текст в верхнем регистре: " << upper << endl;
    }
};

class LowercaseRenderer : public ITextRenderer {
public:
    void render(const string& text) override {
        string lower = text;
        transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        cout << "Рендерим текст в нижнем регистре: " << lower << endl;
    }
};

class FramedTextRenderer : public ITextRenderer {
public:
    void render(const string& text) override {
        string border(text.size() + 4, '*');
        cout << border << endl;
        cout << "* " << text << " *" << endl;
        cout << border << endl;
    }
};

class Text {
protected:
    ITextRenderer& renderer;

public:
    Text(ITextRenderer& rend) : renderer(rend) {}

    virtual void display() = 0;
    virtual ~Text() = default;
};

class SimpleText : public Text {
private:
    string content;

public:
    SimpleText( ITextRenderer& rend, const string& text) : Text(rend), content(text) {}

    void display() override {
        renderer.render(content);
    }
};

int main() {
    UppercaseRenderer upperRenderer;
    LowercaseRenderer lowerRenderer;
    FramedTextRenderer framedRenderer;

    SimpleText text1(upperRenderer, "Привет, мир!");
    SimpleText text2(lowerRenderer, "Привет, мир!");
    SimpleText text3(framedRenderer, "Привет, мир!");

    text1.display();
    text2.display();
    text3.display();
    return 0;
}