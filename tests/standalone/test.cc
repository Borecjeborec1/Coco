#include <iostream>
#include <functional>
#include <map>
#include <thread>
#include <chrono>
#include <atomic>

class Timer {
public:
  static int setTimeout(std::function<void()> func, int delay) {
    int timerId = nextTimerId++;
    std::thread([func, delay, timerId]() {
      std::this_thread::sleep_for(std::chrono::milliseconds(delay));
      if (timers.find(timerId) != timers.end()) {
        func();
        timers.erase(timerId);
      }
      checkAndExit();
    }).detach();
    timers[timerId] = true;
    return timerId;
  }

  static int setImmediate(std::function<void()> func) {
    int timerId = nextTimerId++;
    std::thread([func, timerId]() {
      if (timers.find(timerId) != timers.end()) {
        func();
        timers.erase(timerId);
      }
      checkAndExit();
    }).detach();
    timers[timerId] = true;
    return timerId;
  }

  static int setInterval(std::function<void()> func, int interval) {
    int timerId = nextTimerId++;
    std::thread([func, interval, timerId]() {
      while (timers.find(timerId) != timers.end()) {
        func();
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
      }
      checkAndExit();
    }).detach();
    timers[timerId] = true;
    return timerId;
  }

  static void clearTimeout(int timerId) {
    timers.erase(timerId);
    checkAndExit();
  }

  static void clearImmediate(int timerId) {
    timers.erase(timerId);
    checkAndExit();
  }

  static void clearInterval(int timerId) {
    timers.erase(timerId);
    checkAndExit();
  }

  static std::atomic<bool> shouldExit;

private:
  static int nextTimerId;
  static std::map<int, bool> timers;
  static void checkAndExit() {
    if (timers.empty()) {
      shouldExit = true;
    }
  }
};

int Timer::nextTimerId = 1;
std::map<int, bool> Timer::timers;
std::atomic<bool> Timer::shouldExit(false);

int main() {
  int timeoutId = Timer::setTimeout(
      []() { std::cout << "setTimeout executed." << std::endl; }, 2000);

  int immediateId = Timer::setImmediate(
      []() { std::cout << "setImmediate executed." << std::endl; });

  int intervalId = Timer::setInterval([]() {
    int count = 0;
    std::cout << "setInterval executed (" << count << ")." << std::endl;
    count++;
    if (count >= 5) {
    }
  }, 1000);

  std::cout << "test";
  while (!Timer::shouldExit) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}
