
// All includes goes here
#include "./lib/types.hh"

// All functions with its argument templates goes here

 

// Main Function (Have to be the only main function)
int main(){
  auto str = JSString("Hello, World!") ; 

auto upperCaseStr = str.toUpperCase() ; 

std::cout << upperCaseStr.toString() << std:: endl; 
auto lowerCaseStr = str.toLowerCase() ; 

std::cout << lowerCaseStr.toString() << std:: endl; 
auto substr = str.substr(JSNumber(7), JSNumber(5)) ; 

std::cout << substr.toString() << std:: endl; 
auto charAt = str.charAt(JSNumber(4)) ; 

std::cout << charAt.toString() << std:: endl; 
  return 0;
}  
