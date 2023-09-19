

// All new includes goes here
#include <chrono>
#include "nlohmann-json.hh"

// All Built-in JSMethods goes here
#include <iostream>
#include <sstream>
#include <cmath>
#include <iomanip>

#include <string>

#include <iostream>
#include <limits>
#include <string>
#include <cstdint>
#include <vector>
#include <regex>



bool isFinite(double value) { return std::isfinite(value); }

template <typename T>
bool isNaN(T value)
{
  return std::to_string(value) == std::string("nan") || std::isnan(value);
}

double parseFloat(const std::string &str)
{
  std::istringstream iss(str);
  double result;
  iss >> result;
  return result;
}

double parseInt(const std::string &str, int base = 10)
{
  return std::stoi(str, nullptr, base);
}

std::string toHex(unsigned char value)
{
  std::stringstream ss;
  ss << std::uppercase << std::hex << std::setw(2) << std::setfill('0')
     << static_cast<int>(value);
  return ss.str();
}
char hexToChar(const std::string &hex)
{
  int value;
  std::stringstream ss;
  ss << std::hex << hex;
  ss >> value;
  return static_cast<char>(value);
}

std::string decodeURI(const std::string &uri)
{
  std::string decoded;
  for (size_t i = 0; i < uri.length(); ++i)
  {
    if (uri[i] == '%' && i + 2 < uri.length())
    {
      std::string hex = uri.substr(i + 1, 2);
      decoded += hexToChar(hex);
      i += 2;
    }
    else if (uri[i] == '+')
    {
      decoded += ' ';
    }
    else
    {
      decoded += uri[i];
    }
  }
  return decoded;
}

std::string decodeURIComponent(const std::string &component)
{
  std::string decoded;
  for (size_t i = 0; i < component.length(); ++i)
  {
    if (component[i] == '%' && i + 2 < component.length())
    {
      std::string hex = component.substr(i + 1, 2);
      decoded += hexToChar(hex);
      i += 2;
    }
    else
    {
      decoded += component[i];
    }
  }
  return decoded;
}

std::string encodeURI(const std::string &uri)
{
  std::string encoded;
  for (char c : uri)
  {
    if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
    {
      encoded += c;
    }
    else
    {
      encoded += '%' + toHex(static_cast<unsigned char>(c));
    }
  }
  return encoded;
}

std::string encodeURIComponent(const std::string &component)
{
  std::string encoded;
  for (char c : component)
  {
    if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
    {
      encoded += c;
    }
    else
    {
      encoded += '%' + toHex(static_cast<unsigned char>(c));
    }
  }
  return encoded;
}



class __JSON__
{
public:
  static std::string stringify(const nlohmann::json &jsonObj)
  {
    return jsonObj.dump();
  }

  static nlohmann::json parse(const std::string &jsonString)
  {
    return nlohmann::json::parse(jsonString);
  }
};

#include <iostream>
#include <cmath>
#include <cstdarg>
#include <limits>

class __Math__
{
public:
    static const double E;
    static const double LN10;
    static const double LN2;
    static const double LOG10E;
    static const double LOG2E;
    static const double PI;
    static const double SQRT1_2;
    static const double SQRT2;

    static double abs(double x)
    {
        return std::abs(x);
    }

    static double acos(double x)
    {
        return std::acos(x);
    }

    static double acosh(double x)
    {
        return std::acosh(x);
    }

    static double asin(double x)
    {
        return std::asin(x);
    }

    static double asinh(double x)
    {
        return std::asinh(x);
    }

    static double atan(double x)
    {
        return std::atan(x);
    }

    static double atanh(double x)
    {
        return std::atanh(x);
    }

    static double atan2(double y, double x)
    {
        return std::atan2(y, x);
    }

    static double cbrt(double x)
    {
        return std::cbrt(x);
    }

    static double ceil(double x)
    {
        return std::ceil(x);
    }

    static double cos(double x)
    {
        return std::cos(x);
    }

    static double cosh(double x)
    {
        return std::cosh(x);
    }

    static double exp(double x)
    {
        return std::exp(x);
    }

    static double floor(double x)
    {
        return std::floor(x);
    }

    static double log(double x)
    {
        return std::log(x);
    }

    template <typename T>
    static T min(const T &arg)
    {
        return arg;
    }

