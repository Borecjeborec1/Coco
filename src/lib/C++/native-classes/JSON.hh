// Ignore imports
#include <string>
#include "nlohmann-json.hh"
// Ignore imports end

class __JSON__
{
public:
  static std::string stringify(const nlohmann::json &jsonObj)
  {
    return jsonObj.dump();
  }

  static nlohmann::json parse(const std::string &jsonString)
  {
    return nlohmann::json::parse(jsonString);
  }
};