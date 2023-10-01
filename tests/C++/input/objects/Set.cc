

// All new includes goes here
#include <chrono>
#include <iostream>
#include "./lib/Global-functions.hh"
#include "./lib/native-classes/Array.hh"
#include "./lib/native-classes/Date.hh"
#include "./lib/native-classes/JSON.hh"
#include "./lib/native-classes/Map.hh"
#include "./lib/native-classes/Math.hh"
#include "./lib/native-classes/Number.hh"
#include "./lib/native-classes/Set.hh"
#include "./lib/native-classes/String.hh"
#include "./lib/nlohmann-json.hh"
#include "./lib/operators/json-operators.hh"
#include "./lib/operators/string-operators.hh"
#include "./lib/types-methods/Array-Methods.hh"
#include "./lib/types-methods/Number-Methods.hh"
#include "./lib/types-methods/String-Methods.hh"



// Main Function (Have to be the only main function)
int main(){
  std::cout.setf(std::ios::boolalpha);
  auto set = __Set__ () ; 

std::cout << std::string("Set.prototype.size (Initial Size):") << set.size() << '\n';
set.add(std::string("value1"));
set.add(std::string("value2"));
set.add(std::string("value3"));
std::cout << std::string("Set.prototype.size (After Adding Values):") << set.size() << '\n';
std::cout << std::string("Set.prototype.has('value2'):") << set.has(std::string("value2")) << '\n';
std::cout << std::string("Set.prototype.has('value4'):") << set.has(std::string("value4")) << '\n';
set.deleteKey(std::string("value3"));
std::cout << std::string("Set.prototype.size (After Deleting Value):") << set.size() << '\n';
set.clear();
std::cout << std::string("Set.prototype.size (After Clearing):") << set.size() << '\n';
set.add(std::string("Alice"));
set.add(std::string("Bob"));
set.add(std::string("Charlie"));
std::cout << std::string("Set Values:") << '\n';
for (const auto& value : JS_values(set)) {
        std::cout << value << '\n';
      }
auto setToArray = nlohmann::json{} ; 

std::cout << std::string("Set converted to Array:") << setToArray << '\n';
auto obj1 = nlohmann::json{{"id", static_cast<double>(1)}} ; 

auto obj2 = nlohmann::json{{"id", static_cast<double>(2)}} ; 

set.add(obj1);
set.add(obj2);
std::cout << std::string("Set.prototype.has(obj1):") << set.has(obj1) << '\n';
std::cout << std::string("Set.prototype.has(obj2):") << set.has(obj2) << '\n';
set.add(static_cast<double>(42));
set.add(true);
set.add(std::string("stringValue"));
std::cout << std::string("Set.prototype.has(42):") << set.has(static_cast<double>(42)) << '\n';
std::cout << std::string("Set.prototype.has(true):") << set.has(true) << '\n';
std::cout << std::string("Set.prototype.has('stringValue'):") << set.has(std::string("stringValue")) << '\n';


  
  return 0;
}  
