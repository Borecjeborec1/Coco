#include <iostream>
#include <vector>
#include <string>
#include "../nlohmann-json.hh"

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
    try
    {
      if (callback(element))
      {
        result.push_back(element);
      }
    }
    catch (const std::exception &ex)
    {
      continue;
    }
  }

  return result;
}

template <typename Callable>
nlohmann::json JS_find(const nlohmann::json &arr, Callable callback)
{
  if (arr.empty())
  {
    return "undefined";
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

  return "undefined";
}
template <typename Callable>
int JS_findIndex(const nlohmann::json &arr, Callable callback)
{
  if (arr.empty())
  {
    return -1;
  }

  nlohmann::json::value_t expected_type = arr[0].type();
  int index = 0;

  for (const auto &element : arr)
  {
    if (element.type() != expected_type)
    {
      return -1;
    }

    bool satisfiesCallback = false;
    try
    {
      satisfiesCallback = callback(element);
    }
    catch (const std::exception &ex)
    {
      return -1;
    }

    if (satisfiesCallback)
    {
      return index;
    }

    index++;
  }

  return -1;
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

template <typename Callable>
nlohmann::json JS_flatMap(const nlohmann::json &arr, Callable callback)
{
  nlohmann::json result = nlohmann::json::array();

  for (const auto &element : arr)
  {
    try
    {
      nlohmann::json mapped = callback(element);

      if (mapped.is_array())
      {
        result.insert(result.end(), mapped.begin(), mapped.end());
      }
      else
      {
        result.push_back(mapped);
      }
    }
    catch (const std::exception &ex)
    {
      continue;
    }
  }

  return result;
}

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
      result += delimiter;
    }

    result += element.dump();
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

template <typename Callable>
nlohmann::json JS_map(const nlohmann::json &arr, Callable callback)
{
  nlohmann::json result = nlohmann::json::array();

  for (const auto &element : arr)
  {
    try
    {
      result.push_back(callback(element));
    }
    catch (const std::exception &ex)
    {
      continue;
    }
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

template <typename Callable>
nlohmann::json JS_reduce(const nlohmann::json &arr, Callable callback,
                         nlohmann::json initialValue = nlohmann::json())
{
  nlohmann::json accumulator = initialValue;

  for (const auto &element : arr)
  {
    try
    {
      accumulator = callback(accumulator, element);
    }
    catch (const std::exception &ex)
    {
      continue;
    }
  }

  return accumulator;
}

template <typename Callable>
nlohmann::json JS_reduceRight(const nlohmann::json &arr, Callable callback,
                              nlohmann::json initialValue = nlohmann::json())
{
  nlohmann::json accumulator = initialValue;

  for (auto it = arr.rbegin(); it != arr.rend(); ++it)
  {
    try
    {
      nlohmann::json element = *it;
      accumulator = callback(element, accumulator);
    }
    catch (const std::exception &ex)
    {
      continue;
    }
  }

  return accumulator;
}

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

template <typename Callable>
bool JS_some(const nlohmann::json &arr, Callable callback)
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
      continue;
    }

    if (satisfiesCallback)
    {
      return true;
    }
  }

  return false;
}

nlohmann::json JS_sort(
    const nlohmann::json &arr,
    std::function<int(const nlohmann::json &, const nlohmann::json &)> compare =
        nullptr)
{
  nlohmann::json result = arr;

  if (!compare)
  {
    compare = [](const nlohmann::json &a, const nlohmann::json &b) -> int
    {
      if (a.is_number() && b.is_number())
      {
        return a < b ? -1 : (a > b ? 1 : 0);
      }
      else if (a.is_string() && b.is_string())
      {
        return a < b ? -1 : (a > b ? 1 : 0);
      }
      else
      {
        return a.is_number() ? -1 : 1;
      }
    };
  }

  std::sort(result.begin(), result.end(),
            [&](const nlohmann::json &a, const nlohmann::json &b) -> bool
            {
              return compare(a, b) < 0;
            });

  return result;
}

nlohmann::json
JS_splice(nlohmann::json &arr, int start, int deleteCount,
          const nlohmann::json &insertItems = nlohmann::json::array())
{
  nlohmann::json removedItems = nlohmann::json::array();

  if (start < 0)
  {
    start = arr.size() + start;
    if (start < 0)
    {
      start = 0;
    }
  }
  if (start > static_cast<int>(arr.size()))
  {
    start = arr.size();
  }
  if (deleteCount < 0)
  {
    deleteCount = 0;
  }
  if (deleteCount > static_cast<int>(arr.size()) - start)
  {
    deleteCount = arr.size() - start;
  }

  for (int i = 0; i < deleteCount; ++i)
  {
    removedItems.push_back(arr[start + i]);
  }

  nlohmann::json result = nlohmann::json::array();

  for (int i = 0; i < start; ++i)
  {
    result.push_back(arr[i]);
  }

  for (const auto &item : insertItems)
  {
    result.push_back(item);
  }

  for (int i = start + deleteCount; i < static_cast<int>(arr.size()); ++i)
  {
    result.push_back(arr[i]);
  }

  arr = result;

  return removedItems;
}

std::string JS_toLocaleString(const nlohmann::json &arr) { return arr.dump(); }

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
