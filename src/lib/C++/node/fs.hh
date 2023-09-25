// Ignore imports
#include <fstream>
#include <string>
#include <functional>
// Ignore imports end

class __fs__
{
public:
    static void readFile(const std::string &path, const std::function<void(std::string err, std::string data)> &callback)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            callback("Error opening file", "");
            return;
        }

        std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
        file.close();

        callback("", content);
    }

    static std::string readFileSync(const std::string &path)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            throw std::runtime_error("Error opening file");
        }

        std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
        file.close();

        return content;
    }
};
