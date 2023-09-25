

// All new includes goes here
#include <chrono>
#include "nlohmann-json.hh"

// All Built-in JSMethods goes here
#include <iostream>
#include <sstream>
#include <cmath>
#include <iomanip>

#include <iostream>
#include <vector>
#include <string>

#include <string>
#include <ctime>
#include <chrono>
#include <cstdarg>
#include <limits>
#include <cstdint>

#include <fstream>
#include <functional>
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>
#include <random>
#include <algorithm>
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



class __Array__ {
public:
  static nlohmann::json from(const nlohmann::json &obj) {
    if (obj.is_string()) {
      std::string str = obj;
      nlohmann::json jsonArray;
      for (char c : str) {
        jsonArray.push_back(std::string(1, c));
      }
      return jsonArray;
    } else {
      return {};
    }
  }

  template <typename... Args> static nlohmann::json of(Args... elements) {
    nlohmann::json jsonArray;
    addElementsToArray(jsonArray, elements...);
    return jsonArray;
  }

private:
  template <typename T, typename... Args>
  static void addElementsToArray(nlohmann::json &jsonArray, T element,
                                 Args... elements) {
    jsonArray.push_back(element);
    addElementsToArray(jsonArray, elements...);
  }

  static void addElementsToArray(nlohmann::json &jsonArray) {}
};



bool JS_CAST_ExclamationBoolean(int value) { return !(value != 0); }

bool JS_CAST_ExclamationBoolean(double value) { return !(value != 0.0); }

bool JS_CAST_ExclamationBoolean(const std::string &value) {
  return !(!value.empty());
}

bool JS_CAST_ExclamationBoolean(bool value) { return !value; }

bool JS_CAST_ExclamationBoolean(const nlohmann::json &value) {
  return !(!value.empty());
}


class __Date__ {
public:
  __Date__() {
    std::chrono::system_clock::time_point now =
        std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm timeInfo = *std::gmtime(&now_c);
    int timezoneDiff = getTimezoneOffset();
    int hourToAddFromTimezoneDiff = timezoneDiff / 60;
    int minsToAddFromTimezoneDiff = timezoneDiff % 60;
    milliseconds_ = std::chrono::duration_cast<std::chrono::milliseconds>(
                        now.time_since_epoch())
                        .count();
    year_ = timeInfo.tm_year + 1900;
    month_ = timeInfo.tm_mon + 1;
    day_ = timeInfo.tm_mday;
    hours_ = timeInfo.tm_hour - hourToAddFromTimezoneDiff;
    minutes_ = timeInfo.tm_min - minsToAddFromTimezoneDiff;
    seconds_ = timeInfo.tm_sec;
  }

  __Date__(int year, int month, int day, int hours = 0, int minutes = 0,
           int seconds = 0, int milliseconds = 0)
      : year_(year), month_(month), day_(day), hours_(hours), minutes_(minutes),
        seconds_(seconds), milliseconds_(milliseconds) {}
  __Date__(long long milliseconds) {
    milliseconds_ = milliseconds;
    long long seconds = milliseconds / 1000LL;

    std::tm *timeInfo = std::gmtime(&seconds);
    year_ = timeInfo->tm_year + 1900;
    month_ = timeInfo->tm_mon + 1;
    day_ = timeInfo->tm_mday;
    hours_ = timeInfo->tm_hour;
    minutes_ = timeInfo->tm_min;
    seconds_ = timeInfo->tm_sec;
  }
  static long long parse(const std::string &dateString) {
    int year, month, day, hours, minutes, seconds;
    sscanf(dateString.c_str(), "%d-%d-%dT%d:%d:%d", &year, &month, &day, &hours,
           &minutes, &seconds);
    __Date__ parsedDate(year, month, day, hours, minutes, seconds);
    return parsedDate.toMillisecondsSinceEpoch();
  }

  static long long now() {
    std::chrono::milliseconds ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
    return ms.count();
  }
  static long long UTC(int year, int month, int day, int hours = 0,
                       int minutes = 0, int seconds = 0, int milliseconds = 0) {
    std::tm timeInfo{};
    timeInfo.tm_year = year - 1900;
    timeInfo.tm_mon = month;
    timeInfo.tm_mday = day;
    timeInfo.tm_hour = hours + 1;
    timeInfo.tm_min = minutes;
    timeInfo.tm_sec = seconds;

    std::chrono::system_clock::time_point timePoint =
        std::chrono::system_clock::from_time_t(std::mktime(&timeInfo));
    timePoint += std::chrono::milliseconds(milliseconds);

    std::chrono::milliseconds ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            timePoint.time_since_epoch());
    return ms.count();
  }

  void setFullYear(int year) { year_ = year; }

  void setMonth(int month) {
    if (month < 0) {
      int yearsToSubtract = (-month - 1) / 12 + 1;
      setFullYear(year_ - yearsToSubtract);
      month = 11 - ((-month - 1) % 12);
    } else if (month > 11) {
      int yearsToAdd = month / 12;
      setFullYear(year_ + yearsToAdd);
      month = month % 12;
    }
    month_ = month + 1;
  }

  void setDate(int day) {
    while (day < 1) {
      int prevMonthDays = daysInMonth(year_, month_ - 1);
      setMonth(month_ - 2);
      day += prevMonthDays;
    }
    while (day > daysInMonth(year_, month_)) {
      day -= daysInMonth(year_, month_);
      setMonth(month_);
    }
    day_ = day;
  }

  void setHours(int hours) {
    if (hours < 0) {
      int daysToSubtract = (-hours - 1) / 24 + 1;
      setDate(day_ - daysToSubtract);
      hours = 23 - ((-hours - 1) % 24);
    } else if (hours > 23) {
      int daysToAdd = hours / 24;
      setDate(day_ + daysToAdd);
      hours = hours % 24;
    }
    hours_ = hours;
  }

  void setMinutes(int minutes) {
    if (minutes < 0) {
      int hoursToSubtract = (-minutes - 1) / 60 + 1;
      setHours(hours_ - hoursToSubtract);
      minutes = 59 - ((-minutes - 1) % 60);
    } else if (minutes > 59) {
      int hoursToAdd = minutes / 60;
      setHours(hours_ + hoursToAdd);
      minutes = minutes % 60;
    }
    minutes_ = minutes;
  }

  void setSeconds(int seconds) {
    if (seconds < 0) {
      int minutesToSubtract = (-seconds - 1) / 60 + 1;
      setMinutes(minutes_ - minutesToSubtract);
      seconds = 59 - ((-seconds - 1) % 60);
    } else if (seconds > 59) {
      int minutesToAdd = seconds / 60;
      setMinutes(minutes_ + minutesToAdd);
      seconds = seconds % 60;
    }
    seconds_ = seconds;
  }

  void setMilliseconds(int milliseconds) {
    if (milliseconds < 0) {
      int secondsToSubtract = (-milliseconds - 1) / 1000 + 1;
      setSeconds(seconds_ - secondsToSubtract);
      milliseconds = 999 - ((-milliseconds - 1) % 1000);
    } else if (milliseconds > 999) {
      int secondsToAdd = milliseconds / 1000;
      setSeconds(seconds_ + secondsToAdd);
      milliseconds = milliseconds % 1000;
    }
    milliseconds_ = milliseconds;
  }

  std::string toISOString() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << year_ << "-" << std::setw(2)
        << month_ << "-" << std::setw(2) << day_ << "T" << std::setw(2)
        << hours_ << ":" << std::setw(2) << minutes_ << ":" << std::setw(2)
        << seconds_ << "Z";
    return oss.str();
  }
  std::string toString() const {
    std::string dateString = toDateString();
    std::string timeString = toTimeString();

    return dateString + " " + timeString;
  }

  std::string toDateString() const {
    char buffer[80];
    std::tm timeInfo{};
    timeInfo.tm_year = year_ - 1900;
    timeInfo.tm_mon = month_ - 1;
    timeInfo.tm_mday = day_;
    timeInfo.tm_hour = hours_;
    timeInfo.tm_min = minutes_;
    timeInfo.tm_sec = seconds_;

    std::mktime(&timeInfo);

    if (std::strftime(buffer, sizeof(buffer), "%a %b %d %Y", &timeInfo) == 0) {
      return "";
    }

    return buffer;
  }
  std::string toTimeString() const {
    int timezoneOffset = getTimezoneOffset();
    int absTimezoneOffset = std::abs(timezoneOffset);
    int hoursOffset = absTimezoneOffset / 60;
    int minutesOffset = absTimezoneOffset % 60;

    std::string offsetSign = (timezoneOffset <= 0) ? "+" : "";
    std::ostringstream offsetStream;
    offsetStream << offsetSign << std::setfill('0') << std::setw(2)
                 << hoursOffset << std::setw(2) << minutesOffset;

    std::string timezoneName = getTimezoneName();

    std::ostringstream timeStream;
    timeStream << std::setfill('0') << std::setw(2) << hours_ << ":"
               << std::setw(2) << minutes_ << ":" << std::setw(2) << seconds_
               << " GMT" << offsetStream.str() << " (" << timezoneName << ")";

    return timeStream.str();
  }

  std::string getTimezoneName() const {
    // Implement your logic to retrieve the timezone name based on the offset
    // here.
    // You can use a library like ICU or a manual mapping of offsets to timezone
    // names.
    // For simplicity, this example just returns a hardcoded value.
    return "Central European Summer Time";
  }
  std::string toJSON() const { return toISOString(); }

  long long valueOf() const { return toMilliseconds(); }

  int getDate() const { return day_; }

  int getDay() const {
    std::tm timeInfo = {};
    timeInfo.tm_year = year_ - 1900;
    timeInfo.tm_mon = month_ - 1;
    timeInfo.tm_mday = day_;
    std::time_t timeSinceEpoch = std::mktime(&timeInfo);
    return timeInfo.tm_wday;
  }

  int getFullYear() const { return year_; }
  int getMonth() const { return month_ - 1; }

  int getHours() const { return hours_; }
  int getMinutes() const { return minutes_; }

  int getSeconds() const { return seconds_; }
  long long getMilliseconds() const { return milliseconds_; }
  long long getTime() const { return toMilliseconds(); }

  int getTimezoneOffset() const {
    std::time_t now = std::time(nullptr);
    std::tm localTime = *std::localtime(&now);
    std::tm gmTime = *std::gmtime(&now);

    int localMinutes = localTime.tm_hour * 60 + localTime.tm_min;
    int gmMinutes = gmTime.tm_hour * 60 + gmTime.tm_min;

    return gmMinutes - localMinutes;
  }
  std::string toUTCString() const {
    int timezoneDiff = getTimezoneOffset();
    int hourToAddFromTimezoneDiff = timezoneDiff / 60;
    int minsToAddFromTimezoneDiff = timezoneDiff % 60;
    char buffer[256];
    std::tm timeInfo{};
    timeInfo.tm_year = year_ - 1900;
    timeInfo.tm_mon = month_ - 1;
    timeInfo.tm_mday = day_;
    timeInfo.tm_hour = hours_ + hourToAddFromTimezoneDiff;
    timeInfo.tm_min = minutes_ + minsToAddFromTimezoneDiff;
    timeInfo.tm_sec = seconds_;

    std::tm temp = timeInfo;
    std::mktime(&temp);
    timeInfo.tm_wday = temp.tm_wday;

    if (std::strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT",
                      &timeInfo) == 0) {
      return "";
    }

    return buffer;
  }

  std::string toLocaleString() const {
    char buffer[256];
    std::tm timeInfo{};
    timeInfo.tm_year = year_ - 1900;
    timeInfo.tm_mon = month_ - 1;
    timeInfo.tm_mday = day_;
    timeInfo.tm_hour = hours_;
    timeInfo.tm_min = minutes_;
    timeInfo.tm_sec = seconds_;

    if (std::strftime(buffer, sizeof(buffer), "%x", &timeInfo) == 0) {
      return "";
    }

    char timeBuffer[256];
    if (std::strftime(timeBuffer, sizeof(timeBuffer), "%I:%M:%S %p",
                      &timeInfo) == 0) {
      return "";
    }

    return std::string(buffer) + ", " + timeBuffer;
  }

  std::string toLocaleDateString() const {
    char buffer[256];
    std::tm timeInfo{};
    timeInfo.tm_year = year_ - 1900;
    timeInfo.tm_mon = month_ - 1;
    timeInfo.tm_mday = day_;

    if (std::strftime(buffer, sizeof(buffer), "%x", &timeInfo) == 0) {
      return "";
    }

    return std::string(buffer);
  }

  std::string toLocaleTimeString() const {
    char buffer[256];
    std::tm timeInfo{};
    timeInfo.tm_hour = hours_;
    timeInfo.tm_min = minutes_;
    timeInfo.tm_sec = seconds_;

    if (std::strftime(buffer, sizeof(buffer), "%I:%M:%S %p", &timeInfo) == 0) {
      return "";
    }

    return buffer;
  }

  friend std::ostream &operator<<(std::ostream &os, const __Date__ &date) {
    os << date.toISOString();
    return os;
  }

  bool operator<(const __Date__ &other) const {
    return toMilliseconds() < other.toMilliseconds();
  }

  bool operator<=(const __Date__ &other) const {
    return toMilliseconds() <= other.toMilliseconds();
  }

  bool operator>(const __Date__ &other) const {
    return toMilliseconds() > other.toMilliseconds();
  }

  bool operator>=(const __Date__ &other) const {
    return toMilliseconds() >= other.toMilliseconds();
  }

  bool operator==(const __Date__ &other) const {
    return toMilliseconds() == other.toMilliseconds();
  }

  bool operator!=(const __Date__ &other) const {
    return toMilliseconds() != other.toMilliseconds();
  }
  bool operator<(const double &other) const {
    return toMilliseconds() < (long long)other;
  }

  bool operator<=(const double &other) const {
    return toMilliseconds() <= (long long)other;
  }

  bool operator>(const double &other) const {
    return toMilliseconds() > (long long)other;
  }

  bool operator>=(const double &other) const {
    return toMilliseconds() >= (long long)other;
  }

  bool operator==(const double &other) const {
    return toMilliseconds() == (long long)other;
  }

  bool operator!=(const double &other) const {
    return toMilliseconds() != (long long)other;
  }
  bool operator<(const std::string &other) const { return false; }

  bool operator<=(const std::string &other) const { return false; }

  bool operator>(const std::string &other) const { return false; }

  bool operator>=(const std::string &other) const { return false; }

  bool operator==(const std::string &other) const {
    return toISOString() == other;
  }

  bool operator!=(const std::string &other) const {
    return toISOString() != other;
  }

  std::string operator+(const std::string &str) const {
    return toDateString() + str;
  }
  std::string operator-(const std::string &str) const { return toDateString(); }
  __Date__ operator+(const __Date__ &other) const {
    return __Date__(toMilliseconds() + other.toMilliseconds());
  }

  __Date__ operator-(const __Date__ &other) const {
    return __Date__(toMilliseconds() - other.toMilliseconds());
  }
  __Date__ operator+(const double &other) const {
    return __Date__(toMilliseconds() + (long long)other);
  }

  __Date__ operator-(const double &other) const {
    return __Date__(toMilliseconds() - (long long)other);
  }

