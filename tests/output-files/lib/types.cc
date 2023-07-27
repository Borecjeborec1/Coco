#include "types.hh"
JSString JSNumber::toFixed(JSNumber fractionDigits) const {
  std::string format = "%." + fractionDigits.toString() + "f";
  char buffer[50];
  std::sprintf(buffer, format.c_str(), value);
  return JSString(buffer);
}

JSString JSNumber::toPrecision(JSNumber precision) const {
  std::string format = "%." + precision.toString() + "g";
  char buffer[50];
  std::sprintf(buffer, format.c_str(), value);
  return JSString(buffer);
}

JSNumber JSNumber::valueOf() const { return *this; }

JSNumber JSNumber::operator++() {
  ++value;
  return *this;
}

JSNumber JSNumber::operator++(int) {
  JSNumber old(*this);
  ++value;
  return old;
}

JSNumber JSNumber::operator--() {
  --value;
  return *this;
}

JSNumber JSNumber::operator--(int) {
  JSNumber old(*this);
  --value;
  return old;
}

JSNumber JSNumber::operator+(const JSNumber &other) const {
  return JSNumber(value + other.value);
}

JSNumber JSNumber::operator-(const JSNumber &other) const {
  return JSNumber(value - other.value);
}

JSNumber JSNumber::operator*(const JSNumber &other) const {
  return JSNumber(value * other.value);
}

JSNumber JSNumber::operator/(const JSNumber &other) const {
  if (other.value != 0)
    return JSNumber(value / other.value);
  else
    throw std::runtime_error("Division by zero");
}

JSNumber JSNumber::operator^(const JSNumber &other) const {
  return JSNumber(std::pow(value, other.value));
}

bool JSNumber::operator==(const JSNumber &other) const {
  return value == other.value;
}

bool JSNumber::operator!=(const JSNumber &other) const {
  return value != other.value;
}

bool JSNumber::operator<(const JSNumber &other) const {
  return value < other.value;
}

bool JSNumber::operator<=(const JSNumber &other) const {
  return value <= other.value;
}

bool JSNumber::operator>(const JSNumber &other) const {
  return value > other.value;
}

bool JSNumber::operator>=(const JSNumber &other) const {
  return value >= other.value;
}

JSNumber JSNumber::operator%(const JSNumber &other) const {
  if (other.value != 0)
    return JSNumber(std::fmod(value, other.value));
  else
    throw std::runtime_error("Modulo by zero");
}

JSString JSString::operator+(const JSString &other) const {
  return JSString(value + other.value);
}

bool JSString::operator==(const JSString &other) const {
  return value == other.value;
}

bool JSString::operator!=(const JSString &other) const {
  return value != other.value;
}

JSString JSString::operator[](const JSNumber &index) const {
  int idx = static_cast<int>(index.toDouble());
  if (idx >= 0 && idx < value.length())
    return JSString(std::string(1, value[idx]));
  else
    throw std::out_of_range("Index out of range");
}

JSString JSString::slice(JSNumber start, JSNumber end) const {
  return JSString(value.substr(start.toDouble(), end.toDouble()));
}

JSString JSString::substring(JSNumber start_JSTYPE, JSNumber end_JSTYPE) const {
  double start = start_JSTYPE.toDouble();
  double end = end_JSTYPE.toDouble();
  double len = value.length();
  if (start < 0)
    start = 0;
  if (end < 0 || end > len)
    end = len;
  if (start > end)
    std::swap(start, end);
  return JSString(value.substr(start, end - start));
}

JSString JSString::substr(JSNumber start, JSNumber length) const {
  return JSString(value.substr(start.toDouble(), length.toDouble()));
}

JSString JSString::replace(const std::string &search,
                           const std::string &replacement) const {
  std::string result = value;
  size_t pos = 0;
  while ((pos = result.find(search, pos)) != std::string::npos) {
    result.replace(pos, search.length(), replacement);
    pos += replacement.length();
  }
  return JSString(result);
}

JSString JSString::replaceAll(const std::string &search,
                              const std::string &replacement) const {
  std::string result = value;
  size_t pos = 0;
  while ((pos = result.find(search, pos)) != std::string::npos) {
    result.replace(pos, search.length(), replacement);
    pos += replacement.length();
  }
  return JSString(result);
}

JSString JSString::toUpperCase() const {
  std::string result = value;
  for (char &c : result)
    c = std::toupper(c);
  return JSString(result);
}

JSString JSString::toLowerCase() const {
  std::string result = value;
  for (char &c : result)
    c = std::tolower(c);
  return JSString(result);
}

JSString JSString::concat(const JSString &other) const {
  return JSString(value + other.value);
}

JSString JSString::trim() const {
  std::string result = value;
  size_t start = result.find_first_not_of(" \t\r\n");
  size_t end = result.find_last_not_of(" \t\r\n");
  if (start == std::string::npos || end == std::string::npos)
    return JSString("");
  return JSString(result.substr(start, end - start + 1));
}

JSString JSString::trimStart() const {
  std::string result = value;
  size_t start = result.find_first_not_of(" \t\r\n");
  if (start == std::string::npos)
    return JSString("");
  return JSString(result.substr(start));
}

JSString JSString::trimEnd() const {
  std::string result = value;
  size_t end = result.find_last_not_of(" \t\r\n");
  if (end == std::string::npos)
    return JSString("");
  return JSString(result.substr(0, end + 1));
}

JSString JSString::charAt(JSNumber index) const {
  if (index >= 0 && index < value.length())
    return JSString(std::string(1, value[index.toDouble()]));
  else
    throw std::out_of_range("Index out of range");
}

JSNumber JSString::charCodeAt(JSNumber index) const {

  if (index >= 0 && index < value.length())
    return JSNumber(static_cast<JSNumber>(value[index.toDouble()]));
  else
    throw std::out_of_range("Index out of range");
}

bool JSString::includes(const JSString &substring) const {
  return value.find(substring.toString()) != std::string::npos;
}