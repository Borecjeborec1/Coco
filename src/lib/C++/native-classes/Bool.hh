// Ignore imports
#include <string>
#include "nlohmann-json.hh"
// Ignore imports end

bool JS_CAST_ExclamationBoolean(int value) { return !(value != 0); }

bool JS_CAST_ExclamationBoolean(double value) { return !(value != 0.0); }

bool JS_CAST_ExclamationBoolean(const std::string &value) {
  return !(!value.empty());
}

bool JS_CAST_ExclamationBoolean(bool value) { return !value; }

bool JS_CAST_ExclamationBoolean(const nlohmann::json &value) {
  return !(!value.empty());
}