private:
  int year_;
  int month_;
  int day_;
  int hours_;
  int minutes_;
  int seconds_;
  long long int milliseconds_;
  long long toMilliseconds() const {
    std::tm timeInfo;
    timeInfo.tm_year = year_ - 1900;
    timeInfo.tm_mon = month_ - 1;
    timeInfo.tm_mday = day_;
    timeInfo.tm_hour = hours_;
    timeInfo.tm_min = minutes_;
    timeInfo.tm_sec = seconds_;

    std::chrono::system_clock::time_point timePoint =
        std::chrono::system_clock::from_time_t(std::mktime(&timeInfo));

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        timePoint.time_since_epoch());

    return duration.count();
  }
  long long toMillisecondsSinceEpoch() const {
    std::tm timeInfo{};
    timeInfo.tm_year = year_ - 1900;
    timeInfo.tm_mon = month_ - 1;
    timeInfo.tm_mday = day_;
    timeInfo.tm_hour = hours_ + 1;
    timeInfo.tm_min = minutes_;
    timeInfo.tm_sec = seconds_;

    std::time_t timeSinceEpoch = std::mktime(&timeInfo);

    return static_cast<long long>(timeSinceEpoch) * 1000LL + milliseconds_;
  }
  int daysInMonth(int year, int month) {
    int daysInEachMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
      daysInEachMonth[1] = 29;
    }

    if (month < 0) {
      month = 0;
    } else if (month > 11) {
      month = 11;
    }

    return daysInEachMonth[month];
  }
};

std::string JS_toString(__Date__ value) { return value.toString(); }

long long JS_valueOf(__Date__ value) { return value.valueOf(); }

std::string JS_toString(long long value) {
  std::ostringstream stream;
  if (std::fmod(value, 1.0) == 0.0) {
    stream << static_cast<long long>(value);
  } else {
    stream << value;
  }
  return stream.str();
}

long long JS_valueOf(long long value) { return value; }

std::string JS_toLocaleString(__Date__ value) { return value.toLocaleString(); }


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



class __Number__ {
public:
  static const double EPSILON;
  static const double MAX_VALUE;
  static const double MIN_VALUE;
  static const double NaN;
  static const double NEGATIVE_INFINITY;
  static const double POSITIVE_INFINITY;
  static const int64_t MAX_SAFE_INTEGER;
  static const int64_t MIN_SAFE_INTEGER;

  static double parseFloat(const std::string &str) { return std::stod(str); }

  static int32_t parseInt(const std::string &str, int radix = 10) {
    return std::stoi(str, 0, radix);
  }

  static bool isFinite(double num) { return std::isfinite(num); }

  static bool isInteger(double num) { return std::trunc(num) == num; }

  static bool isSafeInteger(double num) {
    return isInteger(num) && num >= MIN_SAFE_INTEGER && num <= MAX_SAFE_INTEGER;
  }
};

const double __Number__::EPSILON = std::numeric_limits<double>::epsilon();
const double __Number__::MAX_VALUE = std::numeric_limits<double>::max();
const double __Number__::MIN_VALUE = std::numeric_limits<double>::min();
const double __Number__::NaN = std::numeric_limits<double>::quiet_NaN();
const double __Number__::NEGATIVE_INFINITY =
    -std::numeric_limits<double>::infinity();
const double __Number__::POSITIVE_INFINITY =
    std::numeric_limits<double>::infinity();
const int64_t __Number__::MAX_SAFE_INTEGER =
    std::numeric_limits<int64_t>::max();
const int64_t __Number__::MIN_SAFE_INTEGER =
    std::numeric_limits<int64_t>::min();

#include <iostream>
#include <string>
#include <sstream>

class __String__ {
public:
  template <typename... Args>
  static std::string fromCharCode(Args... charCodes) {
    std::string result;
    appendChars(result, charCodes...);
    return result;
  }

  template <typename... Args>
  static std::string fromCodePoint(Args... codePoints) {
    std::string result;
    appendCodePoints(result, codePoints...);
    return result;
  }

  // static std::string raw(const std::vector<std::string> &strings) {
  //   std::ostringstream oss;
  //   for (size_t i = 0; i < strings.size(); ++i) {
  //     oss << strings[i];
  //     if (i < strings.size() - 1) {
  //       oss << "\\";
  //     }
  //   }
  //   return oss.str();
  // }

private:
  // Helper function to append characters to the result string
  template <typename... Args>
  static void appendChars(std::string &result, int charCode, Args... args) {
    result += static_cast<char>(charCode);
    appendChars(result, args...);
  }

  // Base case for appendChars to end recursion
  static void appendChars(std::string &) {}

  // Helper function to append code points to the result string
  template <typename... Args>
  static void appendCodePoints(std::string &result, int codePoint,
                               Args... args) {
    if (codePoint >= 0x10000) {
      codePoint -= 0x10000;
      result += static_cast<char>((codePoint >> 10) + 0xD800);
      result += static_cast<char>((codePoint & 0x3FF) + 0xDC00);
    } else {
      result += static_cast<char>(codePoint);
    }
    appendCodePoints(result, args...);
  }

