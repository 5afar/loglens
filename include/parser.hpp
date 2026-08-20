#pragma once

#include <string>
#include <optional>

struct LogEntry {
    std::string timestamp;
    std::string method;
    std::string endpoint;

    int status{};
    long long latency_ms{};
};

class Parser {
public:
    std::optional<LogEntry> parse(const std::string& line) const;
};