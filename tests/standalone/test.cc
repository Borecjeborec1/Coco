

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
  auto iterations = static_cast<int>(100000000) ; 

auto Nodejs = std::chrono::high_resolution_clock::now();
auto sum = static_cast<int>(0) ; 

for (auto i = static_cast<long long int>(1) ; 
 (i <= iterations); i++ ) { 
sum = sum + i; 
 } 
auto x = static_cast<int>(12) ; 

auto y = std::string("12") ; 

std::cout << (JS_toString(x) == JS_toString(y)) << '\n';
std::cout << (typeid(x) == typeid(y) && JS_toString(x) == JS_toString(y)) << '\n';

          auto end_time = std::chrono::high_resolution_clock::now();
          auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
              end_time - Nodejs);
        
          std::cout << "Nodejs: " << duration.count() << "ms" << std::endl;
          
std::cout << std::string("Sum:") << sum << '\n';


  
  return 0;
}  
