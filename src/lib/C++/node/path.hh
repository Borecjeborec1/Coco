#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class __path__ {
public:
  static std::string basename(const std::string &path,
                              const std::string &suffix = "") {
    std::string base = path.substr(path.find_last_of('/') + 1);
    if (suffix.empty() ||
        base.substr(base.length() - suffix.length()) != suffix) {
      return base;
    }
    return base.substr(0, base.length() - suffix.length());
  }

  static char delimiter() { return '/'; }

  static std::string dirname(const std::string &path) {
    size_t found = path.find_last_of('/');
    if (found != std::string::npos) {
      return path.substr(0, found);
    }
    return "";
  }

  static std::string extname(const std::string &path) {
    size_t found = path.find_last_of('.');
    if (found != std::string::npos && found > path.find_last_of('/')) {
      return path.substr(found);
    }
    return "";
  }

  static std::string join(const std::vector<std::string> &paths) {
    std::string result;
    for (const std::string &path : paths) {
      if (!result.empty() && result.back() != '/') {
        result += '/';
      }
      result += path;
    }
    return result;
  }
};