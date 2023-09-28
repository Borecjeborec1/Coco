

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
#include "./lib/types-methods/Array-methods.hh"
#include "./lib/types-methods/Boolean-methods.hh"
#include "./lib/types-methods/Number-methods.hh"
#include "./lib/types-methods/String-methods.hh"

namespace test {
                auto someVariable = static_cast<int>(123) ; 

auto sum = [](auto a, auto b) { 
return ((a + b) + someVariable);  
 };
auto test = sum;

            };

// Main Function (Have to be the only main function)
int main(){
  std::cout.setf(std::ios::boolalpha);
  
std::cout << test::test(static_cast<int>(2), static_cast<int>(3)) << '\n';
  return 0;
}  
