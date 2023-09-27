

// All new includes goes here
#include <chrono>
#include <iostream>
#include "./lib/Global-functions.hh"
#include "./lib/native-classes/Array.hh"
#include "./lib/native-classes/Date.hh"
#include "./lib/native-classes/JSON.hh"
#include "./lib/native-classes/Math.hh"
#include "./lib/native-classes/Number.hh"
#include "./lib/native-classes/String.hh"
#include "./lib/nlohmann-json.hh"
#include "./lib/operators/json-operators.hh"
#include "./lib/operators/string-operators.hh"
#include "./lib/types-methods/Array-methods.hh"
#include "./lib/types-methods/Boolean-methods.hh"
#include "./lib/types-methods/Number-methods.hh"
#include "./lib/types-methods/String-methods.hh"

// Main Function (Have to be the only main function)
int main()
{
  std::cout.setf(std::ios::boolalpha);

  auto speedTest = std::chrono::high_resolution_clock::now();
  auto sum = static_cast<long long unsigned>(0);

  for (auto i = static_cast<long long>(0);
       (i < static_cast<long long>(10000000002)); i++)
  {
    sum = sum + ((i * i) / i);
  }
  std::cout << sum << '\n';

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - speedTest);

  std::cout << "speedTest: " << duration.count() << "ms" << std::endl;

  return 0;
}
