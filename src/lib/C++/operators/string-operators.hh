// Ignore imports
#include <string>
// Ignore imports end

std::string operator+(const double &lhs, const std::string &rhs)
{
  return std::string(std::to_string(lhs)) + rhs;
}

std::string operator+(const std::string &lhs, const double &rhs)
{
  return lhs + std::string(std::to_string(rhs));
}

bool operator==(const double &lhs, const std::string &rhs)
{
  return std::string(std::to_string(lhs)) == rhs;
}

bool operator==(const std::string &lhs, const double &rhs)
{
  return lhs == std::string(std::to_string(rhs));
}

bool operator<(const std::string &lhs, const double &rhs)
{
  return false;
}

bool operator>(const std::string &lhs, const double &rhs)
{
  return false;
}
