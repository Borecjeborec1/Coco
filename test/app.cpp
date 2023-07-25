
// All includes goes here

#include <iostream>
#include <string>
#include <cmath>

class JSValue {
public:
  virtual ~JSValue() {}
  virtual std::string toString() const = 0;
};

class JSBool : public JSValue {
private:
  bool value;

public:
  JSBool(bool val) : value(val) {}

  std::string toString() const override { return value ? "true" : "false"; }

  JSBool operator!() const { return JSBool(!value); }

  JSBool operator==(const JSBool &other) const {
    return JSBool(value == other.value);
  }

  JSBool operator&&(const JSBool &other) const {
    return JSBool(value && other.value);
  }

  JSBool operator||(const JSBool &other) const {
    return JSBool(value || other.value);
  }
};

class JSNumber : public JSValue {
private:
  double value;

public:
  JSNumber(double val) : value(val) {}

  std::string toString() const override { return std::to_string(value); }

  // METHODS
  JSString toExponential(int fractionDigits) const {
    return JSString(std::to_string(value) + "e" +
                    std::to_string(fractionDigits));
  }

  JSString toFixed(int fractionDigits) const {
    std::string format = "%." + std::to_string(fractionDigits) + "f";
    char buffer[50];
    std::sprintf(buffer, format.c_str(), value);
    return JSString(buffer);
  }

  JSString toPrecision(int precision) const {
    std::string format = "%." + std::to_string(precision) + "g";
    char buffer[50];
    std::sprintf(buffer, format.c_str(), value);
    return JSString(buffer);
  }

  JSNumber valueOf() const { return *this; }

  // OPERATORS
  JSNumber operator++() {
    ++value;
    return *this;
  }

  JSNumber operator++(int) {
    JSNumber old(*this);
    ++value;
    return old;
  }

  JSNumber operator--() {
    --value;
    return *this;
  }

  JSNumber operator--(int) {
    JSNumber old(*this);
    --value;
    return old;
  }

  JSNumber operator+(const JSNumber &other) const {
    return JSNumber(value + other.value);
  }

  JSNumber operator-(const JSNumber &other) const {
    return JSNumber(value - other.value);
  }

  JSNumber operator*(const JSNumber &other) const {
    return JSNumber(value * other.value);
  }

  JSNumber operator/(const JSNumber &other) const {
    if (other.value != 0)
      return JSNumber(value / other.value);
    else
      throw std::runtime_error("Division by zero");
  }

  JSNumber operator^(const JSNumber &other) const {
    return JSNumber(std::pow(value, other.value));
  }

  JSBool operator==(const JSNumber &other) const {
    return JSBool(value == other.value);
  }

  JSBool operator!=(const JSNumber &other) const {
    return JSBool(value != other.value);
  }

  JSBool operator<(const JSNumber &other) const {
    return JSBool(value < other.value);
  }

  JSBool operator<=(const JSNumber &other) const {
    return JSBool(value <= other.value);
  }

  JSBool operator>(const JSNumber &other) const {
    return JSBool(value > other.value);
  }

  JSBool operator>=(const JSNumber &other) const {
    return JSBool(value >= other.value);
  }

  JSNumber operator%(const JSNumber &other) const {
    if (other.value != 0)
      return JSNumber(std::fmod(value, other.value));
    else
      throw std::runtime_error("Modulo by zero");
  }
};

class JSString : public JSValue {
private:
  std::string value;

public:
  JSString(const std::string &val) : value(val) {}

  std::string toString() const override { return value; }

  // OPERATORS
  JSString operator+(const JSString &other) const {
    return JSString(value + other.value);
  }
  JSBool operator==(const JSString &other) const {
    return JSBool(value == other.value);
  }
  JSBool operator!=(const JSString &other) const {
    return JSBool(value != other.value);
  }

  // METHODS
  // TODO: USE JSTypes or int/string/bool???
  // TODO: STRING SEARCH METHODS
  JSNumber length() const { return JSNumber(value.length()); }

  JSString slice(int start, int end) const {
    return JSString(value.substr(start, end));
  }

  JSString substring(int start, int end) const {
    int len = value.length();
    if (start < 0)
      start = 0;
    if (end < 0 || end > len)
      end = len;
    if (start > end)
      std::swap(start, end);
    return JSString(value.substr(start, end - start));
  }

  JSString substr(int start, int length) const {
    return JSString(value.substr(start, length));
  }

  JSString replace(const std::string &search,
                   const std::string &replacement) const {
    std::string result = value;
    size_t pos = 0;
    while ((pos = result.find(search, pos)) != std::string::npos) {
      result.replace(pos, search.length(), replacement);
      pos += replacement.length();
    }
    return JSString(result);
  }

  JSString replaceAll(const std::string &search,
                      const std::string &replacement) const {
    std::string result = value;
    size_t pos = 0;
    while ((pos = result.find(search, pos)) != std::string::npos) {
      result.replace(pos, search.length(), replacement);
      pos += replacement.length();
    }
    return JSString(result);
  }

  JSString toUpperCase() const {
    std::string result = value;
    for (char &c : result)
      c = std::toupper(c);
    return JSString(result);
  }

  JSString toLowerCase() const {
    std::string result = value;
    for (char &c : result)
      c = std::tolower(c);
    return JSString(result);
  }

  JSString concat(const JSString &other) const {
    return JSString(value + other.value);
  }

  JSString trim() const {
    std::string result = value;
    size_t start = result.find_first_not_of(" \t\r\n");
    size_t end = result.find_last_not_of(" \t\r\n");
    if (start == std::string::npos || end == std::string::npos)
      return JSString("");
    return JSString(result.substr(start, end - start + 1));
  }

  JSString trimStart() const {
    std::string result = value;
    size_t start = result.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
      return JSString("");
    return JSString(result.substr(start));
  }

  JSString trimEnd() const {
    std::string result = value;
    size_t end = result.find_last_not_of(" \t\r\n");
    if (end == std::string::npos)
      return JSString("");
    return JSString(result.substr(0, end + 1));
  }

  // TODO: PAD START AND PAD END IMPLEMENTATION
  JSString charAt(int index) const {
    if (index >= 0 && index < value.length())
      return JSString(std::string(1, value[index]));
    else
      throw std::out_of_range("Index out of range");
  }

  JSNumber charCodeAt(int index) const {
    if (index >= 0 && index < value.length())
      return JSNumber(static_cast<int>(value[index]));
    else
      throw std::out_of_range("Index out of range");
  }

  // std::vector<JSString> split(const std::string& delimiter) const {
  //     std::vector<JSString> result;
  //     size_t start = 0;
  //     size_t end = 0;
  //     while ((end = value.find(delimiter, start)) != std::string::npos) {
  //         result.push_back(JSString(value.substr(start, end - start)));
  //         start = end + delimiter.length();
  //     }
  //     result.push_back(JSString(value.substr(start)));
  //     return result;
  // }
};

// All functions with its argument templates goes here

// Main Function (Have to be the only main function)
int main() {
  auto a = std::vector<double>{JSNumber(1), JSString("test")};

  std::cout << a.toString() << std::endl;
  return 0;
}
