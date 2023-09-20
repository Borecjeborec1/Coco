// Ignore imports
#include <iostream>
#include <vector>
#include <string>
#include "nlohmann-json.hh"
// Ignore imports end

nlohmann::json JS_concat(const nlohmann::json &arr1,
                         const nlohmann::json &arr2)
{
  nlohmann::json result = arr1;
  for (const auto &element : arr2)
  {
    result.push_back(element);
  }
  return result;
}

nlohmann::json JS_copyWithin(nlohmann::json &arr, int target, int start,
                             int end = INT_MAX)
{
  if (!arr.is_array())
  {
    throw std::runtime_error("Input is not an array.");
  }

  int length = static_cast<int>(arr.size());

  target =
      (target < 0) ? std::max(length + target, 0) : std::min(target, length);
  start = (start < 0) ? std::max(length + start, 0) : std::min(start, length);
  end = (end < 0) ? std::max(length + end, 0) : std::min(end, length);

  int to = target;
  int from = start;

  while (from < end && to < length)
  {
    arr[to] = arr[from];
    ++to;
    ++from;
  }
  return arr;
}

nlohmann::json JS_entries(const nlohmann::json &arr)
{
  nlohmann::json result;
  int index = 0;
  for (const auto &element : arr)
  {
    nlohmann::json entry;
    entry.push_back(index);
    entry.push_back(element);
    result.push_back(entry);
    index++;
  }
  return result;
}

template <typename Callable>
bool JS_every(const nlohmann::json &arr, Callable callback)
{
  if (arr.empty())
  {
    return false;
  }

  nlohmann::json::value_t expected_type = arr[0].type();

  for (const auto &element : arr)
  {
    if (element.type() != expected_type)
    {
      return false;
    }

    bool satisfiesCallback = false;
    try
    {
      satisfiesCallback = callback(element);
    }
    catch (const std::exception &ex)
    {
      return false;
    }

    if (!satisfiesCallback)
    {
      return false;
    }
  }

  return true;
}

nlohmann::json JS_fill(nlohmann::json &arr, double value, int start, int end)
{
  start = std::max(start, 0);
  end = std::min(end, static_cast<int>(arr.size()));

  for (int i = start; i < end; i++)
  {
    arr[i] = value;
  }

  return arr;
}

template <typename Callable>
nlohmann::json JS_filter(const nlohmann::json &arr, Callable callback)
{
  if (arr.empty())
  {
    return nlohmann::json::array();
  }

  nlohmann::json result = nlohmann::json::array();

  for (const auto &element : arr)
  {
    bool satisfiesCallback = false;
    try
    {
      satisfiesCallback = callback(element);
    }
    catch (const std::exception &ex)
    {
      continue;
    }

    if (satisfiesCallback)
    {
      result.push_back(element);
    }
  }

  return result;
}

template <typename Callable>
nlohmann::json JS_find(const nlohmann::json &arr, Callable callback)
{
  if (arr.empty())
  {
    return -1;
  }

  nlohmann::json::value_t expected_type = arr[0].type();

  for (const auto &element : arr)
  {
    if (element.type() != expected_type)
    {
      continue;
    }

    try
    {
      if (callback(element))
      {
        return element;
      }
    }
    catch (const std::exception &ex)
    {
      continue;
    }
  }

  return -1;
}
template <typename Callable>
int JS_findIndex(const nlohmann::json &arr, Callable callback)
{
  if (arr.empty())
  {
    return -1; // Return -1 to indicate no matching element found
  }

  nlohmann::json::value_t expected_type = arr[0].type();
  int index = 0;

  for (const auto &element : arr)
  {
    if (element.type() != expected_type)
    {
      return -1; // Return -1 if types are not the same
    }

    bool satisfiesCallback = false;
    try
    {
      satisfiesCallback = callback(element);
    }
    catch (const std::exception &ex)
    {
      // Handle exceptions from the callback function
      return -1;
    }

    if (satisfiesCallback)
    {
      return index; // Return the index of the first matching element
    }

    index++;
  }

  return -1; // Return -1 if no matching element is found
}

