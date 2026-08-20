#pragma once

#include "analyzer.hpp"

#include <string>

class Report {
public:
    static std::string render(
        const std::string& filename,
        const Analysis& analysis
    );
};