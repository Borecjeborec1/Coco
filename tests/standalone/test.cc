

// All new includes goes here
#include <chrono>
#include <iostream>

namespace getRandomInt
{
  auto getRandomInt = [](auto _min, auto _max)
  {
    return (__Math__::floor((__Math__::random() * ((_max - _min) + static_cast<int>(1)))) + _min);
  };
};

// Main Function (Have to be the only main function)
int main()
{
  std::cout.setf(std::ios::boolalpha);

  std::cout << getRandomInt::getRandomInt(static_cast<int>(1), static_cast<int>(3)) << '\n';

  return 0;
}
