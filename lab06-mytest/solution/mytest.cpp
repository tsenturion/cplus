#include "mytest.hpp"
#include "mytest_internal.hpp"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace mytest {
    vector<TestCase> test_registry;
    vector<std::string> subcase_stack;
    bool test_failed = false;

    TestRegister::TestRegister(TestFunction func, const std::string& name) {
        test_registry.emplace_back(name, func);
    }

void print_failure_message(const char* expr, const char* file, int line, const std::string& message) {
        printf("CHECK(%s) at %s:%d failed\n", expr, file, line);
        
        if (!message.empty()) {
            printf("message: %s\n", message.c_str());
        }
        for (const auto& subcase : subcase_stack) {
            printf("in subcase %s\n", subcase.c_str());
        }
        test_failed = true;
    }

    SubcaseGuard::SubcaseGuard(const std::string& name) {
        subcase_stack.push_back(name);
    }

    SubcaseGuard::~SubcaseGuard() {
        subcase_stack.pop_back();
    }

    void run_all_tests() {
        int total_tests = test_registry.size();
        int passed_tests = 0;

        for (const auto& test : test_registry) {
            test_failed = false;
            printf("Running \"%s\"...\n", test.name.c_str());
            test.func();

            if (!test_failed) {
                passed_tests++;
            }
        }

        printf("===== Tests passed: %d/%d =====\n", passed_tests, total_tests);
    }
}
