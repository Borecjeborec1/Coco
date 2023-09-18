#include <iostream>

template <typename T>
T min(const T &arg)
{
  return arg;
}

template <typename T>
T max(const T &arg)
{
  return arg;
}

template <typename T, typename... Args>
T min(const T &first, const Args &...args)
{
  T rest = min(args...);
  return (first < rest) ? first : rest;
}

template <typename T, typename... Args>
T max(const T &first, const Args &...args)
{
  T rest = max(args...);
  return (first > rest) ? first : rest;
}

int main()
{
  int min_val = min(5, 2, 9, 1, 7);
  int max_val = max(5, 2, 9, 1, 7);

  std::cout << "Minimum value: " << min_val << std::endl;
  std::cout << "Maximum value: " << max_val << std::endl;

  return 0;
}
