//https://github.com/doctest/doctest 
//https://code-basics.com/ru/languages/clang - посмотреть на разные
//https://huggingface.co/ - нейронки
//https://chat.deepseek.com/ - без vpn
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

//#include <iostream>
#include <doctesh.h>

//int main()
//{
//
//    std::cout << "Hello World!\n";
//}

int add(int a, int b) {
    return a + b;
}

TEST_CASE("Testing the add function") {
    CHECK(add(2, 3) == 5);
    CHECK(add(-1, 1) == 0);
    CHECK(add(0, 0) == 0);
    CHECK(add(-1, -1) == -2);
}

// CHECK без прерывания
// REQUIRE с прерыванием

//TEST_CASE("Testing with fixtures") {
//    int a = 5;
//    int b = 10;
//
//    SUBCASE("Check addition") {
//        CHECK(add(a, b) == 15);
//    }
//
//    SUBCASE("Chech subtration") {
//        CHESK(add(a, b) == -5)
//    }
//}

//TEST_CASE_FIXTURE 