// C++ Fundamentals: exercise mod07-ex3b

#include <mutex>
#include <iostream>
#include <string>
#include <thread>

// Exercise: Add forwarding constructors and CTAD.

namespace detail {

/// Safe value ownership type.
template<typename T>
struct value_data {
  T          value{};
  std::mutex mut;
};

} // namspace detail

// Forward-declataration used for the friend class specification.
template<typename T>
class safe_value;

/// Scoped-constrained safe value accessor.
template<typename T>
class value_guard {
private:
  detail::value_data<T> &data_;

  /// NOTE: Private constructor to prevent construction "in the wild".
  value_guard(detail::value_data<T> &data)
    : data_{data} {
    // Lock value access as long as the guard lives.
    data_.mut.lock();
  }

  friend class safe_value<T>; // Allow `safe_value` to construct.

public:
  ~value_guard() {
    // Unlock value access, guarded lifetime ends here.
    data_.mut.unlock();
  }

  /// Immutable value accessor.
  const T &value() const {
    return data_.value;
  }

  /// Mutable value accessor.
  T &value() {
    return data_.value;
  }
};

/// Safe value abstraction.
template<typename T>
class safe_value {
private:
  detail::value_data<T> data_;

public:
  value_guard<T> lock() {
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

  safe_value x0{42u};   // Unsigned integer.
  safe_value x1{42};    // Signed integer.
  safe_value x2{3.14f}; // Single-precision floating-point.

  struct Id {
    unsigned long id{};
    std::string   tag;
  };

  safe_value     x3{Id{.id = 123, .tag = "Radio"}}; // Move construction.
  safe_value<Id> x4;                                // Default construction.

  x4.lock().value().tag = "Covfefe";
}

// Compiler Explorer: https://www.godbolt.org/z/7rdY8GY4G
