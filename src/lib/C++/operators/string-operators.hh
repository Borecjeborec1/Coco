// Ignore imports
#include <string>
// Ignore imports end

std::string operator+(const double &lhs, const std::string &rhs) {
  return std::string(std::to_string(lhs)) + rhs;
}

std::string operator+(const std::string &lhs, const double &rhs) {
  return lhs + std::string(std::to_string(rhs));
}

bool operator==(const double &lhs, const std::string &rhs) {
  return std::string(std::to_string(lhs)) == rhs;
}

bool operator==(const std::string &lhs, const double &rhs) {
  return lhs == std::string(std::to_string(rhs));
}

bool operator<(const std::string &lhs, const double &rhs) { return false; }

bool operator>(const std::string &lhs, const double &rhs) { return false; }

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

bool operator<(const std::string &lhs, const int &rhs) { return false; }

bool operator>(const std::string &lhs, const int &rhs) { return false; }

std::string operator+(const long long &lhs, const std::string &rhs) {
  return std::string(std::to_string(lhs)) + rhs;
}

std::string operator+(const std::string &lhs, const long long &rhs) {
  return lhs + std::string(std::to_string(rhs));
}

bool operator==(const long long &lhs, const std::string &rhs) {
  return std::string(std::to_string(lhs)) == rhs;
}

bool operator==(const std::string &lhs, const long long &rhs) {
  return lhs == std::string(std::to_string(rhs));
}

bool operator<(const std::string &lhs, const long long &rhs) { return false; }

bool operator>(const std::string &lhs, const long long &rhs) { return false; }

std::string operator+(const bool &lhs, const std::string &rhs) {
  return std::string(std::to_string(lhs)) + rhs;
}

std::string operator+(const std::string &lhs, const bool &rhs) {
  return lhs + std::string(std::to_string(rhs));
}

bool operator==(const bool &lhs, const std::string &rhs) {
  return std::string(std::to_string(lhs)) == rhs;
}

bool operator==(const std::string &lhs, const bool &rhs) {
  return lhs == std::string(std::to_string(rhs));
}

bool operator<(const std::string &lhs, const bool &rhs) { return false; }

bool operator>(const std::string &lhs, const bool &rhs) { return false; }
