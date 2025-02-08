#pragma once
#include "mytest.hpp"

namespace mytest {
    extern std::vector<TestCase> test_registry;
    extern std::vector<std::string> subcase_stack;

    void print_failure_message(const char* expr, const char* file, int line, const std::string& message);
    void run_all_tests();
}
