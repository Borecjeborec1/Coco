#include "../../../src/lib/types-methods/All-Types.hh"
#include <string>
#include <iostream>

int main() {
  auto num = static_cast<double>(12);
  auto boolean = static_cast<bool>(true);
  auto str = std::string("test");

  std::cout << JS_valueOf(num) << std::endl;
  std::cout << JS_valueOf(boolean) << std::endl;
  std::cout << JS_valueOf(str) << std::endl;

  return 0;
}