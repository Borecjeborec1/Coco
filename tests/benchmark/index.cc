#include <chrono>
#include <iostream>

int main() {
  auto Heyo = std::chrono::high_resolution_clock::now();
  double i = 0;
  while (true) {
    i += 0.0004;
    if ((i >= 10000)) {
      break;
    }
  }

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end_time - Heyo);

  std::cout << "Heyo: " << duration.count() << "ms" << std::endl;

  return 0;
}