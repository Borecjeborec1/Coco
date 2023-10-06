#include <iostream>
#include <string>
#include <sstream>

class __String__
{
public:
  template <typename... Args>
  static std::string fromCharCode(Args... charCodes)
  {
    std::string result;
    appendChars(result, charCodes...);
    return result;
  }

  template <typename... Args>
  static std::string fromCodePoint(Args... codePoints)
  {
    std::string result;
    appendCodePoints(result, codePoints...);
    return result;
  }

  // static std::string raw(const std::vector<std::string> &strings) {

private:
  template <typename... Args>
  static void appendChars(std::string &result, int charCode, Args... args)
  {
    result += static_cast<char>(charCode);
    appendChars(result, args...);
  }

  static void appendChars(std::string &) {}

  template <typename... Args>
  static void appendCodePoints(std::string &result, int codePoint,
                               Args... args)
  {
    if (codePoint >= 0x10000)
    {
      codePoint -= 0x10000;
      result += static_cast<char>((codePoint >> 10) + 0xD800);
      result += static_cast<char>((codePoint & 0x3FF) + 0xDC00);
    }
    else
    {
      result += static_cast<char>(codePoint);
    }
    appendCodePoints(result, args...);
  }

  static void appendCodePoints(std::string &) {}
};
