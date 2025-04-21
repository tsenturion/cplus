/*
компонент
    operation
    add
    remove
    getChild

лист
составной объект
клиент
*/

#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

class FileSystemItem {
public:
    virtual void display(int indent = 0) const = 0;
    virtual ~FileSystemItem() = default;
};

class File : public FileSystemItem {
private:
    string name;

public:
    File(const string& name) : name(name) {}
    void display(int indent = 0) const override {
        cout << string(indent, ' ') << "- " << name << endl;
    }
};

class Folder : public FileSystemItem {
private:
    string name;
    vector<shared_ptr<FileSystemItem>> children;

public:
    Folder(const string& name) : name(name) {}

    void add(const shared_ptr<FileSystemItem>& item) {
        children.push_back(item);
    }

    void display(int indent = 0) const override {
        cout << string(indent, ' ') << "+ " << name << endl;
        for (const auto& child : children) {
            child->display(indent + 2);
        }
    }
};

int main() {
    auto file1 = make_shared<File>("file1.txt");
    auto file2 = make_shared<File>("file2.txt");
    auto file3 = make_shared<File>("file3.txt");

    auto folder1 = make_shared<Folder>("folder1");
    auto folder2 = make_shared<Folder>("folder2");
    auto folder3 = make_shared<Folder>("folder3");

    folder1->add(file1);
    folder2->add(folder1);
    folder2->add(file2);
    folder3->add(file3);
    folder1->add(folder3);

    folder1->display();

    return 0;
}