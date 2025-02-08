#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>

namespace mytest {
    using TestFunction = void(*)();

    struct TestCase {
        std::string name;
        TestFunction func;
        TestCase(std::string n, TestFunction f) : name(std::move(n)), func(f) {}
    };

    struct TestRegistrar {
        TestRegistrar(TestFunction func, const std::string& name);
    };
//-------------------------------
    struct SubcaseGuard {
        explicit SubcaseGuard(const std::string& name);
        ~SubcaseGuard();
    };

    extern bool test_failed;
}

#define TEST_CASE(name) \
    static void mytest_##name(); \
    static mytest::TestRegistrar reg_##name(mytest_##name, name); \
    static void mytest_##name()

//-------------------------------
#define CHECK(expr) \
    do { \
        if (!(expr)) { \
            mytest::print_failure_message(#expr, __FILE__, __LINE__, ""); \
        } \
    } while (0)

// Аналог CHECK с сообщением
#define CHECK_MESSAGE(expr, msg) \
    do { \
        if (!(expr)) { \
            mytest::print_failure_message(#expr, __FILE__, __LINE__, msg); \
        } \
    } while (0)

// Макрос для вложенных подслучаев
#define SUBCASE(name) \
    if (mytest::SubcaseGuard mytest_subcase_guard{name}; true)
