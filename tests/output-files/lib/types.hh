#ifndef TYPES_HH
#define TYPES_HH

#include <string>
#include <vector>
#include <cctype>
#include <regex>
#include <cmath>

class JSString;
class JSArray;

class JSValue {
public:
  virtual ~JSValue() {}
  virtual std::string toString() const = 0;
};

class JSNumber : public JSValue {
private:
  double value;

public:
  JSNumber(double val);

  std::string toString() const override;

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
  double toDouble() const { return value; }
};

class JSString : public JSValue {
private:
  std::string value;
  JSNumber _length;

public:
  JSString(const std::string &val);
  std::string toString() const override;

  JSString operator+(const JSString &other) const;
  bool operator==(const JSString &other) const;
  bool operator!=(const JSString &other) const;
  JSString operator[](const JSNumber &index) const;

  const JSNumber &length = _length;
  JSString slice(JSNumber start, JSNumber end) const;
  JSString substring(JSNumber start, JSNumber end) const;
  JSString substr(JSNumber start, JSNumber length) const;
  JSString replace(const JSString &search, const JSString &replacement) const;
  JSString replaceAll(const JSString &search,
                      const JSString &replacement) const;
  JSString toUpperCase() const;
  JSString toLowerCase() const;
  JSString concat(const JSString &other) const;
  JSString trim() const;
  JSString trimStart() const;
  JSString trimEnd() const;
  JSString charAt(JSNumber index) const;
  JSNumber charCodeAt(JSNumber index) const;
  bool includes(const JSString &substring) const;
  bool startsWith(const JSString &searchString) const;
  bool endsWith(const JSString &searchString) const;
  JSArray split(const JSString &separator) const;
  JSNumber indexOf(const JSString &searchValue) const;
  JSNumber lastIndexOf(const JSString &searchValue) const;
  JSString padStart(JSNumber targetLength, const JSString &padString) const;
  JSString padEnd(JSNumber targetLength, const JSString &padString) const;
  JSArray match(const JSString &regexp) const;
  JSNumber search(const JSString &regexp) const;
};

class JSArray : public JSValue {
private:
  std::vector<JSValue *> elements;

public:
  JSArray() {}
  template <typename T> JSArray(T value) { push(value); }
  ~JSArray() {
    for (JSValue *value : elements) {
      delete value;
    }
  };

  std::string toString() const override;
  void pop();
  JSNumber size() const;

  void push(const JSString &value);
  void push(const JSNumber &value);
  void push(const std::string &value);
  void push(const double value);
};

#endif // TYPES_HH
