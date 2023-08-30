#include <chrono>
#include <iostream>
#include <string>

int main() {
  std::cout.setf(std::ios::boolalpha);
  const auto N = static_cast<double>(1000000000);

  auto sum = static_cast<double>(0);

  auto Sum = std::chrono::high_resolution_clock::now();
  for (float i = 1; (i <= N); i++) {
    std::cout << i << std::endl;
    sum += (i * i);
  }

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end_time - Sum);

  std::cout << "Sum: " << duration.count() << "ms" << std::endl;

  std::cout << std::string("Sum:") << sum << '\n';
  return 0;
}