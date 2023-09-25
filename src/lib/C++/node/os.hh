// Ignore imports
#include <string>
#include "nlohmann-json.hh"
// Ignore imports end

#ifdef _WIN32
#include <WinSock2.h>
#include <Windows.h>
#include <ShlObj.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>
#include <Pdh.h>
#pragma comment(lib, "Pdh.lib")
#pragma comment(lib, "iphlpapi.lib")
#else
#include <sys/utsname.h>
#include <sys/param.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/sysctl.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
class __os__
{
public:
    static std::string EOL;
    static std::string devNull;
    static nlohmann::json constants;
    static std::string arch()
    {
#if defined(__arm__)
        return "arm";
#elif defined(__aarch64__)
        return "arm64";
#elif defined(__i386__)
        return "ia32";
#elif defined(__mips__)
        return "mips";
#elif defined(__mipsel__)
        return "mipsel";
#elif defined(__powerpc__) || defined(__ppc__) || defined(__PPC__)
        return "ppc";
#elif defined(__powerpc64__) || defined(__ppc64__) || defined(__PPC64__)
        return "ppc64";
#elif defined(__riscv) && defined(__LP64__)
        return "riscv64";
#elif defined(__s390__)
        return "s390";
#elif defined(__s390x__)
        return "s390x";
#else
        return "x64";
#endif
    }

    static long long freemem()
    {
#ifdef _WIN32
        MEMORYSTATUSEX memoryStatus;
        memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&memoryStatus);
        return static_cast<long long>(memoryStatus.ullAvailPhys);
#else
        int mib[2] = {CTL_HW, HW_USERMEM};
        long long userMemory;
        size_t len = sizeof(userMemory);
        sysctl(mib, 2, &userMemory, &len, NULL, 0);
        return userMemory;
#endif
    }

    static std::string homedir()
    {
#ifdef _WIN32
        const char *userProfile = std::getenv("USERPROFILE");
        if (userProfile != nullptr)
        {
            return userProfile;
        }
        else
        {
            wchar_t profilePath[MAX_PATH];
            if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, profilePath)))
            {
                auto wst = std::wstring(profilePath);
                return std::string(wst.begin(), wst.end());
            }
        }
        return "";
#else
        const char *home = std::getenv("HOME");
        if (home != nullptr)
        {
            return home;
        }
        else
        {
            struct passwd *pw = getpwuid(geteuid());
            if (pw != nullptr)
            {
                return pw->pw_dir;
            }
        }
        return "";