    template <typename T>
    static T max(const T &arg)
    {
        return arg;
    }

    template <typename T, typename... Args>
    static T min(const T &first, const Args &...args)
    {
        T rest = min(args...);
        return (first < rest) ? first : rest;
    }

    template <typename T, typename... Args>
    static T max(const T &first, const Args &...args)
    {
        T rest = max(args...);
        return (first > rest) ? first : rest;
    }
    static double pow(double x, double y)
    {
        return std::pow(x, y);
    }

    static double random()
    {
        return (double)rand() / RAND_MAX;
    }

    static double round(double x)
    {
        return std::round(x);
    }

    static int sign(double x)
    {
        if (x < 0)
            return -1;
        if (x > 0)
            return 1;
        return 0;
    }

    static double sin(double x)
    {
        return std::sin(x);
    }

    static double sinh(double x)
    {
        return std::sinh(x);
    }

    static double sqrt(double x)
    {
        return std::sqrt(x);
    }

    static double tan(double x)
    {
        return std::tan(x);
    }

    static double tanh(double x)
    {
        return std::tanh(x);
    }

    static double trunc(double x)
    {
        return (x < 0) ? std::ceil(x) : std::floor(x);
    }
};

const double __Math__::E = 2.718281828459045;
const double __Math__::LN10 = 2.302585092994046;
const double __Math__::LN2 = 0.6931471805599453;
const double __Math__::LOG10E = 0.4342944819032518;
const double __Math__::LOG2E = 1.4426950408889634;
const double __Math__::PI = 3.141592653589793;
const double __Math__::SQRT1_2 = 0.7071067811865476;
const double __Math__::SQRT2 = 1.4142135623730951;



class __Number__
{
public:
    static const double EPSILON;
    static const double MAX_VALUE;
    static const double MIN_VALUE;
    static const double NaN;
    static const double NEGATIVE_INFINITY;
    static const double POSITIVE_INFINITY;
    static const int64_t MAX_SAFE_INTEGER;
    static const int64_t MIN_SAFE_INTEGER;

    __Number__(double value = 0.0) : value_(value) {}

    static double parseFloat(const std::string &str)
    {
        return std::stod(str);
    }

    static int32_t parseInt(const std::string &str, int radix = 10)
    {
        return std::stoi(str, 0, radix);
    }

    static bool isFinite(double num)
    {
        return std::isfinite(num);
    }

    static bool isInteger(double num)
    {
        return std::trunc(num) == num;
    }

    static bool isSafeInteger(double num)
    {
        return isInteger(num) && num >= MIN_SAFE_INTEGER && num <= MAX_SAFE_INTEGER;
    }

    double valueOf() const
    {
        return value_;
    }

    std::string toString() const
    {
        return std::to_string(value_);
    }

    double toPrecision(int precision) const
    {
        if (!std::isfinite(value_) || precision < 1 || precision > 21)
        {
            return value_;
        }
        return std::stod(std::to_string(value_));
    }

    double toFixed(int decimalPlaces) const
    {
        if (!std::isfinite(value_))
        {
            return value_;
        }
        double multiplier = std::pow(10.0, decimalPlaces);
        return std::round(value_ * multiplier) / multiplier;
    }

private:
    double value_;
};

const double __Number__::EPSILON = std::numeric_limits<double>::epsilon();
const double __Number__::MAX_VALUE = std::numeric_limits<double>::max();
const double __Number__::MIN_VALUE = std::numeric_limits<double>::min();
const double __Number__::NaN = std::numeric_limits<double>::quiet_NaN();
const double __Number__::NEGATIVE_INFINITY = -std::numeric_limits<double>::infinity();
const double __Number__::POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
const int64_t __Number__::MAX_SAFE_INTEGER = std::numeric_limits<int64_t>::max();
const int64_t __Number__::MIN_SAFE_INTEGER = std::numeric_limits<int64_t>::min();


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



nlohmann::json JS_concat(const nlohmann::json &arr1,
                         const nlohmann::json &arr2) {
  nlohmann::json result = arr1;
  for (const auto &element : arr2) {
    result.push_back(element);
  }
  return result;
}

