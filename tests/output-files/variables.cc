
// All includes goes here
#include "./lib/types.hh"
#include <iostream>

// Global operators
std::ostream& operator<<(std::ostream& os, const JSValue& value) {
  os << value.toString();
  return os;
}

// All functions with its argument templates goes here

auto exampleFunction() { 
auto x = JSNumber(1000) ; 

auto y = JSNumber(30) ; 

if (true) { 
auto x = JSNumber(40) ; 

auto y = JSNumber(50) ; 

std::cout << x << std:: endl; 
std::cout << y << std:: endl;  
 } 
std::cout << x << std:: endl; 
std::cout << y << std:: endl; }; 
 

// Main Function (Have to be the only main function)
int main(){
  auto x = JSNumber(10) ; 

auto PI = JSNumber(3.14) ; 

auto y = JSString("Hello") ; 

std::cout << x << std:: endl; 
std::cout << y << std:: endl; 

exampleFunction();
  return 0;
}  