#endif
    }

    static std::string hostname()
    {
// Platform-specific code to get the hostname
#ifdef _WIN32
        char computerName[256];
        DWORD size = sizeof(computerName);
        if (GetComputerNameA(computerName, &size))
        {
            return computerName;
        }
        else
        {
            return "";
        }
#else
        char hostname[HOST_NAME_MAX];
        if (gethostname(hostname, sizeof(hostname)) == 0)
        {
            return hostname;
        }
        else
        {
            return "";
        }
#endif
    }

    static std::string machine()
    {
#ifdef _WIN32
        OSVERSIONINFOEX osvi;
        ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
        if (GetVersionEx((OSVERSIONINFO *)&osvi))
        {
            if (osvi.dwMajorVersion == 10 && osvi.dwMinorVersion == 0 && osvi.dwBuildNumber == 19042)
            {
                return "x86_64"; // Windows reports x86_64 for 64-bit on this version
            }
            else
            {
                SYSTEM_INFO sysInfo;
                GetNativeSystemInfo(&sysInfo);
                switch (sysInfo.wProcessorArchitecture)
                {
                case PROCESSOR_ARCHITECTURE_ARM:
                    return "arm";
                case PROCESSOR_ARCHITECTURE_ARM64:
                    return "arm64";
                case PROCESSOR_ARCHITECTURE_IA64:
                    return "ia64";
                case PROCESSOR_ARCHITECTURE_AMD64:
                    return "x86_64";
                case PROCESSOR_ARCHITECTURE_INTEL:
                    return "i686";
                default:
                    return "";
                }
            }
        }
        else
        {
            return "";
        }
#else
        struct utsname sysInfo;
        if (uname(&sysInfo) == 0)
        {
            return sysInfo.machine;
        }
        else
        {
            return "";
        }
#endif
    }

    static std::string platform()
    {
#ifdef _WIN32
        return "win32";
#elif defined(__linux__)
        struct utsname sysInfo;
        if (uname(&sysInfo) == 0)
        {
            if (std::string(sysInfo.sysname) == "Linux")
            {
                return "linux";
            }
        }
        return "";
#else
        struct utsname sysInfo;
        if (uname(&sysInfo) == 0)
        {
            if (std::string(sysInfo.sysname) == "Darwin")
            {
                return "darwin";
            }
            else if (std::string(sysInfo.sysname) == "FreeBSD")
            {
                return "freebsd";
            }
            else if (std::string(sysInfo.sysname) == "OpenBSD")
            {
                return "openbsd";
            }
            else if (std::string(sysInfo.sysname) == "NetBSD")
            {
                return "netbsd";
            }
            else if (std::string(sysInfo.sysname) == "AIX")
            {
                return "aix";
            }
            else if (std::string(sysInfo.sysname) == "SunOS")
            {
                return "sunos";
            }
        }
        return "";
#endif
    }

    static std::string release()
    {
#ifdef _WIN32
        OSVERSIONINFOEX osvi;
        ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
        if (GetVersionEx((OSVERSIONINFO *)&osvi))
        {
            std::string releaseInfo = "Windows ";
            releaseInfo += std::to_string(osvi.dwMajorVersion);
            releaseInfo += ".";
            releaseInfo += std::to_string(osvi.dwMinorVersion);
            return releaseInfo;
        }
        else
        {
            return "";
        }
#else
        struct utsname sysInfo;
        if (uname(&sysInfo) == 0)
        {
            return sysInfo.release;
        }
        else
        {
            return "";
        }
#endif
    }
    static std::string tmpdir()
    {
// Platform-specific code to get the temporary directory
#ifdef _WIN32
        const char *tempDir = std::getenv("TEMP");
        if (tempDir != nullptr)
        {
            return tempDir;
        }
        else
        {
            const char *tmpDir = std::getenv("TMP");
            if (tmpDir != nullptr)
            {
                return tmpDir;
            }
            else
            {
                return "C:\\Windows\\Temp"; // Default Windows temporary directory
            }
        }
#else
        const char *tmpDir = std::getenv("TMPDIR");
        if (tmpDir != nullptr)
        {
            return tmpDir;
        }
        else
        {
            return "/tmp"; // Default POSIX temporary directory
        }
#endif
    }
    static long long totalmem()
    {
// Platform-specific code to get the total system memory
#ifdef _WIN32
        MEMORYSTATUSEX memoryStatus;
        memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
        if (GlobalMemoryStatusEx(&memoryStatus))
        {
            return static_cast<long long>(memoryStatus.ullTotalPhys);
        }
        else
        {
            return 0;
        }
#else
        long long pageSize = sysconf(_SC_PAGE_SIZE);
        long long pageCount = sysconf(_SC_PHYS_PAGES);
        if (pageSize > 0 && pageCount > 0)
        {
            return pageSize * pageCount;
        }
        else
        {
            return 0;
        }
#endif
    }
    static std::string type()
    {
// Platform-specific code to get the operating system name
#ifdef _WIN32
        return "Windows_NT";
#elif defined(__linux__)
        struct utsname sysInfo;
        if (uname(&sysInfo) == 0)
        {
            return sysInfo.sysname;
        }
        else
        {
            return "";
        }
#else
        struct utsname sysInfo;
        if (uname(&sysInfo) == 0)
        {
            return sysInfo.sysname;
        }
        else
        {
            return "";
        }
#endif
    }
    static long long uptime()
    {
// Platform-specific code to get the system uptime
#ifdef _WIN32
        // Use the GetTickCount64 function to get the system uptime in milliseconds
        return static_cast<long long>(GetTickCount64() / 1000);
#else
        // Use the sysinfo function to get the system uptime in seconds
        struct sysinfo info;
        if (sysinfo(&info) != -1)
        {
            return static_cast<long long>(info.uptime);
        }
        else
        {
            return -1; // Error occurred
        }
#endif
    }
    static std::string version()
    {
        OSVERSIONINFOEX osvi;
        ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

        if (GetVersionEx((OSVERSIONINFO *)&osvi))
        {
            return std::to_string(osvi.dwMajorVersion) + "." +
                   std::to_string(osvi.dwMinorVersion) + "." +
                   std::to_string(osvi.dwBuildNumber);
        }
        else
        {
            return "";
        }
    }
    static nlohmann::json networkInterfaces()
    {
        nlohmann::json networkInterfacesJson;

// Platform-specific code to get network interface information
#ifdef _WIN32
        // Windows code to get network interfaces
        IP_ADAPTER_ADDRESSES *adapterAddresses = nullptr;
        ULONG outBufLen = 0;

        if (GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, nullptr, nullptr, &outBufLen) == ERROR_BUFFER_OVERFLOW)
        {
            adapterAddresses = (IP_ADAPTER_ADDRESSES *)malloc(outBufLen);
            if (GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, nullptr, adapterAddresses, &outBufLen) == NO_ERROR)
            {
                for (IP_ADAPTER_ADDRESSES *adapter = adapterAddresses; adapter; adapter = adapter->Next)
                {
                    nlohmann::json addressesJson;

                    for (IP_ADAPTER_UNICAST_ADDRESS *address = adapter->FirstUnicastAddress; address; address = address->Next)
                    {
                        nlohmann::json addressJson;
                        sockaddr *sockaddrPtr = address->Address.lpSockaddr;

                        if (sockaddrPtr->sa_family == AF_INET)
                        {
                            sockaddr_in *ipv4Address = reinterpret_cast<sockaddr_in *>(sockaddrPtr);
                            addressJson["address"] = inet_ntoa(ipv4Address->sin_addr);
                            addressJson["netmask"] = "";
                            addressJson["family"] = "IPv4";
                        }
                        else if (sockaddrPtr->sa_family == AF_INET6)
                        {
                            sockaddr_in6 *ipv6Address = reinterpret_cast<sockaddr_in6 *>(sockaddrPtr);
                            char ipv6AddressStr[INET6_ADDRSTRLEN];
                            if (inet_ntop(AF_INET6, &(ipv6Address->sin6_addr), ipv6AddressStr, INET6_ADDRSTRLEN))
                            {
                                addressJson["address"] = ipv6AddressStr;
                                addressJson["netmask"] = "";
                                addressJson["family"] = "IPv6";
                            }
                        }

                        addressJson["mac"] = "";
                        addressJson["internal"] = false;
                        addressJson["scopeid"] = 0;
                        addressJson["cidr"] = ""; // You can calculate CIDR if needed

                        addressesJson.push_back(addressJson);
                    }

                    networkInterfacesJson[adapter->AdapterName] = addressesJson;
                }
            }

            free(adapterAddresses);
        }
