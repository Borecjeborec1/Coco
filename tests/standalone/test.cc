

// All new includes goes here
#include <chrono>
#include <iostream>
#include "./lib/Global-functions.hh"
#include "./lib/native-classes/Array.hh"
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
  class mathLib
  {
  public:
    nlohmann::json some_const;
    nlohmann::json some_const2;
    ;
    mathLib()
    {
      some_const = static_cast<int>(1231);
      some_const2 = static_cast<int>(1231);
    }
    nlohmann::json addConst(nlohmann::json x)
    {
      return (x + some_const);
    }
  };
  auto idk = mathLib();

  std::cout << idk.addConst(static_cast<int>(123)) << '\n';

  return 0;
}
