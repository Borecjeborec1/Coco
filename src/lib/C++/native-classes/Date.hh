#include <sstream>
#include <ctime>
#include <chrono>
#include <iomanip>

class __Date__
{
public:
  __Date__()
  {
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
  __Date__(long long milliseconds)
  {
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
  static long long parse(const std::string &dateString)
  {
    int year, month, day, hours, minutes, seconds;
    sscanf(dateString.c_str(), "%d-%d-%dT%d:%d:%d", &year, &month, &day, &hours,
           &minutes, &seconds);
    __Date__ parsedDate(year, month, day, hours, minutes, seconds);
    return parsedDate.toMillisecondsSinceEpoch();
  }

  static long long now()
  {
    std::chrono::milliseconds ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
    return ms.count();
  }
  static long long UTC(int year, int month, int day, int hours = 0,
                       int minutes = 0, int seconds = 0, int milliseconds = 0)
  {
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

  void setMonth(int month)
  {
    if (month < 0)
    {
      int yearsToSubtract = (-month - 1) / 12 + 1;
      setFullYear(year_ - yearsToSubtract);
      month = 11 - ((-month - 1) % 12);
    }
    else if (month > 11)
    {
      int yearsToAdd = month / 12;
      setFullYear(year_ + yearsToAdd);
      month = month % 12;
    }
    month_ = month + 1;
  }

  void setDate(int day)
  {
    while (day < 1)
    {
      int prevMonthDays = daysInMonth(year_, month_ - 1);
      setMonth(month_ - 2);
      day += prevMonthDays;
    }
    while (day > daysInMonth(year_, month_))
    {
      day -= daysInMonth(year_, month_);
      setMonth(month_);
    }
    day_ = day;
  }

  void setHours(int hours)
  {
    if (hours < 0)
    {
      int daysToSubtract = (-hours - 1) / 24 + 1;
      setDate(day_ - daysToSubtract);
      hours = 23 - ((-hours - 1) % 24);
    }
    else if (hours > 23)
    {
      int daysToAdd = hours / 24;
      setDate(day_ + daysToAdd);
      hours = hours % 24;
    }
    hours_ = hours;
  }

  void setMinutes(int minutes)
  {
    if (minutes < 0)
    {
      int hoursToSubtract = (-minutes - 1) / 60 + 1;
      setHours(hours_ - hoursToSubtract);
      minutes = 59 - ((-minutes - 1) % 60);
    }
    else if (minutes > 59)
    {
      int hoursToAdd = minutes / 60;
      setHours(hours_ + hoursToAdd);
      minutes = minutes % 60;
    }
    minutes_ = minutes;
  }

  void setSeconds(int seconds)
  {
    if (seconds < 0)
    {
      int minutesToSubtract = (-seconds - 1) / 60 + 1;
      setMinutes(minutes_ - minutesToSubtract);
      seconds = 59 - ((-seconds - 1) % 60);
    }
    else if (seconds > 59)
    {
      int minutesToAdd = seconds / 60;
      setMinutes(minutes_ + minutesToAdd);
      seconds = seconds % 60;
    }
    seconds_ = seconds;
  }

  void setMilliseconds(int milliseconds)
  {
    if (milliseconds < 0)
    {
      int secondsToSubtract = (-milliseconds - 1) / 1000 + 1;
      setSeconds(seconds_ - secondsToSubtract);
      milliseconds = 999 - ((-milliseconds - 1) % 1000);
    }
    else if (milliseconds > 999)
    {
      int secondsToAdd = milliseconds / 1000;
      setSeconds(seconds_ + secondsToAdd);
      milliseconds = milliseconds % 1000;
    }
    milliseconds_ = milliseconds;
  }

  std::string toISOString() const
  {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << year_ << "-" << std::setw(2)
        << month_ << "-" << std::setw(2) << day_ << "T" << std::setw(2)
        << hours_ << ":" << std::setw(2) << minutes_ << ":" << std::setw(2)
        << seconds_ << "Z";
    return oss.str();
  }
  std::string toString() const
  {
    std::string dateString = toDateString();
    std::string timeString = toTimeString();

    return dateString + " " + timeString;
  }

  std::string toDateString() const
  {
    char buffer[80];
    std::tm timeInfo{};
    timeInfo.tm_year = year_ - 1900;
    timeInfo.tm_mon = month_ - 1;
    timeInfo.tm_mday = day_;
    timeInfo.tm_hour = hours_;
    timeInfo.tm_min = minutes_;
    timeInfo.tm_sec = seconds_;

    std::mktime(&timeInfo);

    if (std::strftime(buffer, sizeof(buffer), "%a %b %d %Y", &timeInfo) == 0)
    {
      return "";
    }

    return buffer;
  }
  std::string toTimeString() const
  {
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

  std::string getTimezoneName() const
  {
    // For simplicity, this example just returns a hardcoded value.
    return "Central European Summer Time";
  }
  std::string toJSON() const { return toISOString(); }

  long long valueOf() const { return toMilliseconds(); }

  int getDate() const { return day_; }

  int getDay() const
  {
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

  int getTimezoneOffset() const
  {
    std::time_t now = std::time(nullptr);
    std::tm localTime = *std::localtime(&now);
    std::tm gmTime = *std::gmtime(&now);

    int localMinutes = localTime.tm_hour * 60 + localTime.tm_min;
    int gmMinutes = gmTime.tm_hour * 60 + gmTime.tm_min;

    return gmMinutes - localMinutes;
  }
  std::string toUTCString() const
  {
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
                      &timeInfo) == 0)
    {
      return "";
    }

    return buffer;
  }

  std::string toLocaleString() const
  {
    char buffer[256];
    std::tm timeInfo{};
    timeInfo.tm_year = year_ - 1900;
    timeInfo.tm_mon = month_ - 1;
    timeInfo.tm_mday = day_;
    timeInfo.tm_hour = hours_;
    timeInfo.tm_min = minutes_;
    timeInfo.tm_sec = seconds_;

    if (std::strftime(buffer, sizeof(buffer), "%x", &timeInfo) == 0)
    {
      return "";
    }

    char timeBuffer[256];
    if (std::strftime(timeBuffer, sizeof(timeBuffer), "%I:%M:%S %p",
                      &timeInfo) == 0)
    {
      return "";
    }

    return std::string(buffer) + ", " + timeBuffer;
  }

  std::string toLocaleDateString() const
  {
    char buffer[256];
    std::tm timeInfo{};
    timeInfo.tm_year = year_ - 1900;
    timeInfo.tm_mon = month_ - 1;
    timeInfo.tm_mday = day_;

    if (std::strftime(buffer, sizeof(buffer), "%x", &timeInfo) == 0)
    {
      return "";
    }

    return std::string(buffer);
  }

  std::string toLocaleTimeString() const
  {
    char buffer[256];
    std::tm timeInfo{};
    timeInfo.tm_hour = hours_;
    timeInfo.tm_min = minutes_;
    timeInfo.tm_sec = seconds_;

    if (std::strftime(buffer, sizeof(buffer), "%I:%M:%S %p", &timeInfo) == 0)
    {
      return "";
    }

    return buffer;
  }

  friend std::ostream &operator<<(std::ostream &os, const __Date__ &date)
  {
    os << date.toISOString();
    return os;
  }

  bool operator<(const __Date__ &other) const
  {
    return toMilliseconds() < other.toMilliseconds();
  }

  bool operator<=(const __Date__ &other) const
  {
    return toMilliseconds() <= other.toMilliseconds();
  }

  bool operator>(const __Date__ &other) const
  {
    return toMilliseconds() > other.toMilliseconds();
  }

  bool operator>=(const __Date__ &other) const
  {
    return toMilliseconds() >= other.toMilliseconds();
  }

  bool operator==(const __Date__ &other) const
  {
    return toMilliseconds() == other.toMilliseconds();
  }

  bool operator!=(const __Date__ &other) const
  {
    return toMilliseconds() != other.toMilliseconds();
  }
  bool operator<(const double &other) const
  {
    return toMilliseconds() < (long long)other;
  }

  bool operator<=(const double &other) const
  {
    return toMilliseconds() <= (long long)other;
  }

  bool operator>(const double &other) const
  {
    return toMilliseconds() > (long long)other;
  }

  bool operator>=(const double &other) const
  {
    return toMilliseconds() >= (long long)other;
  }

  bool operator==(const double &other) const
  {
    return toMilliseconds() == (long long)other;
  }

  bool operator!=(const double &other) const
  {
    return toMilliseconds() != (long long)other;
  }
  bool operator<(const std::string &other) const { return false; }

  bool operator<=(const std::string &other) const { return false; }

  bool operator>(const std::string &other) const { return false; }

  bool operator>=(const std::string &other) const { return false; }

  bool operator==(const std::string &other) const
  {
    return toISOString() == other;
  }

  bool operator!=(const std::string &other) const
  {
    return toISOString() != other;
  }

  std::string operator+(const std::string &str) const
  {
    return toDateString() + str;
  }
  std::string operator-(const std::string &str) const { return toDateString(); }
  __Date__ operator+(const __Date__ &other) const
  {
    return __Date__(toMilliseconds() + other.toMilliseconds());
  }

  __Date__ operator-(const __Date__ &other) const
  {
    return __Date__(toMilliseconds() - other.toMilliseconds());
  }
  __Date__ operator+(const double &other) const
  {
    return __Date__(toMilliseconds() + (long long)other);
  }

  __Date__ operator-(const double &other) const
  {
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
  long long toMilliseconds() const
  {
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
  long long toMillisecondsSinceEpoch() const
  {
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
  int daysInMonth(int year, int month)
  {
    int daysInEachMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
      daysInEachMonth[1] = 29;
    }

    if (month < 0)
    {
      month = 0;
    }
    else if (month > 11)
    {
      month = 11;
    }

    return daysInEachMonth[month];
  }
};

std::string JS_toString(__Date__ value) { return value.toString(); }

long long JS_valueOf(__Date__ value) { return value.valueOf(); }

std::string JS_toString(long long value)
{
  return std::to_string(value);
}

long long JS_valueOf(long long value) { return value; }

std::string JS_toLocaleString(__Date__ value) { return value.toLocaleString(); }