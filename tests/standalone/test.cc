

// All new includes goes here
#include <chrono>
#include <iostream>
#include "./lib/Global-functions.hh"
#include "./lib/native-classes/Array.hh"
#include "./lib/native-classes/Date.hh"
#include "./lib/native-classes/JSON.hh"
#include "./lib/native-classes/Math.hh"
#include "./lib/native-classes/Number.hh"
#include "./lib/native-classes/String.hh"
#include "./lib/nlohmann-json.hh"
#include "./lib/operators/json-operators.hh"
#include "./lib/operators/string-operators.hh"
#include "./lib/types-methods/Array-Methods.hh"
#include "./lib/types-methods/Boolean-Methods.hh"
#include "./lib/types-methods/Number-Methods.hh"
#include "./lib/types-methods/String-Methods.hh"

namespace test {
auto sum = [](auto a, auto b) { return (a + b); };
auto subst = [](auto a, auto b) { return (a - b); };
//  = nlohmann::json{{"sum", sum}, {"subst", subst}};
};
namespace sfckZM {
auto sum = [](auto a, auto b) { return (a + b); };
auto subst = [](auto a, auto b) { return (a - b); };
//  = nlohmann::json{{"sum", sum}, {"subst", subst}};
};

// Main Function (Have to be the only main function)
int main() {
  std::cout.setf(std::ios::boolalpha);

  auto sum = sfckZM::summ || 5;
  auto subst = sfckZM::subst;
  std::cout << sum(static_cast<int>(1), static_cast<int>(2)) << '\n';
  std::cout << test::sum(static_cast<int>(1), static_cast<int>(2)) << '\n';

  return 0;
}
