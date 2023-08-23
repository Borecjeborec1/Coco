#include <iostream>
#include <string>
#include <map>
#include <variant>

class JS_Object {
public:
  using Value = std::variant<int, double, std::string, JS_Object>;

  JS_Object() = default;

  JS_Object(std::initializer_list<std::pair<std::string, Value>> init) {
    for (const auto &pair : init) {
      properties[pair.first] = pair.second;
    }
  }
  void addProperty(const std::string &name, const Value &value) {
    properties[name] = value;
  }

  const Value &operator[](const std::string &name) const {
    return properties.at(name);
  }

private:
  std::map<std::string, Value> properties;
};