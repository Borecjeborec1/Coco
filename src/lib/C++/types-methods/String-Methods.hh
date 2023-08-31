// Ignore imports
#include <string>
#include <vector>
#include <regex>
#include "nlohmann-json.hh"
// Ignore imports end

/////////////////////////// STRING METHODS ///////////////////////////////
std::string JS_valueOf(std::string value) { return std::string(value); }

std::string JS_charAt(const std::string &str, int index) {
  if (index >= 0 && index < str.length()) {
    return str.substr(index, 1);
  }
  return "";
}

int JS_charCodeAt(const std::string &str, int index) {
  if (index >= 0 && index < str.length()) {
    return static_cast<int>(str[index]);
  }
  return 0;
}

std::string JS_concat(const std::vector<std::string> &args) {
  std::string result;
  for (const std::string &arg : args) {
    result += arg;
  }
  return result;
}

template <typename... Args>
std::string JS_concat(const std::string &arg1, Args... args) {
  std::vector<std::string> argList = {arg1, args...};
  return JS_concat(argList);
}

bool JS_includes(const std::string &str, const std::string &searchStr) {
  return str.find(searchStr) != std::string::npos;
}

bool JS_endsWith(const std::string &str, const std::string &searchStr) {
  if (str.length() < searchStr.length()) {
    return false;
  }
  return str.compare(str.length() - searchStr.length(), searchStr.length(),
                     searchStr) == 0;
}

int JS_indexOf(const std::string &str, const std::string &searchStr) {
  size_t pos = str.find(searchStr);
  if (pos != std::string::npos) {
    return static_cast<int>(pos);
  }
  return -1;
}

int JS_lastIndexOf(const std::string &str, const std::string &searchStr) {
  size_t pos = str.rfind(searchStr);
  if (pos != std::string::npos) {
    return static_cast<int>(pos);
  }
  return -1;
}

int JS_localeCompare(const std::string &str1, const std::string &str2) {
  // Implementation may vary based on the desired locale comparison rules
  return str1.compare(str2);
}
nlohmann::json JS_match(const std::string &str, const std::string &regexStr) {
  std::regex regex(regexStr);
  std::smatch match;

  nlohmann::json result = nlohmann::json::array();

  if (std::regex_search(str, match, regex)) {
    nlohmann::json matchDetails = nlohmann::json::object();
    matchDetails["match"] = match[0].str();
    matchDetails["index"] = static_cast<int>(match.position());
    matchDetails["input"] = str;
    matchDetails["groups"] = nlohmann::json::object(); // No groups for now
    result.push_back(matchDetails);
  }

  return result;
}

nlohmann::json JS_matchAll(const std::string &str,
                           const std::string &regexStr) {
  std::regex regex(regexStr);
  std::sregex_iterator it(str.begin(), str.end(), regex);
  std::sregex_iterator end;

  nlohmann::json result = nlohmann::json::array();

  while (it != end) {
    nlohmann::json matchDetails = nlohmann::json::object();
    std::smatch match = *it;

    matchDetails["match"] = match[0].str();
    matchDetails["index"] = static_cast<int>(match.position());
    matchDetails["input"] = str;
    matchDetails["groups"] = nlohmann::json::object(); // No groups for now

    result.push_back(matchDetails);
    ++it;
  }

  return result;
}
std::string JS_normalize(const std::string &str) {
  // Implementation for normalizing Unicode strings (NFC normalization)
  // (You may use Unicode normalization libraries for this)
  return str; // Placeholder return value
}

std::string JS_padEnd(const std::string &str, int targetLength,
                      const std::string &padString) {
  if (targetLength <= str.length()) {
    return str;
  }
  int remainingLength = targetLength - str.length();
  int padCount = remainingLength / padString.length();
  int padRemainder = remainingLength % padString.length();
  std::string result = str;
  for (int i = 0; i < padCount; i++) {
    result += padString;
  }
  if (padRemainder > 0) {
    result += padString.substr(0, padRemainder);
  }
  return result;
}

