#include <iostream>
#include <chrono>

int main() {
  const int N = 1000000000;
  long long sum = 0;

  auto start_time = std::chrono::high_resolution_clock::now();

  for (int i = 1; i <= N; ++i) {
    sum += i * i;
  }

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time);

  std::cout << "Sum: " << sum << std::endl;
  std::cout << "Time taken: " << duration.count() << "ms" << std::endl;

  return 0;
}