nlohmann::json JS_copyWithin(nlohmann::json &arr, int target, int start,
                             int end = INT_MAX) {
  if (!arr.is_array()) {
    throw std::runtime_error("Input is not an array.");
  }

  int length = static_cast<int>(arr.size());

  target =
      (target < 0) ? std::max(length + target, 0) : std::min(target, length);
  start = (start < 0) ? std::max(length + start, 0) : std::min(start, length);
  end = (end < 0) ? std::max(length + end, 0) : std::min(end, length);

  int to = target;
  int from = start;

  while (from < end && to < length) {
    arr[to] = arr[from];
    ++to;
    ++from;
  }
  return arr;
}

nlohmann::json JS_entries(const nlohmann::json &arr) {
  nlohmann::json result;
  int index = 0;
  for (const auto &element : arr) {
    nlohmann::json entry;
    entry.push_back(index);
    entry.push_back(element);
    result.push_back(entry);
    index++;
  }
  return result;
}

bool JS_every(const nlohmann::json &arr, std::function<bool(double)> callback) {
  for (const auto &element : arr) {
    if (!callback(element.get<double>())) {
      return false;
    }
  }
  return true;
}

nlohmann::json JS_fill(nlohmann::json &arr, double value, int start, int end) {
  start = std::max(start, 0);
  end = std::min(end, static_cast<int>(arr.size()));

  for (int i = start; i < end; i++) {
    arr[i] = value;
  }

  return arr;
}

nlohmann::json JS_filter(const nlohmann::json &arr,
                         std::function<bool(double)> callback) {
  nlohmann::json result;
  for (const auto &element : arr) {
    double value = element.get<double>();
    if (callback(value)) {
      result.push_back(value);
    }
  }
  return result;
}

nlohmann::json JS_find(const nlohmann::json &arr,
                       std::function<bool(double)> callback) {
  for (size_t i = 0; i < arr.size(); ++i) {
    double value = static_cast<double>(arr[i]);
    if (callback(value)) {
      return value;
    }
  }
  return nullptr;
}

int JS_findIndex(const nlohmann::json &arr,
                 std::function<bool(double)> callback) {
  for (size_t i = 0; i < arr.size(); ++i) {
    double value = static_cast<double>(arr[i]);
    if (callback(value)) {
      return i;
    }
  }
  return -1;
}

nlohmann::json JS_flat(const nlohmann::json &arr, int depth = 1) {
  if (depth <= 0) {
    return arr;
  }

  nlohmann::json result;
  for (const auto &element : arr) {
    if (element.is_array()) {
      result.insert(result.end(), JS_flat(element, depth - 1).begin(),
                    JS_flat(element, depth - 1).end());
    } else {
      result.push_back(element);
    }
  }
  return result;
}

// nlohmann::json JS_flatMap(const nlohmann::json &arr,
//                           std::function<nlohmann::json(double)> callback) {
//   nlohmann::json result;
//   for (const auto &element : arr) {
//     nlohmann::json mapped = callback(element);
//     if (mapped.is_array()) {
//       result.insert(result.end(), mapped.begin(), mapped.end());
//     } else {
//       result.push_back(mapped);
//     }
//   }
//   return result;
// }

void JS_forEach(const nlohmann::json &arr,
                std::function<void(double)> callback) {
  for (const auto &element : arr) {
    double value = element.get<double>();
    callback(value);
  }
}

template <typename T>
bool JS_includes(const nlohmann::json &arr, const T &searchElement) {
  for (const auto &element : arr) {
    T value = element.get<T>();
    if (value == searchElement) {
      return true;
    }
  }
  return false;
}

template <typename T>
int JS_indexOf(const nlohmann::json &arr, const T &searchElement,
               int fromIndex = 0) {
  fromIndex = std::max(fromIndex, 0);
  for (int i = fromIndex; i < static_cast<int>(arr.size()); i++) {
    T value = arr[i].get<T>();
    if (value == searchElement) {
      return i;
    }
  }
  return -1;
}

bool JS_isArray(const nlohmann::json &arr) { return arr.is_array(); }

std::string JS_join(const nlohmann::json &arr,
                    const std::string &separator = ",") {
  std::string result;
  bool firstElement = true;

  for (const auto &element : arr) {
    if (!firstElement) {
      result += separator;
    }

    if (element.is_string()) {
      result += element.get<std::string>();
    } else {
      result += element.dump();
    }
    firstElement = false;
  }

  return result;
}

