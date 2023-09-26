// Ignore imports
#include <string>
#include "../nlohmann-json.hh"
// Ignore imports end

nlohmann::json &operator+=(nlohmann::json &j, int x) {
  if (j.is_number()) {
    j = j.get<int>() + x;
  }
  return j;
}

nlohmann::json &operator-=(nlohmann::json &j, int x) {
  if (j.is_number()) {
    j = j.get<int>() - x;
  }
  return j;
}

nlohmann::json &operator*=(nlohmann::json &j, int x) {
  if (j.is_number()) {
    j = j.get<int>() * x;
  }
  return j;
}

nlohmann::json &operator/=(nlohmann::json &j, int x) {
  if (j.is_number() && x != 0) {
    j = j.get<int>() / x;
  }
  return j;
}

nlohmann::json &operator++(nlohmann::json &j) {
  if (j.is_number()) {
    j = j.get<int>() + 1;
  }
  return j;
}

nlohmann::json &operator--(nlohmann::json &j) {
  if (j.is_number()) {
    j = j.get<int>() - 1;
  }
  return j;
}

nlohmann::json operator+(const nlohmann::json &lhs, const int &rhs) {
  if (lhs.is_number()) {
    return lhs.get<int>() + rhs;
  }
  return nlohmann::json();
}

nlohmann::json operator-(const nlohmann::json &lhs, const int &rhs) {
  if (lhs.is_number()) {
    return lhs.get<int>() - rhs;
  }
  return nlohmann::json();
}

nlohmann::json operator*(const nlohmann::json &lhs, const int &rhs) {
  if (lhs.is_number()) {
    return lhs.get<int>() * rhs;
  }
  return nlohmann::json();
}

nlohmann::json operator%(const nlohmann::json &lhs, const int &rhs) {
  if (lhs.is_number() && rhs != 0) {
    return lhs.get<int>() % rhs;
  }
  return nlohmann::json();
}

nlohmann::json operator/(const nlohmann::json &lhs, int &rhs) {
  if (lhs.is_number() && rhs != 0) {
    return lhs.get<int>() / rhs;
  }
  return nlohmann::json();
}
