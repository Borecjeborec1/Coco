#include <iostream>
#include <vector>
#include <variant>
#include <initializer_list>

class NestedArray {
public:
  NestedArray() = default;

  NestedArray(std::initializer_list<
              std::variant<double, std::string, bool, NestedArray>> init)
      : elements(init) {}

  void
  push(const std::variant<double, std::string, bool, NestedArray> &element) {
    elements.push_back(element);
  }

  auto &operator[](std::size_t index) { return elements[index]; }

private:
  std::vector<std::variant<double, std::string, bool, NestedArray>> elements;
};

int main() {
  auto array =
      NestedArray{3.14, "Nested", true, NestedArray{1.23, "InnerNested"}};

  std::cout << "test1" << std::endl;
  std::cout << std::get<double>(array[0]) << std::endl;
  std::cout << "test3" << std::endl;
  std::cout << std::get<bool>(array[2]) << std::endl;

  NestedArray &nestedArray = std::get<NestedArray>(array[3]);
  std::cout << std::get<double>(nestedArray[0]) << std::endl;
  std::cout << std::get<std::string>(nestedArray[1]) << std::endl;

  return 0;
}
