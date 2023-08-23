#include "json.hpp"
#include <iostream>

int main() {
  nlohmann::json jsonObj = {};

  nlohmann::json jsonArray = {1.5, "hello", true, jsonObj};

  std::cout << jsonArray["name"] << std::endl;
  std::cout << jsonArray[0] << std::endl;

  return 0;
}