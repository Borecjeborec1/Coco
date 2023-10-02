#include <iostream>
#include <vector>
#include <string>
#include "../nlohmann-json.hh"

class __Array__ {
public:
  static nlohmann::json from(const nlohmann::json &obj) {
    if (obj.is_string()) {
      std::string str = obj;
      nlohmann::json jsonArray;
      for (char c : str) {
        jsonArray.push_back(std::string(1, c));
      }
      return jsonArray;
    } else {
      return {};
    }
  }

  template <typename... Args> static nlohmann::json of(Args... elements) {
    nlohmann::json jsonArray;
    addElementsToArray(jsonArray, elements...);
    return jsonArray;
  }

private:
  template <typename T, typename... Args>
  static void addElementsToArray(nlohmann::json &jsonArray, T element,
                                 Args... elements) {
    jsonArray.push_back(element);
    addElementsToArray(jsonArray, elements...);
  }

  static void addElementsToArray(nlohmann::json &jsonArray) {}
};
