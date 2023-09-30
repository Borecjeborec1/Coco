

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
#include "./lib/Timer.hh"
#include "./lib/types-methods/Array-Methods.hh"
#include "./lib/types-methods/Boolean-Methods.hh"
#include "./lib/types-methods/Number-Methods.hh"
#include "./lib/types-methods/String-Methods.hh"



// Main Function (Have to be the only main function)
int main(){
  std::cout.setf(std::ios::boolalpha);
  std::cout << std::string("HELLO WORLD!") << '\n';
auto x = __Timer__::setTimeout([]() { std::cout << std::string("setTimeout executed") << '\n';
return; } , static_cast<int>(2000)) ; 

auto y = __Timer__::setImmediate([]() { std::cout << std::string("setImmidiate executed") << '\n';
return; } ) ; 

auto z = __Timer__::setInterval([]() { 
auto count = static_cast<int>(0) ; 

std::cout << ((std::string("setInterval executed (") + count) + std::string(").")) << '\n';
count++ ;
if ((count >= static_cast<int>(5))) {

} 
 } , static_cast<int>(1000)) ; 

std::cout << std::string("test") << '\n';


    while (!__Timer__::shouldExit) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      };
    
  return 0;
}  