  // Base case for appendCodePoints to end recursion
  static void appendCodePoints(std::string &) {}
};



#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

class __fs__
{
public:
    static void readFile(const std::string &path, const std::function<void(std::string err, std::string data)> &callback)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            callback("Error opening file", "");
            return;
        }

        std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
        file.close();

        callback("", content);
    }

    static std::string readFileSync(const std::string &path, const std::string &encoding)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            throw std::runtime_error("Error opening file");
        }

        std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
        file.close();

        return content;
    }
    static void writeFile(const std::string &path, const std::string &data, const std::function<void(std::string err)> &callback)
    {
        std::ofstream file(path);
        if (!file.is_open())
        {
            callback("Error opening file");
            return;
        }

        file << data;
        file.close();

        callback("");
    }

    static void writeFileSync(const std::string &path, const std::string &data)
    {
        std::ofstream file(path);
        if (!file.is_open())
        {
            throw std::runtime_error("Error opening file");
        }

        file << data;
        file.close();
    }
    static void access(const std::string &path, std::filesystem::perms mode, const std::function<void(std::string err)> &callback)
    {
        try
        {
            std::filesystem::path filePath(path);
            std::filesystem::perms permissions = std::filesystem::status(filePath).permissions();

            // Check if the specified access mode is granted
            bool hasAccess = true;

            if ((mode & std::filesystem::perms::owner_read) != std::filesystem::perms::none && (permissions & std::filesystem::perms::owner_read) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::owner_write) != std::filesystem::perms::none && (permissions & std::filesystem::perms::owner_write) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::owner_exec) != std::filesystem::perms::none && (permissions & std::filesystem::perms::owner_exec) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::group_read) != std::filesystem::perms::none && (permissions & std::filesystem::perms::group_read) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::group_write) != std::filesystem::perms::none && (permissions & std::filesystem::perms::group_write) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::group_exec) != std::filesystem::perms::none && (permissions & std::filesystem::perms::group_exec) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::others_read) != std::filesystem::perms::none && (permissions & std::filesystem::perms::others_read) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::others_write) != std::filesystem::perms::none && (permissions & std::filesystem::perms::others_write) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::others_exec) != std::filesystem::perms::none && (permissions & std::filesystem::perms::others_exec) == std::filesystem::perms::none)
                hasAccess = false;

            if (!hasAccess)
            {
                callback("Permission denied");
            }
            else
            {
                callback("");
            }
        }
        catch (const std::exception &e)
        {
            // Handle other errors
            callback(e.what());
        }
    }

    static void access(const std::string &path, const std::function<void(std::string err)> &callback)
    {
        try
        {
            std::filesystem::path filePath(path);
            std::filesystem::perms permissions = std::filesystem::status(filePath).permissions();

            // Check if the specified access mode is granted
            bool hasAccess = true;

            if ((permissions & std::filesystem::perms::owner_read) == std::filesystem::perms::none)
                hasAccess = false;

            if ((permissions & std::filesystem::perms::owner_write) == std::filesystem::perms::none)
                hasAccess = false;

            if ((permissions & std::filesystem::perms::owner_exec) == std::filesystem::perms::none)
                hasAccess = false;

            if ((permissions & std::filesystem::perms::group_read) == std::filesystem::perms::none)
                hasAccess = false;

            if ((permissions & std::filesystem::perms::group_write) == std::filesystem::perms::none)
                hasAccess = false;

            if ((permissions & std::filesystem::perms::group_exec) == std::filesystem::perms::none)
                hasAccess = false;

            if ((permissions & std::filesystem::perms::others_read) == std::filesystem::perms::none)
                hasAccess = false;

            if ((permissions & std::filesystem::perms::others_write) == std::filesystem::perms::none)
                hasAccess = false;

            if ((permissions & std::filesystem::perms::others_exec) == std::filesystem::perms::none)
                hasAccess = false;

            if (!hasAccess)
            {
                callback("Permission denied");
            }
            else
            {
                callback("");
            }
        }
        catch (const std::exception &e)
        {
            // Handle other errors
            callback(e.what());
        }
    }

    static void accessSync(const std::string &path, std::filesystem::perms mode = std::filesystem::perms::owner_read)
    {
        try
        {
            std::filesystem::path filePath(path);
            std::filesystem::perms permissions = std::filesystem::status(filePath).permissions();

            // Check if the specified access mode is granted
            bool hasAccess = true;

            if ((mode & std::filesystem::perms::owner_read) != std::filesystem::perms::none && (permissions & std::filesystem::perms::owner_read) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::owner_write) != std::filesystem::perms::none && (permissions & std::filesystem::perms::owner_write) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::owner_exec) != std::filesystem::perms::none && (permissions & std::filesystem::perms::owner_exec) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::group_read) != std::filesystem::perms::none && (permissions & std::filesystem::perms::group_read) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::group_write) != std::filesystem::perms::none && (permissions & std::filesystem::perms::group_write) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::group_exec) != std::filesystem::perms::none && (permissions & std::filesystem::perms::group_exec) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::others_read) != std::filesystem::perms::none && (permissions & std::filesystem::perms::others_read) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::others_write) != std::filesystem::perms::none && (permissions & std::filesystem::perms::others_write) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::others_exec) != std::filesystem::perms::none && (permissions & std::filesystem::perms::others_exec) == std::filesystem::perms::none)
                hasAccess = false;

            if (!hasAccess)
            {
                throw std::runtime_error("Permission denied");
            }
        }
        catch (const std::exception &e)
        {
            // Handle other errors
            throw std::runtime_error(e.what());
        }
    }

    static void appendFile(const std::string &path, const std::string &data, const std::function<void(std::string err)> &callback)
    {
        try
        {
            std::ofstream file(path, std::ios::app);

            if (!file.is_open())
            {
                callback("Error opening file");
                return;
            }

            file << data;
            file.close();

            callback("");
        }
        catch (const std::exception &e)
        {
            callback(e.what());
        }
    }

    static void appendFileSync(const std::string &path, const std::string &data)
    {
        try
        {
            std::ofstream file(path, std::ios::app);

            if (!file.is_open())
            {
                throw std::runtime_error("Error opening file");
            }

            file << data;
            file.close();
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error(e.what());
        }
    }

    static void chmod(const std::string &path, int mode, const std::function<void(std::string err)> &callback)
    {
        try
        {
            std::filesystem::path filePath(path);

            if (std::filesystem::exists(filePath))
            {
                std::filesystem::permissions(filePath, static_cast<std::filesystem::perms>(mode));
                callback("");
            }
            else
            {
                callback("File not found");
            }
        }
        catch (const std::exception &e)
        {
            callback(e.what());
        }
    }

    static void chmodSync(const std::string &path, int mode)
    {
        try
        {
            std::filesystem::path filePath(path);

            if (std::filesystem::exists(filePath))
            {
                std::filesystem::permissions(filePath, static_cast<std::filesystem::perms>(mode));
            }
            else
            {
                throw std::runtime_error("File not found");
            }
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error(e.what());
        }
    }
    static void chown(const std::string &path, int uid, int gid, const std::function<void(std::string err)> &callback)
    {
        try
        {
#ifdef _WIN32
            callback("Unsupported operation on Windows");
#else
            if (::chown(path.c_str(), uid, gid) != 0)
            {
                callback(std::strerror(errno));
                return;
            }

            callback("");
#endif
        }
        catch (const std::exception &e)
        {
            callback(e.what());
        }
    }

    static void chownSync(const std::string &path, int uid, int gid)
    {
        try
        {
#ifdef _WIN32
            throw std::runtime_error("Unsupported operation on Windows");
#else
            if (::chown(path.c_str(), uid, gid) != 0)
            {
                throw std::runtime_error(std::strerror(errno));
            }
#endif
        }
        catch (const std::exception &e)
        {
            // Handle other errors
            throw std::runtime_error(e.what());
        }
    }

    static void copyFile(const std::string &src, const std::string &dest, int mode, const std::function<void(std::string err)> &callback)
    {
        try
        {
#ifdef _WIN32
            if (!CopyFileA(src.c_str(), dest.c_str(), (mode & 1) != 0))
            {
                callback("Error copying file");
                return;
            }
#else
            int src_fd = ::open(src.c_str(), O_RDONLY);
            if (src_fd == -1)
            {
                callback(std::strerror(errno));
                return;
            }

            int dest_fd = ::open(dest.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (dest_fd == -1)
            {
                ::close(src_fd);

                callback(std::strerror(errno));
                return;
            }

            ssize_t bytes_copied = sendfile(dest_fd, src_fd, nullptr, 0);
            if (bytes_copied == -1)
            {
                ::close(src_fd);
                ::close(dest_fd);

                callback(std::strerror(errno));
                return;
            }

            ::close(src_fd);
            ::close(dest_fd);

            if ((mode & 1) != 0 && bytes_copied > 0)
            {
                if (std::remove(dest.c_str()) != 0)
                {
                    callback(std::strerror(errno));
                    return;
                }
            }
#endif

            callback("");
        }
        catch (const std::exception &e)
        {
            callback(e.what());
        }
    }
    static void copyFileSync(const std::string &src, const std::string &dest, int mode)
    {
        try
        {
#ifdef _WIN32
            if (!CopyFileA(src.c_str(), dest.c_str(), (mode & 1) != 0))
            {
                throw std::runtime_error("Error copying file");
            }
#else
            int src_fd = ::open(src.c_str(), O_RDONLY);
            if (src_fd == -1)
            {
                throw std::runtime_error(std::strerror(errno));
            }

            int dest_fd = ::open(dest.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (dest_fd == -1)
            {
                ::close(src_fd);

                // Handle errors
                throw std::runtime_error(std::strerror(errno));
            }

            ssize_t bytes_copied = sendfile(dest_fd, src_fd, nullptr, 0);
            if (bytes_copied == -1)
            {
                ::close(src_fd);
                ::close(dest_fd);

                throw std::runtime_error(std::strerror(errno));
            }

            ::close(src_fd);
            ::close(dest_fd);

            if ((mode & 1) != 0 && bytes_copied > 0)
            {
                if (std::remove(dest.c_str()) != 0)
                {
                    throw std::runtime_error(std::strerror(errno));
                }
            }
#endif
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error(e.what());
        }
    }
    static void mkdir(const std::string &path, const nlohmann::json &options, const std::function<void(std::string err, std::string createdDir)> &callback)
    {
        try
        {
            bool recursive = options.value("recursive", false);

            if (recursive)
            {
                std::filesystem::create_directories(path);
                callback("", path);
            }
            else
            {
                std::filesystem::create_directory(path);
                callback("", path);
            }
        }
        catch (const std::system_error &e)
        {
            callback(e.what(), "");
        }
    }

    static std::string mkdirSync(const std::string &path, const nlohmann::json &options)
    {
        try
        {
            bool recursive = options.value("recursive", false);

            if (recursive)
            {
                std::filesystem::create_directories(path);
                return path;
            }
            else
            {
                std::filesystem::create_directory(path);
                return path;
            }
        }
        catch (const std::system_error &e)
        {
            return e.what();
        }
    }
    static void mkdtemp(const std::string &prefix, const nlohmann::json &options, const std::function<void(std::string err, std::string tmpDir)> &callback)
    {
        try
        {
            std::string encoding = options.value("encoding", "utf8");

            // Generate a unique temporary directory name
            std::string tmpDir = generateTempDirName(prefix);

            // Create the temporary directory
            if (std::filesystem::create_directory(tmpDir))
            {
                callback("", tmpDir);
            }
            else
            {
                throw std::runtime_error("Error creating temporary directory");
            }
        }
        catch (const std::exception &e)
        {
            callback(e.what(), "");
        }
    }

    // Synchronous version - mkdtempSync
    static std::string mkdtempSync(const std::string &prefix, const nlohmann::json &options)
    {
        try
        {
            std::string encoding = options.value("encoding", "utf8");

            // Generate a unique temporary directory name
            std::string tmpDir = generateTempDirName(prefix);

            // Create the temporary directory
            if (std::filesystem::create_directory(tmpDir))
            {
                return tmpDir;
            }
            else
            {
                throw std::runtime_error("Error creating temporary directory");
            }
        }
        catch (const std::exception &e)
        {
            return e.what();
        }
    }
    static void readdir(const std::string &path, const nlohmann::json &options, const std::function<void(std::string err, nlohmann::json files)> &callback)
    {
        try
        {
            std::string encoding = options.value("encoding", "utf8");
            bool withFileTypes = options.value("withFileTypes", false);
            bool recursive = options.value("recursive", false);

            std::vector<nlohmann::json> fileList;

            if (withFileTypes)
            {
                for (const auto &entry : std::filesystem::recursive_directory_iterator(path))
                {
                    nlohmann::json file;

                    if (entry.is_directory())
                    {
                        file["name"] = entry.path().filename();
                        file["isDirectory"] = true;
                    }
                    else
                    {
                        file["name"] = entry.path().filename();
                        file["isDirectory"] = false;
                    }

                    fileList.push_back(file);
                }
            }
            else if (recursive)
            {
                for (const auto &entry : std::filesystem::recursive_directory_iterator(path))
                {
                    fileList.push_back(entry.path().filename());
                }
            }
            else
            {
                for (const auto &entry : std::filesystem::directory_iterator(path))
                {
                    fileList.push_back(entry.path().filename());
                }
            }

            callback("", fileList);
        }
        catch (const std::exception &e)
        {
            callback(e.what(), nlohmann::json());
        }
    }

    static void readdir(const std::string &path, const std::function<void(std::string err, nlohmann::json files)> &callback)
    {
        try
        {
            nlohmann::json options = {};
            std::string encoding = options.value("encoding", "utf8");
            bool withFileTypes = options.value("withFileTypes", false);
            bool recursive = options.value("recursive", false);

            std::vector<nlohmann::json> fileList;

            if (withFileTypes)
            {
                for (const auto &entry : std::filesystem::recursive_directory_iterator(path))
                {
                    nlohmann::json file;

                    if (entry.is_directory())
                    {
                        file["name"] = entry.path().filename();
                        file["isDirectory"] = true;
                    }
                    else
                    {
                        file["name"] = entry.path().filename();
                        file["isDirectory"] = false;
                    }

                    fileList.push_back(file);
                }
            }
            else if (recursive)
            {
                for (const auto &entry : std::filesystem::recursive_directory_iterator(path))
                {
                    fileList.push_back(entry.path().filename());
                }
            }
            else
            {
                for (const auto &entry : std::filesystem::directory_iterator(path))
                {
                    fileList.push_back(entry.path().filename());
                }
            }

            callback("", fileList);
        }
        catch (const std::exception &e)
        {
            callback(e.what(), nlohmann::json());
        }
    }

    // Synchronous version - readdirSync
    static nlohmann::json readdirSync(const std::string &path, const nlohmann::json &options = nlohmann::json{{"encoding", "utf3218"}})
    {
        std::string encoding = options.contains("encoding") ? options["encoding"].get<std::string>() : "utf8";
        bool withFileTypes = options.contains("withFileTypes") ? options["withFileTypes"].get<bool>() : false;
        bool recursive = options.contains("recursive") ? options["recursive"].get<bool>() : false;

        std::vector<nlohmann::json> fileList;

        if (withFileTypes)
        {
            for (const auto &entry : std::filesystem::recursive_directory_iterator(path))
            {
                nlohmann::json file;

                if (entry.is_directory())
                {
                    file["name"] = entry.path().filename();
                    file["isDirectory"] = true;
                }
                else
                {
                    file["name"] = entry.path().filename();
                    file["isDirectory"] = false;
                }

                fileList.push_back(file);
            }
        }
        else if (recursive)
        {
            for (const auto &entry : std::filesystem::recursive_directory_iterator(path))
            {
                fileList.push_back(entry.path().filename());
            }
        }
        else
        {
            for (const auto &entry : std::filesystem::directory_iterator(path))
            {
                fileList.push_back(entry.path().filename());
            }
        }

        return fileList;
    }

private:
    // Generate a unique temporary directory name
    static std::string generateTempDirName(const std::string &prefix)
    {
        // Generate six random characters
        static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        static const size_t charsetSize = sizeof(charset) - 1;
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> distr(0, charsetSize - 1);

        std::string randomChars;
        for (int i = 0; i < 6; ++i)
        {
            randomChars += charset[distr(gen)];
        }

        // Concatenate the prefix and random characters
        return prefix + randomChars;
    }
};



#ifdef _WIN32
#include <WinSock2.h>
#include <Windows.h>
#include <ShlObj.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>
#include <Pdh.h>
#pragma comment(lib, "Pdh.lib")
#pragma comment(lib, "iphlpapi.lib")
#else
#include <sys/utsname.h>
#include <sys/param.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/sysctl.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
class __os__
{
public:
    static std::string EOL;
    static std::string devNull;
    static nlohmann::json constants;
    static std::string arch()
    {
#if defined(__arm__)
        return "arm";
#elif defined(__aarch64__)
        return "arm64";
#elif defined(__i386__)
        return "ia32";
#elif defined(__mips__)
        return "mips";
#elif defined(__mipsel__)
        return "mipsel";
#elif defined(__powerpc__) || defined(__ppc__) || defined(__PPC__)
        return "ppc";
#elif defined(__powerpc64__) || defined(__ppc64__) || defined(__PPC64__)
        return "ppc64";
#elif defined(__riscv) && defined(__LP64__)
        return "riscv64";
#elif defined(__s390__)
        return "s390";
#elif defined(__s390x__)
        return "s390x";
#else
        return "x64";
#endif
    }

    static long long freemem()
    {
#ifdef _WIN32
        MEMORYSTATUSEX memoryStatus;
        memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&memoryStatus);
        return static_cast<long long>(memoryStatus.ullAvailPhys);
#else
        int mib[2] = {CTL_HW, HW_USERMEM};
        long long userMemory;
        size_t len = sizeof(userMemory);
        sysctl(mib, 2, &userMemory, &len, NULL, 0);
        return userMemory;
#endif
    }

    static std::string homedir()
    {
#ifdef _WIN32
        const char *userProfile = std::getenv("USERPROFILE");
        if (userProfile != nullptr)
        {
            return userProfile;
        }
        else
        {
            wchar_t profilePath[MAX_PATH];
            if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, profilePath)))
            {
                auto wst = std::wstring(profilePath);
                return std::string(wst.begin(), wst.end());
            }
        }
        return "";
