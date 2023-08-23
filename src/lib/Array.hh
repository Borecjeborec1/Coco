#include <vector>
#include <variant>
#include <string>

class JSArray {
private:
  using Element = std::variant<double, std::string, bool, JSArray>;

  std::vector<Element> elements;

public:
  JSArray() = default;

  template <typename T> JSArray(T value) { push(value); }

  ~JSArray() {
    for (const auto &element : elements) {
      if (std::holds_alternative<JSArray>(element)) {
        delete &std::get<JSArray>(element);
      }
    }
  }

  void push(const std::string &value) { elements.push_back(value); }

  void push(const double &value) { elements.push_back(value); }

  void push(const bool &value) { elements.push_back(value); }

  void push(const JSArray &value) { elements.push_back(value); }

  // void print() const {
  //   for (const auto &element : elements) {
  //     if (std::holds_alternative<std::string>(element)) {
  //       std::cout << "String: " << std::get<std::string>(element) <<
  //       std::endl;
  //     } else if (std::holds_alternative<double>(element)) {
  //       std::cout << "Double: " << std::get<double>(element) << std::endl;
  //     } else if (std::holds_alternative<bool>(element)) {
  //       std::cout << "Bool: " << std::get<bool>(element) << std::endl;
  //     } else if (std::holds_alternative<JSArray>(element)) {
  //       std::cout << "Nested Array:" << std::endl;
  //       std::get<JSArray>(element).print();
  //     }
  //   }
  // }
};
