#include <iostream>
#include <chrono>

int main() {
  const int N = 1500;

  double sum = 0;

  auto start_time = std::chrono::high_resolution_clock::now();

  for (double i = 1; i <= N; i += 3e-7) {
    sum += (i * i);
  }

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time);

  std::cout << "Sum: " << duration.count() << "ms" << std::endl;

  std::cout << std::string("Sum:") << sum << '\n';
  return 0;
}