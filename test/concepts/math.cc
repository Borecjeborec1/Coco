
// All includes goes here
#include "./lib/types.hh"

// All functions with its argument templates goes here

 

// Main Function (Have to be the only main function)
int main(){
  auto num = -JSNumber(3.75)  ; 

auto absNum = std::abs(num) ; 

std::cout << absNum.toString() << std:: endl; 
auto ceilNum = std::ceil(num) ; 

std::cout << ceilNum.toString() << std:: endl; 
auto floorNum = std::floor(num) ; 

std::cout << floorNum.toString() << std:: endl; 
auto roundNum = std::round(num) ; 

std::cout << roundNum.toString() << std:: endl; 
auto maxNum = std::max(JSNumber(2), JSNumber(5), JSNumber(8), JSNumber(1)) ; 

std::cout << maxNum.toString() << std:: endl; 
auto minNum = std::min(JSNumber(2), JSNumber(5), JSNumber(8), JSNumber(1)) ; 

std::cout << minNum.toString() << std:: endl; 
auto randomNum = std::random() ; 

std::cout << randomNum.toString() << std:: endl; 
  return 0;
}  
