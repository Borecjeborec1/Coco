// Ignore imports
#include <iostream>
#include <limits>
#include <cmath>
#include <string>
#include <cstdint>
// Ignore imports end

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