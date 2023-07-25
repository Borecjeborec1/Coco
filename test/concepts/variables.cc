
// All includes goes here
#include "./lib/types.hh"

// All functions with its argument templates goes here

 

// Main Function (Have to be the only main function)
int main(){
  auto x = JSNumber(10) ; 

auto PI = JSNumber(3.14) ; 

auto y = JSString("Hello") ; 

std::cout << x.toString() << std:: endl; 
std::cout << y.toString() << std:: endl; 
  return 0;
}  
