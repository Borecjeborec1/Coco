#include "types.hh"

JSString::JSString(const std::string &val)
    : value(val), _length(value.length()) {}

std::string JSString::toString() const { return value; }
JSNumber JSNumber::operator%(const JSNumber &other) const {
  if (other.value != 0)
    return JSNumber(std::fmod(value, other.value));
  else
    throw std::runtime_error("Modulo by zero");
}

JSString JSString::operator+(const JSString &other) const {
  return JSString(value + other.value);
}

bool JSString::operator==(const JSString &other) const {
  return value == other.value;
}

bool JSString::operator!=(const JSString &other) const {
  return value != other.value;
}

JSString JSString::operator[](const JSNumber &index) const {
  int idx = static_cast<int>(index.toDouble());
  if (idx >= 0 && idx < value.length())
    return JSString(std::string(1, value[idx]));
  else
    throw std::out_of_range("Index out of range");
}

JSString JSString::slice(JSNumber start, JSNumber end) const {
  return JSString(value.substr(start.toDouble(), end.toDouble()));
}

JSString JSString::substring(JSNumber start_JSTYPE, JSNumber end_JSTYPE) const {
  double start = start_JSTYPE.toDouble();
  double end = end_JSTYPE.toDouble();
  double len = value.length();
  if (start < 0)
    start = 0;
  if (end < 0 || end > len)
    end = len;
  if (start > end)
    std::swap(start, end);
  return JSString(value.substr(start, end - start));
}

JSString JSString::substr(JSNumber start, JSNumber length) const {
  return JSString(value.substr(start.toDouble(), length.toDouble()));
}

JSString JSString::replace(const JSString &search,
                           const JSString &replacement) const {
  std::string result = value;
  size_t pos = 0;
  while ((pos = result.find(search.toString(), pos)) != std::string::npos) {
    result.replace(pos, search.toString().length(), replacement.toString());
    pos += replacement.toString().length();
  }
  return JSString(result);
}

JSString JSString::replaceAll(const JSString &search,
                              const JSString &replacement) const {
  std::string result = value;
  size_t pos = 0;
  while ((pos = result.find(search.toString(), pos)) != std::string::npos) {
    result.replace(pos, search.toString().length(), replacement.toString());
    pos += replacement.toString().length();
  }
  return JSString(result);
}

JSString JSString::toUpperCase() const {
  std::string result = value;
  for (char &c : result)
    c = std::toupper(c);
  return JSString(result);
}

JSString JSString::toLowerCase() const {
  std::string result = value;
  for (char &c : result)
    c = std::tolower(c);
  return JSString(result);
}

JSString JSString::concat(const JSString &other) const {
  return JSString(value + other.value);
}

JSString JSString::trim() const {
  std::string result = value;
  JSNumber start = result.find_first_not_of(" \t\r\n");
  JSNumber end = result.find_last_not_of(" \t\r\n");
  if (start == std::string::npos || end == std::string::npos)
    return JSString("");
  return JSString(
      result.substr(start.toDouble(), (end - start + 1).toDouble()));
}

JSString JSString::trimStart() const {
  std::string result = value;
  JSNumber start = result.find_first_not_of(" \t\r\n");
  if (start == std::string::npos)
    return JSString("");
  return JSString(result.substr(start.toDouble()));
}

JSString JSString::trimEnd() const {
  std::string result = value;
  JSNumber end = result.find_last_not_of(" \t\r\n");
  if (end == std::string::npos)
    return JSString("");
  return JSString(result.substr(0, (end + 1).toDouble()));
}

JSString JSString::charAt(JSNumber index) const {
  if (index >= 0 && index < value.length())
    return JSString(std::string(1, value[index.toDouble()]));
  else
    throw std::out_of_range("Index out of range");
}

JSNumber JSString::charCodeAt(JSNumber index) const {

  if (index >= 0 && index < value.length())
    return JSNumber(static_cast<JSNumber>(value[index.toDouble()]));
  else
    throw std::out_of_range("Index out of range");
}

bool JSString::includes(const JSString &substring) const {
  return value.find(substring.toString()) != std::string::npos;
}

JSArray JSString::match(const JSString &regexp) const {
  JSArray result;
  std::regex rgx(regexp.toString());
  std::smatch matches;
  std::string tempValue = value;
  while (std::regex_search(tempValue, matches, rgx)) {
    result.push(matches.str());
    tempValue = matches.suffix();
  }
  return result;
}

JSArray JSString::split(const JSString &separator) const {
  JSArray result;
  size_t start = 0;
  size_t end = value.find(separator.toString());
  while (end != std::string::npos) {
    result.push(JSString(value.substr(start, end - start)));
    start = end + separator.toString().length();
    end = value.find(separator.toString(), start);
  }
  result.push(JSString(value.substr(start)));
  return result;
}

bool JSString::startsWith(const JSString &searchString) const {
  return value.find(searchString.toString()) == 0;
}

bool JSString::endsWith(const JSString &searchString) const {
  JSNumber pos = value.rfind(searchString.toString());
  return pos != std::string::npos &&
         pos == value.length() - searchString.toString().length();
}

JSNumber JSString::indexOf(const JSString &searchValue) const {
  JSNumber pos = value.find(searchValue.toString());
  return pos != std::string::npos ? JSNumber(static_cast<JSNumber>(pos))
                                  : JSNumber(-1);
}

JSNumber JSString::lastIndexOf(const JSString &searchValue) const {
  JSNumber pos = value.rfind(searchValue.toString());
  return pos != std::string::npos ? JSNumber(static_cast<JSNumber>(pos))
                                  : JSNumber(-1);
}

JSString JSString::padStart(JSNumber targetLength,
                            const JSString &padString) const {
  if (targetLength <= _length)
    return JSString(value);

  JSNumber padLength = targetLength - _length;
  JSNumber padCount = padLength / padString.toString().length();
  JSNumber remainingPadLength = padLength % padString.toString().length();
  std::string paddedString;
  for (JSNumber i = 0; i < padCount; ++i) {
    paddedString += padString.toString();
  }
  paddedString += padString.toString().substr(0, remainingPadLength.toDouble());
  paddedString += value;
  return JSString(paddedString);
}

JSString JSString::padEnd(JSNumber targetLength,
                          const JSString &padString) const {
  if (targetLength <= _length)
    return JSString(value);

  JSNumber padLength = targetLength - _length;
  JSNumber padCount = padLength / padString.toString().length();
  JSNumber remainingPadLength = padLength % padString.toString().length();
  std::string paddedString = value;
  for (JSNumber i = 0; i < padCount; ++i) {
    paddedString += padString.toString();
  }
  paddedString += padString.toString().substr(0, remainingPadLength.toDouble());
  return JSString(paddedString);
}

JSNumber JSString::search(const JSString &regexp) const {
  std::regex rgx(regexp.toString());
  std::smatch matches;
  if (std::regex_search(value, matches, rgx)) {
    return JSNumber(static_cast<JSNumber>(matches.position()));
  }
  return JSNumber(-1);
}
