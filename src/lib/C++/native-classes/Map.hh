#include <string>
#include <map>
#include "../nlohmann-json.hh"

class __Map__
{
private:
  nlohmann::json data;

public:
  __Map__() {}

  void set(const std::string &key, const nlohmann::json &value)
  {
    data[key] = value;
  }

  nlohmann::json get(const std::string &key) const
  {
    if (data.find(key) != data.end())
    {
      return data[key];
    }
    return nlohmann::json();
  }

  bool has(const std::string &key) const
  {
    return data.find(key) != data.end();
  }

  bool deleteKey(const std::string &key)
  {
    auto it = data.find(key);
    if (it != data.end())
    {
      data.erase(it);
      return true;
    }
    return false;
  }

  void clear() { data.clear(); }

  size_t size() const { return data.size(); }

  nlohmann::json entries() const
  {
    nlohmann::json result;
    int index = 0;
    for (const auto &element : data)
    {
      nlohmann::json entry;
      entry.push_back(index);
      entry.push_back(element);
      result.push_back(entry);
      index++;
    }
    return result;
  }

  nlohmann::json keys() const
  {
    nlohmann::json keysArray;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
      keysArray.push_back(it.key());
    }
    return keysArray;
  }

  nlohmann::json values() const
  {
    nlohmann::json valuesArray;
    for (auto &pair : data.items())
    {
      valuesArray.push_back(pair.value());
    }
    return valuesArray;
  }

  void forEach(std::function<void(const std::string &, const nlohmann::json &)>
                   callback) const
  {
    for (auto &pair : data.items())
    {
      callback(pair.key(), pair.value());
    }
  }
};

nlohmann::json JS_entries(const __Map__ &map) { return map.entries(); }
nlohmann::json JS_keys(const __Map__ &map) { return map.keys(); }
nlohmann::json JS_values(const __Map__ &map) { return map.values(); }
