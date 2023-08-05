
// All new includes goes here
#include <iostream>


// All JSMethods goes here


#include <string>
#include <cmath>

/////////////////////////// BOOLEAN METHODS ///////////////////////////////
std::string JS_toString(bool value) { return value ? "true" : "false"; }
bool JS_valueOf(bool value) { return value; }
/////////////////////////// BOOLEAN METHODS END ///////////////////////////////

/////////////////////////// NUMBER METHODS ///////////////////////////////
// Function to convert a number to a fixed-point notation string with the
// specified decimal places
std::string JS_toFixed(double value, int decimalPlaces) {
  std::string format = "%." + std::to_string(decimalPlaces) + "f";
  char buffer[100];
  std::sprintf(buffer, format.c_str(), value);
  return buffer;
}

// Function to convert a number to exponential notation with the specified
// number of decimal places
std::string JS_toExponential(double value, int decimalPlaces) {
  std::string format = "%." + std::to_string(decimalPlaces) + "e";
  char buffer[100];
  std::sprintf(buffer, format.c_str(), value);
  return buffer;
}

// Function to convert a number to a string representation with the specified
// radix
std::string JS_toString(double value) { return std::to_string(value); }

// Function to get the primitive value of a number
double JS_valueOf(double value) { return value; }

// Function to convert a number to a localized string representation
std::string JS_toLocaleString(double value) {
  // Implementation of localized string representation is beyond the scope of
  // this example
  // You may need to implement your own logic based on the desired locale
  return std::to_string(value);
}

// Function to check if a number is finite
bool JS_isFinite(double value) { return std::isfinite(value); }

// Function to check if a number is NaN (Not-a-Number)
bool JS_isNaN(double value) { return std::isnan(value); }

// Function to parse an integer from a string with the specified radix
int JS_parseInt(const std::string &str, int radix) {
  // Implementation of parseInt is beyond the scope of this example
  // You may need to implement your own parsing logic here
  return std::stoi(str, nullptr, radix);
}

// Function to parse a floating-point number from a string
double JS_parseFloat(const std::string &str) {
  // Implementation of parseFloat is beyond the scope of this example
  // You may need to implement your own parsing logic here
  return std::stod(str);
}
/////////////////////////// NUMBER METHODS END ///////////////////////////////


// All functions with its argument templates goes here

 

// Main Function (Have to be the only main function)
int main(){
  auto str = std::string("Hello, world!") ; 

std::cout << std::string("Original String:") << JS_toString(str) << '\n';
std::cout << std::string("Length:") << str.length << '\n';
std::cout << std::string("Slice:") << JS_toString(JS_slice(str)) << '\n';
std::cout << std::string("Substring:") << JS_toString(JS_substring(str)) << '\n';
std::cout << std::string("Substr:") << JS_toString(JS_substr(str)) << '\n';
std::cout << std::string("Replace:") << JS_toString(JS_replace(str)) << '\n';
std::cout << std::string("ReplaceAll:") << JS_toString(str.replaceAll(std::string("l"), std::string("L"))) << '\n';
std::cout << std::string("ToUpperCase:") << JS_toUpperCase << '\n';
std::cout << std::string("ToLowerCase:") << JS_toLowerCase << '\n';
auto otherString = std::string(" Welcome") ; 

std::cout << std::string("Concat:") << JS_toString(JS_concat(str)) << '\n';
auto stringWithSpaces = std::string("   Hello!   ") ; 

std::cout << std::string("Trim:") << JS_toString(JS_trim) << '\n';
auto stringWithSpacesStart = std::string("   Hello!") ; 

std::cout << std::string("TrimStart:") << JS_toString(JS_trimStart) << '\n';
auto stringWithSpacesEnd = std::string("Hello!   ") ; 

std::cout << std::string("TrimEnd:") << JS_toString(JS_trimEnd) << '\n';
std::cout << std::string("CharAt:") << JS_toString(JS_charAt(str)) << '\n';
std::cout << std::string("CharCodeAt:") << JS_valueOf << '\n';
std::cout << std::string("Includes:") << JS_includes(str) << '\n';
std::cout << std::string("StartsWith:") << JS_startsWith(str) << '\n';
std::cout << std::string("EndsWith:") << JS_endsWith(str) << '\n';
std::cout << std::string("Split:") << JS_toString(JS_split(str)) << '\n';
std::cout << std::string("IndexOf:") << JS_valueOf << '\n';
std::cout << std::string("LastIndexOf:") << JS_valueOf << '\n';
std::cout << std::string("PadStart:") << JS_toString(JS_padStart(str)) << '\n';
std::cout << std::string("PadEnd:") << JS_toString(JS_padEnd(str)) << '\n';
auto regExp = std::string("\b\w+\b") ; 

std::cout << std::string("Match:") << JS_toString(JS_match(str)) << '\n';
auto regExpSearch = std::string("world") ; 

std::cout << std::string("Search:") << JS_valueOf << '\n';
  return 0;
}  
