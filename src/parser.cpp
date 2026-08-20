#include "parser.hpp"

#include <sstream>

namespace {

bool is_valid_method(const std::string& method) {
  return method == "GET" || method == "POST" || method == "PUT" ||
         method == "DELETE" || method == "PATCH";
}

}

std::optional<LogEntry> Parser::parse(const std::string& line) const {
  std::istringstream stream(line);

  LogEntry entry;

  if (!(stream >> entry.timestamp >> entry.method >> entry.endpoint >>
        entry.status >> entry.latency_ms)) {
    return std::nullopt;
  }
  if (!stream.eof()) {
    return std::nullopt;
  }

  if (!is_valid_method(entry.method)) {
    return std::nullopt;
  }
  if (entry.status < 100 || entry.status > 599) {
    return std::nullopt;
  }
  if (entry.latency_ms < 0) {
    return std::nullopt;
  }

  return entry;
}