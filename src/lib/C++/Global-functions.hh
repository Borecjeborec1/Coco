// Ignore imports
#include <iostream>
#include <sstream>
#include <cmath>
#include <iomanip>
// Ignore imports end

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
