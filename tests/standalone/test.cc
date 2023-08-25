
// All new includes goes here
#include <iostream>
#include <variant>

#include "json.hpp"

// All JSMethods goes here
#include <string>
#include "nlohmann-json.hpp"

class JSON {
public:
  static std::string stringify(const nlohmann::json &jsonObj) {
    return jsonObj.dump();
  }

  static nlohmann::json parse(const std::string &jsonString) {
    return nlohmann::json::parse(jsonString);
  }
};

#include <string>
#include <cmath>
#include <vector>

/////////////////////////// GROUPED METHODS ///////////////////////////////
template <typename valueOfTemplate>
valueOfTemplate JS_valueOf(valueOfTemplate value) {
  return value;
}
/////////////////////////// GROUPED METHODS END ///////////////////////////////

/////////////////////////// BOOLEAN METHODS ///////////////////////////////
std::string JS_toString(bool value) { return value ? "true" : "false"; }
/////////////////////////// BOOLEAN METHODS END ///////////////////////////////

/////////////////////////// NUMBER METHODS ///////////////////////////////
// Function to convert a number to a fixed-point notation string with the
// specified decimal places
std::string JS_toFixed(double value, int decimalPlaces) {
  std::string format = "%." + std::to_string(decimalPlaces) + "f";
  char buffer[100];
  std::sprintf(buffer, format.c_str(), value);
  return buffer;
}

// Function to convert a number to exponential notation with the specified
// number of decimal places
std::string JS_toExponential(double value, int decimalPlaces) {
  std::string format = "%." + std::to_string(decimalPlaces) + "e";
  char buffer[100];
  std::sprintf(buffer, format.c_str(), value);
  return buffer;
}

// Function to convert a number to a string representation with the specified
// radix
std::string JS_toString(double value) { return std::to_string(value); }

// Function to convert a number to a localized string representation
std::string JS_toLocaleString(double value) {
  // Implementation of localized string representation is beyond the scope of
  // this example
  // You may need to implement your own logic based on the desired locale
  return std::to_string(value);
}

// Function to check if a number is finite
bool JS_isFinite(double value) { return std::isfinite(value); }

// Function to check if a number is NaN (Not-a-Number)
bool JS_isNaN(double value) { return std::isnan(value); }

// Function to parse an integer from a string with the specified radix
int JS_parseInt(const std::string &str, int radix) {
  // Implementation of parseInt is beyond the scope of this example
  // You may need to implement your own parsing logic here
  return std::stoi(str, nullptr, radix);
}

// Function to parse a floating-point number from a string
double JS_parseFloat(const std::string &str) {
  // Implementation of parseFloat is beyond the scope of this example
  // You may need to implement your own parsing logic here
  return std::stod(str);
}
/////////////////////////// NUMBER METHODS END ///////////////////////////////

/////////////////////////// STRING METHODS ///////////////////////////////
std::string JS_charAt(const std::string &str, int index) {
  if (index >= 0 && index < str.length()) {
    return str.substr(index, 1);
  }
  return "";
}

int JS_charCodeAt(const std::string &str, int index) {
  if (index >= 0 && index < str.length()) {
    return static_cast<int>(str[index]);
  }
  return 0;
}

std::string JS_concat(const std::vector<std::string> &args) {
  std::string result;
  for (const std::string &arg : args) {
    result += arg;
  }
  return result;
}

bool JS_includes(const std::string &str, const std::string &searchStr) {
  return str.find(searchStr) != std::string::npos;
}

bool JS_endsWith(const std::string &str, const std::string &searchStr) {
  if (str.length() < searchStr.length()) {
    return false;
  }
  return str.compare(str.length() - searchStr.length(), searchStr.length(),
                     searchStr) == 0;
}

int JS_indexOf(const std::string &str, const std::string &searchStr) {
  size_t pos = str.find(searchStr);
  if (pos != std::string::npos) {
    return static_cast<int>(pos);
  }
  return -1;
}

int JS_lastIndexOf(const std::string &str, const std::string &searchStr) {
  size_t pos = str.rfind(searchStr);
  if (pos != std::string::npos) {
    return static_cast<int>(pos);
  }
  return -1;
}

int JS_localeCompare(const std::string &str1, const std::string &str2) {
  // Implementation may vary based on the desired locale comparison rules
  return str1.compare(str2);
}

std::vector<std::string> JS_match(const std::string &str,
                                  const std::string &regexStr) {
  // Implementation for matching regex in a string
  // (You may use regex libraries for this)
  return std::vector<std::string>(); // Placeholder return value
}

std::vector<std::vector<std::string>> JS_matchAll(const std::string &str,
                                                  const std::string &regexStr) {
  // Implementation for matching all occurrences of a regex in a string
  // (You may use regex libraries for this)
  return std::vector<std::vector<std::string>>(); // Placeholder return value
}

std::string JS_normalize(const std::string &str) {
  // Implementation for normalizing Unicode strings (NFC normalization)
  // (You may use Unicode normalization libraries for this)
  return str; // Placeholder return value
}

