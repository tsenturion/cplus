#include "mytest.hpp"
#include "mytest_internal.hpp"

#include <iostream>
#include <vector>
#include <string>

namespace mytest {
    std::vector<TestCase> test_registry;
    std::vector<std::string> subcase_stack;
    bool test_failed = false;

    TestRegistrar::TestRegistrar(TestFunction func, const std::string& name) {
        test_registry.emplace_back(name, func);
    }

    void print_failure_message(const char* expr, const char* file, int line, const std::string& message) {
        std::cerr << "CHECK(" << expr << ") at " << file << ":" << line << " failed!\n";
        if (!message.empty()) {
            std::cerr << "    message: " << message << "\n";
        }
        for (const auto& subcase : subcase_stack) {
            std::cerr << "    in subcase " << subcase << "\n";
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
            std::cerr << "Running \"" << test.name << "\"...\n";
            test.func();
            if (!test_failed) {
                passed_tests++;
            }
        }

        std::cerr << "===== Tests passed: " << passed_tests << "/" << total_tests << " =====\n";
    }
}
