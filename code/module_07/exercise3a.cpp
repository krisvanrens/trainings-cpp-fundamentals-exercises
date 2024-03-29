// C++ Fundamentals: exercise mod07-ex3a

#include <mutex>
#include <iostream>
#include <string>
#include <thread>

// Exercise: Make the `safe_value` abstraction type-generic.

namespace detail {

/// Safe value ownership type.
struct value_data {
  unsigned int value{};
  std::mutex   mut;
};

} // namspace detail

/// Scoped-constrained safe value accessor.
class value_guard {
private:
  detail::value_data &data_;

  /// NOTE: Private constructor to prevent construction "in the wild".
  value_guard(detail::value_data &data)
    : data_{data} {
    // Lock value access as long as the guard lives.
    data_.mut.lock();
  }

  friend class safe_value; // Allow `safe_value` to construct.

public:
  ~value_guard() {
    // Unlock value access, guarded lifetime ends here.
    data_.mut.unlock();
  }

  /// Immutable value accessor.
  const unsigned int &value() const {
    return data_.value;
  }

  /// Mutable value accessor.
  unsigned int &value() {
    return data_.value;
  }
};

/// Safe value abstraction.
class safe_value {
private:
  detail::value_data data_;

public:
  value_guard lock() {
    return value_guard(data_);
  }
};

int main() {
  safe_value<unsigned int> c;

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

  safe_value<int>   x1; // Signed integer.
  safe_value<float> x2; // Single-precision floating-point.

  struct Id {
    unsigned long id{};
    std::string   tag;
  };

  safe_value<Id> x3; // Custom type.
  x3.lock().value().tag = "Covfefe";
}

// Compiler Explorer: https://www.godbolt.org/z/c9hzxjxeY
