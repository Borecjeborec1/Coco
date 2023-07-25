
// All includes goes here
#include "./lib/types.hh"

// All functions with its argument templates goes here

 

// Main Function (Have to be the only main function)
int main(){
  for (auto i = JSNumber(0) ; 
 (i < JSNumber(5)); i++ ) { 
std::cout << i.toString() << std:: endl;  
 } 
auto j = JSNumber(0) ; 

while ((j < JSNumber(5))) { 
std::cout << j.toString() << std:: endl; 
j++ ; } 

auto k = JSNumber(0) ; 

do { 
std::cout << k.toString() << std:: endl; 
k++ ; } while ((k < JSNumber(5))); 

  return 0;
}  
