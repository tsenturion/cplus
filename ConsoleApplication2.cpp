//https://github.com/doctest/doctest 
//https://code-basics.com/ru/languages/clang - посмотреть на разные
//https://huggingface.co/ - нейронки
//https://chat.deepseek.com/ - без vpn
/*
Основные функции и макросы:
1. TEST_CASE("description") - определяет тестовый случай
2. SUBCASE("description") - определяет подслучай внутри TEST_CASE
3. CHECK(condition) - проверяет условие без прерывания выполнения теста
4. REQUIRE(condition) - проверяет условие с прерыванием теста при неудаче
5. CHECK_MESSAGE(condition, message) - проверка с пользовательским сообщением
6. CAPTURE(expression) - захватывает значение выражения для вывода при ошибке
7. CHECK_THROWS(expression) - проверяет, что выражение выбрасывает исключение
8. CHECK_NOTHROW(expression) - проверяет, что выражение не выбрасывает исключение
9. CHECK_THROWS_AS(expression, exception_type) - проверяет тип выброшенного исключения
10. TEST_CASE_FIXTURE(FixtureClass, "description") - тест с использованием фикстуры
11. SKIP("reason") - пропускает выполнение теста с указанной причиной
12. WARN(condition) - выводит предупреждение, если условие ложно
13. FAIL(message) - принудительно проваливает тест с указанным сообщением
14. INFO(message) - выводит дополнительную информацию при провале теста

Классы:
- Doctest::Context - управление контекстом выполнения тестов
- Doctest::String - строковый класс для работы с сообщениями об ошибках
- Doctest::Approx - класс для сравнения чисел с плавающей точкой

Методы:
- addFilter() - добавление фильтра для выборочного запуска тестов
- setOption() - установка опций выполнения тестов
- applyCommandLine() - применение параметров командной строки
- run() - запуск тестов
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

//#include <iostream>
#include <doctesh.h>

//int main()
//{
//
//    std::cout << "Hello World!\n";
//}

int add(int a, int b) {
    /*
    добавляет а + б
    */
    return a + b;
}

TEST_CASE("Testing the add function") {
    CHECK(add(2, 3) == 5);
    CHECK(add(-1, 1) == 0);
    CHECK(add(0, 0) == 0);
    CHECK(add(-1, -1) == -2);
}

//int factorial(int n) {
//    return (n <= 1) ? 1 : n * factorial(n - 1);
//}
//
//TEST_CASE() {
//    SUBCASE("Base cases") {
//        CHECK(factorial(0) == 1);
//    }
//}

// CHECK без прерывания
// REQUIRE с прерыванием

//TEST_CASE("Testing with fixtures") {
//    int a = 5;
//    int b = 10;
//
//    SUBCASE("Check addition") {
//        a = 6;
//        CHECK(add(a, b) == 16);
//    }
//
//    SUBCASE("Chech subtration") {
//        CHESK(add(a, b) == -5)
//    }
//
//    SUBCASE("")
//}

//TEST_CASE_FIXTURE 

//g++ -std=c++11 -o test_program test_program.cpp
//./test_program

//struct VectorFixture {
//    std::vecor<int> vec;
//
//    VectorFixture() {
//        vec = { 1, 2, 3, 4, 5, 6 };
//    }
//};
//
//TEST_CASE_FIXTURE(VectorFixture, "Testing vector operations") {
//    CHECK(vec.size() == 6);
//    CHECK(vec[0] == 1);
//    CHECK(vec.back() == 6);
//
//    SUBCASE("Adding an element") {
//        vec.puch_back(6);
//        CHECK(vec.size() == 7);
//        CHECK(vec.back() == 7);
//    }
//
//    SUBCASE("Removing an element") {
//        vec.pop_back();
//        CHECK(vec.size() == 5);
//        CHECK(vec.back() == 5);
//    }
//}

//int square(int x) {
//    return x * x;
//}
//
//TEST_CASE("Tesing the square function") {
//    int inputs[] = { 0, 1, 2, 3, 4 };
//    int expected[] = { 0, 1, 4, 9, 16 };
//
//    for (int i = 0; i < 5; ++i) {
//        CAPTURE(inputs[i]); 
//        CHECK(square(inputs[i]) == expected[i]);
//    }
//}

//#include <stdexcept>
//
//void throw_if_negarive(int x) {
//    if (x < 0) {
//        throw std::runtime_error("negative value");
//    }
//}
//
//TEST_CASE("Tesing exception throwing") {
//    CHECK_NOTHROW(throw_if_negarive(1));
//    CHECK_THROWS(throw_if_negarive(-1));
//    CHECH_THROWS_AS(throw_if_negarive(-1), std::runtime_error);
//}

TEST_CASE("Testing with custom messages") {
    int a = 5;
    int b = 10;
    CHECK_MESSAGE(a + b == 15, "ожидается сумма 15" << (a + b));
}

TEST_CASE("This test is skipped") {
    SKIP("not implemented yet");
    CHECK(1 == 2);
}

