
// All includes goes here
#include "./lib/types.hh"

// All functions with its argument templates goes here
template < typename qtbn, typename qxns>
auto add(qtbn a, qxns b) { 
return (a + b); }; 
 

// Main Function (Have to be the only main function)
int main(){
  
auto result = add(JSNumber(5), JSNumber(3)) ; 

std::cout << result.toString() << std:: endl; 
auto multiply = [](auto a, auto b) { 
return (a * b);  
 }  ; 

auto product = multiply(JSNumber(2), JSNumber(4)) ; 

std::cout << product.toString() << std:: endl; 
auto divide = [](auto a, auto b) { return (a / b); }  ; 

auto quotient = divide(JSNumber(10), JSNumber(2)) ; 

std::cout << quotient.toString() << std:: endl; 
  return 0;
}  