std::string JS_padStart(const std::string &str, int targetLength,
                        const std::string &padString) {
  if (targetLength <= str.length()) {
    return str;
  }
  int remainingLength = targetLength - str.length();
  int padCount = remainingLength / padString.length();
  int padRemainder = remainingLength % padString.length();
  std::string result;
  for (int i = 0; i < padCount; i++) {
    result += padString;
  }
  if (padRemainder > 0) {
    result += padString.substr(0, padRemainder);
  }
  result += str;
  return result;
}

std::string JS_repeat(const std::string &str, int count) {
  if (count <= 0) {
    return "";
  }
  std::string result;
  for (int i = 0; i < count; i++) {
    result += str;
  }
  return result;
}

std::string JS_replace(const std::string &str, const std::string &searchValue,
                       const std::string &replaceValue) {
  std::string result = str;
  size_t pos = 0;

  while ((pos = result.find(searchValue, pos)) != std::string::npos) {
    result.replace(pos, searchValue.length(), replaceValue);
    pos += replaceValue.length();
  }

  return result;
}

int JS_search(const std::string &str, const std::string &regexStr) {
  std::regex regex(regexStr);
  std::smatch match;

  if (std::regex_search(str, match, regex)) {
    return static_cast<int>(match.position());
  }

  return -1;
}

std::string JS_slice(const std::string &str, int start, int end) {
  if (start < 0) {
    start += str.length();
  }
  if (end < 0) {
    end += str.length();
  }
  if (start < 0) {
    start = 0;
  }
  if (end > str.length()) {
    end = str.length();
  }
  if (end <= start) {
    return "";
  }
  return str.substr(start, end - start);
}

nlohmann::json JS_split(const std::string &str, const std::string &separator) {
  nlohmann::json result = nlohmann::json::array();
  size_t start = 0;
  size_t end = str.find(separator);

  while (end != std::string::npos) {
    result.push_back(str.substr(start, end - start));
    start = end + separator.length();
    end = str.find(separator, start);
  }

  result.push_back(str.substr(start));

  return result;
}

bool JS_startsWith(const std::string &str, const std::string &searchStr) {
  if (str.length() < searchStr.length()) {
    return false;
  }
  return str.compare(0, searchStr.length(), searchStr) == 0;
}

std::string JS_substr(const std::string &str, int start, int length) {
  if (start < 0) {
    start += str.length();
  }
  if (length <= 0 || start >= str.length()) {
    return "";
  }
  if (start + length > str.length()) {
    length = str.length() - start;
  }
  return str.substr(start, length);
}

std::string JS_substring(const std::string &str, int start, int end) {
  if (start < 0) {
    start = 0;
  }
  if (end < 0) {
    end = 0;
  }
  if (start > end) {
    std::swap(start, end);
  }
  if (end > str.length()) {
    end = str.length();
  }
  return str.substr(start, end - start);
}

std::string JS_toLocaleLowerCase(const std::string &str) {
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(), ::tolower);
  return result;
}

std::string JS_toLocaleUpperCase(const std::string &str) {
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(), ::toupper);
  return result;
}

std::string JS_toLowerCase(const std::string &str) {
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(), ::tolower);
  return result;
}

std::string JS_toUpperCase(const std::string &str) {
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(), ::toupper);
  return result;
}

std::string JS_toString(const std::string &str) { return str; }

std::string JS_trim(const std::string &str) {
  std::regex trimPattern("^\\s+|\\s+$");
  return std::regex_replace(str, trimPattern, "");
}

std::string JS_trimEnd(const std::string &str) {
  std::regex trimPattern("\\s+$");
  return std::regex_replace(str, trimPattern, "");
}

std::string JS_trimStart(const std::string &str) {
  std::regex trimPattern("^\\s+");
  return std::regex_replace(str, trimPattern, "");
}
/////////////////////////// STRING METHODS END ///////////////////////////////