nlohmann::json JS_keys(const nlohmann::json &arr) {
  nlohmann::json result;
  for (size_t i = 0; i < arr.size(); i++) {
    result.push_back(static_cast<double>(i));
  }
  return result;
}

int JS_lastIndexOf(const nlohmann::json &arr, double searchElement,
                   int fromIndex = -1) {
  if (fromIndex == -1) {
    fromIndex = static_cast<int>(arr.size()) - 1;
  }
  fromIndex = std::min(fromIndex, static_cast<int>(arr.size()) - 1);
  for (int i = fromIndex; i >= 0; i--) {
    double value = arr[i].get<double>();
    if (value == searchElement) {
      return i;
    }
  }
  return -1;
}

nlohmann::json JS_map(const nlohmann::json &arr,
                      std::function<nlohmann::json(double)> callback) {
  nlohmann::json result;
  for (const auto &element : arr) {
    double value = element.get<double>();
    nlohmann::json mapped = callback(value);
    result.push_back(mapped);
  }
  return result;
}

nlohmann::json JS_pop(nlohmann::json &arr) {
  if (arr.is_array() && !arr.empty()) {
    nlohmann::json popped = arr.back();
    arr.erase(--arr.end());
    return popped;
  }
  return nullptr;
}

template <typename T> T JS_push(nlohmann::json &arr, T element) {
  arr.push_back(element);
  return arr.size();
}

// template <typename Callback>
// nlohmann::json JS_reduce(const nlohmann::json &arr, Callback callback,
//                          const nlohmann::json &initialValue = nullptr) {
//   nlohmann::json accumulator = initialValue ? initialValue : nullptr;
//   double sum = 0;

//   for (const auto &element : arr) {
//     double value = element.get<double>();
//     if (accumulator) {
//       accumulator = callback(accumulator, value);
//     } else {
//       sum += value;
//     }
//   }

//   if (!accumulator) {
//     return sum;
//   }

//   return accumulator;
// }

// // reduceRight()
// nlohmann::json
// JS_reduceRight(const nlohmann::json &arr,
//                std::function<nlohmann::json(nlohmann::json, double)>
//                callback,
//                const nlohmann::json &initialValue = nullptr) {
//   // Convert the reversed JSON array to a vector of JSON values
//   std::vector<nlohmann::json> reversed(arr.rbegin(), arr.rend());

//   // Perform the reduce operation on the reversed vector
//   nlohmann::json result = JS_reduce(reversed, callback, initialValue);

//   return result;
// }

nlohmann::json JS_reverse(nlohmann::json &arr) {
  std::reverse(arr.begin(), arr.end());
  return arr;
}

nlohmann::json JS_shift(nlohmann::json &arr) {
  if (arr.empty()) {
    return nullptr;
  }
  nlohmann::json shifted = arr.front();
  arr.erase(arr.begin());
  return shifted;
}

nlohmann::json JS_slice(const nlohmann::json &arr, int start = 0,
                        int end = INT_MAX) {
  start = std::max(start, 0);
  end = std::min(end, static_cast<int>(arr.size()));

  nlohmann::json result;
  for (int i = start; i < end; i++) {
    result.push_back(arr[i]);
  }
  return result;
}

bool JS_some(const nlohmann::json &arr, std::function<bool(double)> callback) {
  for (const auto &element : arr) {
    double value = element.get<double>();
    if (callback(value)) {
      return true;
    }
  }
  return false;
}

nlohmann::json
JS_sort(nlohmann::json &arr,
        std::function<bool(double, double)> compareFunction = nullptr) {
  if (compareFunction) {
    std::sort(arr.begin(), arr.end(),
              [&](const nlohmann::json &a, const nlohmann::json &b) {
                return compareFunction(a.get<double>(), b.get<double>());
              });
  } else {
    std::sort(arr.begin(), arr.end(),
              [](const nlohmann::json &a, const nlohmann::json &b) {
                return a.get<double>() < b.get<double>();
              });
  }
  return arr;
}

