#include <string>
#include "../nlohmann-json.hh"

class __Set__
{
private:
    nlohmann::json data;

public:
    __Set__() {}

    void add(const nlohmann::json &value)
    {
        data[value.dump()] = value;
    }

    bool deleteKey(const nlohmann::json &value)
    {
        auto key = value.dump();
        auto it = data.find(key);
        if (it != data.end())
        {
            data.erase(it);
            return true;
        }
        return false;
    }

    bool has(const nlohmann::json &value) const
    {
        return data.find(value.dump()) != data.end();
    }

    void clear()
    {
        data.clear();
    }

    int size() const
    {
        return data.size();
    }

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

nlohmann::json JS_entries(const __Set__ &someSet) { return someSet.entries(); }
nlohmann::json JS_keys(const __Set__ &someSet) { return someSet.keys(); }
nlohmann::json JS_values(const __Set__ &someSet) { return someSet.values(); }
