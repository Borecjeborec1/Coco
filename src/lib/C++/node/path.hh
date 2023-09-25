// Ignore imports
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "nlohmann-json.hh"
// Ignore imports end

class __path__
{
public:
  static char sep;
  static char delimiter;
  static std::string basename(const std::string &path,
                              const std::string &suffix = "")
  {
    std::string base = path.substr(path.find_last_of('/') + 1);
    if (suffix.empty() ||
        base.substr(base.length() - suffix.length()) != suffix)
    {
      return base;
    }
    return base.substr(0, base.length() - suffix.length());
  }

  static std::string dirname(const std::string &path)
  {
    size_t found = path.find_last_of('/');
    if (found != std::string::npos)
    {
      return path.substr(0, found);
    }
    return "";
  }

  static std::string extname(const std::string &path)
  {
    size_t found = path.find_last_of('.');
    if (found != std::string::npos && found > path.find_last_of('/'))
    {
      return path.substr(found);
    }
    return "";
  }

  template <typename... Args>
  static std::string join(Args... args)
  {
    std::string result;
    joinInternal(result, args...);
    if (!result.empty() && result.back() == sep)
    {
      result.pop_back();
    }
    return result;
  }
  static bool isAbsolute(const std::string &path)
  {
    if (path.empty())
    {
      return false;
    }

    if (path[0] == sep || path[0] == '/')
    {
      return true;
    }

    if (path.length() >= 3 && std::isalpha(path[0]) && path[1] == ':' &&
        (path[2] == sep || path[2] == '/'))
    {
      return true;
    }

    return false;
  }
  static std::string normalize(const std::string &path)
  {
    if (path.empty())
    {
      return ".";
    }

    char separator = sep;

    std::vector<std::string> segments;
    size_t start = 0;
    size_t end = 0;
    while ((end = path.find_first_of("/\\", start)) != std::string::npos)
    {
      std::string segment = path.substr(start, end - start);
      start = end + 1;

      if (segment == "..")
      {
        if (!segments.empty() && segments.back() != "..")
        {
          segments.pop_back();
        }
        else
        {
          segments.push_back("..");
        }
      }
      else if (segment != "." && !segment.empty())
      {
        segments.push_back(segment);
      }
    }

    std::string lastSegment = path.substr(start);

    if (lastSegment == "..")
    {
      if (!segments.empty() && segments.back() != "..")
      {
        segments.pop_back();
      }
      else
      {
        segments.push_back("..");
      }
    }
    else if (lastSegment != "." && !lastSegment.empty())
    {
      segments.push_back(lastSegment);
    }

    std::string normalizedPath;
    for (const std::string &segment : segments)
    {
      normalizedPath += segment;
      normalizedPath += separator;
    }

    if (!path.empty() && (path.back() == '/' || path.back() == '\\'))
    {
      normalizedPath += separator;
    }

    if (isAbsolute(path))
    {
      if (normalizedPath.empty() || normalizedPath[0] != separator)
      {
        normalizedPath = separator + normalizedPath;
      }
    }
    if (!normalizedPath.empty() && normalizedPath.back() == sep)
    {
      normalizedPath.pop_back();
    }
    return normalizedPath;
  }
  static nlohmann::json parse(const std::string &path)
  {
    nlohmann::json result;

    size_t lastSeparatorPos = path.find_last_of("/\\");
    std::string dir, base;
    if (lastSeparatorPos != std::string::npos)
    {
      dir = path.substr(0, lastSeparatorPos);
      base = path.substr(lastSeparatorPos + 1);
    }
    else
    {
      dir = path;
      base = path; // Set base to path if there's no separator
    }

    size_t rootEnd = 0;
    if (isAbsolute(path))
    {
      // Check for Windows-style drive letter
      if (path.size() > 2 && path[1] == ':' && (path[2] == '/' || path[2] == '\\'))
      {
        rootEnd = 3; // Include drive letter and slash (e.g., "C:/")
      }
      else
      {
        rootEnd = 1; // Just a single slash for other absolute paths
      }
    }

    size_t extPos = base.find_last_of('.');
    std::string root = path.substr(0, rootEnd);
    std::string ext = (extPos != std::string::npos) ? base.substr(extPos) : "";
    std::string name =
        (extPos != std::string::npos) ? base.substr(0, extPos) : base;

    result["root"] = root;
    result["dir"] = dir;
    result["base"] = base;
    result["ext"] = ext;
    result["name"] = name;

    return result;
  }
  static std::string relative(const std::string &from, const std::string &to)
  {
    std::string sep = std::string(1, __path__::sep);

    std::string normalizedFrom = normalize(from);
    std::string normalizedTo = normalize(to);

    std::vector<std::string> fromSegments;
    std::vector<std::string> toSegments;
    size_t start = 0;
    size_t end = 0;

    while ((end = normalizedFrom.find(sep, start)) != std::string::npos)
    {
      std::string seg = normalizedFrom.substr(start, end - start);
      std::string segment = normalizedTo.substr(start, end - start);
      fromSegments.push_back(seg);
      toSegments.push_back(segment);
      start = end + 1;
    }
    fromSegments.push_back(normalizedFrom.substr(start));
    toSegments.push_back(normalizedTo.substr(start));

    size_t commonPrefixLength = 0;
    while (commonPrefixLength < fromSegments.size() &&
           commonPrefixLength < toSegments.size() &&
           fromSegments[commonPrefixLength] == toSegments[commonPrefixLength])
    {
      commonPrefixLength++;
    }

    std::string relativePath;
    for (size_t i = commonPrefixLength; i < fromSegments.size(); i++)
    {
      relativePath += "..";
      relativePath += sep;
    }

    for (size_t i = commonPrefixLength; i < toSegments.size(); i++)
    {
      relativePath += toSegments[i];
      relativePath += sep;
    }

    if (!relativePath.empty())
    {
      relativePath.pop_back();
    }

    return relativePath;
  }
  static std::string toNamespacedPath(const std::string &path)
  {
    if (!path.empty() && path[1] == ':' && (path[2] == '/' || path[2] == '\\'))
    {
      return "\\\\?\\" + path;
    }

    return path;
  }
  static std::string format(const nlohmann::json &pathObject)
  {
    std::string result;

    if (pathObject.find("dir") != pathObject.end())
    {
      result += pathObject["dir"];
    }
    else
    {
      if (pathObject.find("root") != pathObject.end())
      {
        result += pathObject["root"];
      }
    }

    if (pathObject.find("base") != pathObject.end())
    {
      result += sep;
      result += pathObject["base"];
    }
    else
    {
      if (pathObject.find("name") != pathObject.end())
      {
        result += sep;
        result += pathObject["name"];
      }

      if (pathObject.find("ext") != pathObject.end())
      {
        if (pathObject["ext"].empty() || pathObject["ext"][0] != '.')
        {
          result += '.';
        }
        result += pathObject["ext"];
      }
    }

    return result;
  }

private:
  template <typename T, typename... Args>
  static void joinInternal(std::string &result, const T &first, Args... args)
  {
    result += first;
    result += sep;
    joinInternal(result, args...);
  }

  static void joinInternal(std::string &result)
  {
    // Do nothing, this is the base case
  }
};

char __path__::sep = '\\';
char __path__::delimiter = ';';