#else
        struct ifaddrs *ifAddrStruct = nullptr;
        if (getifaddrs(&ifAddrStruct) == 0)
        {
            for (struct ifaddrs *ifa = ifAddrStruct; ifa; ifa = ifa->ifa_next)
            {
                if (!ifa->ifa_addr)
                {
                    continue;
                }

                nlohmann::json addressesJson;
                sockaddr *sockaddrPtr = ifa->ifa_addr;

                if (sockaddrPtr->sa_family == AF_INET)
                {
                    sockaddr_in *ipv4Address = reinterpret_cast<sockaddr_in *>(sockaddrPtr);
                    nlohmann::json addressJson;
                    addressJson["address"] = inet_ntoa(ipv4Address->sin_addr);
                    addressJson["netmask"] = inet_ntoa(reinterpret_cast<sockaddr_in *>(ifa->ifa_netmask)->sin_addr);
                    addressJson["family"] = "IPv4";
                    addressJson["mac"] = "";
                    addressJson["internal"] = (ifa->ifa_flags & IFF_LOOPBACK) != 0;
                    addressJson["scopeid"] = 0;
                    addressJson["cidr"] = ""; // You can calculate CIDR if needed
                    addressesJson.push_back(addressJson);
                }
                else if (sockaddrPtr->sa_family == AF_INET6)
                {
                    sockaddr_in6 *ipv6Address = reinterpret_cast<sockaddr_in6 *>(sockaddrPtr);
                    char ipv6AddressStr[INET6_ADDRSTRLEN];
                    if (inet_ntop(AF_INET6, &(ipv6Address->sin6_addr), ipv6AddressStr, INET6_ADDRSTRLEN))
                    {
                        nlohmann::json addressJson;
                        addressJson["address"] = ipv6AddressStr;
                        addressJson["netmask"] = "";
                        addressJson["family"] = "IPv6";
                        addressJson["mac"] = "";
                        addressJson["internal"] = (ifa->ifa_flags & IFF_LOOPBACK) != 0;
                        addressJson["scopeid"] = ipv6Address->sin6_scope_id;
                        addressJson["cidr"] = ""; // You can calculate CIDR if needed
                        addressesJson.push_back(addressJson);
                    }
                }

                networkInterfacesJson[ifa->ifa_name] = addressesJson;
            }

            freeifaddrs(ifAddrStruct);
        }