nlohmann::json JS_splice(nlohmann::json &arr, int start, int deleteCount,
                         const nlohmann::json &items = nullptr) {
  start = std::max(start, 0);
  deleteCount = std::max(deleteCount, 0);
  int end = start + deleteCount;

  nlohmann::json removed;

  auto eraseBegin = arr.begin() + start;
  auto eraseEnd = arr.begin() + end;
  for (auto it = eraseBegin; it != eraseEnd; ++it) {
    removed.push_back(*it);
  }
  arr.erase(eraseBegin, eraseEnd);

  if (items.is_array()) {
    for (const auto &item : items) {
      arr.insert(arr.begin() + start, item);
      start++;
    }
  }

  return removed;
}

std::string JS_toLocaleString(const nlohmann::json &arr) {
  std::string result = "";

  for (size_t i = 0; i < arr.size(); i++) {
    if (i > 0) {
      result += ", ";
    }

    result += arr[i].dump();
  }

  return result;
}

std::string JS_toSource(const nlohmann::json &arr) {
  return JS_toLocaleString(arr);
}

std::string JS_toString(const nlohmann::json &arr) {
  return JS_toLocaleString(arr);
}

size_t JS_unshift(nlohmann::json &arr, const nlohmann::json &items) {
  for (auto it = items.rbegin(); it != items.rend(); ++it) {
    arr.insert(arr.begin(), *it);
  }
  return arr.size();
}

nlohmann::json JS_values(const nlohmann::json &arr) { return arr; }



/////////////////////////// BOOLEAN METHODS ///////////////////////////////
std::string JS_toString(bool value) { return value ? "true" : "false"; }
bool JS_valueOf(bool value) { return value ? true : false; }
/////////////////////////// BOOLEAN METHODS END ///////////////////////////////



/////////////////////////// NUMBER METHODS ///////////////////////////////
double JS_valueOf(double value) { return static_cast<double>(value); }
std::string JS_toFixed(double value, int decimalPlaces)
{
  std::ostringstream stream;
  stream.precision(decimalPlaces);
  stream << std::fixed << value;
  return stream.str();
}

std::string JS_toExponential(double value, int decimalPlaces)
{
  std::ostringstream stream;
  stream.precision(decimalPlaces);
  stream << std::scientific << value;
  return stream.str();
}
#include <iomanip>
std::string JS_toPrecision(double value, int precision)
{
  std::ostringstream stream;

  if (value == 0.0)
  {
    stream << std::fixed << std::setprecision(precision) << value;
  }
  else
  {
    int intPartLength = static_cast<int>(std::log10(std::abs(value))) + 1;
    int significantDigits = precision - intPartLength;

    if (significantDigits <= 0)
    {
      stream << std::fixed << std::setprecision(precision) << value;
    }
    else
    {
      stream << std::fixed << std::setprecision(significantDigits) << value;
    }
  }

  return stream.str();
}
std::string JS_toString(double value)
{
  // Trim trailing zeros for non-integer values
  std::ostringstream stream;
  if (std::fmod(value, 1.0) == 0.0)
  {
    stream << static_cast<int>(value);
  }
  else
  {
    stream << value;
  }
  return stream.str();
}

std::string JS_toLocaleString(double value) { return std::to_string(value); }

bool JS_isFinite(double value) { return std::isfinite(value); }

bool JS_isNaN(double value) { return std::isnan(value); }

int JS_valueOf(int value) { return static_cast<int>(value); }
std::string JS_toString(int value)
{
  // Trim trailing zeros for non-integer values
  std::ostringstream stream;
  if (std::fmod(value, 1.0) == 0.0)
  {
    stream << static_cast<int>(value);
  }
  else
  {
    stream << value;
  }
  return stream.str();
}

/////////////////////////// NUMBER METHODS END ///////////////////////////////



/////////////////////////// STRING METHODS ///////////////////////////////
std::string JS_valueOf(std::string value) { return std::string(value); }

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

