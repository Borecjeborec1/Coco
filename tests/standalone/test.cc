

// All new includes goes here
#include <chrono>
#include <iostream>
#include "./lib/Global-functions.hh"
#include "./lib/native-classes/Array.hh"
#include "./lib/native-classes/Boolean.hh"
#include "./lib/native-classes/Date.hh"
#include "./lib/native-classes/JSON.hh"
#include "./lib/native-classes/Map.hh"
#include "./lib/native-classes/Math.hh"
#include "./lib/native-classes/Number.hh"
#include "./lib/native-classes/Set.hh"
#include "./lib/native-classes/String.hh"
#include "./lib/nlohmann-json.hh"
#include "./lib/operators/json-operators.hh"
#include "./lib/operators/string-operators.hh"
#include "./lib/types-methods/Array-Methods.hh"
#include "./lib/types-methods/Number-Methods.hh"
#include "./lib/types-methods/String-Methods.hh"

// Main Function (Have to be the only main function)
int main()
{
  std::cout.setf(std::ios::boolalpha);
  std::function<long long(long long)> factorialRecursive = [&](auto n)
  {
    if ((JS_toString(n)) == (JS_toString(static_cast<long long>(0))))
    {
      return static_cast<long long>(1);
    }
    return (n * factorialRecursive((n - static_cast<long long>(1))));
  };
  auto factorialIterative = [](auto n)
  {
    auto result = static_cast<long long>(1);

    for (auto i = static_cast<long long>(2);
         (i <= n); i++)
    {
      result *= i;
    }
    return result;
  };
  auto numberToCalculate = static_cast<long long>(10000);
  auto ojbSZo = std::chrono::high_resolution_clock::now();
  for (auto i = static_cast<long long>(0);
       (i < static_cast<long long>(100000)); i++)
  {
    factorialIterative(numberToCalculate);
  }

  std::cout << "Iterative: " << (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - ojbSZo)).count() << "ms" << std::endl;

  auto qgXBpx = std::chrono::high_resolution_clock::now();
  for (auto i = static_cast<long long>(0);
       (i < static_cast<long long>(100000)); i++)
  {
    factorialRecursive(numberToCalculate);
  }

  std::cout << "Recursive: " << (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - qgXBpx)).count() << "ms" << std::endl;

  return 0;
}