std::string JS_padEnd(const std::string &str, int targetLength,
                      const std::string &padString) {
  if (targetLength <= str.length()) {
    return str;
  }
  int remainingLength = targetLength - str.length();
  int padCount = remainingLength / padString.length();
  int padRemainder = remainingLength % padString.length();
  std::string result = str;
  for (int i = 0; i < padCount; i++) {
    result += padString;
  }
  if (padRemainder > 0) {
    result += padString.substr(0, padRemainder);
  }
  return result;
}

std::string JS_padStart(const std::string &str, int targetLength,
                        const std::string &padString) {
  if (targetLength <= str.length()) {
    return str;
  }
  int remainingLength = targetLength - str.length();
  int padCount = remainingLength / padString.length();
  int padRemainder = remainingLength % padString.length();
  std::string result;
  for (int i = 0; i < padCount; i++) {
    result += padString;
  }
  if (padRemainder > 0) {
    result += padString.substr(0, padRemainder);
  }
  result += str;
  return result;
}

std::string JS_repeat(const std::string &str, int count) {
  if (count <= 0) {
    return "";
  }
  std::string result;
  for (int i = 0; i < count; i++) {
    result += str;
  }
  return result;
}

std::string JS_replace(const std::string &str, const std::string &searchValue,
                       const std::string &replaceValue) {
  // Implementation for replacing occurrences of a substring with another string
  // (You may use string replacement functions for this)
  return str; // Placeholder return value
}

int JS_search(const std::string &str, const std::string &regexStr) {
  // Implementation for searching a regex in a string
  // (You may use regex libraries for this)
  return -1; // Placeholder return value
}

std::string JS_slice(const std::string &str, int start, int end) {
  if (start < 0) {
    start += str.length();
  }
  if (end < 0) {
    end += str.length();
  }
  if (start < 0) {
    start = 0;
  }
  if (end > str.length()) {
    end = str.length();
  }
  if (end <= start) {
    return "";
  }
  return str.substr(start, end - start);
}

std::vector<std::string> JS_split(const std::string &str,
                                  const std::string &separator) {
  // Implementation for splitting a string into an array of substrings
  // (You may use string split functions for this)
  return std::vector<std::string>(); // Placeholder return value
}

bool JS_startsWith(const std::string &str, const std::string &searchStr) {
  if (str.length() < searchStr.length()) {
    return false;
  }
  return str.compare(0, searchStr.length(), searchStr) == 0;
}

std::string JS_substr(const std::string &str, int start, int length) {
  if (start < 0) {
    start += str.length();
  }
  if (length <= 0 || start >= str.length()) {
    return "";
  }
  if (start + length > str.length()) {
    length = str.length() - start;
  }
  return str.substr(start, length);
}

std::string JS_substring(const std::string &str, int start, int end) {
  if (start < 0) {
    start = 0;
  }
  if (end < 0) {
    end = 0;
  }
  if (start > end) {
    std::swap(start, end);
  }
  if (end > str.length()) {
    end = str.length();
  }
  return str.substr(start, end - start);
}

std::string JS_toLocaleLowerCase(const std::string &str) {
  // Implementation for converting a string to locale-specific lower case
  // (You may use locale-specific case conversion functions for this)
  return str; // Placeholder return value
}

std::string JS_toLocaleUpperCase(const std::string &str) {
  // Implementation for converting a string to locale-specific upper case
  // (You may use locale-specific case conversion functions for this)
  return str; // Placeholder return value
}

std::string JS_toLowerCase(const std::string &str) {
  // Implementation for converting a string to lower case
  // (You may use case conversion functions for this)
  return str; // Placeholder return value
}

std::string JS_toUpperCase(const std::string &str) {
  // Implementation for converting a string to upper case
  // (You may use case conversion functions for this)
  return str; // Placeholder return value
}

std::string JS_toString(const std::string &str) { return str; }

std::string JS_trim(const std::string &str) {
  // Implementation for trimming leading and trailing whitespaces from a string
  // (You may use trim functions for this)
  return str; // Placeholder return value
}

std::string JS_trimEnd(const std::string &str) {
  // Implementation for trimming trailing whitespaces from a string
  // (You may use trim functions for this)
  return str; // Placeholder return value
}

std::string JS_trimStart(const std::string &str) {
  // Implementation for trimming leading whitespaces from a string
  // (You may use trim functions for this)
  return str; // Placeholder return value
}
/////////////////////////// STRING METHODS END ///////////////////////////////

// All functions with its argument templates goes here
template <typename ipdr, typename nrku> auto add(ipdr a, nrku b) {
  return (a + b);
};

// Main Function (Have to be the only main function)
int main() {
  auto x = static_cast<double>(21);

  auto y = static_cast<double>(12);

  auto ydas = std::variant<double, std::string>("test");
  ydas = 21;
  auto ydasd = nlohmann::json{static_cast<double>(23), std::string("dsa")};

  auto z = add(x, y);

  auto obj =
      nlohmann::json{{"x", static_cast<double>(12)}, {"y", std::string("231")}};

  auto num = static_cast<double>(123);
  auto xyz = static_cast<double>(0) - static_cast<double>(42);
  std::cout << xyz;
  auto add = [](auto a, auto b) { return a + b; };

  std::cout << add(x, y);

  return 0;
}
