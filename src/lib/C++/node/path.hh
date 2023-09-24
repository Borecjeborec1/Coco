#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "nlohmann-json.hh"

class __path__ {
public:
  static char sep;
  static char delimiter;
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

  template <typename... Args> static std::string join(Args... args) {
    std::string result;
    joinInternal(result, args...);
    return result;
  }
  static bool isAbsolute(const std::string &path) {
    // Check if the path starts with a drive letter followed by a backslash
    return path.length() >= 3 && std::isalpha(path[0]) && path[1] == ':' &&
           (path[2] == '\\' || path[2] == '/');
  }
  static std::string normalize(const std::string &path) {
    std::vector<std::string> components;
    std::istringstream iss(path);
    std::string component;

    while (std::getline(iss, component, '\\')) {
      if (component == ".." && !components.empty()) {
        components.pop_back();
      } else if (component != ".") {
        components.push_back(component);
      }
    }

    // Rebuild the normalized path with backslashes
    std::string normalizedPath = join(components, "\\");

    // Check if the original path had a trailing slash
    if (path.back() == '\\') {
      normalizedPath += "\\";
    }

    return normalizedPath;
  }
  static nlohmann::json parse(const std::string &path) {
    nlohmann::json result;

    // Separate the path into components
    size_t lastSeparatorPos = path.find_last_of("/\\");
    std::string dir, base;
    if (lastSeparatorPos != std::string::npos) {
      dir = path.substr(0, lastSeparatorPos);
      base = path.substr(lastSeparatorPos + 1);
    } else {
      base = path;
    }

    // Determine root and extension
    size_t rootEnd = 0;
    if (isAbsolute(path)) {
      rootEnd = lastSeparatorPos + 1;
    }

    size_t extPos = base.find_last_of('.');
    std::string root = path.substr(0, rootEnd);
    std::string ext = (extPos != std::string::npos) ? base.substr(extPos) : "";
    std::string name =
        (extPos != std::string::npos) ? base.substr(0, extPos) : base;

    // Fill the result object
    result["root"] = root;
    result["dir"] = dir;
    result["base"] = base;
    result["ext"] = ext;
    result["name"] = name;

    return result;
  }
  static std::string relative(const std::string &from, const std::string &to) {
    // Calculate the relative path
    nlohmann::json result;

    // Split paths into directories
    std::vector<std::string> fromParts = splitPath(from);
    std::vector<std::string> toParts = splitPath(to);

    // Find the common root
    size_t i = 0;
    while (i < fromParts.size() && i < toParts.size() &&
           fromParts[i] == toParts[i]) {
      i++;
    }

    // Build the relative path
    for (size_t j = i; j < fromParts.size(); j++) {
      result["dir"] += ".." + pathSeparator();
    }

    for (size_t j = i; j < toParts.size(); j++) {
      if (!result["dir"].empty()) {
        result["dir"] += pathSeparator();
      }
      result["dir"] += toParts[j];
    }

    return result["dir"].get<std::string>();
  }

private:
  template <typename T, typename... Args>
  static void joinInternal(std::string &result, const T &first, Args... args) {
    result += first;
    result += '/';
    joinInternal(result, args...);
  }

  static void joinInternal(std::string &result) {
    // Do nothing, this is the base case
  }
  static std::vector<std::string> splitPath(const std::string &path) {
    // Split a path into its components
    std::vector<std::string> parts;
    size_t start = 0;
    size_t end;
    while ((end = path.find(pathSeparator(), start)) != std::string::npos) {
      parts.push_back(path.substr(start, end - start));
      start = end + 1;
    }
    parts.push_back(path.substr(start));
    return parts;
  }

  static std::string pathSeparator() { return "\\"; }
};

char __path__::sep = '\\';
char __path__::delimiter = ';';