#else
        const char *home = std::getenv("HOME");
        if (home != nullptr)
        {
            return home;
        }
        else
        {
            struct passwd *pw = getpwuid(geteuid());
            if (pw != nullptr)
            {
                return pw->pw_dir;
            }
        }
        return "";
#endif
    }

    static std::string hostname()
    {
#ifdef _WIN32
        char computerName[256];
        DWORD size = sizeof(computerName);
        if (GetComputerNameA(computerName, &size))
        {
            return computerName;
        }
        else
        {
            return "";
        }
#else
        char hostname[HOST_NAME_MAX];
        if (gethostname(hostname, sizeof(hostname)) == 0)
        {
            return hostname;
        }
        else
        {
            return "";
        }
#endif
    }

    static std::string machine()
    {
#ifdef _WIN32
        OSVERSIONINFOEX osvi;
        ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
        if (GetVersionEx((OSVERSIONINFO *)&osvi))
        {
            if (osvi.dwMajorVersion == 10 && osvi.dwMinorVersion == 0 && osvi.dwBuildNumber == 19042)
            {
                return "x86_64";
            }
            else
            {
                SYSTEM_INFO sysInfo;
                GetNativeSystemInfo(&sysInfo);
                switch (sysInfo.wProcessorArchitecture)
                {
                case PROCESSOR_ARCHITECTURE_ARM:
                    return "arm";
                case PROCESSOR_ARCHITECTURE_ARM64:
                    return "arm64";
                case PROCESSOR_ARCHITECTURE_IA64:
                    return "ia64";
                case PROCESSOR_ARCHITECTURE_AMD64:
                    return "x86_64";
                case PROCESSOR_ARCHITECTURE_INTEL:
                    return "i686";
                default:
                    return "";
                }
            }
        }
        else
        {
            return "";
        }
#else
        struct utsname sysInfo;
        if (uname(&sysInfo) == 0)
        {
            return sysInfo.machine;
        }
        else
        {
            return "";
        }
#endif
    }

    static std::string platform()
    {
#ifdef _WIN32
        return "win32";
#elif defined(__linux__)
        struct utsname sysInfo;
        if (uname(&sysInfo) == 0)
        {
            if (std::string(sysInfo.sysname) == "Linux")
            {
                return "linux";
            }
        }
        return "";
#else
        struct utsname sysInfo;
        if (uname(&sysInfo) == 0)
        {
            if (std::string(sysInfo.sysname) == "Darwin")
            {
                return "darwin";
            }
            else if (std::string(sysInfo.sysname) == "FreeBSD")
            {
                return "freebsd";
            }
            else if (std::string(sysInfo.sysname) == "OpenBSD")
            {
                return "openbsd";
            }
            else if (std::string(sysInfo.sysname) == "NetBSD")
            {
                return "netbsd";
            }
            else if (std::string(sysInfo.sysname) == "AIX")
            {
                return "aix";
            }
            else if (std::string(sysInfo.sysname) == "SunOS")
            {
                return "sunos";
            }
        }
        return "";
#endif
    }

    static std::string release()
    {
#ifdef _WIN32
        OSVERSIONINFOEX osvi;
        ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
        if (GetVersionEx((OSVERSIONINFO *)&osvi))
        {
            std::string releaseInfo = "Windows ";
            releaseInfo += std::to_string(osvi.dwMajorVersion);
            releaseInfo += ".";
            releaseInfo += std::to_string(osvi.dwMinorVersion);
            return releaseInfo;
        }
        else
        {
            return "";
        }
#else
        struct utsname sysInfo;
        if (uname(&sysInfo) == 0)
        {
            return sysInfo.release;
        }
        else
        {
            return "";
        }
#endif
    }
    static std::string tmpdir()
    {
#ifdef _WIN32
        const char *tempDir = std::getenv("TEMP");
        if (tempDir != nullptr)
        {
            return tempDir;
        }
        else
        {
            const char *tmpDir = std::getenv("TMP");
            if (tmpDir != nullptr)
            {
                return tmpDir;
            }
            else
            {
                return "C:\\Windows\\Temp";
            }
        }
#else
        const char *tmpDir = std::getenv("TMPDIR");
        if (tmpDir != nullptr)
        {
            return tmpDir;
        }
        else
        {
            return "/tmp";
        }
#endif
    }
    static long long totalmem()
    {
#ifdef _WIN32
        MEMORYSTATUSEX memoryStatus;
        memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
        if (GlobalMemoryStatusEx(&memoryStatus))
        {
            return static_cast<long long>(memoryStatus.ullTotalPhys);
        }
        else
        {
            return 0;
        }
#else
        long long pageSize = sysconf(_SC_PAGE_SIZE);
        long long pageCount = sysconf(_SC_PHYS_PAGES);
        if (pageSize > 0 && pageCount > 0)
        {
            return pageSize * pageCount;
        }
        else
        {
            return 0;
        }
#endif
    }
    static std::string type()
    {
#ifdef _WIN32
        return "Windows_NT";
#elif defined(__linux__)
        struct utsname sysInfo;
        if (uname(&sysInfo) == 0)
        {
            return sysInfo.sysname;
        }
        else
        {
            return "";
        }
#else
        struct utsname sysInfo;
        if (uname(&sysInfo) == 0)
        {
            return sysInfo.sysname;
        }
        else
        {
            return "";
        }
#endif
    }
    static long long uptime()
    {
#ifdef _WIN32
        return static_cast<long long>(GetTickCount64() / 1000);
#else
        struct sysinfo info;
        if (sysinfo(&info) != -1)
        {
            return static_cast<long long>(info.uptime);
        }
        else
        {
            return -1;
        }
#endif
    }
    static std::string version()
    {
        OSVERSIONINFOEX osvi;
        ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

        if (GetVersionEx((OSVERSIONINFO *)&osvi))
        {
            return std::to_string(osvi.dwMajorVersion) + "." +
                   std::to_string(osvi.dwMinorVersion) + "." +
                   std::to_string(osvi.dwBuildNumber);
        }
        else
        {
            return "";
        }
    }
    static nlohmann::json networkInterfaces()
    {
        nlohmann::json networkInterfacesJson;

#ifdef _WIN32
        IP_ADAPTER_ADDRESSES *adapterAddresses = nullptr;
        ULONG outBufLen = 0;

        if (GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, nullptr, nullptr, &outBufLen) == ERROR_BUFFER_OVERFLOW)
        {
            adapterAddresses = (IP_ADAPTER_ADDRESSES *)malloc(outBufLen);
            if (GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, nullptr, adapterAddresses, &outBufLen) == NO_ERROR)
            {
                for (IP_ADAPTER_ADDRESSES *adapter = adapterAddresses; adapter; adapter = adapter->Next)
                {
                    nlohmann::json addressesJson;

                    for (IP_ADAPTER_UNICAST_ADDRESS *address = adapter->FirstUnicastAddress; address; address = address->Next)
                    {
                        nlohmann::json addressJson;
                        sockaddr *sockaddrPtr = address->Address.lpSockaddr;

                        if (sockaddrPtr->sa_family == AF_INET)
                        {
                            sockaddr_in *ipv4Address = reinterpret_cast<sockaddr_in *>(sockaddrPtr);
                            addressJson["address"] = inet_ntoa(ipv4Address->sin_addr);
                            addressJson["netmask"] = "";
                            addressJson["family"] = "IPv4";
                        }
                        else if (sockaddrPtr->sa_family == AF_INET6)
                        {
                            sockaddr_in6 *ipv6Address = reinterpret_cast<sockaddr_in6 *>(sockaddrPtr);
                            char ipv6AddressStr[INET6_ADDRSTRLEN];
                            if (inet_ntop(AF_INET6, &(ipv6Address->sin6_addr), ipv6AddressStr, INET6_ADDRSTRLEN))
                            {
                                addressJson["address"] = ipv6AddressStr;
                                addressJson["netmask"] = "";
                                addressJson["family"] = "IPv6";
                            }
                        }

                        addressJson["mac"] = "";
                        addressJson["internal"] = false;
                        addressJson["scopeid"] = 0;
                        addressJson["cidr"] = "";

                        addressesJson.push_back(addressJson);
                    }

                    networkInterfacesJson[adapter->AdapterName] = addressesJson;
                }
            }

            free(adapterAddresses);
        }
