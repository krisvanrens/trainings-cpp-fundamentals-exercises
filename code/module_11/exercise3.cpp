// C++ Fundamentals: exercise mod11-ex3

#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <utility>

// Exercise: Extend custom type Mutex to support the following value access operations:
//
//   A) Dereference to get the wrapped value: `*x` as an alternative to `x.value()`.
//   B) Pointer-dereference to get directory to wrapped value member:
//       `x->member` as an alternative to `x.value().member`.
//

namespace detail {

/// Safe value ownership type.
template<typename T>
struct MutexData {
  T          value{};
  std::mutex mut;

  MutexData() = default;

  explicit MutexData(T&& v)
    : value{std::forward<T>(v)} {
  }
};

} // namespace detail

// Forward-declataration used for the friend class specification.
template<typename T>
class Mutex;

/// Scoped-constrained safe value accessor.
template<typename T>
class MutexGuard {
private:
  detail::MutexData<T>& data_;

  MutexGuard(detail::MutexData<T>& data)
    : data_{data} {
    data_.mut.lock();
  }

  friend class Mutex<T>; // Allow `Mutex` to construct.

public:
  ~MutexGuard() {
    data_.mut.unlock();
  }

  const T& value() const {
    return data_.value;
  }

  T& value() {
    return data_.value;
  }
};

/// Safe value abstraction.
template<typename T>
class Mutex {
private:
  detail::MutexData<T> data_;

public:
  Mutex() = default;

  explicit Mutex(T&& value)
    : data_{std::forward<T>(value)} {
  }

  MutexGuard<T> lock() {
    return MutexGuard(data_);
  }
};

// Template deduction guides, not needed for C++20:

// template<typename T>
// MutexGuard(T) -> MutexGuard<T>;

// template<typename T>
// Mutex(T) -> Mutex<T>;

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
  std::cout << *c.lock() << '\n';        // One million...for sure!

  Mutex x0{42u};   // Unsigned integer.
  Mutex x1{42};    // Signed integer.
  Mutex x2{3.14f}; // Single-precision floating-point.

  struct Id {
    unsigned long id{};
    std::string   tag;
  };

  Mutex     x3{Id{.id = 123, .tag = "Radio"}}; // Move construction.
  Mutex<Id> x4;                                // Default construction.

  std::cout << x3.lock().value().tag << '\n';
  std::cout << (*x3.lock()).tag << '\n';
  std::cout << x3.lock()->tag << '\n';

  x4.lock().value().tag = "Covfefe";
  (*x4.lock()).tag      = "Covfefe";
  x4.lock()->tag        = "Covfefe";
}

// Compiler Explorer: https://www.godbolt.org/z/hvesKnTf4
