#include "types.hh"

JSNumber::JSNumber(double val) : value(val) {}

std::string JSNumber::toString() const { return std::to_string(value); }

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
