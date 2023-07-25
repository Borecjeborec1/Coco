#ifndef TYPES_HH
#define TYPES_HH

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

class JSString;

class JSValue {
public:
  virtual ~JSValue() {}
  virtual std::string toString() const = 0;
};

class JSNumber : public JSValue {
private:
  double value;

public:
  JSNumber(double val) : value(val) {}

  std::string toString() const override { return std::to_string(value); }

  JSString toFixed(JSNumber fractionDigits) const;
  JSString toPrecision(JSNumber precision) const;
  JSNumber valueOf() const;

  JSNumber operator++();
  JSNumber operator++(int);
  JSNumber operator--();
  JSNumber operator--(int);
  JSNumber operator+(const JSNumber &other) const;
  JSNumber operator-(const JSNumber &other) const;
  JSNumber operator*(const JSNumber &other) const;
  JSNumber operator/(const JSNumber &other) const;
  JSNumber operator^(const JSNumber &other) const;
  bool operator==(const JSNumber &other) const;
  bool operator!=(const JSNumber &other) const;
  bool operator<(const JSNumber &other) const;
  bool operator<=(const JSNumber &other) const;
  bool operator>(const JSNumber &other) const;
  bool operator>=(const JSNumber &other) const;
  JSNumber operator%(const JSNumber &other) const;
  // Method to parse back to double
  double toDouble() const { return value; }
};

class JSString : public JSValue {
private:
  std::string value;

public:
  JSString(const std::string &val) : value(val) {}

  std::string toString() const override { return value; }

  JSString operator+(const JSString &other) const;
  bool operator==(const JSString &other) const;
  bool operator!=(const JSString &other) const;
  JSString operator[](const JSNumber &index) const;

  JSNumber length() const;
  JSString slice(JSNumber start, JSNumber end) const;
  JSString substring(JSNumber start, JSNumber end) const;
  JSString substr(JSNumber start, JSNumber length) const;
  JSString replace(const std::string &search,
                   const std::string &replacement) const;
  JSString replaceAll(const std::string &search,
                      const std::string &replacement) const;
  JSString toUpperCase() const;
  JSString toLowerCase() const;
  JSString concat(const JSString &other) const;
  JSString trim() const;
  JSString trimStart() const;
  JSString trimEnd() const;
  JSString charAt(JSNumber index) const;
  JSNumber charCodeAt(JSNumber index) const;
};

class JSArray : public JSValue {
private:
  std::vector<JSValue *> elements;

public:
  JSArray() {}

  template <typename... Args> JSArray(Args... args) { (push(args), ...); }

  ~JSArray() {
    // Clean up memory allocated for JSValue objects
    for (JSValue *value : elements) {
      delete value;
    }
  }

  std::string toString() const override {
    std::string result = "[";
    for (size_t i = 0; i < elements.size(); ++i) {
      if (i > 0) {
        result += ", ";
      }
      result += elements[i]->toString();
    }
    result += "]";
    return result;
  }

  template <typename T> void push(const T &value) {
    elements.push_back(new T(value));
  }

  void pop() {
    if (!elements.empty()) {
      delete elements.back();
      elements.pop_back();
    }
  }

  JSValue *get(size_t index) const {
    if (index >= 0 && index < elements.size()) {
      return elements[index];
    } else {
      throw std::out_of_range("Index out of range");
    }
  }

  size_t size() const { return elements.size(); }
};

#endif // TYPES_HH
