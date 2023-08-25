#include <string>
#include "nlohmann-json.hpp"

class JSON {
public:
  static std::string stringify(const nlohmann::json &jsonObj) {
    return jsonObj.dump();
  }

  static nlohmann::json parse(const std::string &jsonString) {
    return nlohmann::json::parse(jsonString);
  }
};