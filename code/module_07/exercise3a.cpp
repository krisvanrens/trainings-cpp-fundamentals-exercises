// C++ Fundamentals: exercise mod07-ex3a

#include <iostream>
#include <mutex>
#include <string>
#include <thread>

// Exercise: Make the `Mutex` abstraction type-generic.
//
// Difficulty rating for this exercise: ⭐⭐⭐

namespace detail {

/// Safe value ownership type.
struct MutexData {
  unsigned int value{};
  std::mutex   mut;
};

} // namespace detail

/// Scoped-constrained safe value accessor.
class MutexGuard {
private:
  detail::MutexData& data_;

  MutexGuard(detail::MutexData& data)
    : data_{data} {
    data_.mut.lock();
  }

  friend class Mutex; // Allow `Mutex` to construct.

public:
  ~MutexGuard() {
    data_.mut.unlock();
  }

  const unsigned int& value() const {
    return data_.value;
  }

  unsigned int& value() {
    return data_.value;
  }
};

/// Safe value abstraction.
class Mutex {
private:
  detail::MutexData data_;

public:
  MutexGuard lock() {
    return MutexGuard(data_);
  }
};

int main() {
  Mutex<unsigned int> c;

  std::thread t1{[&] {
    for (unsigned int i = 0; i < 500'000; i++) {
      auto g = c.lock(); // Create a guard that locks this scope.
      g.value()++;       // Increment the value via the guard.

      std::this_thread::yield(); // Introduce concurrency delays.
    }
  }};

  std::thread t2{[&] {
    for (unsigned int i = 0; i < 500'000; i++) {
      c.lock().value()++; // Direct locking + modification.

      std::this_thread::yield(); // Introduce concurrency delays.
    }
  }};

  t1.join();
  t2.join();

  std::cout << c.lock().value() << '\n'; // One million...for sure!

  Mutex<int>   x1; // Signed integer.
  Mutex<float> x2; // Single-precision floating-point.

  struct Id {
    unsigned long id{};
    std::string   tag;
  };

  Mutex<Id> x3; // Custom type.
  x3.lock().value().tag = "Covfefe";
}

// Compiler Explorer: https://www.godbolt.org/z/adK69sYEz