#else
        struct ifaddrs *ifAddrStruct = nullptr;
        if (getifaddrs(&ifAddrStruct) == 0)
        {
            for (struct ifaddrs *ifa = ifAddrStruct; ifa; ifa = ifa->ifa_next)
            {
                if (!ifa->ifa_addr)
                {
                    continue;
                }

                nlohmann::json addressesJson;
                sockaddr *sockaddrPtr = ifa->ifa_addr;

                if (sockaddrPtr->sa_family == AF_INET)
                {
                    sockaddr_in *ipv4Address = reinterpret_cast<sockaddr_in *>(sockaddrPtr);
                    nlohmann::json addressJson;
                    addressJson["address"] = inet_ntoa(ipv4Address->sin_addr);
                    addressJson["netmask"] = inet_ntoa(reinterpret_cast<sockaddr_in *>(ifa->ifa_netmask)->sin_addr);
                    addressJson["family"] = "IPv4";
                    addressJson["mac"] = "";
                    addressJson["internal"] = (ifa->ifa_flags & IFF_LOOPBACK) != 0;
                    addressJson["scopeid"] = 0;
                    addressJson["cidr"] = "";
                    addressesJson.push_back(addressJson);
                }
                else if (sockaddrPtr->sa_family == AF_INET6)
                {
                    sockaddr_in6 *ipv6Address = reinterpret_cast<sockaddr_in6 *>(sockaddrPtr);
                    char ipv6AddressStr[INET6_ADDRSTRLEN];
                    if (inet_ntop(AF_INET6, &(ipv6Address->sin6_addr), ipv6AddressStr, INET6_ADDRSTRLEN))
                    {
                        nlohmann::json addressJson;
                        addressJson["address"] = ipv6AddressStr;
                        addressJson["netmask"] = "";
                        addressJson["family"] = "IPv6";
                        addressJson["mac"] = "";
                        addressJson["internal"] = (ifa->ifa_flags & IFF_LOOPBACK) != 0;
                        addressJson["scopeid"] = ipv6Address->sin6_scope_id;
                        addressJson["cidr"] = "";
                        addressesJson.push_back(addressJson);
                    }
                }

                networkInterfacesJson[ifa->ifa_name] = addressesJson;
            }

            freeifaddrs(ifAddrStruct);
        }
#endif

        return networkInterfacesJson;
    }

    static nlohmann::json cpus()
    {
        nlohmann::json cpusArray;

#ifdef _WIN32
        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);
        DWORD numCores = sysInfo.dwNumberOfProcessors;

        for (DWORD core = 0; core < numCores; core++)
        {
            nlohmann::json cpuInfo;
            cpuInfo["model"] = "Unknown";
            cpuInfo["speed"] = 0;

            FILETIME idleTime, kernelTime, userTime;
            if (GetSystemTimes(&idleTime, &kernelTime, &userTime))
            {
                ULARGE_INTEGER idleTimeValue, kernelTimeValue, userTimeValue;
                idleTimeValue.LowPart = idleTime.dwLowDateTime;
                idleTimeValue.HighPart = idleTime.dwHighDateTime;
                kernelTimeValue.LowPart = kernelTime.dwLowDateTime;
                kernelTimeValue.HighPart = kernelTime.dwHighDateTime;
                userTimeValue.LowPart = userTime.dwLowDateTime;
                userTimeValue.HighPart = userTime.dwHighDateTime;

                ULONGLONG totalTime = kernelTimeValue.QuadPart + userTimeValue.QuadPart;
                ULONGLONG idleTotalTime = idleTimeValue.QuadPart;

                cpuInfo["times"]["user"] = static_cast<double>(userTimeValue.QuadPart) / totalTime * 1000.0;
                cpuInfo["times"]["nice"] = 0;
                cpuInfo["times"]["sys"] = static_cast<double>(kernelTimeValue.QuadPart) / totalTime * 1000.0;
                cpuInfo["times"]["idle"] = static_cast<double>(idleTotalTime) / totalTime * 1000.0;
                cpuInfo["times"]["irq"] = 0;
            }

            cpusArray.push_back(cpuInfo);
        }
