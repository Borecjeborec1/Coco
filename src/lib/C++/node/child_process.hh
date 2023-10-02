#include <string>
#include <fstream>
#include <sstream>
#include <functional>
#include <iostream>
#include "../nlohmann-json.hh"

#ifdef _WIN32
#else
#endif

class __child_process__
{
public:
    static nlohmann::json exec(const std::string &command, const nlohmann::json &options = nlohmann::json(),
                               const std::function<void(std::string _error, std::string _stdout, std::string _stderr)> &callback)
    {
        std::stringstream result;
        std::stringstream errors;
        int exitCode = 0;

#ifdef _WIN32
        FILE *pipe = _popen(command.c_str(), "r");
#else
        FILE *pipe = popen(command.c_str(), "r");
#endif

        if (pipe)
        {
            char buffer[128];
            while (!feof(pipe))
            {
                if (fgets(buffer, sizeof(buffer), pipe) != nullptr)
                {
                    result << buffer;
                }
            }
#ifdef _WIN32
            exitCode = _pclose(pipe);
#else
            exitCode = pclose(pipe);
#endif
        }
        else
        {
            errors << "Failed to execute command.";
            exitCode = -1;
        }

        callback(errors.str(), result.str(), "");

        nlohmann::json resultJson;
        resultJson["error"] = errors.str();
        resultJson["stdout"] = result.str();
        resultJson["stderr"] = "";
        resultJson["code"] = exitCode;

        return resultJson;
    }

    static nlohmann::json execFile(const std::string &command, const nlohmann::json &args = nlohmann::json(), const nlohmann::json &options = nlohmann::json(), const std::function<void(std::string _error, std::string _stdout, std::string _stderr)> &callback);

    // spawn
    static nlohmann::json execSync(const std::string &command, const nlohmann::json &options = nlohmann::json());

    static nlohmann::json execFileSync(const std::string &command, const nlohmann::json &args = nlohmann::json(), const nlohmann::json &options = nlohmann::json());
    // spawnSync
};