nlohmann::json JS_flat(const nlohmann::json &arr, int depth = 1)
{
  if (depth <= 0)
  {
    return arr;
  }

  nlohmann::json result;
  for (const auto &element : arr)
  {
    if (element.is_array())
    {
      result.insert(result.end(), JS_flat(element, depth - 1).begin(),
                    JS_flat(element, depth - 1).end());
    }
    else
    {
      result.push_back(element);
    }
  }
  return result;
}

// nlohmann::json JS_flatMap(const nlohmann::json &arr,
//                           std::function<nlohmann::json(double)> callback) {
//   nlohmann::json result;
//   for (const auto &element : arr) {
//     nlohmann::json mapped = callback(element);
//     if (mapped.is_array()) {
//       result.insert(result.end(), mapped.begin(), mapped.end());
//     } else {
//       result.push_back(mapped);
//     }
//   }
//   return result;
// }

template <typename Callable>
void JS_forEach(const nlohmann::json &arr, Callable callback)
{
  if (arr.empty())
  {
    return;
  }

  nlohmann::json::value_t expected_type = arr[0].type();

  for (const auto &element : arr)
  {
    if (element.type() != expected_type)
    {
      continue;
    }

    try
    {
      callback(element);
    }
    catch (const std::exception &ex)
    {
      continue;
    }
  }
}

template <typename T>
bool JS_includes(const nlohmann::json &arr, const T &searchElement)
{
  for (const auto &element : arr)
  {
    try
    {

      T value = element.get<T>();
      if (value == searchElement)
      {
        return true;
      }
    }
    catch (const std::exception &ex)
    {
      continue;
    }
  }
  return false;
}

template <typename T>
int JS_indexOf(const nlohmann::json &arr, const T &searchElement,
               int fromIndex = 0)
{
  fromIndex = std::max(fromIndex, 0);
  for (int i = fromIndex; i < static_cast<int>(arr.size()); i++)
  {
    try
    {

      T value = arr[i].get<T>();
      if (value == searchElement)
      {
        return i;
      }
    }
    catch (const std::exception &ex)
    {
      continue;
    }
  }
  return -1;
}

bool JS_isArray(const nlohmann::json &arr) { return arr.is_array(); }

std::string JS_join(const nlohmann::json &arr, const std::string &delimiter)
{
  std::string result;

  for (const auto &element : arr)
  {
    if (!result.empty())
    {
      result += delimiter; // Add the delimiter between elements
    }

    result += element.dump(); // Convert the element to a string and append it
  }

  return result;
}

nlohmann::json JS_keys(const nlohmann::json &arr)
{
  nlohmann::json result;
  for (int i = 0; i < arr.size(); i++)
  {
    result.push_back(i);
  }
  return result;
}

template <typename T>
int JS_lastIndexOf(const nlohmann::json &arr, const T &searchElement,
                   int fromIndex = -1)
{
  if (arr.empty())
  {
    return -1;
  }

  if (fromIndex == -1)
  {
    fromIndex = static_cast<int>(arr.size()) - 1;
  }
  else
  {
    fromIndex = std::min(fromIndex, static_cast<int>(arr.size()) - 1);
  }

  for (int i = fromIndex; i >= 0; i--)
  {
    try
    {
      T value = arr[i].get<T>();
      if (value == searchElement)
      {
        return i;
      }
    }
    catch (const std::exception &ex)
    {
      continue;
    }
  }

  return -1;
}

nlohmann::json JS_map(const nlohmann::json &arr,
                      std::function<nlohmann::json(double)> callback)
{
  nlohmann::json result;
  for (const auto &element : arr)
  {
    double value = element.get<double>();
    nlohmann::json mapped = callback(value);
    result.push_back(mapped);
  }
  return result;
}

nlohmann::json JS_pop(nlohmann::json &arr)
{
  if (arr.is_array() && !arr.empty())
  {
    nlohmann::json popped = arr.back();
    arr.erase(--arr.end());
    return popped;
  }
  return nullptr;
}

template <typename T>
T JS_push(nlohmann::json &arr, T element)
{
  arr.push_back(element);
  return arr.size();
}