#endif

        return networkInterfacesJson;
    }

    static nlohmann::json cpus()
    {
        nlohmann::json cpusArray;

#ifdef _WIN32
        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);
        DWORD numCores = sysInfo.dwNumberOfProcessors;

        for (DWORD core = 0; core < numCores; core++)
        {
            nlohmann::json cpuInfo;
            cpuInfo["model"] = "Unknown";
            cpuInfo["speed"] = 0;

            FILETIME idleTime, kernelTime, userTime;
            if (GetSystemTimes(&idleTime, &kernelTime, &userTime))
            {
                ULARGE_INTEGER idleTimeValue, kernelTimeValue, userTimeValue;
                idleTimeValue.LowPart = idleTime.dwLowDateTime;
                idleTimeValue.HighPart = idleTime.dwHighDateTime;
                kernelTimeValue.LowPart = kernelTime.dwLowDateTime;
                kernelTimeValue.HighPart = kernelTime.dwHighDateTime;
                userTimeValue.LowPart = userTime.dwLowDateTime;
                userTimeValue.HighPart = userTime.dwHighDateTime;

                ULONGLONG totalTime = kernelTimeValue.QuadPart + userTimeValue.QuadPart;
                ULONGLONG idleTotalTime = idleTimeValue.QuadPart;

                cpuInfo["times"]["user"] = static_cast<double>(userTimeValue.QuadPart) / totalTime * 1000.0;
                cpuInfo["times"]["nice"] = 0; // Windows doesn't have nice values
                cpuInfo["times"]["sys"] = static_cast<double>(kernelTimeValue.QuadPart) / totalTime * 1000.0;
                cpuInfo["times"]["idle"] = static_cast<double>(idleTotalTime) / totalTime * 1000.0;
                cpuInfo["times"]["irq"] = 0; // Windows doesn't have IRQ values
            }

            cpusArray.push_back(cpuInfo);
        }
#else
        std::ifstream cpuInfoFile("/proc/cpuinfo");
        std::string line;
        nlohmann::json cpuInfo;

        while (std::getline(cpuInfoFile, line))
        {
            if (line.empty())
            {
                cpusArray.push_back(cpuInfo);
                cpuInfo = nlohmann::json();
            }
            else
            {
                size_t colonPos = line.find(':');
                if (colonPos != std::string::npos)
                {
                    std::string key = line.substr(0, colonPos);
                    std::string value = line.substr(colonPos + 1);
                    key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());
                    value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());
                    cpuInfo[key] = value;
                }
            }
        }
#endif

        return cpusArray;
    }
};

#ifdef _WIN32
std::string __os__::EOL = "\n";
#else
std::string __os__::EOL = "\r\n";
#endif

#ifdef _WIN32
std::string __os__::devNull = "\\\\.\\nul";
#else
std::string __os__::devNull = "/dev/null";
#endif

nlohmann::json constants = {};