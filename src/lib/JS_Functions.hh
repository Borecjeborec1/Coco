

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
