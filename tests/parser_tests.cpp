/*
Parser принимает строку формата:

timestamp method endpoint status latency_ms

При этом:

1. Все пять полей обязательны.
2. Дополнительные поля запрещены.
3. method должен быть GET, POST, PUT, DELETE или PATCH.
4. status должен находиться в диапазоне 100..599.
5. latency_ms не может быть отрицательным.
6. При валидной строке возвращается LogEntry.
7. При невалидной строке возвращается std::nullopt.

2026-08-18T12:41:23 GET /api/users 200 42

timestamp  = "2026-08-18T12:41:23"
method     = "GET"
endpoint   = "/api/users"
status     = 200
latency_ms = 42
*/
#include "parser.hpp"

#include <gtest/gtest.h>

TEST(ParserTest, ParsesValidLogEntry) {
    Parser parser;

    const auto result =
        parser.parse("2026-08-18T12:41:23 GET /api/users 200 42");

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result->timestamp, "2026-08-18T12:41:23");
    EXPECT_EQ(result->method, "GET");
    EXPECT_EQ(result->endpoint, "/api/users");
    EXPECT_EQ(result->status, 200);
    EXPECT_EQ(result->latency_ms, 42);
}
TEST(ParserTest, RejectsLogEntryWithoutLatency) {
    Parser parser;

    const auto result =
        parser.parse("2026-08-18T12:41:23 GET /api/users 200");

    EXPECT_FALSE(result.has_value());
}


class ValidMethodTest : public ::testing::TestWithParam<std::string> {
};

TEST_P(ValidMethodTest, AcceptsValidMethod) {
    Parser parser;

    const std::string method = GetParam();

    const auto result =
        parser.parse("2026-08-18T12:41:23 " + method + " /api/users 200 42");

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->method, method);
}

INSTANTIATE_TEST_SUITE_P(
    ValidMethods,
    ValidMethodTest,
    ::testing::Values(
        "GET",
        "POST",
        "PUT",
        "DELETE",
        "PATCH"
    )
);


class InvalidMethodTest : public ::testing::TestWithParam<std::string> {
};

TEST_P(InvalidMethodTest, RejectsInvalidMethod) {
    Parser parser;

    const std::string method = GetParam();

    const auto result =
        parser.parse("2026-08-18T12:41:23 " + method + " /api/users 200 42");

    EXPECT_FALSE(result.has_value());
}

INSTANTIATE_TEST_SUITE_P(
    InvalidMethods,
    InvalidMethodTest,
    ::testing::Values(
        "OPTIONS",
        "HEAD",
        "CONNECT",
        "TRACE",
        "INVALID"
    )
);