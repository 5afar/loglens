#pragma once

#include "parser.hpp"

#include <map>
#include <string>
#include <vector>

struct Analysis {
    long long total_requests{};
    long long errors{};

    std::map<int, long long> status_codes;
    std::map<std::string, long long> endpoints;

    std::vector<long long> latencies;
};

class Analyzer {
public:
    void add(const LogEntry& entry);

    [[nodiscard]]
    Analysis result() const;

private:
    Analysis analysis_;
};