#else
        std::ifstream cpuInfoFile("/proc/cpuinfo");
        std::string line;
        nlohmann::json cpuInfo;

        while (std::getline(cpuInfoFile, line))
        {
            if (line.empty())
            {
                cpusArray.push_back(cpuInfo);
                cpuInfo = nlohmann::json();
            }
            else
            {
                size_t colonPos = line.find(':');
                if (colonPos != std::string::npos)
                {
                    std::string key = line.substr(0, colonPos);
                    std::string value = line.substr(colonPos + 1);
                    key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());
                    value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());
                    cpuInfo[key] = value;
                }
            }
        }
#endif

        return cpusArray;
    }
};

#ifdef _WIN32
std::string __os__::EOL = "\n";
#else
std::string __os__::EOL = "\r\n";
#endif

#ifdef _WIN32
std::string __os__::devNull = "\\\\.\\nul";
#else
std::string __os__::devNull = "/dev/null";
#endif

nlohmann::json constants = {};


class __path__
{
public:
  static char sep;
  static char delimiter;
  static std::string basename(const std::string &path,
                              const std::string &suffix = "")
  {
    std::string base = path.substr(path.find_last_of('/') + 1);
    if (suffix.empty() ||
        base.substr(base.length() - suffix.length()) != suffix)
    {
      return base;
    }
    return base.substr(0, base.length() - suffix.length());
  }

  static std::string dirname(const std::string &path)
  {
    size_t found = path.find_last_of('/');
    if (found != std::string::npos)
    {
      return path.substr(0, found);
    }
    return "";
  }

  static std::string extname(const std::string &path)
  {
    size_t found = path.find_last_of('.');
    if (found != std::string::npos && found > path.find_last_of('/'))
    {
      return path.substr(found);
    }
    return "";
  }

  template <typename... Args>
  static std::string join(Args... args)
  {
    std::string result;
    joinInternal(result, args...);
    if (!result.empty() && result.back() == sep)
    {
      result.pop_back();
    }
    return result;
  }
  static bool isAbsolute(const std::string &path)
  {
    if (path.empty())
    {
      return false;
    }

    if (path[0] == sep || path[0] == '/')
    {
      return true;
    }

    if (path.length() >= 3 && std::isalpha(path[0]) && path[1] == ':' &&
        (path[2] == sep || path[2] == '/'))
    {
      return true;
    }

    return false;
  }
  static std::string normalize(const std::string &path)
  {
    if (path.empty())
    {
      return ".";
    }

    char separator = sep;

    std::vector<std::string> segments;
    size_t start = 0;
    size_t end = 0;
    while ((end = path.find_first_of("/\\", start)) != std::string::npos)
    {
      std::string segment = path.substr(start, end - start);
      start = end + 1;

      if (segment == "..")
      {
        if (!segments.empty() && segments.back() != "..")
        {
          segments.pop_back();
        }
        else
        {
          segments.push_back("..");
        }
      }
      else if (segment != "." && !segment.empty())
      {
        segments.push_back(segment);
      }
    }

    std::string lastSegment = path.substr(start);

    if (lastSegment == "..")
    {
      if (!segments.empty() && segments.back() != "..")
      {
        segments.pop_back();
      }
      else
      {
        segments.push_back("..");
      }
    }
    else if (lastSegment != "." && !lastSegment.empty())
    {
      segments.push_back(lastSegment);
    }

    std::string normalizedPath;
    for (const std::string &segment : segments)
    {
      normalizedPath += segment;
      normalizedPath += separator;
    }

    if (!path.empty() && (path.back() == '/' || path.back() == '\\'))
    {
      normalizedPath += separator;
    }

    if (isAbsolute(path))
    {
      if (normalizedPath.empty() || normalizedPath[0] != separator)
      {
        normalizedPath = separator + normalizedPath;
      }
    }
    if (!normalizedPath.empty() && normalizedPath.back() == sep)
    {
      normalizedPath.pop_back();
    }
    return normalizedPath;
  }
  static nlohmann::json parse(const std::string &path)
  {
    nlohmann::json result;

    size_t lastSeparatorPos = path.find_last_of("/\\");
    std::string dir, base;
    if (lastSeparatorPos != std::string::npos)
    {
      dir = path.substr(0, lastSeparatorPos);
      base = path.substr(lastSeparatorPos + 1);
    }
    else
    {
      dir = path;
      base = path; // Set base to path if there's no separator
    }

    size_t rootEnd = 0;
    if (isAbsolute(path))
    {
      // Check for Windows-style drive letter
      if (path.size() > 2 && path[1] == ':' && (path[2] == '/' || path[2] == '\\'))
      {
        rootEnd = 3; // Include drive letter and slash (e.g., "C:/")
      }
      else
      {
        rootEnd = 1; // Just a single slash for other absolute paths
      }
    }

    size_t extPos = base.find_last_of('.');
    std::string root = path.substr(0, rootEnd);
    std::string ext = (extPos != std::string::npos) ? base.substr(extPos) : "";
    std::string name =
        (extPos != std::string::npos) ? base.substr(0, extPos) : base;

    result["root"] = root;
    result["dir"] = dir;
    result["base"] = base;
    result["ext"] = ext;
    result["name"] = name;

    return result;
  }
  static std::string relative(const std::string &from, const std::string &to)
  {
    std::string sep = std::string(1, __path__::sep);

    std::string normalizedFrom = normalize(from);
    std::string normalizedTo = normalize(to);

    std::vector<std::string> fromSegments;
    std::vector<std::string> toSegments;
    size_t start = 0;
    size_t end = 0;

    while ((end = normalizedFrom.find(sep, start)) != std::string::npos)
    {
      std::string seg = normalizedFrom.substr(start, end - start);
      std::string segment = normalizedTo.substr(start, end - start);
      fromSegments.push_back(seg);
      toSegments.push_back(segment);
      start = end + 1;
    }
    fromSegments.push_back(normalizedFrom.substr(start));
    toSegments.push_back(normalizedTo.substr(start));

    size_t commonPrefixLength = 0;
    while (commonPrefixLength < fromSegments.size() &&
           commonPrefixLength < toSegments.size() &&
           fromSegments[commonPrefixLength] == toSegments[commonPrefixLength])
    {
      commonPrefixLength++;
    }

    std::string relativePath;
    for (size_t i = commonPrefixLength; i < fromSegments.size(); i++)
    {
      relativePath += "..";
      relativePath += sep;
    }

    for (size_t i = commonPrefixLength; i < toSegments.size(); i++)
    {
      relativePath += toSegments[i];
      relativePath += sep;
    }

    if (!relativePath.empty())
    {
      relativePath.pop_back();
    }

    return relativePath;
  }
  static std::string toNamespacedPath(const std::string &path)
  {
    if (!path.empty() && path[1] == ':' && (path[2] == '/' || path[2] == '\\'))
    {
      return "\\\\?\\" + path;
    }

    return path;
  }
  static std::string format(const nlohmann::json &pathObject)
  {
    std::string result;

    if (pathObject.find("dir") != pathObject.end())
    {
      result += pathObject["dir"];
    }
    else
    {
      if (pathObject.find("root") != pathObject.end())
      {
        result += pathObject["root"];
      }
    }

    if (pathObject.find("base") != pathObject.end())
    {
      result += sep;
      result += pathObject["base"];
    }
    else
    {
      if (pathObject.find("name") != pathObject.end())
      {
        result += sep;
        result += pathObject["name"];
      }

      if (pathObject.find("ext") != pathObject.end())
      {
        if (pathObject["ext"].empty() || pathObject["ext"][0] != '.')
        {
          result += '.';
        }
        result += pathObject["ext"];
      }
    }

    return result;
  }

private:
  template <typename T, typename... Args>
  static void joinInternal(std::string &result, const T &first, Args... args)
  {
    result += first;
    result += sep;
    joinInternal(result, args...);
  }

  static void joinInternal(std::string &result)
  {
    // Do nothing, this is the base case
  }
};

#ifdef _WIN32
char __path__::sep = '\\';
#else
char __path__::sep = '/';
#endif
#ifdef _WIN32
char __path__::delimiter = ';';
#else
char __path__::delimiter = ':';
#endif


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



nlohmann::json JS_concat(const nlohmann::json &arr1,
                         const nlohmann::json &arr2)
{
  nlohmann::json result = arr1;
  for (const auto &element : arr2)
  {
    result.push_back(element);
  }
  return result;
}

nlohmann::json JS_copyWithin(nlohmann::json &arr, int target, int start,
                             int end = INT_MAX)
{
  if (!arr.is_array())
  {
    throw std::runtime_error("Input is not an array.");
  }

  int length = static_cast<int>(arr.size());

  target =
      (target < 0) ? std::max(length + target, 0) : std::min(target, length);
  start = (start < 0) ? std::max(length + start, 0) : std::min(start, length);
  end = (end < 0) ? std::max(length + end, 0) : std::min(end, length);

  int to = target;
  int from = start;

  while (from < end && to < length)
  {
    arr[to] = arr[from];
    ++to;
    ++from;
  }
  return arr;
}

nlohmann::json JS_entries(const nlohmann::json &arr)
{
  nlohmann::json result;
  int index = 0;
  for (const auto &element : arr)
  {
    nlohmann::json entry;
    entry.push_back(index);
    entry.push_back(element);
    result.push_back(entry);
    index++;
  }
  return result;
}

