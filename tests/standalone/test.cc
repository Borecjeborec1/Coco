#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <thread>
#include <chrono>
#include "./lib/nlohmann-json.hh" // Include the nlohmann JSON library

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#endif

class __child_process__
{
public:
  // Custom type to represent a spawned process
  class ChildProcess
  {
  public:
    std::function<void(const std::string &)> stdoutCallback;
    std::function<void(int)> closeCallback;
    std::function<void(int)> exitCallback;

    ChildProcess() = default;

    // Function to send data to the process's stdin (not implemented here)
    void stdin(const std::string &data)
    {
      // Not implemented
    }

    // Function to kill the process (not implemented here)
    void kill()
    {
      // Not implemented
    }

    // Function to wait for the process to exit (blocking)
    int wait()
    {
#ifdef _WIN32
      DWORD exitCode;
      if (GetExitCodeProcess(processHandle, &exitCode) && exitCode == STILL_ACTIVE)
      {
        WaitForSingleObject(processHandle, INFINITE);
        GetExitCodeProcess(processHandle, &exitCode);
        return static_cast<int>(exitCode);
      }
      else
      {
        return static_cast<int>(exitCode);
      }
#else
      int status;
      pid_t pid = waitpid(processID, &status, 0);
      if (pid != -1)
      {
        if (WIFEXITED(status))
        {
          return WEXITSTATUS(status);
        }
        else
        {
          return -1; // Error
        }
      }
      else
      {
        return -1; // Error
      }
#endif
    }

  private:
#ifdef _WIN32
    HANDLE processHandle;
#else
    pid_t processID;
#endif

    // Private constructor to create a ChildProcess instance
    ChildProcess(
#ifdef _WIN32
        HANDLE handle
#else
        pid_t pid
#endif
        )
        : processHandle(handle),
          processID(pid)
    {
    }

    // Function to read and process the process's output (stdout)
    void readProcessOutput()
    {
      char buffer[1024];
#ifdef _WIN32
      DWORD bytesRead;
#else
      int bytesRead;
#endif
      while (true)
      {
#ifdef _WIN32
        if (!ReadFile(pipeRead, buffer, sizeof(buffer), &bytesRead, nullptr) || bytesRead == 0)
        {
          break;
        }
#else
        bytesRead = read(pipeRead, buffer, sizeof(buffer));
        if (bytesRead <= 0)
        {
          break;
        }
#endif

        // Process the data and call the stdout callback
        std::string data(buffer, bytesRead);
        if (stdoutCallback)
        {
          stdoutCallback(data);
        }
      }

// Close the pipe and call the close and exit callbacks
#ifdef _WIN32
      CloseHandle(pipeRead);
#else
      close(pipeRead);
#endif
      if (closeCallback)
      {
        closeCallback(0);
      }
      if (exitCallback)
      {
        int exitCode = wait();
        exitCallback(exitCode);
      }
    }

    friend ChildProcess spawn(
        const std::string &command,
        const std::vector<std::string> &args,
        const std::function<void(const std::string &)> &stdoutCallback,
        const std::function<void(int)> &closeCallback,
        const std::function<void(int)> &exitCallback);
  };

  // Spawn a new process and return a ChildProcess instance
  static ChildProcess spawn(
      const std::string &command,
      const std::vector<std::string> &args = {},
      const std::function<void(const std::string &)> &stdoutCallback = nullptr,
      const std::function<void(int)> &closeCallback = nullptr,
      const std::function<void(int)> &exitCallback = nullptr)
  {
#ifdef _WIN32
    HANDLE pipeWrite = nullptr;
    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = nullptr;
    if (!CreatePipe(&pipeRead, &pipeWrite, &saAttr, 0))
    {
      // Error creating pipe
      return ChildProcess();
    }
#else
    int pipeFDs[2];
    if (pipe(pipeFDs) == -1)
    {
      // Error creating pipe
      return ChildProcess();
    }
    int pipeRead = pipeFDs[0];
    int pipeWrite = pipeFDs[1];
#endif

#ifdef _WIN32
    // Prepare command line for Windows
    std::string commandLine = command;
    for (const std::string &arg : args)
    {
      commandLine += " " + arg;
    }

    // Create a new process using CreateProcess
    PROCESS_INFORMATION piProcInfo;
    STARTUPINFO siStartInfo;

    ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
    siStartInfo.cb = sizeof(STARTUPINFO);
    siStartInfo.hStdError = pipeWrite;
    siStartInfo.hStdOutput = pipeWrite;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

    if (!CreateProcess(
            nullptr,         // No module name (use command line)
            &commandLine[0], // Command line
            nullptr,         // Process handle not inheritable
            nullptr,         // Thread handle not inheritable
            TRUE,            // Set handle inheritance to TRUE
            0,               // No creation flags
            nullptr,         // Use parent's environment block
            nullptr,         // Use parent's starting directory
            &siStartInfo,    // Pointer to STARTUPINFO structure
            &piProcInfo      // Pointer to PROCESS_INFORMATION structure
            ))
    {
      // Error creating process
      CloseHandle(pipeWrite);
      return ChildProcess();
    }

    // Close the handle to the process, we don't need it
    CloseHandle(piProcInfo.hProcess);
    CloseHandle(piProcInfo.hThread);
#else
    // Prepare command line for POSIX
    std::vector<char *> argv;
    argv.push_back(const_cast<char *>(command.c_str()));
    for (const std::string &arg : args)
    {
      argv.push_back(const_cast<char *>(arg.c_str()));
    }
    argv.push_back(nullptr);

    // Create a new process using fork
    pid_t pid = fork();
    if (pid == -1)
    {
      // Error forking process
      close(pipeWrite);
      return ChildProcess();
    }

    if (pid == 0)
    {
      // Child process
      close(pipeRead);
      dup2(pipeWrite, STDOUT_FILENO);
      dup2(pipeWrite, STDERR_FILENO);
      execvp(command.c_str(), argv.data());
      exit(1); // Exec failed
    }
    else
    {
      // Parent process
      close(pipeWrite);
    }
#endif

    // Create a ChildProcess instance to manage the process
    ChildProcess childProcess(
#ifdef _WIN32
        piProcInfo.hProcess
#else
        pid
#endif
    );

    // Start a thread to read and process the process's output (stdout)
    std::thread outputThread([&]()
                             { childProcess.readProcessOutput(); });
    outputThread.detach();

    // Set the stdout, close, and exit callbacks
    childProcess.stdoutCallback = stdoutCallback;
    childProcess.closeCallback = closeCallback;
    childProcess.exitCallback = exitCallback;

    return childProcess;
  }

private:
#ifdef _WIN32
  static HANDLE pipeRead;
#endif
};

#ifdef _WIN32
HANDLE __child_process__::pipeRead = nullptr;
#endif

int main()
{
  // Test the spawn() function
  __child_process__::ChildProcess child = __child_process__::spawn(
      "ls", {"-lh", "/usr"}, [](const std::string &data)
      { std::cout << "stdout: " << data; },
      [](int)
      {
        std::cout << "child process close all stdio\n";
      },
      [](int exitCode)
      {
        std::cout << "child process exited with code " << exitCode << "\n";
      });

  // Wait for the process to exit
  int exitCode = child.wait();
  std::cout << "Child process wait result: " << exitCode << "\n";

  return 0;
}
