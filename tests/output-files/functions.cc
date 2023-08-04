
// All includes goes here
#include "./lib/types.hh"
#include <iostream>

// Global operators
std::ostream& operator<<(std::ostream& os, const JSValue& value) {
  os << value.toString();
  return os;
}

// All functions with its argument templates goes here
template < typename qwvf, typename pitq>
auto add(qwvf a, pitq b) { 
return (a + b); }; 
 

// Main Function (Have to be the only main function)
int main(){
  
auto result = add(JSNumber(5), JSNumber(3)) ; 

std::cout << result << std:: endl; 
auto multiply = [](auto a, auto b) { 
return (a * b);  
 }  ; 

auto product = multiply(JSNumber(2), JSNumber(4)) ; 

std::cout << product << std:: endl; 
auto divide = [](auto a, auto b) { return (a / b); }  ; 

auto quotient = divide(JSNumber(10), JSNumber(2)) ; 

std::cout << quotient << std:: endl; 
  return 0;
}  