template <typename Callable>
bool JS_every(const nlohmann::json &arr, Callable callback)
{
  if (arr.empty())
  {
    return false;
  }

  nlohmann::json::value_t expected_type = arr[0].type();

  for (const auto &element : arr)
  {
    if (element.type() != expected_type)
    {
      return false;
    }

    bool satisfiesCallback = false;
    try
    {
      satisfiesCallback = callback(element);
    }
    catch (const std::exception &ex)
    {
      return false;
    }

    if (!satisfiesCallback)
    {
      return false;
    }
  }

  return true;
}

nlohmann::json JS_fill(nlohmann::json &arr, double value, int start, int end)
{
  start = std::max(start, 0);
  end = std::min(end, static_cast<int>(arr.size()));

  for (int i = start; i < end; i++)
  {
    arr[i] = value;
  }

  return arr;
}

template <typename Callable>
nlohmann::json JS_filter(const nlohmann::json &arr, Callable callback)
{
  if (arr.empty())
  {
    return nlohmann::json::array();
  }

  nlohmann::json result = nlohmann::json::array();

  for (const auto &element : arr)
  {
    bool satisfiesCallback = false;
    try
    {
      satisfiesCallback = callback(element);
    }
    catch (const std::exception &ex)
    {
      continue;
    }

    if (satisfiesCallback)
    {
      result.push_back(element);
    }
  }

  return result;
}

template <typename Callable>
nlohmann::json JS_find(const nlohmann::json &arr, Callable callback)
{
  if (arr.empty())
  {
    return "undefined";
  }

  nlohmann::json::value_t expected_type = arr[0].type();

  for (const auto &element : arr)
  {
    if (element.type() != expected_type)
    {
      continue;
    }

    try
    {
      if (callback(element))
      {
        return element;
      }
    }
    catch (const std::exception &ex)
    {
      continue;
    }
  }

  return "undefined";
}
template <typename Callable>
int JS_findIndex(const nlohmann::json &arr, Callable callback)
{
  if (arr.empty())
  {
    return -1; // Return -1 to indicate no matching element found
  }

  nlohmann::json::value_t expected_type = arr[0].type();
  int index = 0;

  for (const auto &element : arr)
  {
    if (element.type() != expected_type)
    {
      return -1; // Return -1 if types are not the same
    }

    bool satisfiesCallback = false;
    try
    {
      satisfiesCallback = callback(element);
    }
    catch (const std::exception &ex)
    {
      // Handle exceptions from the callback function
      return -1;
    }

    if (satisfiesCallback)
    {
      return index; // Return the index of the first matching element
    }

    index++;
  }

  return -1; // Return -1 if no matching element is found
}

nlohmann::json JS_flat(const nlohmann::json &arr, int depth = 1)
{
  if (depth <= 0)
  {
    return arr;
  }

  nlohmann::json result;
  for (const auto &element : arr)
  {
    if (element.is_array())
    {
      result.insert(result.end(), JS_flat(element, depth - 1).begin(),
                    JS_flat(element, depth - 1).end());
    }
    else
    {
      result.push_back(element);
    }
  }
  return result;
}

template <typename Callable>
nlohmann::json JS_flatMap(const nlohmann::json &arr, Callable callback)
{
  nlohmann::json result = nlohmann::json::array();

  for (const auto &element : arr)
  {
    try
    {
      nlohmann::json mapped = callback(element);

      if (mapped.is_array())
      {
        // If the result of the callback is an array, concatenate it to the result
        result.insert(result.end(), mapped.begin(), mapped.end());
      }
      else
      {
        // If the result is not an array, add it as a single element to the result
        result.push_back(mapped);
      }
    }
    catch (const std::exception &ex)
    {
      // Handle exceptions from the callback function
      continue;
    }
  }

  return result;
}

template <typename Callable>
void JS_forEach(const nlohmann::json &arr, Callable callback)
{
  if (arr.empty())
  {
    return;
  }

  nlohmann::json::value_t expected_type = arr[0].type();

  for (const auto &element : arr)
  {
    if (element.type() != expected_type)
    {
      continue;
    }

    try
    {
      callback(element);
    }
    catch (const std::exception &ex)
    {
      continue;
    }
  }
}

template <typename T>
bool JS_includes(const nlohmann::json &arr, const T &searchElement)
{
  for (const auto &element : arr)
  {
    try
    {

      T value = element.get<T>();
      if (value == searchElement)
      {
        return true;
      }
    }
    catch (const std::exception &ex)
    {
      continue;
    }
  }
  return false;
}

template <typename T>
int JS_indexOf(const nlohmann::json &arr, const T &searchElement,
               int fromIndex = 0)
{
  fromIndex = std::max(fromIndex, 0);
  for (int i = fromIndex; i < static_cast<int>(arr.size()); i++)
  {
    try
    {

      T value = arr[i].get<T>();
      if (value == searchElement)
      {
        return i;
      }
    }
    catch (const std::exception &ex)
    {
      continue;
    }
  }
  return -1;
}

bool JS_isArray(const nlohmann::json &arr) { return arr.is_array(); }

std::string JS_join(const nlohmann::json &arr, const std::string &delimiter)
{
  std::string result;

  for (const auto &element : arr)
  {
    if (!result.empty())
    {
      result += delimiter; // Add the delimiter between elements
    }

    result += element.dump(); // Convert the element to a string and append it
  }

  return result;
}

nlohmann::json JS_keys(const nlohmann::json &arr)
{
  nlohmann::json result;
  for (int i = 0; i < arr.size(); i++)
  {
    result.push_back(i);
  }
  return result;
}

template <typename T>
int JS_lastIndexOf(const nlohmann::json &arr, const T &searchElement,
                   int fromIndex = -1)
{
  if (arr.empty())
  {
    return -1;
  }

  if (fromIndex == -1)
  {
    fromIndex = static_cast<int>(arr.size()) - 1;
  }
  else
  {
    fromIndex = std::min(fromIndex, static_cast<int>(arr.size()) - 1);
  }

  for (int i = fromIndex; i >= 0; i--)
  {
    try
    {
      T value = arr[i].get<T>();
      if (value == searchElement)
      {
        return i;
      }
    }
    catch (const std::exception &ex)
    {
      continue;
    }
  }

  return -1;
}

template <typename Callable>
nlohmann::json JS_map(const nlohmann::json &arr, Callable callback)
{
  nlohmann::json result = nlohmann::json::array();

  for (const auto &element : arr)
  {
    try
    {
      // Apply the callback function to each element and add the result to the result array
      result.push_back(callback(element));
    }
    catch (const std::exception &ex)
    {
      // Handle exceptions from the callback function
      continue;
    }
  }

  return result;
}

nlohmann::json JS_pop(nlohmann::json &arr)
{
  if (arr.is_array() && !arr.empty())
  {
    nlohmann::json popped = arr.back();
    arr.erase(--arr.end());
    return popped;
  }
  return nullptr;
}

template <typename T>
T JS_push(nlohmann::json &arr, T element)
{
  arr.push_back(element);
  return arr.size();
}

template <typename Callable>
nlohmann::json JS_reduce(const nlohmann::json &arr, Callable callback, nlohmann::json initialValue = nlohmann::json())
{
  nlohmann::json accumulator = initialValue;

  for (const auto &element : arr)
  {
    try
    {
      accumulator = callback(accumulator, element);
    }
    catch (const std::exception &ex)
    {
      continue;
    }
  }

  return accumulator;
}

template <typename Callable>
nlohmann::json JS_reduceRight(const nlohmann::json &arr, Callable callback, nlohmann::json initialValue = nlohmann::json())
{
  nlohmann::json accumulator = initialValue;

  for (auto it = arr.rbegin(); it != arr.rend(); ++it)
  {
    try
    {
      nlohmann::json element = *it;
      accumulator = callback(element, accumulator);
    }
    catch (const std::exception &ex)
    {
      continue;
    }
  }

  return accumulator;
}

nlohmann::json JS_reverse(nlohmann::json &arr)
{
  std::reverse(arr.begin(), arr.end());
  return arr;
}

nlohmann::json JS_shift(nlohmann::json &arr)
{
  if (arr.empty())
  {
    return nullptr;
  }
  nlohmann::json shifted = arr.front();
  arr.erase(arr.begin());
  return shifted;
}

nlohmann::json JS_slice(const nlohmann::json &arr, int start = 0,
                        int end = INT_MAX)
{
  start = std::max(start, 0);
  end = std::min(end, static_cast<int>(arr.size()));

  nlohmann::json result;
  for (int i = start; i < end; i++)
  {
    result.push_back(arr[i]);
  }
  return result;
}

template <typename Callable>
bool JS_some(const nlohmann::json &arr, Callable callback)
{
  if (arr.empty())
  {
    return false;
  }

  nlohmann::json::value_t expected_type = arr[0].type();

  for (const auto &element : arr)
  {
    if (element.type() != expected_type)
    {
      return false; // Return false if types are not the same
    }

    bool satisfiesCallback = false;
    try
    {
      satisfiesCallback = callback(element);
    }
    catch (const std::exception &ex)
    {
      // Handle exceptions from the callback function
      continue;
    }

    if (satisfiesCallback)
    {
      return true; // Return true if at least one element satisfies the callback
    }
  }

  return false; // Return false if no element satisfies the callback
}

nlohmann::json JS_sort(const nlohmann::json &arr, std::function<int(const nlohmann::json &, const nlohmann::json &)> compare = nullptr)
{
  nlohmann::json result = arr;

  if (!compare)
  {
    // Default comparison function for numbers and strings
    compare = [](const nlohmann::json &a, const nlohmann::json &b) -> int
    {
      if (a.is_number() && b.is_number())
      {
        return a < b ? -1 : (a > b ? 1 : 0);
      }
      else if (a.is_string() && b.is_string())
      {
        return a < b ? -1 : (a > b ? 1 : 0);
      }
      else
      {
        // If types are different, place numbers before strings
        return a.is_number() ? -1 : 1;
      }
    };
  }

  std::sort(result.begin(), result.end(), [&](const nlohmann::json &a, const nlohmann::json &b) -> bool
            { return compare(a, b) < 0; });

  return result;
}

