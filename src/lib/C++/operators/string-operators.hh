// Ignore imports
#include <string>
// Ignore imports end

std::string operator+(const int &lhs, const std::string &rhs) {
  return std::string(std::to_string(lhs)) + rhs;
}

std::string operator+(const std::string &lhs, const int &rhs) {
  return lhs + std::string(std::to_string(rhs));
}

bool operator==(const int &lhs, const std::string &rhs) {
  return std::string(std::to_string(lhs)) == rhs;
}

bool operator==(const std::string &lhs, const int &rhs) {
  return lhs == std::string(std::to_string(rhs));
}
