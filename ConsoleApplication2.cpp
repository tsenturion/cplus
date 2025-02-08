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

int square(int x) {
    return x * x;
}

TEST_CASE("Tesing the square function") {
    int inputs[] = { 0, 1, 2, 3, 4 };
    int expected[] = { 0, 1, 4, 9, 16 };

    for (int i = 0; i < 5; ++i) {
        CAPTURE(inputs[i]); 
        CHECK(square(inputs[i]) == expected[i]);
    }
}

