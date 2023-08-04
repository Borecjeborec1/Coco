#include "types.hh"

std::string JSArray::toString() const {
  std::string result = "[";
  for (size_t i = 0; i < elements.size(); ++i) {
    if (i > 0) {
      result += ", ";
    }
    result += elements[i]->toString();
  }
  result += "]";
  return result;
}

void JSArray::pop() {
  if (!elements.empty()) {
    delete elements.back();
    elements.pop_back();
  }
}

void JSArray::push(const JSString &value) {
  elements.push_back(new JSString(value));
}
void JSArray::push(const JSNumber &value) {
  elements.push_back(new JSNumber(value));
}
void JSArray::push(const std::string &value) {
  elements.push_back(new JSString(value));
}
void JSArray::push(const double value) {
  elements.push_back(new JSNumber(value));
}