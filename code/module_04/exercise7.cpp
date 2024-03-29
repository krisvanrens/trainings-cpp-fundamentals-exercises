// C++ Fundamentals: exercise mod04-ex7

#include <iostream>
#include <mutex>
#include <thread>

// Exercise: Implement the `Mutex` abstraction. Read the instructions in the slides.

/// Safe value abstraction.
class Mutex {
  // ...
};

int main() {
  Mutex c;

  std::thread t1{[&] {
    for (unsigned int i = 0; i < 500'000; i++) {
      c.lock().value()++;

      std::this_thread::yield(); // Introduce concurrency delays.
    }
  }};

  std::thread t2{[&] {
    for (unsigned int i = 0; i < 500'000; i++) {
      c.lock().value()++;

      std::this_thread::yield(); // Introduce concurrency delays.
    }
  }};

  t1.join();
  t2.join();

  std::cout << c.lock().value() << '\n'; // One million...for sure!
}

// Compiler Explorer: https://www.godbolt.org/z/hcc3ovWsj
