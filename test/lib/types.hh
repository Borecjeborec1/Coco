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

  JSString toFixed(int fractionDigits) const;
  JSString toPrecision(int precision) const;
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

  JSNumber length() const;
  JSString slice(int start, int end) const;
  JSString substring(int start, int end) const;
  JSString substr(int start, int length) const;
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
  JSString charAt(int index) const;
  JSNumber charCodeAt(int index) const;
};

class JSArray : public JSValue {
private:
  std::vector<JSValue *> elements;

public:
  JSArray() {}

  template <typename... Args> JSArray(Args... args) { initialize(args...); }

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

  void push(JSValue *value) { elements.push_back(value); }

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

private:
  // Helper function for initializing the array
  template <typename T, typename... Args> void initialize(T arg, Args... args) {
    push(arg);
    initialize(args...);
  }

  // Base case for the recursive initialization
  void initialize() {}
};

#endif // TYPES_HH
