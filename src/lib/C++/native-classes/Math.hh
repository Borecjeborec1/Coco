
// Ignore imports
#include <iostream>
#include <cmath>
#include <cstdarg>
#include <limits>
// Ignore imports end

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
