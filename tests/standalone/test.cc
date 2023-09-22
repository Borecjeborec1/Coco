#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

class Date
{
public:
  Date()
  {
    std::time_t now = std::time(nullptr);
    std::tm *timeInfo = std::gmtime(&now);
    year_ = timeInfo->tm_year + 1900;
    month_ = timeInfo->tm_mon + 1;
    day_ = timeInfo->tm_mday;
    hours_ = timeInfo->tm_hour;
    minutes_ = timeInfo->tm_min;
    seconds_ = timeInfo->tm_sec;
  }

  Date(int year, int month, int day, int hours = 0, int minutes = 0, int seconds = 0)
      : year_(year), month_(month), day_(day), hours_(hours), minutes_(minutes), seconds_(seconds) {}

  static Date parse(const std::string &dateString)
  {
    int year, month, day, hours, minutes, seconds;
    sscanf(dateString.c_str(), "%d-%d-%dT%d:%d:%d", &year, &month, &day, &hours, &minutes, &seconds);
    return Date(year, month, day, hours, minutes, seconds);
  }

  std::string toISOString() const
  {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << year_ << "-"
        << std::setw(2) << month_ << "-"
        << std::setw(2) << day_ << "T"
        << std::setw(2) << hours_ << ":"
        << std::setw(2) << minutes_ << ":"
        << std::setw(2) << seconds_ << "Z";
    return oss.str();
  }

private:
  int year_;
  int month_;
  int day_;
  int hours_;
  int minutes_;
  int seconds_;
};

int main()
{
  Date currentDate;
  std::cout << "Current Date: " << currentDate.toISOString() << std::endl;

  std::string dateString = "2023-09-17T12:34:56";
  Date parsedDate = Date::parse(dateString);
  std::cout << "Parsed Date: " << parsedDate.toISOString() << std::endl;

  return 0;
}
