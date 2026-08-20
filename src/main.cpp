#include "parser.hpp"

#include <iostream>

void test(Parser& parser, const std::string& line) {
    const auto result = parser.parse(line);

    if (result) {
        std::cout << "VALID:   " << line << '\n';
    } else {
        std::cout << "INVALID: " << line << '\n';
    }
}

int main() {
    Parser parser;

    test(parser,
         "2026-08-18T12:41:23 GET /api/users 200 42");

    test(parser,
         "2026-08-18T12:41:24 POST /api/orders 500 831");

    test(parser,
         "2026-08-18T12:41:25 BANANA /api/users 200 42");

    test(parser,
         "2026-08-18T12:41:26 GET /api/users 200 -10");

    test(parser,
         "2026-08-18T12:41:27 GET /api/users 999 42");

    test(parser,
         "garbage");

    test(parser,
         "2026-08-18T12:41:28 GET /api/users 200 42 garbage");
}