template <typename... Args>
std::string JS_concat(const std::string &arg1, Args... args) {
  std::vector<std::string> argList = {arg1, args...};
  return JS_concat(argList);
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
nlohmann::json JS_match(const std::string &str, const std::string &regexStr) {
  std::regex regex(regexStr);
  std::smatch match;

  nlohmann::json result = nlohmann::json::array();

  if (std::regex_search(str, match, regex)) {
    nlohmann::json matchDetails = nlohmann::json::object();
    matchDetails["match"] = match[0].str();
    matchDetails["index"] = static_cast<int>(match.position());
    matchDetails["input"] = str;
    matchDetails["groups"] = nlohmann::json::object(); // No groups for now
    result.push_back(matchDetails);
  }

  return result;
}

nlohmann::json JS_match(const std::string &str, const std::regex &regex) {
  std::smatch match;

  nlohmann::json result = nlohmann::json::array();

  if (std::regex_search(str, match, regex)) {
    nlohmann::json matchDetails = nlohmann::json::object();
    matchDetails["match"] = match[0].str();
    matchDetails["index"] = static_cast<int>(match.position());
    matchDetails["input"] = str;
    matchDetails["groups"] = nlohmann::json::object(); // No groups for now
    result.push_back(matchDetails);
  }

  return result;
}

nlohmann::json JS_matchAll(const std::string &str,
                           const std::string &regexStr) {
  std::regex regex(regexStr);
  std::sregex_iterator it(str.begin(), str.end(), regex);
  std::sregex_iterator end;

  nlohmann::json result = nlohmann::json::array();

  while (it != end) {
    nlohmann::json matchDetails = nlohmann::json::object();
    std::smatch match = *it;

    matchDetails["match"] = match[0].str();
    matchDetails["index"] = static_cast<int>(match.position());
    matchDetails["input"] = str;
    matchDetails["groups"] = nlohmann::json::object(); // No groups for now

    result.push_back(matchDetails);
    ++it;
  }

  return result;
}

nlohmann::json JS_matchAll(const std::string &str, const std::regex &regex) {
  std::sregex_iterator it(str.begin(), str.end(), regex);
  std::sregex_iterator end;

  nlohmann::json result = nlohmann::json::array();

  while (it != end) {
    nlohmann::json matchDetails = nlohmann::json::object();
    std::smatch match = *it;

    matchDetails["match"] = match[0].str();
    matchDetails["index"] = static_cast<int>(match.position());
    matchDetails["input"] = str;
    matchDetails["groups"] = nlohmann::json::object(); // No groups for now

    result.push_back(matchDetails);
    ++it;
  }

  return result;
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
  std::string result = str;
  size_t pos = 0;

  while ((pos = result.find(searchValue, pos)) != std::string::npos) {
    result.replace(pos, searchValue.length(), replaceValue);
    pos += replaceValue.length();
  }

  return result;
}

int JS_search(const std::string &str, const std::string &regexStr) {
  std::regex regex(regexStr);
  std::smatch match;

  if (std::regex_search(str, match, regex)) {
    return static_cast<int>(match.position());
  }

  return -1;
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

nlohmann::json JS_split(const std::string &str, const std::string &separator) {
  nlohmann::json result = nlohmann::json::array();
  size_t start = 0;
  size_t end = str.find(separator);

  while (end != std::string::npos) {
    result.push_back(str.substr(start, end - start));
    start = end + separator.length();
    end = str.find(separator, start);
  }

  result.push_back(str.substr(start));

  return result;
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
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(), ::tolower);
  return result;
}

std::string JS_toLocaleUpperCase(const std::string &str) {
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(), ::toupper);
  return result;
}

std::string JS_toLowerCase(const std::string &str) {
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(), ::tolower);
  return result;
}

std::string JS_toUpperCase(const std::string &str) {
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(), ::toupper);
  return result;
}

std::string JS_toString(const std::string &str) { return str; }

std::string JS_trim(const std::string &str) {
  std::regex trimPattern("^\\s+|\\s+$");
  return std::regex_replace(str, trimPattern, "");
}

std::string JS_trimEnd(const std::string &str) {
  std::regex trimPattern("\\s+$");
  return std::regex_replace(str, trimPattern, "");
}

std::string JS_trimStart(const std::string &str) {
  std::regex trimPattern("^\\s+");
  return std::regex_replace(str, trimPattern, "");
}
/////////////////////////// STRING METHODS END ///////////////////////////////


// Main Function (Have to be the only main function)
int main(){
  std::cout.setf(std::ios::boolalpha);
  auto num = static_cast<double>(42) ; 

std::cout << std::string("toFixed:") << JS_toFixed(num, static_cast<double>(2)) << '\n';
std::cout << std::string("toPrecision:") << JS_toPrecision(num, static_cast<double>(3)) << '\n';
std::cout << std::string("toString:") << JS_toString(num) << '\n';
std::cout << std::string("valueOf:") << JS_valueOf(num) << '\n';
  return 0;
}  