nlohmann::json JS_splice(nlohmann::json &arr, int start, int deleteCount, const nlohmann::json &insertItems = nlohmann::json::array())
{
  nlohmann::json removedItems = nlohmann::json::array();

  if (start < 0)
  {
    start = arr.size() + start;
    if (start < 0)
    {
      start = 0;
    }
  }
  if (start > static_cast<int>(arr.size()))
  {
    start = arr.size();
  }
  if (deleteCount < 0)
  {
    deleteCount = 0;
  }
  if (deleteCount > static_cast<int>(arr.size()) - start)
  {
    deleteCount = arr.size() - start;
  }

  // Remove elements and store them in the removedItems array
  for (int i = 0; i < deleteCount; ++i)
  {
    removedItems.push_back(arr[start + i]);
  }

  nlohmann::json result = nlohmann::json::array();

  // Copy elements from the original array to the result array, skipping the removed items
  for (int i = 0; i < start; ++i)
  {
    result.push_back(arr[i]);
  }

  for (const auto &item : insertItems)
  {
    result.push_back(item);
  }

  for (int i = start + deleteCount; i < static_cast<int>(arr.size()); ++i)
  {
    result.push_back(arr[i]);
  }

  arr = result; // Update the original array

  return removedItems;
}

std::string JS_toLocaleString(const nlohmann::json &arr)
{
  return arr.dump();
}

std::string JS_toSource(const nlohmann::json &arr)
{
  return JS_toLocaleString(arr);
}

std::string JS_toString(const nlohmann::json &arr)
{
  return JS_toLocaleString(arr);
}

size_t JS_unshift(nlohmann::json &arr, const nlohmann::json &items)
{
  for (auto it = items.rbegin(); it != items.rend(); ++it)
  {
    arr.insert(arr.begin(), *it);
  }
  return arr.size();
}

nlohmann::json JS_values(const nlohmann::json &arr) { return arr; }



std::string JS_toString(bool value) { return value ? "true" : "false"; }
bool JS_valueOf(bool value) { return value ? true : false; }



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



std::string JS_valueOf(std::string value) { return std::string(value); }

std::string JS_charAt(const std::string &str, int index)
{
  if (index >= 0 && index < str.length())
  {
    return str.substr(index, 1);
  }
  return "";
}

int JS_charCodeAt(const std::string &str, int index)
{
  if (index >= 0 && index < str.length())
  {
    return static_cast<int>(str[index]);
  }
  return 0;
}

std::string JS_concat(const std::vector<std::string> &args)
{
  std::string result;
  for (const std::string &arg : args)
  {
    result += arg;
  }
  return result;
}

template <typename... Args>
std::string JS_concat(const std::string &arg1, Args... args)
{
  std::vector<std::string> argList = {arg1, args...};
  return JS_concat(argList);
}

bool JS_includes(const std::string &str, const std::string &searchStr)
{
  return str.find(searchStr) != std::string::npos;
}

bool JS_endsWith(const std::string &str, const std::string &searchStr)
{
  if (str.length() < searchStr.length())
  {
    return false;
  }
  return str.compare(str.length() - searchStr.length(), searchStr.length(),
                     searchStr) == 0;
}

int JS_indexOf(const std::string &str, const std::string &searchStr)
{
  size_t pos = str.find(searchStr);
  if (pos != std::string::npos)
  {
    return static_cast<int>(pos);
  }
  return -1;
}

int JS_lastIndexOf(const std::string &str, const std::string &searchStr)
{
  size_t pos = str.rfind(searchStr);
  if (pos != std::string::npos)
  {
    return static_cast<int>(pos);
  }
  return -1;
}

int JS_localeCompare(const std::string &str1, const std::string &str2)
{
  // Implementation may vary based on the desired locale comparison rules
  return str1.compare(str2);
}
nlohmann::json JS_match(const std::string &str, const std::string &regexStr)
{
  std::regex regex(regexStr);
  std::smatch match;

  nlohmann::json result = nlohmann::json::array();

  if (std::regex_search(str, match, regex))
  {
    nlohmann::json matchDetails = nlohmann::json::object();
    matchDetails["match"] = match[0].str();
    matchDetails["index"] = static_cast<int>(match.position());
    matchDetails["input"] = str;
    matchDetails["groups"] = nlohmann::json::object(); // No groups for now
    result.push_back(matchDetails);
  }

  return result;
}

nlohmann::json JS_match(const std::string &str, const std::regex &regex)
{
  std::smatch match;

  nlohmann::json result = nlohmann::json::array();

  if (std::regex_search(str, match, regex))
  {
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
                           const std::string &regexStr)
{
  std::regex regex(regexStr);
  std::sregex_iterator it(str.begin(), str.end(), regex);
  std::sregex_iterator end;

  nlohmann::json result = nlohmann::json::array();

  while (it != end)
  {
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

nlohmann::json JS_matchAll(const std::string &str, const std::regex &regex)
{
  std::sregex_iterator it(str.begin(), str.end(), regex);
  std::sregex_iterator end;

  nlohmann::json result = nlohmann::json::array();

  while (it != end)
  {
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

std::string JS_normalize(const std::string &str)
{
  // Implementation for normalizing Unicode strings (NFC normalization)
  // (You may use Unicode normalization libraries for this)
  return str; // Placeholder return value
}

std::string JS_padEnd(const std::string &str, int targetLength,
                      const std::string &padString)
{
  if (targetLength <= str.length())
  {
    return str;
  }
  int remainingLength = targetLength - str.length();
  int padCount = remainingLength / padString.length();
  int padRemainder = remainingLength % padString.length();
  std::string result = str;
  for (int i = 0; i < padCount; i++)
  {
    result += padString;
  }
  if (padRemainder > 0)
  {
    result += padString.substr(0, padRemainder);
  }
  return result;
}

std::string JS_padStart(const std::string &str, int targetLength,
                        const std::string &padString)
{
  if (targetLength <= str.length())
  {
    return str;
  }
  int remainingLength = targetLength - str.length();
  int padCount = remainingLength / padString.length();
  int padRemainder = remainingLength % padString.length();
  std::string result;
  for (int i = 0; i < padCount; i++)
  {
    result += padString;
  }
  if (padRemainder > 0)
  {
    result += padString.substr(0, padRemainder);
  }
  result += str;
  return result;
}

std::string JS_repeat(const std::string &str, int count)
{
  if (count <= 0)
  {
    return "";
  }
  std::string result;
  for (int i = 0; i < count; i++)
  {
    result += str;
  }
  return result;
}

std::string JS_replace(const std::string &str, const std::string &searchValue,
                       const std::string &replaceValue)
{
  std::string result = str;
  size_t pos = 0;

  while ((pos = result.find(searchValue, pos)) != std::string::npos)
  {
    result.replace(pos, searchValue.length(), replaceValue);
    pos += replaceValue.length();
  }

  return result;
}

int JS_search(const std::string &str, const std::string &regexStr)
{
  std::regex regex(regexStr);
  std::smatch match;

  if (std::regex_search(str, match, regex))
  {
    return static_cast<int>(match.position());
  }

  return -1;
}

std::string JS_slice(const std::string &str, int start, int end)
{
  if (start < 0)
  {
    start += str.length();
  }
  if (end < 0)
  {
    end += str.length();
  }
  if (start < 0)
  {
    start = 0;
  }
  if (end > str.length())
  {
    end = str.length();
  }
  if (end <= start)
  {
    return "";
  }
  return str.substr(start, end - start);
}

nlohmann::json JS_split(const std::string &str, const std::string &separator)
{
  nlohmann::json result = nlohmann::json::array();
  size_t start = 0;
  size_t end = str.find(separator);

  while (end != std::string::npos)
  {
    result.push_back(str.substr(start, end - start));
    start = end + separator.length();
    end = str.find(separator, start);
  }

  result.push_back(str.substr(start));

  return result;
}

bool JS_startsWith(const std::string &str, const std::string &searchStr)
{
  if (str.length() < searchStr.length())
  {
    return false;
  }
  return str.compare(0, searchStr.length(), searchStr) == 0;
}

std::string JS_substr(const std::string &str, int start, int length)
{
  if (start < 0)
  {
    start += str.length();
  }
  if (length <= 0 || start >= str.length())
  {
    return "";
  }
  if (start + length > str.length())
  {
    length = str.length() - start;
  }
  return str.substr(start, length);
}

std::string JS_substring(const std::string &str, int start, int end)
{
  if (start < 0)
  {
    start = 0;
  }
  if (end < 0)
  {
    end = 0;
  }
  if (start > end)
  {
    std::swap(start, end);
  }
  if (end > str.length())
  {
    end = str.length();
  }
  return str.substr(start, end - start);
}

std::string JS_toLocaleLowerCase(const std::string &str)
{
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(), ::tolower);
  return result;
}

std::string JS_toLocaleUpperCase(const std::string &str)
{
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(), ::toupper);
  return result;
}

std::string JS_toLowerCase(const std::string &str)
{
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(), ::tolower);
  return result;
}

std::string JS_toUpperCase(const std::string &str)
{
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(), ::toupper);
  return result;
}

std::string JS_toString(const std::string &str) { return str; }

std::string JS_trim(const std::string &str)
{
  std::regex trimPattern("^\\s+|\\s+$");
  return std::regex_replace(str, trimPattern, "");
}

std::string JS_trimEnd(const std::string &str)
{
  std::regex trimPattern("\\s+$");
  return std::regex_replace(str, trimPattern, "");
}

std::string JS_trimStart(const std::string &str)
{
  std::regex trimPattern("^\\s+");
  return std::regex_replace(str, trimPattern, "");
}


// Main Function (Have to be the only main function)
int main(){
  std::cout.setf(std::ios::boolalpha);
  using fs = __fs__;
auto idk = fs::readdirSync(std::string("."), nlohmann::json{}) ; 

std::cout << idk << '\n';
  return 0;
}  