// template <typename Callback>
// nlohmann::json JS_reduce(const nlohmann::json &arr, Callback callback,
//                          const nlohmann::json &initialValue = nullptr) {
//   nlohmann::json accumulator = initialValue ? initialValue : nullptr;
//   double sum = 0;

//   for (const auto &element : arr) {
//     double value = element.get<double>();
//     if (accumulator) {
//       accumulator = callback(accumulator, value);
//     } else {
//       sum += value;
//     }
//   }

//   if (!accumulator) {
//     return sum;
//   }

//   return accumulator;
// }

// // reduceRight()
// nlohmann::json
// JS_reduceRight(const nlohmann::json &arr,
//                std::function<nlohmann::json(nlohmann::json, double)>
//                callback,
//                const nlohmann::json &initialValue = nullptr) {
//   // Convert the reversed JSON array to a vector of JSON values
//   std::vector<nlohmann::json> reversed(arr.rbegin(), arr.rend());

//   // Perform the reduce operation on the reversed vector
//   nlohmann::json result = JS_reduce(reversed, callback, initialValue);

//   return result;
// }

nlohmann::json JS_reverse(nlohmann::json &arr)
{
  std::reverse(arr.begin(), arr.end());
  return arr;
}

nlohmann::json JS_shift(nlohmann::json &arr)
{
  if (arr.empty())
  {
    return nullptr;
  }
  nlohmann::json shifted = arr.front();
  arr.erase(arr.begin());
  return shifted;
}

nlohmann::json JS_slice(const nlohmann::json &arr, int start = 0,
                        int end = INT_MAX)
{
  start = std::max(start, 0);
  end = std::min(end, static_cast<int>(arr.size()));

  nlohmann::json result;
  for (int i = start; i < end; i++)
  {
    result.push_back(arr[i]);
  }
  return result;
}

bool JS_some(const nlohmann::json &arr, std::function<bool(double)> callback)
{
  for (const auto &element : arr)
  {
    double value = element.get<double>();
    if (callback(value))
    {
      return true;
    }
  }
  return false;
}

nlohmann::json
JS_sort(nlohmann::json &arr,
        std::function<bool(double, double)> compareFunction = nullptr)
{
  if (compareFunction)
  {
    std::sort(arr.begin(), arr.end(),
              [&](const nlohmann::json &a, const nlohmann::json &b)
              {
                return compareFunction(a.get<double>(), b.get<double>());
              });
  }
  else
  {
    std::sort(arr.begin(), arr.end(),
              [](const nlohmann::json &a, const nlohmann::json &b)
              {
                return a.get<double>() < b.get<double>();
              });
  }
  return arr;
}

nlohmann::json JS_splice(nlohmann::json &arr, int start, int deleteCount,
                         const nlohmann::json &items = nullptr)
{
  start = std::max(start, 0);
  deleteCount = std::max(deleteCount, 0);
  int end = start + deleteCount;

  nlohmann::json removed;

  auto eraseBegin = arr.begin() + start;
  auto eraseEnd = arr.begin() + end;
  for (auto it = eraseBegin; it != eraseEnd; ++it)
  {
    removed.push_back(*it);
  }
  arr.erase(eraseBegin, eraseEnd);

  if (items.is_array())
  {
    for (const auto &item : items)
    {
      arr.insert(arr.begin() + start, item);
      start++;
    }
  }

  return removed;
}

std::string JS_toLocaleString(const nlohmann::json &arr)
{
  std::string result = "";

  for (size_t i = 0; i < arr.size(); i++)
  {
    if (i > 0)
    {
      result += ", ";
    }

    result += arr[i].dump();
  }

  return result;
}

std::string JS_toSource(const nlohmann::json &arr)
{
  return JS_toLocaleString(arr);
}

std::string JS_toString(const nlohmann::json &arr)
{
  return JS_toLocaleString(arr);
}

size_t JS_unshift(nlohmann::json &arr, const nlohmann::json &items)
{
  for (auto it = items.rbegin(); it != items.rend(); ++it)
  {
    arr.insert(arr.begin(), *it);
  }
  return arr.size();
}

nlohmann::json JS_values(const nlohmann::json &arr) { return arr; }
