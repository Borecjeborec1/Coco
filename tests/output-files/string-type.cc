
// All includes goes here
#include "./lib/types.hh"
#include <iostream>

// Global operators
std::ostream& operator<<(std::ostream& os, const JSValue& value) {
  os << value.toString();
  return os;
}

// All functions with its argument templates goes here

 

// Main Function (Have to be the only main function)
int main(){
  auto str = JSString("Hello, world!") ; 

std::cout << JSString("Original String:") << str.toString() << std:: endl; 
std::cout << JSString("Length:") << str.length << std:: endl; 
std::cout << JSString("Slice:") << str.slice(JSNumber(0), JSNumber(5)).toString() << std:: endl; 
std::cout << JSString("Substring:") << str.substring(JSNumber(7), JSNumber(12)).toString() << std:: endl; 
std::cout << JSString("Substr:") << str.substr(JSNumber(7), JSNumber(5)).toString() << std:: endl; 
std::cout << JSString("Replace:") << str.replace(JSString("world"), JSString("Universe")).toString() << std:: endl; 
std::cout << JSString("ReplaceAll:") << str.replaceAll(JSString("l"), JSString("L")).toString() << std:: endl; 
std::cout << JSString("ToUpperCase:") << str.toUpperCase().toString() << std:: endl; 
std::cout << JSString("ToLowerCase:") << str.toLowerCase().toString() << std:: endl; 
auto otherString = JSString(" Welcome") ; 

std::cout << JSString("Concat:") << str.concat(otherString).toString() << std:: endl; 
auto stringWithSpaces = JSString("   Hello!   ") ; 

std::cout << JSString("Trim:") << stringWithSpaces.trim().toString() << std:: endl; 
auto stringWithSpacesStart = JSString("   Hello!") ; 

std::cout << JSString("TrimStart:") << stringWithSpacesStart.trimStart().toString() << std:: endl; 
auto stringWithSpacesEnd = JSString("Hello!   ") ; 

std::cout << JSString("TrimEnd:") << stringWithSpacesEnd.trimEnd().toString() << std:: endl; 
std::cout << JSString("CharAt:") << str.charAt(JSNumber(4)).toString() << std:: endl; 
std::cout << JSString("CharCodeAt:") << str.charCodeAt(JSNumber(4)).valueOf() << std:: endl; 
std::cout << JSString("Includes:") << str.includes(JSString("world")) << std:: endl; 
std::cout << JSString("StartsWith:") << str.startsWith(JSString("Hello")) << std:: endl; 
std::cout << JSString("EndsWith:") << str.endsWith(JSString("world!")) << std:: endl; 
std::cout << JSString("Split:") << str.split(JSString(",")).toString() << std:: endl; 
std::cout << JSString("IndexOf:") << str.indexOf(JSString("o")).valueOf() << std:: endl; 
std::cout << JSString("LastIndexOf:") << str.lastIndexOf(JSString("o")).valueOf() << std:: endl; 
std::cout << JSString("PadStart:") << str.padStart(JSNumber(15), JSString("*")).toString() << std:: endl; 
std::cout << JSString("PadEnd:") << str.padEnd(JSNumber(15), JSString("*")).toString() << std:: endl; 
auto regExp = JSString("\b\w+\b") ; 

std::cout << JSString("Match:") << str.match(regExp).toString() << std:: endl; 
auto regExpSearch = JSString("world") ; 

std::cout << JSString("Search:") << str.search(regExpSearch).valueOf() << std:: endl; 
  return 0;
}  
