#include <string>
#include "../nlohmann-json.hh"

nlohmann::json &operator+=(nlohmann::json &j, int x)
{
  if (j.is_number())
  {
    j = j.get<int>() + x;
  }
  return j;
}

nlohmann::json &operator-=(nlohmann::json &j, int x)
{
  if (j.is_number())
  {
    j = j.get<int>() - x;
  }
  return j;
}

nlohmann::json &operator*=(nlohmann::json &j, int x)
{
  if (j.is_number())
  {
    j = j.get<int>() * x;
  }
  return j;
}

nlohmann::json &operator/=(nlohmann::json &j, int x)
{
  if (j.is_number() && x != 0)
  {
    j = j.get<int>() / x;
  }
  return j;
}

nlohmann::json operator+(const nlohmann::json &lhs, const int &rhs)
{
  if (lhs.is_number())
  {
    return lhs.get<int>() + rhs;
  }
  return nlohmann::json();
}

nlohmann::json operator-(const nlohmann::json &lhs, const int &rhs)
{
  if (lhs.is_number())
  {
    return lhs.get<int>() - rhs;
  }
  return nlohmann::json();
}

nlohmann::json operator*(const nlohmann::json &lhs, const int &rhs)
{
  if (lhs.is_number())
  {
    return lhs.get<int>() * rhs;
  }
  return nlohmann::json();
}

nlohmann::json operator%(const nlohmann::json &lhs, const int &rhs)
{
  if (lhs.is_number() && rhs != 0)
  {
    return lhs.get<int>() % rhs;
  }
  return nlohmann::json();
}

nlohmann::json operator/(const nlohmann::json &lhs, int &rhs)
{
  if (lhs.is_number() && rhs != 0)
  {
    return lhs.get<int>() / rhs;
  }
  return nlohmann::json();
}

nlohmann::json &operator++(nlohmann::json &j)
{
  if (j.is_number())
  {
    j = j.get<int>() + 1;
  }
  return j;
}

nlohmann::json &operator--(nlohmann::json &j)
{
  if (j.is_number())
  {
    j = j.get<int>() - 1;
  }
  return j;
}

nlohmann::json &operator+=(nlohmann::json &j, double x)
{
  if (j.is_number())
  {
    j = j.get<double>() + x;
  }
  return j;
}

nlohmann::json &operator-=(nlohmann::json &j, double x)
{
  if (j.is_number())
  {
    j = j.get<double>() - x;
  }
  return j;
}

nlohmann::json &operator*=(nlohmann::json &j, double x)
{
  if (j.is_number())
  {
    j = j.get<double>() * x;
  }
  return j;
}

nlohmann::json &operator/=(nlohmann::json &j, double x)
{
  if (j.is_number() && x != 0)
  {
    j = j.get<double>() / x;
  }
  return j;
}

nlohmann::json operator+(const nlohmann::json &lhs, const double &rhs)
{
  if (lhs.is_number())
  {
    return lhs.get<double>() + rhs;
  }
  return nlohmann::json();
}

nlohmann::json operator-(const nlohmann::json &lhs, const double &rhs)
{
  if (lhs.is_number())
  {
    return lhs.get<double>() - rhs;
  }
  return nlohmann::json();
}

nlohmann::json operator*(const nlohmann::json &lhs, const double &rhs)
{
  if (lhs.is_number())
  {
    return lhs.get<double>() * rhs;
  }
  return nlohmann::json();
}

nlohmann::json operator%(const nlohmann::json &lhs, const double &rhs)
{
  if (lhs.is_number() && rhs != 0)
  {
    return lhs.get<int>() % (int)rhs;
  }
  return nlohmann::json();
}

nlohmann::json operator/(const nlohmann::json &lhs, double &rhs)
{
  if (lhs.is_number() && rhs != 0)
  {
    return lhs.get<double>() / rhs;
  }
  return nlohmann::json();
}

nlohmann::json &operator+=(nlohmann::json &j, long long x)
{
  if (j.is_number())
  {
    j = j.get<long long>() + x;
  }
  return j;
}

nlohmann::json &operator-=(nlohmann::json &j, long long x)
{
  if (j.is_number())
  {
    j = j.get<long long>() - x;
  }
  return j;
}

nlohmann::json &operator*=(nlohmann::json &j, long long x)
{
  if (j.is_number())
  {
    j = j.get<long long>() * x;
  }
  return j;
}

nlohmann::json &operator/=(nlohmann::json &j, long long x)
{
  if (j.is_number() && x != 0)
  {
    j = j.get<long long>() / x;
  }
  return j;
}

nlohmann::json operator+(const nlohmann::json &lhs, const long long &rhs)
{
  if (lhs.is_number())
  {
    return lhs.get<long long>() + rhs;
  }
  return nlohmann::json();
}

nlohmann::json operator-(const nlohmann::json &lhs, const long long &rhs)
{
  if (lhs.is_number())
  {
    return lhs.get<long long>() - rhs;
  }
  return nlohmann::json();
}

nlohmann::json operator*(const nlohmann::json &lhs, const long long &rhs)
{
  if (lhs.is_number())
  {
    return lhs.get<long long>() * rhs;
  }
  return nlohmann::json();
}

nlohmann::json operator%(const nlohmann::json &lhs, const long long &rhs)
{
  if (lhs.is_number() && rhs != 0)
  {
    return lhs.get<int>() % (int)rhs;
  }
  return nlohmann::json();
}

nlohmann::json operator/(const nlohmann::json &lhs, long long &rhs)
{
  if (lhs.is_number() && rhs != 0)
  {
    return lhs.get<long long>() / rhs;
  }
  return nlohmann::json();
}

nlohmann::json operator+(const nlohmann::json &lhs, const nlohmann::json &rhs)
{
  if (lhs.is_number())
  {
    return lhs.get<double>() + rhs.get<double>();
  }
  return nlohmann::json();
}

nlohmann::json operator-(const nlohmann::json &lhs, const nlohmann::json &rhs)
{
  if (lhs.is_number())
  {
    return lhs.get<double>() - rhs.get<double>();
  }
  return nlohmann::json();
}

nlohmann::json operator*(const nlohmann::json &lhs, const nlohmann::json &rhs)
{
  if (lhs.is_number())
  {
    return lhs.get<double>() * rhs.get<double>();
  }
  return nlohmann::json();
}

nlohmann::json operator%(const nlohmann::json &lhs, const nlohmann::json &rhs)
{
  if (lhs.is_number() && rhs != 0)
  {
    return lhs.get<long long>() % rhs.get<long long>();
  }
  return nlohmann::json();
}

nlohmann::json operator/(const nlohmann::json &lhs, nlohmann::json &rhs)
{
  if (lhs.is_number() && rhs != 0)
  {
    return lhs.get<double>() / rhs.get<double>();
  }
  return nlohmann::json();
}