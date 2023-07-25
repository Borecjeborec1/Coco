
// All includes goes here
#include "./lib/types.hh"

// All functions with its argument templates goes here

// Main Function (Have to be the only main function)
int main() {
  JSArray idk(JSNumber(1), JSNumber(2), JSNumber(3));

  std::cout << idk.toString() << std::endl; // Output: [1, 2, 3]
  std::cout << idk.size() << std::endl;     // Output: 3

  JSValue *value = idk.get(1);
  JSNumber *numValue = dynamic_cast<JSNumber *>(value);
  if (numValue != nullptr) {
    std::cout << numValue->toString() << std::endl; // Output: 2
  }

  idk.pop();                                // Remove the last element
  std::cout << idk.toString() << std::endl; // Output: [1, 2]

  return 0;
}
