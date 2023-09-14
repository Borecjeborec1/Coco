#include "nlohmann-json.hh"
#include <iostream>
#include <string>

int main() {
  nlohmann::json data = {12.312};
  nlohmann::json dataString = {"heyo"};
  auto var = data[0].is_number()
                 ? data[0].is_number_integer() ? (int)data[0] : (float)data[0]
                 : data[0].is_boolean()
                       ? (bool)data[0]
                       : (data[0].is_string()) ? (std::string)data[0] : data[0];
  var += 21;
  std::cout << var;
  return 0;
}