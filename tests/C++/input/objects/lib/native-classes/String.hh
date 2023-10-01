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
