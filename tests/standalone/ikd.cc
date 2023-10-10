

// All new includes goes here
#include <chrono>
#include <iostream>
#include "./lib/Global-functions.hh"
#include "./lib/native-classes/Array.hh"
#include "./lib/native-classes/Boolean.hh"
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
  auto getRandomInt = [](auto _min, auto _max) { 
return (__Math__::floor((__Math__::random() * ((_max - _min) + static_cast<int>(1)))) + _min);  
 };
for (auto i = static_cast<long long int>(0) ; 
 (i < static_cast<int>(10)); i++ ) { 
auto randomNumber = getRandomInt(static_cast<int>(1), static_cast<int>(100)) ; 

std::cout << randomNumber << '\n'; 
 } 


  
  return 0;
}  
