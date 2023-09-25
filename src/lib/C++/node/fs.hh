// Ignore imports
#include <fstream>
#include <string>
#include <functional>
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>
#include <random>
#include "nlohmann-json.hh"
// Ignore imports end

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

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

    static std::string readFileSync(const std::string &path, const std::string &encoding)
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
    static void writeFile(const std::string &path, const std::string &data, const std::function<void(std::string err)> &callback)
    {
        std::ofstream file(path);
        if (!file.is_open())
        {
            callback("Error opening file");
            return;
        }

        file << data;
        file.close();

        callback("");
    }

    static void writeFileSync(const std::string &path, const std::string &data)
    {
        std::ofstream file(path);
        if (!file.is_open())
        {
            throw std::runtime_error("Error opening file");
        }

        file << data;
        file.close();
    }
    static void access(const std::string &path, std::filesystem::perms mode, const std::function<void(std::string err)> &callback)
    {
        try
        {
            std::filesystem::path filePath(path);
            std::filesystem::perms permissions = std::filesystem::status(filePath).permissions();

            // Check if the specified access mode is granted
            bool hasAccess = true;

            if ((mode & std::filesystem::perms::owner_read) != std::filesystem::perms::none && (permissions & std::filesystem::perms::owner_read) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::owner_write) != std::filesystem::perms::none && (permissions & std::filesystem::perms::owner_write) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::owner_exec) != std::filesystem::perms::none && (permissions & std::filesystem::perms::owner_exec) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::group_read) != std::filesystem::perms::none && (permissions & std::filesystem::perms::group_read) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::group_write) != std::filesystem::perms::none && (permissions & std::filesystem::perms::group_write) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::group_exec) != std::filesystem::perms::none && (permissions & std::filesystem::perms::group_exec) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::others_read) != std::filesystem::perms::none && (permissions & std::filesystem::perms::others_read) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::others_write) != std::filesystem::perms::none && (permissions & std::filesystem::perms::others_write) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::others_exec) != std::filesystem::perms::none && (permissions & std::filesystem::perms::others_exec) == std::filesystem::perms::none)
                hasAccess = false;

            if (!hasAccess)
            {
                callback("Permission denied");
            }
            else
            {
                callback("");
            }
        }
        catch (const std::exception &e)
        {
            // Handle other errors
            callback(e.what());
        }
    }

    static void access(const std::string &path, const std::function<void(std::string err)> &callback)
    {
        try
        {
            std::filesystem::path filePath(path);
            std::filesystem::perms permissions = std::filesystem::status(filePath).permissions();

            // Check if the specified access mode is granted
            bool hasAccess = true;

            if ((permissions & std::filesystem::perms::owner_read) == std::filesystem::perms::none)
                hasAccess = false;

            if ((permissions & std::filesystem::perms::owner_write) == std::filesystem::perms::none)
                hasAccess = false;

            if ((permissions & std::filesystem::perms::owner_exec) == std::filesystem::perms::none)
                hasAccess = false;

            if ((permissions & std::filesystem::perms::group_read) == std::filesystem::perms::none)
                hasAccess = false;

            if ((permissions & std::filesystem::perms::group_write) == std::filesystem::perms::none)
                hasAccess = false;

            if ((permissions & std::filesystem::perms::group_exec) == std::filesystem::perms::none)
                hasAccess = false;

            if ((permissions & std::filesystem::perms::others_read) == std::filesystem::perms::none)
                hasAccess = false;

            if ((permissions & std::filesystem::perms::others_write) == std::filesystem::perms::none)
                hasAccess = false;

            if ((permissions & std::filesystem::perms::others_exec) == std::filesystem::perms::none)
                hasAccess = false;

            if (!hasAccess)
            {
                callback("Permission denied");
            }
            else
            {
                callback("");
            }
        }
        catch (const std::exception &e)
        {
            // Handle other errors
            callback(e.what());
        }
    }

    static void accessSync(const std::string &path, std::filesystem::perms mode = std::filesystem::perms::owner_read)
    {
        try
        {
            std::filesystem::path filePath(path);
            std::filesystem::perms permissions = std::filesystem::status(filePath).permissions();

            // Check if the specified access mode is granted
            bool hasAccess = true;

            if ((mode & std::filesystem::perms::owner_read) != std::filesystem::perms::none && (permissions & std::filesystem::perms::owner_read) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::owner_write) != std::filesystem::perms::none && (permissions & std::filesystem::perms::owner_write) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::owner_exec) != std::filesystem::perms::none && (permissions & std::filesystem::perms::owner_exec) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::group_read) != std::filesystem::perms::none && (permissions & std::filesystem::perms::group_read) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::group_write) != std::filesystem::perms::none && (permissions & std::filesystem::perms::group_write) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::group_exec) != std::filesystem::perms::none && (permissions & std::filesystem::perms::group_exec) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::others_read) != std::filesystem::perms::none && (permissions & std::filesystem::perms::others_read) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::others_write) != std::filesystem::perms::none && (permissions & std::filesystem::perms::others_write) == std::filesystem::perms::none)
                hasAccess = false;

            if ((mode & std::filesystem::perms::others_exec) != std::filesystem::perms::none && (permissions & std::filesystem::perms::others_exec) == std::filesystem::perms::none)
                hasAccess = false;

            if (!hasAccess)
            {
                throw std::runtime_error("Permission denied");
            }
        }
        catch (const std::exception &e)
        {
            // Handle other errors
            throw std::runtime_error(e.what());
        }
    }

    static void appendFile(const std::string &path, const std::string &data, const std::function<void(std::string err)> &callback)
    {
        try
        {
            std::ofstream file(path, std::ios::app);

            if (!file.is_open())
            {
                callback("Error opening file");
                return;
            }

            file << data;
            file.close();

            callback("");
        }
        catch (const std::exception &e)
        {
            callback(e.what());
        }
    }

    static void appendFileSync(const std::string &path, const std::string &data)
    {
        try
        {
            std::ofstream file(path, std::ios::app);

            if (!file.is_open())
            {
                throw std::runtime_error("Error opening file");
            }

            file << data;
            file.close();
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error(e.what());
        }
    }

    static void chmod(const std::string &path, int mode, const std::function<void(std::string err)> &callback)
    {
        try
        {
            std::filesystem::path filePath(path);

            if (std::filesystem::exists(filePath))
            {
                std::filesystem::permissions(filePath, static_cast<std::filesystem::perms>(mode));
                callback("");
            }
            else
            {
                callback("File not found");
            }
        }
        catch (const std::exception &e)
        {
            callback(e.what());
        }
    }

    static void chmodSync(const std::string &path, int mode)
    {
        try
        {
            std::filesystem::path filePath(path);

            if (std::filesystem::exists(filePath))
            {
                std::filesystem::permissions(filePath, static_cast<std::filesystem::perms>(mode));
            }
            else
            {
                throw std::runtime_error("File not found");
            }
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error(e.what());
        }
    }
    static void chown(const std::string &path, int uid, int gid, const std::function<void(std::string err)> &callback)
    {
        try
        {
#ifdef _WIN32
            callback("Unsupported operation on Windows");
#else
            if (::chown(path.c_str(), uid, gid) != 0)
            {
                callback(std::strerror(errno));
                return;
            }

            callback("");
#endif
        }
        catch (const std::exception &e)
        {
            callback(e.what());
        }
    }

    static void chownSync(const std::string &path, int uid, int gid)
    {
        try
        {
#ifdef _WIN32
            throw std::runtime_error("Unsupported operation on Windows");
#else
            if (::chown(path.c_str(), uid, gid) != 0)
            {
                throw std::runtime_error(std::strerror(errno));
            }
#endif
        }
        catch (const std::exception &e)
        {
            // Handle other errors
            throw std::runtime_error(e.what());
        }
    }

    static void copyFile(const std::string &src, const std::string &dest, int mode, const std::function<void(std::string err)> &callback)
    {
        try
        {
#ifdef _WIN32
            if (!CopyFileA(src.c_str(), dest.c_str(), (mode & 1) != 0))
            {
                callback("Error copying file");
                return;
            }
#else
            int src_fd = ::open(src.c_str(), O_RDONLY);
            if (src_fd == -1)
            {
                callback(std::strerror(errno));
                return;
            }

            int dest_fd = ::open(dest.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (dest_fd == -1)
            {
                ::close(src_fd);

                callback(std::strerror(errno));
                return;
            }

            ssize_t bytes_copied = sendfile(dest_fd, src_fd, nullptr, 0);
            if (bytes_copied == -1)
            {
                ::close(src_fd);
                ::close(dest_fd);

                callback(std::strerror(errno));
                return;
            }

            ::close(src_fd);
            ::close(dest_fd);

            if ((mode & 1) != 0 && bytes_copied > 0)
            {
                if (std::remove(dest.c_str()) != 0)
                {
                    callback(std::strerror(errno));
                    return;
                }
            }
#endif

            callback("");
        }
        catch (const std::exception &e)
        {
            callback(e.what());
        }
    }
    static void copyFileSync(const std::string &src, const std::string &dest, int mode)
    {
        try
        {
#ifdef _WIN32
            if (!CopyFileA(src.c_str(), dest.c_str(), (mode & 1) != 0))
            {
                throw std::runtime_error("Error copying file");
            }
#else
            int src_fd = ::open(src.c_str(), O_RDONLY);
            if (src_fd == -1)
            {
                throw std::runtime_error(std::strerror(errno));
            }

            int dest_fd = ::open(dest.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (dest_fd == -1)
            {
                ::close(src_fd);

                // Handle errors
                throw std::runtime_error(std::strerror(errno));
            }

            ssize_t bytes_copied = sendfile(dest_fd, src_fd, nullptr, 0);
            if (bytes_copied == -1)
            {
                ::close(src_fd);
                ::close(dest_fd);

                throw std::runtime_error(std::strerror(errno));
            }

            ::close(src_fd);
            ::close(dest_fd);

            if ((mode & 1) != 0 && bytes_copied > 0)
            {
                if (std::remove(dest.c_str()) != 0)
                {
                    throw std::runtime_error(std::strerror(errno));
                }
            }
#endif
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error(e.what());
        }
    }
    static void mkdir(const std::string &path, const nlohmann::json &options, const std::function<void(std::string err, std::string createdDir)> &callback)
    {
        try
        {
            bool recursive = options.value("recursive", false);

            if (recursive)
            {
                std::filesystem::create_directories(path);
                callback("", path);
            }
            else
            {
                std::filesystem::create_directory(path);
                callback("", path);
            }
        }
        catch (const std::system_error &e)
        {
            callback(e.what(), "");
        }
    }

    static std::string mkdirSync(const std::string &path, const nlohmann::json &options)
    {
        try
        {
            bool recursive = options.value("recursive", false);

            if (recursive)
            {
                std::filesystem::create_directories(path);
                return path;
            }
            else
            {
                std::filesystem::create_directory(path);
                return path;
            }
        }
        catch (const std::system_error &e)
        {
            return e.what();
        }
    }
    static void mkdtemp(const std::string &prefix, const nlohmann::json &options, const std::function<void(std::string err, std::string tmpDir)> &callback)
    {
        try
        {
            std::string encoding = options.value("encoding", "utf8");

            // Generate a unique temporary directory name
            std::string tmpDir = generateTempDirName(prefix);

            // Create the temporary directory
            if (std::filesystem::create_directory(tmpDir))
            {
                callback("", tmpDir);
            }
            else
            {
                throw std::runtime_error("Error creating temporary directory");
            }
        }
        catch (const std::exception &e)
        {
            callback(e.what(), "");
        }
    }

    // Synchronous version - mkdtempSync
    static std::string mkdtempSync(const std::string &prefix, const nlohmann::json &options)
    {
        try
        {
            std::string encoding = options.value("encoding", "utf8");

            // Generate a unique temporary directory name
            std::string tmpDir = generateTempDirName(prefix);

            // Create the temporary directory
            if (std::filesystem::create_directory(tmpDir))
            {
                return tmpDir;
            }
            else
            {
                throw std::runtime_error("Error creating temporary directory");
            }
        }
        catch (const std::exception &e)
        {
            return e.what();
        }
    }
    static void readdir(const std::string &path, const nlohmann::json &options, const std::function<void(std::string err, nlohmann::json files)> &callback)
    {
        try
        {
            std::string encoding = options.value("encoding", "utf8");
            bool withFileTypes = options.value("withFileTypes", false);
            bool recursive = options.value("recursive", false);

            std::vector<nlohmann::json> fileList;

            if (withFileTypes)
            {
                for (const auto &entry : std::filesystem::recursive_directory_iterator(path))
                {
                    nlohmann::json file;

                    if (entry.is_directory())
                    {
                        file["name"] = entry.path().filename();
                        file["isDirectory"] = true;
                    }
                    else
                    {
                        file["name"] = entry.path().filename();
                        file["isDirectory"] = false;
                    }

                    fileList.push_back(file);
                }
            }
            else if (recursive)
            {
                for (const auto &entry : std::filesystem::recursive_directory_iterator(path))
                {
                    fileList.push_back(entry.path().filename());
                }
            }
            else
            {
                for (const auto &entry : std::filesystem::directory_iterator(path))
                {
                    fileList.push_back(entry.path().filename());
                }
            }

            callback("", fileList);
        }
        catch (const std::exception &e)
        {
            callback(e.what(), nlohmann::json());
        }
    }

    static void readdir(const std::string &path, const std::function<void(std::string err, nlohmann::json files)> &callback)
    {
        try
        {
            nlohmann::json options = {};
            std::string encoding = options.value("encoding", "utf8");
            bool withFileTypes = options.value("withFileTypes", false);
            bool recursive = options.value("recursive", false);

            std::vector<nlohmann::json> fileList;

            if (withFileTypes)
            {
                for (const auto &entry : std::filesystem::recursive_directory_iterator(path))
                {
                    nlohmann::json file;

                    if (entry.is_directory())
                    {
                        file["name"] = entry.path().filename();
                        file["isDirectory"] = true;
                    }
                    else
                    {
                        file["name"] = entry.path().filename();
                        file["isDirectory"] = false;
                    }

                    fileList.push_back(file);
                }
            }
            else if (recursive)
            {
                for (const auto &entry : std::filesystem::recursive_directory_iterator(path))
                {
                    fileList.push_back(entry.path().filename());
                }
            }
            else
            {
                for (const auto &entry : std::filesystem::directory_iterator(path))
                {
                    fileList.push_back(entry.path().filename());
                }
            }

            callback("", fileList);
        }
        catch (const std::exception &e)
        {
            callback(e.what(), nlohmann::json());
        }
    }

    // Synchronous version - readdirSync
    static nlohmann::json readdirSync(const std::string &path, const nlohmann::json &options = nlohmann::json{{"encoding", "utf3218"}})
    {
        std::string encoding = options.contains("encoding") ? options["encoding"].get<std::string>() : "utf8";
        bool withFileTypes = options.contains("withFileTypes") ? options["withFileTypes"].get<bool>() : false;
        bool recursive = options.contains("recursive") ? options["recursive"].get<bool>() : false;

        std::vector<nlohmann::json> fileList;

        if (withFileTypes)
        {
            for (const auto &entry : std::filesystem::recursive_directory_iterator(path))
            {
                nlohmann::json file;

                if (entry.is_directory())
                {
                    file["name"] = entry.path().filename();
                    file["isDirectory"] = true;
                }
                else
                {
                    file["name"] = entry.path().filename();
                    file["isDirectory"] = false;
                }

                fileList.push_back(file);
            }
        }
        else if (recursive)
        {
            for (const auto &entry : std::filesystem::recursive_directory_iterator(path))
            {
                fileList.push_back(entry.path().filename());
            }
        }
        else
        {
            for (const auto &entry : std::filesystem::directory_iterator(path))
            {
                fileList.push_back(entry.path().filename());
            }
        }

        return fileList;
    }

private:
    // Generate a unique temporary directory name
    static std::string generateTempDirName(const std::string &prefix)
    {
        // Generate six random characters
        static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        static const size_t charsetSize = sizeof(charset) - 1;
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> distr(0, charsetSize - 1);

        std::string randomChars;
        for (int i = 0; i < 6; ++i)
        {
            randomChars += charset[distr(gen)];
        }

        // Concatenate the prefix and random characters
        return prefix + randomChars;
    }
};
